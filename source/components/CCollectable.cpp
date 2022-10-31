#include "../../include/components/CCollectable.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CCollectable::CCollectable() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CCollectable::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CCollectable::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CCollectable::GetTypeId()));

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CCollectable::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Collectable", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CCollectable& component = dynamic_cast<CCollectable&>(editorContext.mComponent);

			///// \note Speed of the Collectable
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


	IComponent* CreateCollectable(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CCollectable, result);
	}


	/*!
		\brief CCollectableFactory's definition
	*/

	CCollectableFactory::CCollectableFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CCollectableFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateCollectable(result);
	}

	E_RESULT_CODE CCollectableFactory::SetupComponent(CCollectable* pComponent, const TCollectableParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateCollectableFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CCollectableFactory, result);
	}
}