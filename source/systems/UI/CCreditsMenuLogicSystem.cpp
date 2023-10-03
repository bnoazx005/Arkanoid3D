#include "../../include/systems/UI/CCreditsMenuLogicSystem.h"
#include "../../include/Components.h"
#include "../../include/Utilities.h"


using namespace TDEngine2;


namespace Game
{
	CCreditsMenuLogicSystem::CCreditsMenuLogicSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CCreditsMenuLogicSystem::Init(const TCreditsMenuLogicSystemParams& params)
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

	void CCreditsMenuLogicSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<Game::CCreditsMenuPanel>();
	}


	static void ProcessCreditsMenuInput(IWorld* pWorld, CCreditsMenuPanel* pMenuPanel, TPtr<IEventManager> pEventManager, TPtr<IGameModesManager> pGameModesManager)
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


	void CCreditsMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<CCreditsMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			ProcessCreditsMenuInput(pWorld, panels[i], mpEventManager, mpGameModesManager);
		}
	}


	TDE2_API ISystem* CreateCreditsMenuLogicSystem(const TCreditsMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CCreditsMenuLogicSystem, result, params);
	}
}