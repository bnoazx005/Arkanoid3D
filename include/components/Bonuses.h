/*!
	\file Bonuses.h
	\date 06.11.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateScoreBonus(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CScoreBonus
	*/

	class CScoreBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CScoreBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateScoreBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CScoreBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CScoreBonus)
		public:
			TDEngine2::U32 mScoreToAdd = 0;
	};


	/*!
		struct TScoreBonusParameters

		\brief The structure contains parameters for creation of CScoreBonus
	*/

	typedef struct TScoreBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TScoreBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(ScoreBonus, TScoreBonusParameters);


	/*!
		class CScoreMultiplierBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateScoreMultiplierBonus(TDEngine2::E_RESULT_CODE& result);


	class CScoreMultiplierBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CScoreBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateScoreMultiplierBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CScoreMultiplierBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CScoreMultiplierBonus)
		public:
			TDEngine2::U32 mValue = 1;
			TDEngine2::F32 mEffectDuration = 1.0f;
	};


	/*!
		struct TScoreMultiplierBonusParameters

		\brief The structure contains parameters for creation of ScoreMultiplierBonus
	*/

	typedef struct TScoreMultiplierBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TScoreMultiplierBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(ScoreMultiplierBonus, TScoreMultiplierBonusParameters);


	/*!
		class CGodModeBonus

		The bonus that doesn't allow to fail when a ball is missed 
	*/

	TDE2_API TDEngine2::IComponent* CreateGodModeBonus(TDEngine2::E_RESULT_CODE& result);


	class CGodModeBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CScoreBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateGodModeBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CGodModeBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CGodModeBonus)
		public:
			TDEngine2::F32 mEffectDuration = 1.0f;
	};


	/*!
		struct TGodModeBonusParameters

		\brief The structure contains parameters for creation of GodModeBonus
	*/

	typedef struct TGodModeBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TGodModeBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(GodModeBonus, TGodModeBonusParameters);
}