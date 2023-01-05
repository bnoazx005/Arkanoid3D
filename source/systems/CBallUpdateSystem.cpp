#include "../../include/systems/CBallUpdateSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CGameInfo.h"
#include "../../include/components/CBall.h"
#include "../../include/components/CPaddle.h"


using namespace TDEngine2;


namespace Game
{
	CBallUpdateSystem::CBallUpdateSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CBallUpdateSystem::Init(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pEventManager || !pInputContext)
		{
			return RC_INVALID_ARGS;
		}

		mpEventManager = pEventManager;
		mpInputContext = pInputContext;

		mIsInitialized = true;

		return RC_OK;
	}

	void CBallUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<Game::CBall, TDEngine2::CTransform>();
		mGameInfoEntityId = pWorld->FindEntityWithUniqueComponent<Game::CGameInfo>();
	}

	void CBallUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);
		auto& balls = std::get<std::vector<CBall*>>(mSystemContext.mComponentsSlice);

		CGameInfo* pGameInfo = pWorld->FindEntity(mGameInfoEntityId)->GetComponent<CGameInfo>();

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; ++i)
		{
			CTransform* pCurrTransform = transforms[i];
			CBall* pCurrBall = balls[i];

			if (!pCurrBall->mIsMoving && (mpInputContext->IsKeyPressed(E_KEYCODES::KC_SPACE) && pGameInfo->mPlayerLives > 0 || pCurrBall->mNeedUpdateDirection))
			{
				AddDefferedCommand([pWorld, pCurrTransform, pCurrBall]
				{
					if (TEntityId::Invalid != pCurrTransform->GetParent())
					{
						TDEngine2::GroupEntities(pWorld, TEntityId::Invalid, pCurrTransform->GetOwnerId());
					}

					/// \todo Add RandVector2

					pCurrBall->mDirection = RandVector3(TVector3(-1.0f, 0.0f, 1.0f), TVector3(1.0f, 0.0f, 1.0f));
					pCurrBall->mDirection.y = 0.0f;
					pCurrBall->mDirection = Normalize(pCurrBall->mDirection);

					pCurrBall->mNeedUpdateDirection = false;
				});

				pCurrBall->mIsMoving = true;
				pCurrBall->mIsStuck = false;
			}

			if (!pCurrBall->mIsMoving)
			{
				if (!pCurrBall->mIsStuck)
				{
					pCurrTransform->SetPosition(TVector3(0.0f, 0.0f, 1.3f)); /// \fixme Remove this later when linkage with specified position will be possible
				}

				continue;
			}

			pCurrTransform->SetPosition(pCurrTransform->GetPosition() + (pCurrBall->mSpeed * dt) * pCurrBall->mDirection);

			/// \note Process bounces
			{
				auto currPosition = pCurrTransform->GetPosition();

				if (currPosition.x < pGameInfo->mHorizontalConstraints.mLeft || currPosition.x > pGameInfo->mHorizontalConstraints.mRight)
				{
					pCurrBall->mDirection.x = -pCurrBall->mDirection.x;
					pCurrBall->mDirection = Normalize(pCurrBall->mDirection);
				}

				/// \note Reset the ball, update information about the defeat
				if (currPosition.z < pGameInfo->mVerticalConstraints.mLeft && !pGameInfo->mIsGodModeEnabled)
				{
					pGameInfo->mHasPlayerMissedBall = true;

					if (pGameInfo->mPlayerLives >= 1)
					{
						pGameInfo->mPlayerLives--;

						TLivesChangedEvent livesChangedEvent;
						livesChangedEvent.mPlayerLives = pGameInfo->mPlayerLives;

						mpEventManager->Notify(&livesChangedEvent);
					}

					/// \note Remove the extra ball if there is another one
					if (mSystemContext.mComponentsCount >= 2)
					{
						AddDefferedCommand([pWorld, pCurrTransform]
						{
							pWorld->Destroy(pCurrTransform->GetOwnerId());
						});
					}

					pCurrBall->mIsMoving = false;

					auto paddles = pWorld->FindEntitiesWithComponents<Game::CPaddle>();
					if (!paddles.empty())
					{
						TDEngine2::GroupEntities(pWorld, paddles.front(), pCurrTransform->GetOwnerId());
						continue;
					}
				}

				if (currPosition.z > pGameInfo->mVerticalConstraints.mRight || (currPosition.z < pGameInfo->mVerticalConstraints.mLeft && pGameInfo->mIsGodModeEnabled))
				{
					pCurrBall->mDirection.z = -pCurrBall->mDirection.z;
					pCurrBall->mDirection = Normalize(pCurrBall->mDirection);
				}

				pCurrTransform->SetPosition(currPosition);
			}
		}
	}


	TDE2_API ISystem* CreateBallUpdateSystem(TPtr<IEventManager> pEventManager, TPtr<IDesktopInputContext> pInputContext, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CBallUpdateSystem, result, pEventManager, pInputContext);
	}
}