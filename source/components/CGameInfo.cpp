#include "../../include/components/CGameInfo.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CGameInfo::CGameInfo() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CGameInfo::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CGameInfo::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CGameInfo::GetTypeId()));

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CGameInfo::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("GameInfo", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CGameInfo& component = dynamic_cast<CGameInfo&>(editorContext.mComponent);

			///// \note Speed of the GameInfo
			//{
			//	F32 speed = component.mSpeed;

			//	imguiContext.BeginHorizontal();
			//	imguiContext.Label("Speed:");
			//	imguiContext.FloatField("##Speed", speed, [&component, &speed]() { component.mSpeed = speed; });
			//	imguiContext.EndHorizontal();
			//}
		});
	}

#endif


	IComponent* CreateGameInfo(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CGameInfo, result);
	}


	/*!
		\brief CGameInfoFactory's definition
	*/

	CGameInfoFactory::CGameInfoFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CGameInfoFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateGameInfo(result);
	}

	E_RESULT_CODE CGameInfoFactory::SetupComponent(CGameInfo* pComponent, const TGameInfoParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateGameInfoFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CGameInfoFactory, result);
	}
}