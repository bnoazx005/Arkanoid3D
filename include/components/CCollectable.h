/*!
	\file CCollectable.h
	\date 28.10.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateCollectable(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CCollectable
	*/

	class CCollectable : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CCollectable, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateCollectable(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CCollectable)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCollectable)
		public:
	};


	/*!
		struct TCollectableParameters

		\brief The structure contains parameters for creation of CCollectable
	*/

	typedef struct TCollectableParameters : public TDEngine2::TBaseComponentParameters
	{
	} TCollectableParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(Collectable, TCollectableParameters);
}