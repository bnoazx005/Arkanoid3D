#include "../../include/components/UIComponents.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	/*!
		CMainMenuPanel's definition
	*/

	CMainMenuPanel::CMainMenuPanel() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CMainMenuPanel::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CMainMenuPanel::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CMainMenuPanel::GetTypeId()));
			
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CMainMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (CMainMenuPanel* pBonus = dynamic_cast<CMainMenuPanel*>(pDestObject))
		{
			

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CMainMenuPanel::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("MainMenuPanel", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CMainMenuPanel& component = dynamic_cast<CMainMenuPanel&>(editorContext.mComponent);

		});
	}

#endif


	IComponent* CreateMainMenuPanel(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CMainMenuPanel, result);
	}


	/*!
		\brief CMainMenuPanelFactory's definition
	*/

	CMainMenuPanelFactory::CMainMenuPanelFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CMainMenuPanelFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateMainMenuPanel(result);
	}

	E_RESULT_CODE CMainMenuPanelFactory::SetupComponent(CMainMenuPanel* pComponent, const TMainMenuPanelParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateMainMenuPanelFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CMainMenuPanelFactory, result);
	}
}