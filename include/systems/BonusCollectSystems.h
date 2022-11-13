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

			TDE2_API void _onApplyCollectable(const CScoreBonus* pCollectable) override;
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

			TDE2_API void _onApplyCollectable(const CScoreMultiplierBonus* pCollectable) override;
			TDE2_API void _onCollectableEffectFinished() override;
	};


	/*!
		\brief GodModeBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateGodModeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CGodModeBonusCollectSystem : public Game::CCollectingSystem<CGodModeBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateGodModeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CGodModeBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CGodModeBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CGodModeBonus* pCollectable) override;
			TDE2_API void _onCollectableEffectFinished() override;
	};


	/*!
		\brief ExpandPaddleBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateExpandPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CExpandPaddleBonusCollectSystem : public Game::CCollectingSystem<CExpandPaddleBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateExpandPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CExpandPaddleBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CExpandPaddleBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CExpandPaddleBonus* pCollectable) override;
			TDE2_API void _onCollectableEffectFinished() override;

		private:
			TDEngine2::F32 mPrevScale = 1.0f;
	};


	/*!
		\brief StickyPaddleBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateStickyPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CStickyPaddleBonusCollectSystem : public Game::CCollectingSystem<CStickyPaddleBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateStickyPaddleBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CStickyPaddleBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CStickyPaddleBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CStickyPaddleBonus* pCollectable) override;
	};


	/*!
		\brief ExtraLifeBonusCollectSystem
	*/

	TDE2_API TDEngine2::ISystem* CreateExtraLifeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CExtraLifeBonusCollectSystem : public Game::CCollectingSystem<CExtraLifeBonus>
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateExtraLifeBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CExtraLifeBonusCollectSystem);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CExtraLifeBonusCollectSystem)

			TDE2_API void _onApplyCollectable(const CExtraLifeBonus* pCollectable) override;
	};
}