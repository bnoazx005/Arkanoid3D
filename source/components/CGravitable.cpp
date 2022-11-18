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

		mMass = pReader->GetFloat("mass", 1.0f);

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
			pWriter->SetFloat("mass", mMass);

		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CGravitable::Clone(IComponent*& pDestObject) const
	{
		if (auto pComponent = dynamic_cast<CGravitable*>(pDestObject))
		{
			pComponent->mMass = mMass;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CGravitable::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Gravitable", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CGravitable& component = dynamic_cast<CGravitable&>(editorContext.mComponent);

			/// \note Mass
			{
				F32 mass = component.mMass;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Mass:");
				imguiContext.FloatField("##Mass", mass, [&component, &mass]() { component.mMass = mass; });
				imguiContext.EndHorizontal();
			}
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