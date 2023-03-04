#include "../include/GameModes.h"
#include "../include/components/CGameInfo.h"
#include "../include/Components.h"
#include "../include/Utilities.h"


using namespace TDEngine2;


namespace Game
{
	CCommonGameMode::CCommonGameMode(const std::string& name):
		CBaseGameMode(name)
	{
	}

	E_RESULT_CODE CCommonGameMode::SpawnModeWindow(const std::string& prefabId, bool useMainScene)
	{
		auto pSceneManager = mParams.mpSceneManager;
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return RC_FAIL;
		}

		mWindowOwnerSceneId = useMainScene ? MainScene : pGameInfo->mCurrLoadedGameId;

		if (auto sceneResult = pSceneManager->GetScene(mWindowOwnerSceneId))
		{
			if (auto pScene = sceneResult.Get())
			{
				mWindowHierarchyRootEntityId = pScene->Spawn(prefabId)->GetId();
				return RC_OK;
			}

			return sceneResult.GetError();
		}

		return RC_FAIL;
	}

	TDEngine2::E_RESULT_CODE CCommonGameMode::RemoveModeWindow()
	{
		if (TSceneId::Invalid == mWindowOwnerSceneId || TEntityId::Invalid == mWindowHierarchyRootEntityId)
		{
			return RC_OK;
		}

		if (auto sceneResult = mParams.mpSceneManager->GetScene(mWindowOwnerSceneId))
		{
			if (auto pScene = sceneResult.Get())
			{
				E_RESULT_CODE result = pScene->RemoveEntity(mWindowHierarchyRootEntityId);
				TDE2_ASSERT(RC_OK == result);

				mWindowHierarchyRootEntityId = TEntityId::Invalid;
				mWindowOwnerSceneId = TSceneId::Invalid;

				return result;
			}

			return sceneResult.GetError();
		}

		return RC_FAIL;
	}


	/*!
		\brief CPauseGameMode's definition
	*/

	CPauseGameMode::CPauseGameMode() :
		CCommonGameMode("PauseMode")
	{
	}

	void CPauseGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Subscribe(TDEngine2::TResumeToGameEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		/// \todo Replace hardcoded value later
		SpawnModeWindow("PauseWindowUI"); /// \note Spawn a pause window's prefab		

		if (auto pWorld = mParams.mpSceneManager->GetWorld())
		{
			pWorld->SetTimeScaleFactor(0.0f);
		}
	}

	void CPauseGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Unsubscribe(TDEngine2::TResumeToGameEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		if (auto pWorld = mParams.mpSceneManager->GetWorld())
		{
			pWorld->SetTimeScaleFactor(1.0f);
		}

		/// \note Remove the pause window
		RemoveModeWindow();
	}

	void CPauseGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->PopMode();
		}		
	}

	E_RESULT_CODE CPauseGameMode::OnEvent(const TBaseEvent* pEvent)
	{
		mpOwner->PopMode();
		return RC_OK;
	}

	TEventListenerId CPauseGameMode::GetListenerId() const
	{
		return static_cast<TEventListenerId>(TDE2_TYPE_ID(CPauseGameMode));
	}


	TDE2_API IGameMode* CreatePauseGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CPauseGameMode, CPauseGameMode, result, pOwner))
		{
			pMode->mParams = params;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CCoreGameMode's definition
	*/

	CCoreGameMode::CCoreGameMode() :
		CCommonGameMode("CoreMode")
	{
	}

	void CCoreGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Subscribe(TDEngine2::TLivesChangedEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		result = mParams.mpEventManager->Subscribe(TDEngine2::TRestartLevelEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		/// \note Load player's paddle and main UI
		/// \todo Replace hardcoded path
		mParams.mpSceneManager->LoadSceneAsync("Resources/Scenes/PlayerScene.scene", [this](const TResult<TSceneId>& sceneId)
		{
			mPlayerSceneId = sceneId.Get();

			auto&& pEventManager = mParams.mpEventManager;
			auto pWorld = mParams.mpSceneManager->GetWorld();

			if (CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
			{
				{
					TScoreChangedEvent scoreChangedEvent;
					scoreChangedEvent.mNewPlayerScore = pGameInfo->mPlayerScore;

					pEventManager->Notify(&scoreChangedEvent);
				}

				{
					TLivesChangedEvent livesChangedEvent;
					livesChangedEvent.mPlayerLives = pGameInfo->mPlayerLives;

					pEventManager->Notify(&livesChangedEvent);
				}
			}
		});
	}

	void CCoreGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Unsubscribe(TDEngine2::TLivesChangedEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		result = mParams.mpEventManager->Unsubscribe(TDEngine2::TRestartLevelEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		result = mParams.mpSceneManager->UnloadScene(mPlayerSceneId);
		TDE2_ASSERT(RC_OK == result);
	}

	void CCoreGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->PushMode(TPtr<IGameMode>(CreatePauseGameMode(mpOwner, mParams, result)));
		}
	}
	
	E_RESULT_CODE CCoreGameMode::OnEvent(const TBaseEvent* pEvent)
	{
		if (const TLivesChangedEvent* pLivesChangedEvent = dynamic_cast<const TLivesChangedEvent*>(pEvent))
		{
			E_RESULT_CODE result = RC_OK;

			if (pLivesChangedEvent->mPlayerLives <= 0)
			{
				mpOwner->SwitchMode(TPtr<IGameMode>(CreateLevelFinishedGameMode(mpOwner, mParams, result))); /// \todo Add defeat/victory flag passage
			}
		}
		
		if (const TRestartLevelEvent* pRestartLevelEvent = dynamic_cast<const TRestartLevelEvent*>(pEvent))
		{
			mpOwner->PopMode(); // Remove pause game mode

			LoadGameLevel(
				mParams.mpSceneManager, 
				mParams.mpResourceManager, 
				mParams.mpEventManager, 
				MakeScopedFromRawPtr<IGameModesManager>(mpOwner), 
				GetCurrLevelIndex(mParams.mpSceneManager, mParams.mpResourceManager).Get());
		}

		return RC_OK;
	}

	TEventListenerId CCoreGameMode::GetListenerId() const
	{
		return static_cast<TEventListenerId>(TDE2_TYPE_ID(CCoreGameMode));
	}


	TDE2_API IGameMode* CreateCoreGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CCoreGameMode, CCoreGameMode, result, pOwner))
		{
			pMode->mParams = params;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CLevelFinishedGameMode's definition
	*/

	CLevelFinishedGameMode::CLevelFinishedGameMode() :
		CCommonGameMode("LevelFinishedMode")
	{
	}

	void CLevelFinishedGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Subscribe(TDEngine2::TRestartLevelEvent::GetTypeId(), this);

		/// \todo Replace hardcoded value later
		SpawnModeWindow("GameOverWindowUI"); /// \note Spawn a pause window's prefab
	}

	void CLevelFinishedGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Unsubscribe(TDEngine2::TRestartLevelEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);

		/// \note Remove the pause window
		RemoveModeWindow();
	}

	void CLevelFinishedGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;
	}

	E_RESULT_CODE CLevelFinishedGameMode::OnEvent(const TBaseEvent* pEvent)
	{
		RemoveModeWindow();

		TLoadGameLevelEvent loadGameLevelEvent;
		loadGameLevelEvent.mLevelIndex = 1;

		mParams.mpEventManager->Notify(&loadGameLevelEvent);
		
		return RC_OK;
	}

	TEventListenerId CLevelFinishedGameMode::GetListenerId() const
	{
		return static_cast<TEventListenerId>(TDE2_TYPE_ID(CLevelFinishedGameMode));
	}


	TDE2_API IGameMode* CreateLevelFinishedGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CLevelFinishedGameMode, CLevelFinishedGameMode, result, pOwner))
		{
			pMode->mParams = params;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CMainMenuGameMode's definition
	*/

	CMainMenuGameMode::CMainMenuGameMode() :
		CCommonGameMode("MainMenuMode")
	{
	}

	void CMainMenuGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		if (mIsActive)
		{
			return;
		}

		/// \todo Replace hardcoded value later
		SpawnModeWindow("MainMenuWindowUI", true); /// \note Spawn a MainMenu window's prefab		
		mIsActive = true;
	}

	void CMainMenuGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		/// \note Remove the MainMenu window
		RemoveModeWindow();
		mIsActive = false;
	}

	void CMainMenuGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		/*if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateCoreGameMode(mpOwner, mParams, result)));
		}*/

	}


	TDE2_API IGameMode* CreateMainMenuGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CMainMenuGameMode, CMainMenuGameMode, result, pOwner))
		{
			pMode->mParams = params;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CLoadingGameMode's definition
	*/

	CLoadingGameMode::CLoadingGameMode() :
		CCommonGameMode("LoadingMode")
	{
	}

	void CLoadingGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		/// \todo Replace hardcoded value later
		SpawnModeWindow("LoadingWindow", true); /// \note Spawn a Loading window's prefab		
	}

	void CLoadingGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		/// \note Remove the Loading window
		RemoveModeWindow();
	}

	void CLoadingGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		/*if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateCoreGameMode(mpOwner, mParams, result)));
		}*/

	}


	TDE2_API IGameMode* CreateLoadingGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CLoadingGameMode, CLoadingGameMode, result, pOwner))
		{
			pMode->mParams = params;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}
}