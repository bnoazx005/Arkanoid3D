#include "../../include/systems/CStickyBallsProcessSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CBall.h"
#include "../../include/components/CPaddle.h"
#include "../../include/components/CLevelInfo.h"


using namespace TDEngine2;


namespace Game
{
	CStickyBallsProcessSystem::CStickyBallsProcessSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CStickyBallsProcessSystem::Init(TPtr<IEventManager> pEventManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager)
		{
			return RC_INVALID_ARGS;
		}

		pEventManager->Subscribe(TOn3DCollisionRegisteredEvent::GetTypeId(), this);

		mIsInitialized = true;

		return RC_OK;
	}

	void CStickyBallsProcessSystem::InjectBindings(IWorld* pWorld)
	{
		mpWorld = pWorld;
	}

	void CStickyBallsProcessSystem::Update(IWorld* pWorld, F32 dt)
	{
	}

	E_RESULT_CODE CStickyBallsProcessSystem::OnEvent(const TBaseEvent* pEvent)
	{
		const TOn3DCollisionRegisteredEvent* pCollisionEvent = dynamic_cast<const TOn3DCollisionRegisteredEvent*>(pEvent);
		if (!pCollisionEvent)
		{
			return RC_FAIL;
		}

		CEntity* pEntity0 = mpWorld->FindEntity(pCollisionEvent->mEntities[0]);
		CEntity* pEntity1 = mpWorld->FindEntity(pCollisionEvent->mEntities[1]);

		if (!pEntity0 || !pEntity1 || 
			TOn3DCollisionRegisteredEvent::E_COLLISION_EVENT_TYPE::ON_ENTER != pCollisionEvent->mType ||
			CMathUtils::Abs(Dot(ForwardVector3, pCollisionEvent->mContactNormal)) < FloatEpsilon)
		{
			return RC_OK;
		}

		CPaddle* pPaddle = GetValidPtrOrDefault(pEntity0->GetComponent<CPaddle>(), pEntity1->GetComponent<CPaddle>());
		if (!pPaddle || !pPaddle->mIsSticky)
		{
			return RC_OK;
		}

		pPaddle->mIsSticky = false;

		CBall* pBall = pEntity0->GetComponent<CBall>();

		CEntity* pBallEntity = pEntity0;
		CEntity* pPaddleEntity = pEntity1;

		if (!pBall) 
		{
			pBall = pEntity1->GetComponent<CBall>();

			pBallEntity = pEntity1;
			pPaddleEntity = pEntity0;
		}

		if (!pBall)
		{
			TDE2_UNREACHABLE();
			return RC_OK;
		}

		pBall->mIsMoving = false;
		pBall->mIsStuck = true;

		if (CTransform* pBallTransform = pBallEntity->GetComponent<CTransform>())
		{
			/// \todo Fix this magic constant later, used to prevent additional physics event in next frame
			pBallTransform->SetPosition(pBallTransform->GetPosition() + TVector3(0.0f, 0.0f, 0.05f)); 
		}

		AddDefferedCommand([this, pPaddleEntity, pBallEntity]
		{
			GroupEntities(mpWorld, pPaddleEntity->GetId(), pBallEntity->GetId());
		});

		return RC_OK;
	}

	TEventListenerId CStickyBallsProcessSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreateStickyBallsProcessSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CStickyBallsProcessSystem, result, pEventManager);
	}
}