/*!
	\file CCreditsMenuLogicSystem.h
	\date 01.10.2023
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "../../components/UIComponents.h"


namespace Game
{
	struct TCreditsMenuLogicSystemParams
	{
		TDEngine2::TPtr<TDEngine2::IGameModesManager> mpGameModesManager;
		TDEngine2::TPtr<TDEngine2::IEventManager> mpEventManager;
		TDEngine2::TPtr<TDEngine2::ISceneManager> mpSceneManager;
	};


	TDE2_API TDEngine2::ISystem* CreateCreditsMenuLogicSystem(const TCreditsMenuLogicSystemParams& params, TDEngine2::E_RESULT_CODE& result);


	class CCreditsMenuLogicSystem : public TDEngine2::CBaseSystem
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateCreditsMenuLogicSystem(const TCreditsMenuLogicSystemParams&, TDEngine2::E_RESULT_CODE&);

		public:
			TDE2_SYSTEM(CCreditsMenuLogicSystem);

			/*!
				\brief The method initializes an inner state of a system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Init(const TCreditsMenuLogicSystemParams& params);

			/*!
				\brief The method inject components array into a system

				\param[in] pWorld A pointer to a Pause scene's object
			*/

			TDE2_API void InjectBindings(TDEngine2::IWorld* pWorld) override;

			/*!
				\brief The Pause method that should be implemented in all derived classes.
				It contains all the logic that the system will execute during engine's work.

				\param[in] pWorld A pointer to a Pause scene's object

				\param[in] dt A delta time's value
			*/

			TDE2_API void Update(TDEngine2::IWorld* pWorld, TDEngine2::F32 dt) override;

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCreditsMenuLogicSystem)

		private:
			TDEngine2::TPtr<TDEngine2::IGameModesManager> mpGameModesManager = nullptr;
			TDEngine2::TPtr<TDEngine2::IEventManager>     mpEventManager = nullptr;
			TDEngine2::TPtr<TDEngine2::ISceneManager>     mpSceneManager = nullptr;

			TDEngine2::TComponentsQueryLocalSlice<Game::CCreditsMenuPanel> mSystemContext;
	};
}