#include "../../include/components/CGravitable.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CGravitable::CGravitable() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CGravitable::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CGravitable::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CGravitable::GetTypeId()));

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CGravitable::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Gravitable", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CGravitable& component = dynamic_cast<CGravitable&>(editorContext.mComponent);

			///// \note Speed of the Gravitable
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


	IComponent* CreateGravitable(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CGravitable, result);
	}


	/*!
		\brief CGravitableFactory's definition
	*/

	CGravitableFactory::CGravitableFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CGravitableFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateGravitable(result);
	}

	E_RESULT_CODE CGravitableFactory::SetupComponent(CGravitable* pComponent, const TGravitableParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateGravitableFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CGravitableFactory, result);
	}
}