#include "../include/Components.h"
#include "../include/components/CPaddle.h"


namespace Game
{
	//TDE2_DEFINE_FLAG_COMPONENT(Paddle)

	TDEngine2::E_RESULT_CODE RegisterGameComponents(TDEngine2::TPtr<TDEngine2::IWorld> pWorld)
	{
		TDEngine2::E_RESULT_CODE result = TDEngine2::RC_OK;

		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreatePaddleFactory(result)));

		return result;
	}
}