/*!
	\file CPaddlePositionerSystem.h
	\date 13.12.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "../components/CPaddle.h"
#include "../Components.h"
#include <vector>


namespace Game
{
	TDE2_API TDEngine2::ISystem* CreatePaddlePositionerSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::E_RESULT_CODE& result);


	class CPaddlePositionerSystem : public TDEngine2::CBaseSystem, public TDEngine2::IEventHandler
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreatePaddlePositionerSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::E_RESULT_CODE&);

		public:
			TDE2_SYSTEM(CPaddlePositionerSystem);

			/*!
				\brief The method initializes an inner state of a system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Init(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager);

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

			/*!
				\brief The method receives a given event and processes it

				\param[in] pEvent A pointer to event data

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE OnEvent(const TDEngine2::TBaseEvent* pEvent) override;

			/*!
				\brief The method returns an identifier of a listener

				\return The method returns an identifier of a listener
			*/

			TDE2_API TDEngine2::TEventListenerId GetListenerId() const override;
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CPaddlePositionerSystem)

		private:
			TDEngine2::TComponentsQueryLocalSlice<Game::CPaddle, TDEngine2::CTransform> mPaddlesContext;
			TDEngine2::TComponentsQueryLocalSlice<Game::CPlayerPositioner, TDEngine2::CTransform> mPositionersContext;
			TDEngine2::IWorld* mpWorld = nullptr;
			bool mIsDirty = false;
	};
}