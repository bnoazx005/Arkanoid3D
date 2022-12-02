#include "../../include/components/CDamageable.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	struct TDamageableArchiveKeys
	{
		static const std::string mLifesKeyId;
		static const std::string mRewardScoreKeyId;
		static const std::string mConstantKeyId;
	};

	const std::string TDamageableArchiveKeys::mLifesKeyId = "lifes";
	const std::string TDamageableArchiveKeys::mRewardScoreKeyId = "score";
	const std::string TDamageableArchiveKeys::mConstantKeyId = "is_constant";


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

		mLifes = pReader->GetUInt32(TDamageableArchiveKeys::mLifesKeyId, 1);
		mRewardScore = pReader->GetUInt32(TDamageableArchiveKeys::mRewardScoreKeyId, 1);
		mIsConstant = pReader->GetBool(TDamageableArchiveKeys::mConstantKeyId);

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
			pWriter->SetUInt32(TDamageableArchiveKeys::mLifesKeyId, mLifes);
			pWriter->SetUInt32(TDamageableArchiveKeys::mRewardScoreKeyId, mRewardScore);
			pWriter->SetBool(TDamageableArchiveKeys::mConstantKeyId, mIsConstant);

		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CDamageable::Clone(IComponent*& pDestObject) const
	{
		if (CDamageable* pObj = dynamic_cast<CDamageable*>(pDestObject))
		{
			pObj->mLifes = mLifes;
			pObj->mRewardScore = mRewardScore;
			pObj->mIsConstant = mIsConstant;

			return RC_OK;
		}

		return RC_FAIL;
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

			/// \note reward score
			{
				I32 reward = component.mRewardScore;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Reward Score:");
				imguiContext.IntField("##RewardScore", reward, [&component, &reward]() { component.mRewardScore = static_cast<U32>(reward); });
				imguiContext.EndHorizontal();
			}

			/// \note Is constant
			{
				imguiContext.BeginHorizontal();
				imguiContext.Label("Is Constant:");
				imguiContext.Checkbox("##IsConst", component.mIsConstant);
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