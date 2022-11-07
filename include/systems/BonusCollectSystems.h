/*!
	\file BonusCollectSystems.h
	\date 07.11.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "CCollectingSystem.h"
#include "../components/Bonuses.h"


namespace Game
{
	/*!
		\brief AddScoreBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateAddScoreBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CAddScoreBonusCollectSystem : public Game::CCollectingSystem<CScoreBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateAddScoreBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CAddScoreBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CAddScoreBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CScoreBonus* pCollectable) const override;
	};


	/*!
		\brief ScoreMultiplierBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateScoreMultiplierBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CScoreMultiplierBonusCollectSystem : public Game::CCollectingSystem<CScoreMultiplierBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateScoreMultiplierBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CScoreMultiplierBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CScoreMultiplierBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CScoreMultiplierBonus* pCollectable) const override;
	};
}