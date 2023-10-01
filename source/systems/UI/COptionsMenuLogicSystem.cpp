#include "../../include/systems/UI/COptionsMenuLogicSystem.h"
#include "../../include/Components.h"
#include "../../include/Utilities.h"


using namespace TDEngine2;


namespace Game
{
	COptionsMenuLogicSystem::COptionsMenuLogicSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE COptionsMenuLogicSystem::Init(const TOptionsMenuLogicSystemParams& params)
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

	void COptionsMenuLogicSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<Game::COptionsMenuPanel>();
	}


	static void ProcessOptionsMenuInput(IWorld* pWorld, COptionsMenuPanel* pMenuPanel, TPtr<IEventManager> pEventManager, TPtr<IGameModesManager> pGameModesManager)
	{
		/// \note Back button
		if (ProcessButtonOnClick(pWorld, pMenuPanel->mBackButtonEntityId.Get(), [pEventManager, pGameModesManager]
		{
			pGameModesManager->PopMode();
		}))
		{
			return;
		}
	}


	void COptionsMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<COptionsMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			ProcessOptionsMenuInput(pWorld, panels[i], mpEventManager, mpGameModesManager);
		}
	}


	TDE2_API ISystem* CreateOptionsMenuLogicSystem(const TOptionsMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, COptionsMenuLogicSystem, result, params);
	}
}