#include "../include/GameModes.h"
#include "../include/components/CGameInfo.h"
#include "../include/Components.h"


using namespace TDEngine2;


namespace Game
{
	CCommonGameMode::CCommonGameMode(const std::string& name):
		CBaseGameMode(name)
	{
	}

	E_RESULT_CODE CCommonGameMode::SpawnModeWindow(const std::string& prefabId)
	{
		auto pSceneManager = mParams.mpSceneManager;
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return RC_FAIL;
		}

		mWindowOwnerSceneId = pGameInfo->mCurrLoadedGameId;

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
		if (auto sceneResult = mParams.mpSceneManager->GetScene(mWindowOwnerSceneId))
		{
			if (auto pScene = sceneResult.Get())
			{
				E_RESULT_CODE result = pScene->RemoveEntity(mWindowHierarchyRootEntityId);
				TDE2_ASSERT(RC_OK == result);

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

		/// \todo Replace hardcoded value later
		SpawnModeWindow("PauseWindowUI"); /// \note Spawn a pause window's prefab		
	}

	void CPauseGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		/// \note Remove the pause window
		RemoveModeWindow();
	}

	void CPauseGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateCoreGameMode(mpOwner, mParams, result)));
		}
		
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
	}

	void CCoreGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		E_RESULT_CODE result = mParams.mpEventManager->Unsubscribe(TDEngine2::TLivesChangedEvent::GetTypeId(), this);
		TDE2_ASSERT(RC_OK == result);
	}

	void CCoreGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mParams.mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreatePauseGameMode(mpOwner, mParams, result)));
		}
	}
	
	E_RESULT_CODE CCoreGameMode::OnEvent(const TBaseEvent* pEvent)
	{
		const TLivesChangedEvent* pLivesChangedEvent = dynamic_cast<const TLivesChangedEvent*>(pEvent);
		if (!pLivesChangedEvent)
		{
			return RC_OK;
		}

		E_RESULT_CODE result = RC_OK;

		if (pLivesChangedEvent->mPlayerLives <= 0)
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateLevelFinishedGameMode(mpOwner, mParams, result)));
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

		/// \todo Replace hardcoded value later
		SpawnModeWindow("GameOverWindowUI"); /// \note Spawn a pause window's prefab
	}

	void CLevelFinishedGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		/// \note Remove the pause window
		RemoveModeWindow();
	}

	void CLevelFinishedGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;
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
}