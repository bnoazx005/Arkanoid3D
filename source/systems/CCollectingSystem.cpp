#include "../../include/systems/CCollectingSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CCollectable.h"


using namespace TDEngine2;


namespace Game
{
	CCollectingSystem::CCollectingSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CCollectingSystem::Init(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager)
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

	void CCollectingSystem::InjectBindings(IWorld* pWorld)
	{
	}

	void CCollectingSystem::Update(IWorld* pWorld, F32 dt)
	{
	}

	E_RESULT_CODE CCollectingSystem::OnEvent(const TBaseEvent* pEvent)
	{
		const TOn3DCollisionRegisteredEvent* pCollisionEvent = dynamic_cast<const TOn3DCollisionRegisteredEvent*>(pEvent);
		if (!pCollisionEvent)
		{
			return RC_FAIL;
		}

		//CEntity* pEntity0 = mpWorld->FindEntity(pCollisionEvent->mEntities[0]);
		//CEntity* pEntity1 = mpWorld->FindEntity(pCollisionEvent->mEntities[1]);

		//if (!pEntity0 || !pEntity1 || TOn3DCollisionRegisteredEvent::E_COLLISION_EVENT_TYPE::ON_ENTER != pCollisionEvent->mType)
		//{
		//	return RC_OK;
		//}

		//CEntity* pDamageableEntity = pEntity0;

		//CDamageable* pDamageable = pDamageableEntity->GetComponent<CDamageable>();
		//if (!pDamageable)
		//{
		//	pDamageable = pEntity1->GetComponent<CDamageable>();
		//	pDamageableEntity = pEntity1;
		//}

		//CBall* pBall = GetValidPtrOrDefault(pEntity0->GetComponent<CBall>(), pEntity1->GetComponent<CBall>());

		//if (pDamageable && pBall && pDamageable->mLifes > 0)
		//{
		//	pBall->mDirection = Reflect(-pBall->mDirection, pCollisionEvent->mContactNormal);

		//	if (!pDamageable->mIsConstant)
		//	{
		//		pDamageable->mLifes--;
		//	}

		//	if (!pDamageable->mLifes)
		//	{
		//		AddDefferedCommand([this, pDamageableEntity]
		//		{
		//			mpWorld->Destroy(pDamageableEntity);
		//		});
		//	}
		//}

		return RC_OK;
	}

	TEventListenerId CCollectingSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreateCollectingSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CCollectingSystem, result, pEventManager);
	}
}