/*!
	\file CProjectilesPoolSystem.h
	\date 29.11.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "../Components.h"


namespace Game
{
	TDE2_API TDEngine2::ISystem* CreateProjectilesPoolSystem(TDEngine2::E_RESULT_CODE& result);


	class CProjectilesPoolSystem : public TDEngine2::CBaseSystem
	{
	public:
		friend TDE2_API TDEngine2::ISystem* CreateProjectilesPoolSystem(TDEngine2::E_RESULT_CODE&);
	public:
		TDE2_SYSTEM(CProjectilesPoolSystem);

		/*!
			\brief The method initializes an inner state of a system

			\return RC_OK if everything went ok, or some other code, which describes an error
		*/

		TDE2_API TDEngine2::E_RESULT_CODE Init();

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
		DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CProjectilesPoolSystem)

	private:
		TDEngine2::TComponentsQueryLocalSlice<CProjectile, TDEngine2::CTransform> mSystemContext;

		TDEngine2::TEntityId mGameInfoEntityId = TDEngine2::TEntityId::Invalid;
	};
}