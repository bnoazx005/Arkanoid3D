#include "../../include/systems/CProjectilesPoolSystem.h"
#include "../../include/components/CGameInfo.h"


using namespace TDEngine2;


namespace Game
{
	CProjectilesPoolSystem::CProjectilesPoolSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CProjectilesPoolSystem::Init()
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		mIsInitialized = true;

		return RC_OK;
	}

	void CProjectilesPoolSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<CProjectile, CTransform>();
		mGameInfoEntityId = pWorld->FindEntityWithUniqueComponent<Game::CGameInfo>();
	}

	void CProjectilesPoolSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);

		CGameInfo* pGameInfo = pWorld->FindEntity(mGameInfoEntityId)->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return;
		}

		/// \note Not optimal solution but well enough for a proof of concept
		auto& projectilesPool = pGameInfo->mpProjectilesPool;

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			if (transforms[i]->GetPosition().z > pGameInfo->mVerticalConstraints.mRight)
			{
				CEntity* pProjectileEntity = pWorld->FindEntity(transforms[i]->GetOwnerId());

				auto it = std::find(projectilesPool.begin(), projectilesPool.end(), pProjectileEntity);
				if (it == projectilesPool.end())
				{
					projectilesPool.push_back(pProjectileEntity); /// \note Return back to the pool if a projectile goes out of a level
				}
			}
		}
	}


	TDE2_API ISystem* CreateProjectilesPoolSystem(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CProjectilesPoolSystem, result);
	}
}