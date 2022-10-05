#include "../../include/components/CLevelInfo.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CLevelInfo::CLevelInfo() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CLevelInfo::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CLevelInfo::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CLevelInfo::GetTypeId()));

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CLevelInfo::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("LevelInfo", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CLevelInfo& component = dynamic_cast<CLevelInfo&>(editorContext.mComponent);

			///// \note Speed of the LevelInfo
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


	IComponent* CreateLevelInfo(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CLevelInfo, result);
	}


	/*!
		\brief CLevelInfoFactory's definition
	*/

	CLevelInfoFactory::CLevelInfoFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CLevelInfoFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateLevelInfo(result);
	}

	E_RESULT_CODE CLevelInfoFactory::SetupComponent(CLevelInfo* pComponent, const TLevelInfoParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateLevelInfoFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CLevelInfoFactory, result);
	}
}