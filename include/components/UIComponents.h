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
			TDEngine2::TEntityId mResumeButtonEntityId = TDEngine2::TEntityId::Invalid;
			TDEngine2::TEntityId mRestartButtonEntityId = TDEngine2::TEntityId::Invalid;
			TDEngine2::TEntityId mExitToMenuButtonEntityId = TDEngine2::TEntityId::Invalid;
	};


	/*!
		struct TPauseMenuPanelParameters

		\brief The structure contains parameters for creation of CPauseMenuPanel
	*/

	typedef struct TPauseMenuPanelParameters : public TDEngine2::TBaseComponentParameters
	{
	} TPauseMenuPanelParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(PauseMenuPanel, TPauseMenuPanelParameters);
}