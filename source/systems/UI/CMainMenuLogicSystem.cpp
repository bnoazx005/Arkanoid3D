#include "../../include/systems/UI/CMainMenuLogicSystem.h"


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

	void CMainMenuLogicSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& panels = std::get<std::vector<CMainMenuPanel*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{

		}
	}


	TDE2_API ISystem* CreateMainMenuLogicSystem(const TMainMenuLogicSystemParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CMainMenuLogicSystem, result, params);
	}
}