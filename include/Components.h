/*!
	\file Components.h
	\date 29.08.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDEngine2::E_RESULT_CODE RegisterGameComponents(TDEngine2::TPtr<TDEngine2::IWorld> pWorld);

	//TDE2_DECLARE_FLAG_COMPONENT(Paddle);
	//TDE2_REGISTER_UNIQUE_COMPONENT(CPaddle);
}