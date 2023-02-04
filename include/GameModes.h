/*!
	\file GameStates.h
	\date 04.02.2023
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreatePauseGameMode(TDEngine2::IGameModesManager* pOwner, TDEngine2::TPtr<TDEngine2::IInputContext> pInputContext, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CPauseGameMode

		\brief The class represents a mode which is active when a user taps pause button
	*/

	class CPauseGameMode : public TDEngine2::CBaseGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreatePauseGameMode(TDEngine2::IGameModesManager*, TDEngine2::TPtr<TDEngine2::IInputContext>, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CPauseGameMode)
		private:
			TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext;
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreateCoreGameMode(TDEngine2::IGameModesManager* pOwner, TDEngine2::TPtr<TDEngine2::IInputContext> pInputContext, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CCoreGameMode

		\brief The class represents a mode which implements core gameplay state
	*/

	class CCoreGameMode : public TDEngine2::CBaseGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreateCoreGameMode(TDEngine2::IGameModesManager*, TDEngine2::TPtr<TDEngine2::IInputContext>, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCoreGameMode)
		private:
			TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext;
	};
}