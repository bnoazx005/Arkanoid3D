#include "../../include/systems/CDamageablesUpdateSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CLevelInfo.h"


using namespace TDEngine2;


namespace Game
{
	CDamageablesUpdateSystem::CDamageablesUpdateSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CDamageablesUpdateSystem::Init()
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		mIsInitialized = true;

		return RC_OK;
	}

	void CDamageablesUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<CDamageable, CTransform>();
	}

	void CDamageablesUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);
		auto& damageables = std::get<std::vector<CDamageable*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; ++i)
		{
			CTransform* pCurrTransform = transforms[i];
			CDamageable* pCurrDamageables = damageables[i];

		}
	}


	TDE2_API ISystem* CreateDamageablesUpdateSystem(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CDamageablesUpdateSystem, result);
	}
}