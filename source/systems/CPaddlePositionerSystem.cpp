#include "../../include/systems/CPaddlePositionerSystem.h"
#include "../../include/Components.h"


using namespace TDEngine2;


namespace Game
{
	CPaddlePositionerSystem::CPaddlePositionerSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CPaddlePositionerSystem::Init(TPtr<IEventManager> pEventManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager)
		{
			return RC_INVALID_ARGS;
		}

		pEventManager->Subscribe(TGameLevelLoadedEvent::GetTypeId(), this);

		mIsInitialized = true;

		return RC_OK;
	}

	void CPaddlePositionerSystem::InjectBindings(IWorld* pWorld)
	{
		mPaddlesContext = pWorld->CreateLocalComponentsSlice<Game::CPaddle, CTransform>();
		mPositionersContext = pWorld->CreateLocalComponentsSlice<Game::CPlayerPositioner, CTransform>();
		mpWorld = pWorld;
	}

	void CPaddlePositionerSystem::Update(IWorld* pWorld, F32 dt)
	{
		if (!mIsDirty)
		{
			return;
		}

		mIsDirty = false;

		auto& transforms = std::get<std::vector<CTransform*>>(mPaddlesContext.mComponentsSlice);
		auto& positionerTransform = std::get<std::vector<CTransform*>>(mPositionersContext.mComponentsSlice);

		if (positionerTransform.empty())
		{
			return;
		}

		const TVector3 paddlePosition = positionerTransform.front()->GetPosition();

		for (USIZE i = 0; i < mPaddlesContext.mComponentsCount; i++)
		{
			transforms[i]->SetPosition(paddlePosition);
		}
	}

	E_RESULT_CODE CPaddlePositionerSystem::OnEvent(const TBaseEvent* pEvent)
	{
		mIsDirty = true;

		return RC_OK;
	}

	TEventListenerId CPaddlePositionerSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreatePaddlePositionerSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPaddlePositionerSystem, result, pEventManager);
	}
}