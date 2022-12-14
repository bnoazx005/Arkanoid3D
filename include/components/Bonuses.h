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


	/*!
		class CExpandPaddleBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateExpandPaddleBonus(TDEngine2::E_RESULT_CODE& result);


	class CExpandPaddleBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CScoreBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateExpandPaddleBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CExpandPaddleBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CExpandPaddleBonus)
		public:
			TDEngine2::F32 mExpandCoefficient = 1.2f;
			TDEngine2::F32 mEffectDuration = 1.0f;
	};


	/*!
		struct TExpandPaddleBonusParameters

		\brief The structure contains parameters for creation of ExpandPaddleBonus
	*/

	typedef struct TExpandPaddleBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TExpandPaddleBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(ExpandPaddleBonus, TExpandPaddleBonusParameters);


	/*!
		class CStickyPaddleBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateStickyPaddleBonus(TDEngine2::E_RESULT_CODE& result);


	class CStickyPaddleBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CScoreBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateStickyPaddleBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CStickyPaddleBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CStickyPaddleBonus)
		public:
	};


	/*!
		struct TStickyPaddleBonusParameters

		\brief The structure contains parameters for creation of StickyPaddleBonus
	*/

	typedef struct TStickyPaddleBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TStickyPaddleBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(StickyPaddleBonus, TStickyPaddleBonusParameters);


	/*!
		class CExtraLifeBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateExtraLifeBonus(TDEngine2::E_RESULT_CODE& result);


	class CExtraLifeBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CExtraLifeBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateExtraLifeBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CExtraLifeBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CExtraLifeBonus)
		public:
	};


	/*!
		struct TExtraLifeBonusParameters

		\brief The structure contains parameters for creation of ExtraLifeBonus
	*/

	typedef struct TExtraLifeBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TExtraLifeBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(ExtraLifeBonus, TExtraLifeBonusParameters);


	/*!
		class CLaserBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateLaserBonus(TDEngine2::E_RESULT_CODE& result);


	class CLaserBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CLaserBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateLaserBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CLaserBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CLaserBonus)
		public:
			TDEngine2::F32 mEffectDuration = 1.0f;
	};


	/*!
		struct TLaserBonusParameters

		\brief The structure contains parameters for creation of LaserBonus
	*/

	typedef struct TLaserBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TLaserBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(LaserBonus, TLaserBonusParameters);


	/*!
		class CMultipleBallsBonus
	*/

	TDE2_API TDEngine2::IComponent* CreateMultipleBallsBonus(TDEngine2::E_RESULT_CODE& result);


	class CMultipleBallsBonus : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CMultipleBallsBonus, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateMultipleBallsBonus(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CMultipleBallsBonus)

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CMultipleBallsBonus)
		public:
			TDEngine2::U32 mBallsCount = 3;
	};


	/*!
		struct TMultipleBallsBonusParameters

		\brief The structure contains parameters for creation of MultipleBallsBonus
	*/

	typedef struct TMultipleBallsBonusParameters : public TDEngine2::TBaseComponentParameters
	{
	} TMultipleBallsBonusParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(MultipleBallsBonus, TMultipleBallsBonusParameters);
}