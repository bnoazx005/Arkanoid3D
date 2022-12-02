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

	/// UI components
	TDE2_DECLARE_FLAG_COMPONENT(LivesLabel);
	TDE2_DECLARE_FLAG_COMPONENT(ScoreLabel);
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


	/*!
		struct TScoreChangedEvent

		\brief The structure represents an event which occurs when game score's changed
	*/

	typedef struct TScoreChangedEvent : TDEngine2::TBaseEvent
	{
		virtual ~TScoreChangedEvent() = default;

		TDE2_REGISTER_TYPE(TScoreChangedEvent)
		REGISTER_EVENT_TYPE(TScoreChangedEvent)

		TDEngine2::U32 mNewPlayerScore;
	} TScoreChangedEvent, * TScoreChangedEventPtr;


	/*!
		struct TLivesChangedEvent

		\brief The structure represents an event which occurs when game score's changed
	*/

	typedef struct TLivesChangedEvent : TDEngine2::TBaseEvent
	{
		virtual ~TLivesChangedEvent() = default;

		TDE2_REGISTER_TYPE(TLivesChangedEvent)
		REGISTER_EVENT_TYPE(TLivesChangedEvent)

		TDEngine2::U32 mPlayerLives;
	} TLivesChangedEvent, * TLivesChangedEventPtr;
}