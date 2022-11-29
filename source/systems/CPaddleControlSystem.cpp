#include "../../include/systems/CPaddleControlSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CGameInfo.h"


using namespace TDEngine2;


namespace Game
{
	CPaddleControlSystem::CPaddleControlSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CPaddleControlSystem::Init(TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext, TPtr<ISceneManager> pSceneManager)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pInputContext || !pSceneManager)
		{
			return RC_INVALID_ARGS;
		}

		mpInputContext = pInputContext;
		mpSceneManager = pSceneManager;

		mIsInitialized = true;

		return RC_OK;
	}

	void CPaddleControlSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<CPaddle, CTransform>();

		mGameInfoEntityId = pWorld->FindEntityWithUniqueComponent<Game::CGameInfo>();
	}


	static void ProcessLaserShot(IWorld* pWorld, TPtr<ISceneManager> pSceneManager, CTransform* pPaddleTransform, CGameInfo* pGameInfo)
	{
		auto sceneResult = pSceneManager->GetScene(pGameInfo->mCurrLoadedGameId);
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

		auto& projectilesPool = pGameInfo->mpProjectilesPool;

		const TVector3& pos = pPaddleTransform->GetPosition();

		auto spawnProjectile = [&pos, pScene, &projectilesPool](float xOffset)
		{
			if (CEntity* pProjectileEntity = projectilesPool.empty() ? pScene->Spawn("Projectile") : projectilesPool.front()) /// \todo Replace this with configurable id
			{
				if (!projectilesPool.empty())
				{
					projectilesPool.pop_front(); /// \note Remove the entity from the pool
				}

				if (CTransform* pTransform = pProjectileEntity->GetComponent<CTransform>())
				{
					pTransform->SetPosition(TVector3(pos.x + xOffset, pTransform->GetPosition().y, pos.z));
				}
			}
		};

		spawnProjectile(-0.5f);
		spawnProjectile(0.5f);
	}


	void CPaddleControlSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);
		auto& paddles = std::get<std::vector<CPaddle*>>(mSystemContext.mComponentsSlice);

		CGameInfo* pGameInfo = pWorld->FindEntity(mGameInfoEntityId)->GetComponent<CGameInfo>();

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; ++i)
		{
			CTransform* pCurrTransform = transforms[i];
			CPaddle* pCurrPaddle = paddles[i];

			const TVector3 delta = pCurrTransform->GetRightVector() * (dt * pCurrPaddle->mSpeed);

			if (mpInputContext->IsKey(E_KEYCODES::KC_A))
			{
				pCurrTransform->SetPosition(pCurrTransform->GetPosition() - delta);
			}
			else if (mpInputContext->IsKey(E_KEYCODES::KC_D))
			{
				pCurrTransform->SetPosition(pCurrTransform->GetPosition() + delta);
			}
			else 
			{
				const F32 direction = 2.0f * mpInputContext->GetMouseShiftVec().x / CMathUtils::Max(1e-3f, CMathUtils::Abs(mpInputContext->GetMouseShiftVec().x));

				//pCurrTransform->SetPosition(pCurrTransform->GetPosition() + delta * direction);
			}

			/// \note Clamp the horizontal position
			if (!pGameInfo)
			{
				continue;
			}

			auto currPosition = pCurrTransform->GetPosition();
			currPosition.x = CMathUtils::Clamp(pGameInfo->mHorizontalConstraints.mLeft, pGameInfo->mHorizontalConstraints.mRight, currPosition.x);

			pCurrTransform->SetPosition(currPosition);

			if (pGameInfo->mIsLaserEnabled && (mpInputContext->IsKeyPressed(E_KEYCODES::KC_SPACE) || mpInputContext->IsMouseButtonPressed(0)))
			{
				ProcessLaserShot(pWorld, mpSceneManager, pCurrTransform, pGameInfo);
			}
		}
	}


	TDE2_API ISystem* CreatePaddleControlSystem(TPtr<IDesktopInputContext> pInputContext, TPtr<ISceneManager> pSceneManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPaddleControlSystem, result, pInputContext, pSceneManager);
	}
}