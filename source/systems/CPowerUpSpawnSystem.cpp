#include "../../include/systems/CPowerUpSpawnSystem.h"
#include "../../include/Components.h"


using namespace TDEngine2;


namespace Game
{
	CPowerUpSpawnSystem::CPowerUpSpawnSystem() :
		CBaseSystem(), mRandomUtility(static_cast<int>(time(nullptr)))
	{
	}

	E_RESULT_CODE CPowerUpSpawnSystem::Init(TPtr<IEventManager> pEventManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager)
		{
			return RC_INVALID_ARGS;
		}

		mpEventManager = pEventManager;

		pEventManager->Subscribe(TSpawnNewBonusEvent::GetTypeId(), this);

		mIsInitialized = true;

		return RC_OK;
	}

	void CPowerUpSpawnSystem::InjectBindings(IWorld* pWorld)
	{
		mpWorld = pWorld;
	}

	void CPowerUpSpawnSystem::Update(IWorld* pWorld, F32 dt)
	{
	}

	E_RESULT_CODE CPowerUpSpawnSystem::OnEvent(const TBaseEvent* pEvent)
	{
		
		return RC_OK;
	}

	TEventListenerId CPowerUpSpawnSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreatePowerUpSpawnSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPowerUpSpawnSystem, result, pEventManager);
	}
}