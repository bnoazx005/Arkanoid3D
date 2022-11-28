#include "../../include/systems/CPowerUpSpawnSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CGameInfo.h"
#include "../../include/components/Bonuses.h"
#include <vector>


using namespace TDEngine2;


namespace Game
{
	CPowerUpSpawnSystem::CPowerUpSpawnSystem() :
		CBaseSystem(), mRandomUtility(static_cast<int>(time(nullptr)))
	{
	}

	E_RESULT_CODE CPowerUpSpawnSystem::Init(TPtr<IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager || !pSceneManager)
		{
			return RC_INVALID_ARGS;
		}

		mpEventManager = pEventManager;
		mpSceneManager = pSceneManager;

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


	struct TPowerUpConfigEntity
	{
		TypeId mPowerUpTypeId;
		F32 mProbability;
		std::string mPrefabId;
	};


	E_RESULT_CODE CPowerUpSpawnSystem::OnEvent(const TBaseEvent* pEvent)
	{
		const TSpawnNewBonusEvent* pSpawnEvent = dynamic_cast<const TSpawnNewBonusEvent*>(pEvent);
		if (!pSpawnEvent)
		{
			return RC_FAIL;
		}

		const TVector3& spawnPosition = pSpawnEvent->mPosition;
		
		/// \todo Replace with configurable YAML archive
		static const std::vector<TPowerUpConfigEntity> PowerUpsTable
		{
			{ CScoreBonus::GetTypeId(),				0.15f, "PowerUp_AddScore" },
			{ CScoreMultiplierBonus::GetTypeId(),	0.15f, "PowerUp_Score2X" },
			{ CExpandPaddleBonus::GetTypeId(),		0.15f, "PowerUp_ExpandPaddle" },
			{ CGodModeBonus::GetTypeId(),			0.15f, "PowerUp_GodMode" },
			{ CStickyPaddleBonus::GetTypeId(),		0.15f, "PowerUp_StickyPaddle" },
			{ CExtraLifeBonus::GetTypeId(),			0.15f, "PowerUp_ExtraLife" },
			{ CLaserBonus::GetTypeId(),				0.15f, "PowerUp_Laser" },
			{ CMultipleBallsBonus::GetTypeId(),		0.15f, "PowerUp_MultiplyBallsCount" },
			{ CTransform::GetTypeId(),				1.0f, "PowerUp" }, /// \note The default one
		};

		CEntity* pEntity = mpWorld->FindEntity(pSpawnEvent->mSpawnerEntityId);
		if (!pEntity)
		{
			return RC_OK;
		}

		/// \todo Replace with utility function GetCurrLoadedScene()
		CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			return RC_OK;
		}

		auto sceneResult = mpSceneManager->GetScene(pGameInfo->mCurrLoadedGameId);
		if (sceneResult.HasError())
		{
			TDE2_ASSERT(false);
			return RC_OK;
		}

		IScene* pScene = sceneResult.Get();
		if (!pScene)
		{
			TDE2_ASSERT(false);
			return RC_OK;
		}

		const F32 probabilityFactor = mRandomUtility.Get(0.0f, 1.0f);

		for (auto&& currPowerUp : PowerUpsTable)
		{
			if (!pEntity->HasComponent(currPowerUp.mPowerUpTypeId))
			{
				continue;
			}

			if (probabilityFactor > currPowerUp.mProbability)
			{
				continue;
			}

			/// \note Spawn
			CEntity* pPowerUpEntity = pScene->Spawn(currPowerUp.mPrefabId);
			if (!pPowerUpEntity)
			{
				continue;
			}

			CTransform* pPowerUpTransform = pPowerUpEntity->GetComponent<CTransform>();
			pPowerUpTransform->SetPosition(spawnPosition);
		}

		return RC_OK;
	}

	TEventListenerId CPowerUpSpawnSystem::GetListenerId() const
	{
		return TEventListenerId(GetTypeId());
	}


	TDE2_API ISystem* CreatePowerUpSpawnSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPowerUpSpawnSystem, result, pEventManager, pSceneManager);
	}
}