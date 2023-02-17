#include "../../include/systems/UI/CMainMenuLogicSystem.h"
#include "../../include/Components.h"


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


	static void ProcessMainMenuInput(IWorld* pWorld, CMainMenuPanel* pMenuPanel, TPtr<IEventManager> pEventManager)
	{
		if (CEntity* pQuitButtonEntity = pWorld->FindEntity(pMenuPanel->mQuitButtonEntityId))
		{
			CInputReceiver* pQuitButton = pQuitButtonEntity->GetComponent<CInputReceiver>();
			if (!pQuitButton->mCurrState && pQuitButton->mPrevState) /// \note Process logic on release of the button
			{
				TExitGameEvent exitGameEvent;
				pEventManager->Notify(&exitGameEvent);
			}
		}
	}


	void CMainMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<CMainMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			ProcessMainMenuInput(pWorld, panels[i], mpEventManager);
		}
	}


	TDE2_API ISystem* CreateMainMenuLogicSystem(const TMainMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CMainMenuLogicSystem, result, params);
	}
}