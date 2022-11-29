#include "../../include/components/CBrick.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CBrick::CBrick() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CBrick::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mPowerUpPrefabId = pReader->GetString("bonus_prefab_id");
		mSpawnProbability = pReader->GetFloat("spawn_probability");

		return RC_OK;
	}

	E_RESULT_CODE CBrick::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CBrick::GetTypeId()));
			pWriter->SetString("bonus_prefab_id", mPowerUpPrefabId);
			pWriter->SetFloat("spawn_probability", mSpawnProbability);

		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CBrick::Clone(IComponent*& pDestObject) const
	{
		if (CBrick* pBonus = dynamic_cast<CBrick*>(pDestObject))
		{
			pBonus->mPowerUpPrefabId = mPowerUpPrefabId;
			pBonus->mSpawnProbability = mSpawnProbability;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CBrick::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Brick", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CBrick& component = dynamic_cast<CBrick&>(editorContext.mComponent);

			/// \note Spawn probability
			{
				std::string prefabId = component.mPowerUpPrefabId;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Power Up Prefab Id:");
				imguiContext.TextField("##PowerUpPrefabId", prefabId, [&component](auto&& value) { component.mPowerUpPrefabId = value; });
				imguiContext.EndHorizontal();
			}

			/// \note Spawn probability
			{
				F32 probability = component.mSpawnProbability;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Spawn Probability:");
				imguiContext.FloatField("##SpawnProbability", probability, [&component, &probability]() { component.mSpawnProbability = probability; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateBrick(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CBrick, result);
	}


	/*!
		\brief CBrickFactory's definition
	*/

	CBrickFactory::CBrickFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CBrickFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateBrick(result);
	}

	E_RESULT_CODE CBrickFactory::SetupComponent(CBrick* pComponent, const TBrickParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateBrickFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CBrickFactory, result);
	}
}