/*!
	\file CBrick.h
	\date 01.09.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateBrick(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CBrick
	*/

	class CBrick : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CBrick, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateBrick(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CBrick)

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

	#if TDE2_EDITORS_ENABLED
			TDE2_API static void DrawInspectorGUI(const TDEngine2::TEditorContext& context);
	#endif
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CBrick)
		public:
	};


	/*!
		struct TBrickParameters

		\brief The structure contains parameters for creation of CBrick
	*/

	typedef struct TBrickParameters : public TDEngine2::TBaseComponentParameters
	{
	} TBrickParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(Brick, TBrickParameters);
}