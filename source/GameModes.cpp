#include "../include/GameModes.h"
#include "../include/components/CGameInfo.h"


using namespace TDEngine2;


namespace Game
{
	/*!
		\brief CPauseGameMode's definition
	*/

	CPauseGameMode::CPauseGameMode() :
		CBaseGameMode("PauseMode")
	{
	}

	void CPauseGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));

		/// \note Spawn a pause window's prefab
		TPtr<IWorld> pWorld = mpSceneManager->GetWorld();

		CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return;
		}

		mSceneId = pGameInfo->mCurrLoadedGameId;

		if (auto sceneResult = mpSceneManager->GetScene(mSceneId))
		{
			if (auto pScene = sceneResult.Get())
			{
				mPauseWindowEntityId = pScene->Spawn("PauseWindowUI")->GetId(); /// \note Replace hardcoded identifier
			}
		}
	}

	void CPauseGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));

		/// \note Remove the pause window
		if (auto sceneResult = mpSceneManager->GetScene(mSceneId))
		{
			if (auto pScene = sceneResult.Get())
			{
				E_RESULT_CODE result = pScene->RemoveEntity(mPauseWindowEntityId);
				TDE2_ASSERT(RC_OK == result);
			}
		}
	}

	void CPauseGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateCoreGameMode(mpOwner, { DynamicPtrCast<IInputContext>(mpInputContext), mpSceneManager }, result)));
		}
		
	}


	TDE2_API IGameMode* CreatePauseGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CPauseGameMode, CPauseGameMode, result, pOwner))
		{
			pMode->mpInputContext = DynamicPtrCast<IDesktopInputContext>(params.mpInputContext);
			pMode->mpSceneManager = params.mpSceneManager;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CCoreGameMode's definition
	*/

	CCoreGameMode::CCoreGameMode() :
		CBaseGameMode("CoreMode")
	{
	}

	void CCoreGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));
	}

	void CCoreGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));
	}

	void CCoreGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreatePauseGameMode(mpOwner, { DynamicPtrCast<IInputContext>(mpInputContext), mpSceneManager }, result)));
		}
	}


	TDE2_API IGameMode* CreateCoreGameMode(IGameModesManager* pOwner, const TStateInitParams& params, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CCoreGameMode, CCoreGameMode, result, pOwner))
		{
			pMode->mpInputContext = DynamicPtrCast<IDesktopInputContext>(params.mpInputContext);
			pMode->mpSceneManager = params.mpSceneManager;

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CLevelFinishedGameMode's definition
	*/

	CLevelFinishedGameMode::CLevelFinishedGameMode() :
		CBaseGameMode("LevelFinishedMode")
	{
	}

	void CLevelFinishedGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));
	}

	void CLevelFinishedGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));
	}

	void CLevelFinishedGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

	}


	TDE2_API IGameMode* CreateLevelFinishedGameMode(IGameModesManager* pOwner, TPtr<IInputContext> pInputContext, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CLevelFinishedGameMode, CLevelFinishedGameMode, result, pOwner))
		{
			pMode->mpInputContext = DynamicPtrCast<IDesktopInputContext>(pInputContext);

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}
}