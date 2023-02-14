#include "../../include/components/UIComponents.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	/*!
		CMainMenuPanel's definition
	*/

	struct TMainMenuPanelArchiveKeys
	{
		static const std::string mPlayButtonEntityIdKey;
	};

	const std::string TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey = "play_button_entity_id";


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

		mPlayButtonEntityId = static_cast<TEntityId>(pReader->GetUInt32(TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey, static_cast<U32>(TEntityId::Invalid)));

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
			
			pWriter->SetUInt32(TMainMenuPanelArchiveKeys::mPlayButtonEntityIdKey, static_cast<U32>(mPlayButtonEntityId));
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CMainMenuPanel::PostLoad(CEntityManager* pEntityManager, const TEntitiesMapper& entitiesIdentifiersRemapper)
	{
		auto it = entitiesIdentifiersRemapper.find(mPlayButtonEntityId);
		if (it != entitiesIdentifiersRemapper.cend())
		{
			mPlayButtonEntityId = it->second;
		}

		return CBaseComponent::PostLoad(pEntityManager, entitiesIdentifiersRemapper);
	}

	E_RESULT_CODE CMainMenuPanel::Clone(IComponent*& pDestObject) const
	{
		if (CMainMenuPanel* pObject = dynamic_cast<CMainMenuPanel*>(pDestObject))
		{
			pObject->mPlayButtonEntityId = mPlayButtonEntityId;

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

			/// play button entity id
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Play Button EntityId: ");

				CImGUIExtensions::EntityRefField(
					MakeScopedFromRawPtr<IImGUIContext>(&imguiContext),
					MakeScopedFromRawPtr<IWorld>(&editorContext.mWorld), 
					Wrench::StringUtils::GetEmptyStr(), 
					component.mPlayButtonEntityId);

				imguiContext.EndHorizontal();
			}
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