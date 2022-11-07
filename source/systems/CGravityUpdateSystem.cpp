#include "../../include/systems/CGravityUpdateSystem.h"
#include "../../include/Components.h"
#include "../../include/components/CGravitable.h"


using namespace TDEngine2;


namespace Game
{
	const TVector3 CGravityUpdateSystem::mGravityDirection = TVector3(0.0f, 0.0f, -2.0f);


	CGravityUpdateSystem::CGravityUpdateSystem() :
		CBaseSystem()
	{
	}

	E_RESULT_CODE CGravityUpdateSystem::Init()
	{
		if (mIsInitialized)
		{
			return RC_FAIL;
		}

		mIsInitialized = true;

		return RC_OK;
	}

	void CGravityUpdateSystem::InjectBindings(IWorld* pWorld)
	{
		mSystemContext = pWorld->CreateLocalComponentsSlice<CGravitable, CTransform>();
	}

	void CGravityUpdateSystem::Update(IWorld* pWorld, F32 dt)
	{
		auto& transforms = std::get<std::vector<CTransform*>>(mSystemContext.mComponentsSlice);
		auto& gravitable = std::get<std::vector<CGravitable*>>(mSystemContext.mComponentsSlice);

		for (USIZE i = 0; i < mSystemContext.mComponentsCount; i++)
		{
			transforms[i]->SetPosition(transforms[i]->GetPosition() + (dt * gravitable[i]->mMass) * mGravityDirection);
		}
	}


	TDE2_API ISystem* CreateGravityUpdateSystem(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CGravityUpdateSystem, result);
	}
}