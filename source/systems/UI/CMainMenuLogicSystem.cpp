#include "../../include/systems/UI/CMainMenuLogicSystem.h"
#include "../../include/Components.h"
#include "../../include/Utilities.h"


using namespace TDEngine2;


namespace Game
{
	CMainMenuLogicSystem::CMainMenuLogicSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CMainMenuLogicSystem::Init(const TMainMenuLogicSystemParams& params)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!params.mpGameModesManager || !params.mpEventManager || !params.mpSceneManager)
		{
			return RC_INVALID_ARGS;
		}

		mpGameModesManager = params.mpGameModesManager;
		mpEventManager = params.mpEventManager;
		mpSceneManager = params.mpSceneManager;

		mIsInitialized = true;

		return RC_OK;
	}

	void CMainMenuLogicSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<Game::CMainMenuPanel>();
	}


	static void ProcessMainMenuInput(ISystem* pOwnerSystem, IWorld* pWorld, CMainMenuPanel* pMenuPanel, TPtr<IEventManager> pEventManager)
	{
		/// \note Start button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mPlayButtonEntityId.Get(), [pEventManager]
		{
			TLoadGameLevelEvent loadGameLevelEvent;
			loadGameLevelEvent.mLevelIndex = 1;

			pEventManager->Notify(&loadGameLevelEvent);
		}))
		{
			return;
		}

		/// \note Settings button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mSettingsButtonEntityId.Get(), [pOwnerSystem, pEventManager]
		{
			pOwnerSystem->AddDefferedCommand([pEventManager]
			{
				TLoadSettingsMenuEvent loadSettingsMenuEvent;
				pEventManager->Notify(&loadSettingsMenuEvent);
			});
		}))
		{
			return;
		}

		/// \note Credits button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mCreditsButtonEntityId.Get(), [pOwnerSystem, pEventManager]
		{
			pOwnerSystem->AddDefferedCommand([pEventManager]
			{
				TLoadCreditsMenuEvent loadCreditsMenuEvent;
				pEventManager->Notify(&loadCreditsMenuEvent);
			});
		}))
		{
			return;
		}

		/// \note Quit button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mQuitButtonEntityId.Get(), [pEventManager]
		{
			TExitGameEvent exitGameEvent;
			pEventManager->Notify(&exitGameEvent);
		}))
		{
			return;
		}
	}


	void CMainMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<CMainMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			ProcessMainMenuInput(this, pWorld, panels[i], mpEventManager);
		}
	}


	TDE2_API ISystem* CreateMainMenuLogicSystem(const TMainMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CMainMenuLogicSystem, result, params);
	}
}