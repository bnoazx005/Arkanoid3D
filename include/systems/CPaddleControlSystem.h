/*!
	\file CPaddleControlSystem.h
	\date 30.08.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "../components/CPaddle.h"


namespace Game
{
	TDE2_API TDEngine2::ISystem* CreatePaddleControlSystem(TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext, TDEngine2::E_RESULT_CODE& result);


	class CPaddleControlSystem : public TDEngine2::CBaseSystem
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreatePaddleControlSystem(TDEngine2::TPtr<TDEngine2::IDesktopInputContext>, TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_SYSTEM(CPaddleControlSystem);

			/*!
				\brief The method initializes an inner state of a system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Init(TDEngine2::TPtr<TDEngine2::IDesktopInputContext>);

			/*!
				\brief The method inject components array into a system

				\param[in] pWorld A pointer to a main scene's object
			*/

			TDE2_API void InjectBindings(TDEngine2::IWorld* pWorld) override;

			/*!
				\brief The main method that should be implemented in all derived classes.
				It contains all the logic that the system will execute during engine's work.

				\param[in] pWorld A pointer to a main scene's object

				\param[in] dt A delta time's value
			*/

			TDE2_API void Update(TDEngine2::IWorld* pWorld, TDEngine2::F32 dt) override;
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CPaddleControlSystem)

		private:
			TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext = nullptr;
			
			TDEngine2::TComponentsQueryLocalSlice<CPaddle, TDEngine2::CTransform> mSystemContext;
	};
}