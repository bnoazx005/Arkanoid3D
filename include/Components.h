/*!
	\file Components.h
	\date 29.08.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDEngine2::E_RESULT_CODE RegisterGameComponents(TDEngine2::TPtr<TDEngine2::IWorld> pWorld
#if TDE2_EDITORS_ENABLED
		, TDEngine2::TPtr<TDEngine2::IEditorsManager> pEditorsManager
#endif 
	);


	TDE2_DECLARE_FLAG_COMPONENT(Projectile);
	//TDE2_REGISTER_UNIQUE_COMPONENT(CPaddle);
}


namespace TDEngine2
{
	/*!
		struct TSpawnNewBonusEvent

		\brief The structure represents an event which occurs when a new power up should be spawned
	*/

	typedef struct TSpawnNewBonusEvent : TDEngine2::TBaseEvent
	{
		virtual ~TSpawnNewBonusEvent() = default;

		TDE2_REGISTER_TYPE(TSpawnNewBonusEvent)
		REGISTER_EVENT_TYPE(TSpawnNewBonusEvent)

		TDEngine2::TVector3 mPosition;
		TDEngine2::TEntityId mSpawnerEntityId;
	} TSpawnNewBonusEvent, * TSpawnNewBonusEventPtr;
}