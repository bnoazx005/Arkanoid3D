#include "../../include/systems/CDamageablesUpdateSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CGameInfo.h"


using namespace TDEngine2;


namespace Game
{
	CDamageablesUpdateSystem::CDamageablesUpdateSystem() :
		CBaseSystem(), mRandomUtility(static_cast<int>(time(nullptr)))
	{
	}

	E_RESULT_CODE CDamageablesUpdateSystem::Init(TPtr<IEventManager> pEventManager)
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

		pEventManager->Subscribe(TOn3DCollisionRegisteredEvent::GetTypeId(), this);

		mIsInitialized = true;

		return RC_OK;
	}

	void CDamageablesUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mpWorld = pWorld;
	}

	void CDamageablesUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
	}

	E_RESULT_CODE CDamageablesUpdateSystem::OnEvent(const TBaseEvent* pEvent)
	{
		const TOn3DCollisionRegisteredEvent* pCollisionEvent = dynamic_cast<const TOn3DCollisionRegisteredEvent*>(pEvent);
		if (!pCollisionEvent)
		{
			return RC_FAIL;
		}

		CEntity* pEntity0 = mpWorld->FindEntity(pCollisionEvent->mEntities[0]);
		CEntity* pEntity1 = mpWorld->FindEntity(pCollisionEvent->mEntities[1]);

		if (!pEntity0 || !pEntity1 || TOn3DCollisionRegisteredEvent::E_COLLISION_EVENT_TYPE::ON_ENTER != pCollisionEvent->mType)
		{
			return RC_OK;
		}

		CEntity* pDamageableEntity = pEntity0;

		CDamageable* pDamageable = pDamageableEntity->GetComponent<CDamageable>();
		if (!pDamageable)
		{
			pDamageable = pEntity1->GetComponent<CDamageable>();
			pDamageableEntity = pEntity1;
		}

		CBall* pBall = GetValidPtrOrDefault(pEntity0->GetComponent<CBall>(), pEntity1->GetComponent<CBall>());
		CProjectile* pProjectile = GetValidPtrOrDefault(pEntity0->GetComponent<CProjectile>(), pEntity1->GetComponent<CProjectile>());

		if (pDamageable && (pBall || pProjectile) && pDamageable->mLifes > 0)
		{
			if (pBall)
			{
				pBall->mDirection = Reflect(-pBall->mDirection, pCollisionEvent->mContactNormal);
			}

			if (!pDamageable->mIsConstant)
			{
				pDamageable->mLifes--;
			}

			if (!pDamageable->mLifes)
			{
				CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();

				const F32 probabilityFactor = mRandomUtility.Get(0.0f, 1.0f);
				if (probabilityFactor < pGameInfo->mBonusesSpawnCommonProbability)
				{
					TSpawnNewBonusEvent spawnEvent;

					if (auto pTransform = pDamageableEntity->GetComponent<CTransform>())
					{
						spawnEvent.mPosition = pTransform->GetPosition();
						spawnEvent.mSpawnerEntityId = pDamageableEntity->GetId();

						LOG_MESSAGE(Wrench::StringUtils::Format("[CDamageablesUpdateSystem] A new power up is spawned at {0}", spawnEvent.mPosition.ToString()));
					}

					mpEventManager->Notify(&spawnEvent);
				}

				/// \note Update the score
				{
					pGameInfo->mPlayerScore += pGameInfo->mScoreMultiplier * pDamageable->mRewardScore;

					TScoreChangedEvent scoreChangedEvent;
					scoreChangedEvent.mNewPlayerScore = pGameInfo->mPlayerScore;

					mpEventManager->Notify(&scoreChangedEvent);
				}

				AddDefferedCommand([this, pDamageableEntity]
				{
					mpWorld->Destroy(pDamageableEntity);
				});
			}
		}

		return RC_OK;
	}

	TEventListenerId CDamageablesUpdateSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreateDamageablesUpdateSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CDamageablesUpdateSystem, result, pEventManager);
	}
}