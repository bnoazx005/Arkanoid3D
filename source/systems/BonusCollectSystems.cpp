#include "../../include/systems/BonusCollectSystems.h"
#include "../../include/Components.h"
#include "../../include/components/CLevelInfo.h"
#include "../../include/components/CPaddle.h"


using namespace TDEngine2;


namespace Game
{
	/*!
		\brief AddScoreBonusCollectSystem
	*/

	CAddScoreBonusCollectSystem::CAddScoreBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CAddScoreBonusCollectSystem::_onApplyCollectable(const CScoreBonus* pCollectable)
	{
		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mPlayerScore += pLevelInfo->mScoreMultiplier * pCollectable->mScoreToAdd;
	}


	TDE2_API ISystem* CreateAddScoreBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CAddScoreBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief ScoreMultiplierBonusCollectSystem
	*/

	CScoreMultiplierBonusCollectSystem::CScoreMultiplierBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CScoreMultiplierBonusCollectSystem::_onApplyCollectable(const CScoreMultiplierBonus* pCollectable)
	{
		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mScoreMultiplier = pCollectable->mValue;

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;
	}

	void CScoreMultiplierBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mScoreMultiplier = 1;
	}


	TDE2_API ISystem* CreateScoreMultiplierBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CScoreMultiplierBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief GodModeBonusCollectSystem
	*/

	CGodModeBonusCollectSystem::CGodModeBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CGodModeBonusCollectSystem::_onApplyCollectable(const CGodModeBonus* pCollectable)
	{
		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mIsGodModeEnabled = true;

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;
	}

	void CGodModeBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mIsGodModeEnabled = false;
	}


	TDE2_API ISystem* CreateGodModeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CGodModeBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief ExpandPaddleBonusCollectSystem
	*/

	CExpandPaddleBonusCollectSystem::CExpandPaddleBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	static void ApplyScaleForPaddles(IWorld* mpWorld, F32 paddleScale)
	{
		for (auto currEntityId : mpWorld->FindEntitiesWithComponents<CPaddle>())
		{
			CEntity* pEntity = mpWorld->FindEntity(currEntityId);
			if (!pEntity)
			{
				continue;
			}

			CTransform* pTransform = pEntity->GetComponent<CTransform>();

			TVector3 scale = pTransform->GetScale();
			scale.x *= paddleScale;

			pTransform->SetScale(scale);
		}
	}

	void CExpandPaddleBonusCollectSystem::_onApplyCollectable(const CExpandPaddleBonus* pCollectable)
	{
		ApplyScaleForPaddles(mpWorld, pCollectable->mExpandCoefficient);

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;

		mPrevScale = pCollectable->mExpandCoefficient;
	}

	void CExpandPaddleBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		ApplyScaleForPaddles(mpWorld, 1.0f / mPrevScale);
	}


	TDE2_API ISystem* CreateExpandPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CExpandPaddleBonusCollectSystem, result, pEventManager);
	}
}