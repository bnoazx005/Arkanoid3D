#include "../../include/systems/CBallUpdateSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CLevelInfo.h"
#include "../../include/components/CBall.h"
#include "../../include/components/CPaddle.h"


using namespace TDEngine2;


namespace Game
{
	CBallUpdateSystem::CBallUpdateSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CBallUpdateSystem::Init(TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext)
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		if (!pInputContext)
		{
			return RC_INVALID_ARGS;
		}

		mpInputContext = pInputContext;

		mIsInitialized = true;

		return RC_OK;
	}

	void CBallUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext.mpBalls.clear();
		mSystemContext.mpTransforms.clear();

		for (TEntityId currEntityId : pWorld->FindEntitiesWithComponents<Game::CBall, TDEngine2::CTransform>())
		{
			CEntity* pCurrEntity = pWorld->FindEntity(currEntityId);

			mSystemContext.mpTransforms.push_back(pCurrEntity->GetComponent<CTransform>());
			mSystemContext.mpBalls.push_back(pCurrEntity->GetComponent<Game::CBall>());
		}

		mSystemContext.mComponentsCount = mSystemContext.mpBalls.size();

		mLevelInfoEntityId = pWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>();
	}

	void CBallUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = mSystemContext.mpTransforms;
		auto& balls = mSystemContext.mpBalls;

		CLevelInfo* pLevelInfo = pWorld->FindEntity(mLevelInfoEntityId)->GetComponent<CLevelInfo>();

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; ++i)
		{
			CTransform* pCurrTransform = transforms[i];
			CBall* pCurrBall = balls[i];

			if (!pCurrBall->mIsMoving && (mpInputContext->IsKeyPressed(E_KEYCODES::KC_SPACE) && pLevelInfo->mPlayerLives > 0 || pCurrBall->mNeedUpdateDirection))
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

				if (currPosition.x < pLevelInfo->mHorizontalConstraints.mLeft || currPosition.x > pLevelInfo->mHorizontalConstraints.mRight)
				{
					pCurrBall->mDirection.x = -pCurrBall->mDirection.x;
					pCurrBall->mDirection = Normalize(pCurrBall->mDirection);
				}

				/// \note Reset the ball, update information about the defeat
				if (currPosition.z < pLevelInfo->mVerticalConstraints.mLeft && !pLevelInfo->mIsGodModeEnabled)
				{
					pLevelInfo->mHasPlayerMissedBall = true;
					pLevelInfo->mPlayerLives = std::max<U32>(0, pLevelInfo->mPlayerLives - 1);

					pCurrBall->mIsMoving = false;

					auto paddles = pWorld->FindEntitiesWithComponents<Game::CPaddle>();
					if (!paddles.empty())
					{
						TDEngine2::GroupEntities(pWorld, paddles.front(), pCurrTransform->GetOwnerId());
						continue;
					}
				}

				if (currPosition.z > pLevelInfo->mVerticalConstraints.mRight || (currPosition.z < pLevelInfo->mVerticalConstraints.mLeft && pLevelInfo->mIsGodModeEnabled))
				{
					pCurrBall->mDirection.z = -pCurrBall->mDirection.z;
					pCurrBall->mDirection = Normalize(pCurrBall->mDirection);
				}

				pCurrTransform->SetPosition(currPosition);
			}
		}
	}


	TDE2_API ISystem* CreateBallUpdateSystem(TPtr<IDesktopInputContext> pInputContext, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CBallUpdateSystem, result, pInputContext);
	}
}