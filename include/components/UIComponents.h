/*!
	\file UIComponents.h
	\date 13.02.2023
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateMainMenuPanel(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CMainMenuPanel
	*/

	class CMainMenuPanel : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CMainMenuPanel, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateMainMenuPanel(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CMainMenuPanel)

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
				\brief The method is called after all entities of particular scene were loaded. It remaps all identifiers to
				make them correctly corresponds to saved state

				\param[in, out] pEntityManager A pointer to entities manager
				\param[in] entitiesIdentifiersRemapper A structure that maps saved identifier to current runtime equivalent
			*/

			TDE2_API TDEngine2::E_RESULT_CODE PostLoad(TDEngine2::CEntityManager* pEntityManager, const TDEngine2::TEntitiesMapper& entitiesIdentifiersRemapper) override;

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CMainMenuPanel)
		public:
			TDEngine2::CEntityRef mPlayButtonEntityId;
			TDEngine2::CEntityRef mSettingsButtonEntityId;
			TDEngine2::CEntityRef mCreditsButtonEntityId;
			TDEngine2::CEntityRef mQuitButtonEntityId;
	};


	/*!
		struct TMainMenuPanelParameters

		\brief The structure contains parameters for creation of CMainMenuPanel
	*/

	typedef struct TMainMenuPanelParameters : public TDEngine2::TBaseComponentParameters
	{
	} TMainMenuPanelParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(MainMenuPanel, TMainMenuPanelParameters);


	TDE2_API TDEngine2::IComponent* CreatePauseMenuPanel(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CPauseMenuPanel
	*/

	class CPauseMenuPanel : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CPauseMenuPanel, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreatePauseMenuPanel(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CPauseMenuPanel)

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
				\brief The method is called after all entities of particular scene were loaded. It remaps all identifiers to
				make them correctly corresponds to saved state

				\param[in, out] pEntityManager A pointer to entities manager
				\param[in] entitiesIdentifiersRemapper A structure that maps saved identifier to current runtime equivalent
			*/

			TDE2_API TDEngine2::E_RESULT_CODE PostLoad(TDEngine2::CEntityManager* pEntityManager, const TDEngine2::TEntitiesMapper& entitiesIdentifiersRemapper) override;

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CPauseMenuPanel)
		public:
			TDEngine2::CEntityRef mResumeButtonEntityId;
			TDEngine2::CEntityRef mRestartButtonEntityId;
			TDEngine2::CEntityRef mExitToMenuButtonEntityId;
	};


	/*!
		struct TPauseMenuPanelParameters

		\brief The structure contains parameters for creation of CPauseMenuPanel
	*/

	typedef struct TPauseMenuPanelParameters : public TDEngine2::TBaseComponentParameters
	{
	} TPauseMenuPanelParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(PauseMenuPanel, TPauseMenuPanelParameters);


	/*!
		class COptionsMenuPanel
	*/

	class COptionsMenuPanel : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<COptionsMenuPanel, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateOptionsMenuPanel(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(COptionsMenuPanel)

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
				\brief The method is called after all entities of particular scene were loaded. It remaps all identifiers to
				make them correctly corresponds to saved state

				\param[in, out] pEntityManager A pointer to entities manager
				\param[in] entitiesIdentifiersRemapper A structure that maps saved identifier to current runtime equivalent
			*/

			TDE2_API TDEngine2::E_RESULT_CODE PostLoad(TDEngine2::CEntityManager* pEntityManager, const TDEngine2::TEntitiesMapper& entitiesIdentifiersRemapper) override;

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(COptionsMenuPanel)
		public:
			TDEngine2::CEntityRef mBackButtonEntityId;
	};


	/*!
		struct TOptionsMenuPanelParameters

		\brief The structure contains parameters for creation of COptionsMenuPanel
	*/

	typedef struct TOptionsMenuPanelParameters : public TDEngine2::TBaseComponentParameters
	{
	} TOptionsMenuPanelParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(OptionsMenuPanel, TOptionsMenuPanelParameters);


	/*!
		class CCreditsMenuPanel
	*/

	class CCreditsMenuPanel : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CCreditsMenuPanel, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateCreditsMenuPanel(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CCreditsMenuPanel)

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
				\brief The method is called after all entities of particular scene were loaded. It remaps all identifiers to
				make them correctly corresponds to saved state

				\param[in, out] pEntityManager A pointer to entities manager
				\param[in] entitiesIdentifiersRemapper A structure that maps saved identifier to current runtime equivalent
			*/

			TDE2_API TDEngine2::E_RESULT_CODE PostLoad(TDEngine2::CEntityManager* pEntityManager, const TDEngine2::TEntitiesMapper& entitiesIdentifiersRemapper) override;

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
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCreditsMenuPanel)
		public:
			TDEngine2::CEntityRef mBackButtonEntityId;
	};


	/*!
		struct TCreditsMenuPanelParameters

		\brief The structure contains parameters for creation of CCreditsMenuPanel
	*/

	typedef struct TCreditsMenuPanelParameters : public TDEngine2::TBaseComponentParameters
	{
	} TCreditsMenuPanelParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(CreditsMenuPanel, TCreditsMenuPanelParameters);
}