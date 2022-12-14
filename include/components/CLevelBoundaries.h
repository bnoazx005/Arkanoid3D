/*!
	\file CLevelBoundaries.h
	\date 13.12.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateLevelBoundaries(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CLevelBoundaries
	*/

	class CLevelBoundaries : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CLevelBoundaries, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateLevelBoundaries(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CLevelBoundaries)

			/*!
				\brief The method deserializes object's state from given reader

				\param[in, out] pReader An input stream of data that contains information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Load(TDEngine2::IArchiveReader* pReader) override;

			/*!
				\brief The method serializes object's state into given stream

				\param[in, out] pWriter An output stream of data that writes information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Save(TDEngine2::IArchiveWriter* pWriter) override;

			/*!
				\brief The method creates a new deep copy of the instance and returns a smart pointer to it.
				The original state of the object stays the same

				\param[in] pDestObject A valid pointer to an object which the properties will be assigned into
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Clone(TDEngine2::IComponent*& pDestObject) const override;

	#if TDE2_EDITORS_ENABLED
			TDE2_API static void DrawInspectorGUI(const TDEngine2::TEditorContext& context);
	#endif
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CLevelBoundaries)
		public:
			TDEngine2::TRangeF32 mHorizontalConstraints = TDEngine2::TRangeF32(-4.0f, 4.0f);
			TDEngine2::TRangeF32 mVerticalConstraints = TDEngine2::TRangeF32(-5.0f, 4.0f);
	};


	/*!
		struct TLevelBoundariesParameters

		\brief The structure contains parameters for creation of CLevelBoundaries
	*/

	typedef struct TLevelBoundariesParameters : public TDEngine2::TBaseComponentParameters
	{
	} TLevelBoundariesParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(LevelBoundaries, TLevelBoundariesParameters);
}