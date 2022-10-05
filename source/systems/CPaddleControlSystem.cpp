#include "../../include/systems/CPaddleControlSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CLevelInfo.h"


using namespace TDEngine2;


namespace Game
{
	CPaddleControlSystem::CPaddleControlSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CPaddleControlSystem::Init(TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext)
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

	void CPaddleControlSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<CPaddle, CTransform>();

		mLevelInfoEntityId = pWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>();
	}

	void CPaddleControlSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);
		auto& paddles = std::get<std::vector<CPaddle*>>(mSystemContext.mComponentsSlice);

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
			if (CLevelInfo* pLevelInfo = pWorld->FindEntity(mLevelInfoEntityId)->GetComponent<CLevelInfo>())
			{
				auto currPosition = pCurrTransform->GetPosition();
				currPosition.x = CMathUtils::Clamp(pLevelInfo->mHorizontalConstraints.mLeft, pLevelInfo->mHorizontalConstraints.mRight, currPosition.x);

				pCurrTransform->SetPosition(currPosition);
			}
		}
	}


	TDE2_API ISystem* CreatePaddleControlSystem(TPtr<IDesktopInputContext> pInputContext, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CPaddleControlSystem, result, pInputContext);
	}
}