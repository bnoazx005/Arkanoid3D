#include "../../include/systems/CGameUIUpdateSystem.h"
#include "../../include/Components.h"


using namespace TDEngine2;


namespace Game
{
	CGameUIUpdateSystem::CGameUIUpdateSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CGameUIUpdateSystem::Init(TPtr<IEventManager> pEventManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager)
		{
			return RC_INVALID_ARGS;
		}

		pEventManager->Subscribe(TScoreChangedEvent::GetTypeId(), this);
		pEventManager->Subscribe(TLivesChangedEvent::GetTypeId(), this);

		mIsInitialized = true;

		return RC_OK;
	}

	void CGameUIUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mpWorld = pWorld;

		auto&& scoresLabels = mpWorld->FindEntitiesWithComponents<CScoreLabel>();
		auto&& livesLabels = mpWorld->FindEntitiesWithComponents<CLivesLabel>();

		mScoreLabelElementId = scoresLabels.empty() ? TEntityId::Invalid : scoresLabels.front();
		mLivesLabelElementId = livesLabels.empty() ? TEntityId::Invalid : livesLabels.front();
	}

	void CGameUIUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
	}

	E_RESULT_CODE CGameUIUpdateSystem::OnEvent(const TBaseEvent* pEvent)
	{
		if (const TScoreChangedEvent* pScoreEvent = dynamic_cast<const TScoreChangedEvent*>(pEvent))
		{
			if (auto pScoreEntity = mpWorld->FindEntity(mScoreLabelElementId))
			{
				if (auto pLabel = pScoreEntity->GetComponent<CLabel>())
				{
					pLabel->SetText(std::to_string(pScoreEvent->mNewPlayerScore));
				}
			}

			return RC_OK;
		}

		if (const TLivesChangedEvent* pLivesEvent = dynamic_cast<const TLivesChangedEvent*>(pEvent))
		{
			if (auto pLivesEntity = mpWorld->FindEntity(mLivesLabelElementId))
			{
				if (auto pLabel = pLivesEntity->GetComponent<CLabel>())
				{
					pLabel->SetText(std::to_string(pLivesEvent->mPlayerLives));
				}
			}

			return RC_OK;
		}

		return RC_OK;
	}

	TEventListenerId CGameUIUpdateSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreateGameUIUpdateSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CGameUIUpdateSystem, result, pEventManager);
	}
}