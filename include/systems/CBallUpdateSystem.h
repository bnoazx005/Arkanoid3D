/*!
	\file CBallUpdateSystem.h
	\date 04.10.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	class CBall;


	TDE2_API TDEngine2::ISystem* CreateBallUpdateSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext, TDEngine2::E_RESULT_CODE& result);


	class CBallUpdateSystem : public TDEngine2::CBaseSystem
	{
		public:
			friend TDE2_API TDEngine2::ISystem* CreateBallUpdateSystem(TDEngine2::TPtr<TDEngine2::IEventManager>, TDEngine2::TPtr<TDEngine2::IDesktopInputContext>, TDEngine2::E_RESULT_CODE&);
		private:
			struct TSystemContext
			{
				std::vector<TDEngine2::CTransform*> mpTransforms;
				std::vector<CBall*>                 mpBalls;

				TDEngine2::USIZE                    mComponentsCount;
			};
		public:
			TDE2_SYSTEM(CBallUpdateSystem);

			/*!
				\brief The method initializes an inner state of a system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Init(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::IDesktopInputContext>);

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CBallUpdateSystem)

		private:
			TDEngine2::TPtr<TDEngine2::IEventManager> mpEventManager = nullptr;
			TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext = nullptr;
			
			TSystemContext mSystemContext;
			
			TDEngine2::TEntityId mGameInfoEntityId = TDEngine2::TEntityId::Invalid;
	};
}