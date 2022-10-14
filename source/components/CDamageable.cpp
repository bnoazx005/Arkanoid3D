#include "../../include/components/CDamageable.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CDamageable::CDamageable() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CDamageable::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CDamageable::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CDamageable::GetTypeId()));

		}
		pWriter->EndGroup();

		return RC_OK;
	}

#if TDE2_EDITORS_ENABLED

	void CDamageable::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Damageable", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CDamageable& component = dynamic_cast<CDamageable&>(editorContext.mComponent);

			/// \note Lifes count
			{
				I32 lifes = component.mLifes;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Lifes:");
				imguiContext.IntField("##Lifes", lifes, [&component, &lifes]() { component.mLifes = static_cast<U32>(lifes); });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateDamageable(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CDamageable, result);
	}


	/*!
		\brief CDamageableFactory's definition
	*/

	CDamageableFactory::CDamageableFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CDamageableFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateDamageable(result);
	}

	E_RESULT_CODE CDamageableFactory::SetupComponent(CDamageable* pComponent, const TDamageableParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateDamageableFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CDamageableFactory, result);
	}
}