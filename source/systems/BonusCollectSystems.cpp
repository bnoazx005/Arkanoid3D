#include "../../include/systems/BonusCollectSystems.h"
#include "../../include/Components.h"
#include "../../include/components/CGameInfo.h"
#include "../../include/components/CPaddle.h"
#include "../../include/components/CBall.h"


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
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mPlayerScore += pGameInfo->mScoreMultiplier * pCollectable->mScoreToAdd;

		TScoreChangedEvent scoreChangedEvent;
		scoreChangedEvent.mNewPlayerScore = pGameInfo->mPlayerScore;

		mpEventManager->Notify(&scoreChangedEvent);
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
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mScoreMultiplier = pCollectable->mValue;

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;
	}

	void CScoreMultiplierBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mScoreMultiplier = 1;
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
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mIsGodModeEnabled = true;

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;
	}

	void CGodModeBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mIsGodModeEnabled = false;
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


	/*!
		\brief StickyPaddleBonusCollectSystem
	*/

	CStickyPaddleBonusCollectSystem::CStickyPaddleBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CStickyPaddleBonusCollectSystem::_onApplyCollectable(const CStickyPaddleBonus* pCollectable)
	{
		for (auto currEntityId : mpWorld->FindEntitiesWithComponents<CPaddle>())
		{
			CEntity* pEntity = mpWorld->FindEntity(currEntityId);
			if (!pEntity)
			{
				continue;
			}

			if (CPaddle* pPaddle = pEntity->GetComponent<CPaddle>())
			{
				pPaddle->mIsSticky = true;
			}
		}
	}


	TDE2_API ISystem* CreateStickyPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CStickyPaddleBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief ExtraLifeBonusCollectSystem
	*/

	CExtraLifeBonusCollectSystem::CExtraLifeBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CExtraLifeBonusCollectSystem::_onApplyCollectable(const CExtraLifeBonus* pCollectable)
	{
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mPlayerLives++;
	}


	TDE2_API ISystem* CreateExtraLifeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CExtraLifeBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief LaserBonusCollectSystem
	*/

	CLaserBonusCollectSystem::CLaserBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CLaserBonusCollectSystem::_onApplyCollectable(const CLaserBonus* pCollectable)
	{
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mIsLaserEnabled = true;

		mCurrTimer += pCollectable->mEffectDuration;
		mIsEffectActive = true;
	}

	void CLaserBonusCollectSystem::_onCollectableEffectFinished()
	{
		CCollectingSystem::_onCollectableEffectFinished();

		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		pGameInfo->mIsLaserEnabled = false;
	}


	TDE2_API ISystem* CreateLaserBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CLaserBonusCollectSystem, result, pEventManager);
	}


	/*!
		\brief MultipleBallsBonusCollectSystem
	*/

	CMultipleBallsBonusCollectSystem::CMultipleBallsBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CMultipleBallsBonusCollectSystem::_onApplyCollectable(const CMultipleBallsBonus* pCollectable)
	{
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return;
		}

		auto sceneResult = mpSceneManager->GetScene(pGameInfo->mCurrLoadedGameId);
		if (sceneResult.HasError())
		{
			TDE2_ASSERT(false);
			return;
		}

		IScene* pScene = sceneResult.Get();
		if (!pScene)
		{
			TDE2_ASSERT(false);
			return;
		}

		const U32 ballsCount = pCollectable->mBallsCount;

		/// \note Instantiate new balls 
		for (TEntityId currBallEntityId : mpWorld->FindEntitiesWithComponents<CBall>())
		{
			CEntity* pEntity = mpWorld->FindEntity(currBallEntityId);
			if (!pEntity)
			{
				continue;
			}

			CTransform* pBallTransform = pEntity->GetComponent<CTransform>();
			const TVector3& ballPosition = pBallTransform->GetPosition();

			for (U32 i = 0; i < ballsCount; i++)
			{
				CEntity* pNewBallEntity = pScene->Spawn("Ball"); /// \todo Replace constant with configurable identifier
				if (!pNewBallEntity)
				{
					continue;
				}

				CTransform* pNewBallTransform = pNewBallEntity->GetComponent<CTransform>();
				pNewBallTransform->SetPosition(ballPosition);

				CBall* pNewBall = pNewBallEntity->GetComponent<CBall>();
				pNewBall->mNeedUpdateDirection = true;
			}
		}
	}


	TDE2_API ISystem* CreateMultipleBallsBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CMultipleBallsBonusCollectSystem, result, pEventManager, pSceneManager);
	}
}