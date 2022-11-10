#include "../../include/components/Bonuses.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	/*!
		CScoreBonus's definition
	*/

	CScoreBonus::CScoreBonus() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CScoreBonus::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mScoreToAdd = pReader->GetUInt32("score");

		return RC_OK;
	}

	E_RESULT_CODE CScoreBonus::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CScoreBonus::GetTypeId()));
			pWriter->SetUInt32("score", mScoreToAdd);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CScoreBonus::Clone(IComponent*& pDestObject) const
	{
		if (CScoreBonus* pBonus = dynamic_cast<CScoreBonus*>(pDestObject))
		{
			pBonus->mScoreToAdd = mScoreToAdd;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CScoreBonus::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("ScoreBonus", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CScoreBonus& component = dynamic_cast<CScoreBonus&>(editorContext.mComponent);

			/// \note score
			{
				I32 score = static_cast<I32>(component.mScoreToAdd);

				imguiContext.BeginHorizontal();
				imguiContext.Label("Score:");
				imguiContext.IntField("##Score", score, [&component, &score]() { component.mScoreToAdd = score; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateScoreBonus(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CScoreBonus, result);
	}


	/*!
		\brief CScoreBonusFactory's definition
	*/

	CScoreBonusFactory::CScoreBonusFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CScoreBonusFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateScoreBonus(result);
	}

	E_RESULT_CODE CScoreBonusFactory::SetupComponent(CScoreBonus* pComponent, const TScoreBonusParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateScoreBonusFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CScoreBonusFactory, result);
	}


	/*!
		class CScoreMultiplierBonus's definition
	*/

	CScoreMultiplierBonus::CScoreMultiplierBonus() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CScoreMultiplierBonus::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mValue = pReader->GetUInt32("multiplier");
		mEffectDuration = pReader->GetFloat("duration");

		return RC_OK;
	}

	E_RESULT_CODE CScoreMultiplierBonus::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CScoreMultiplierBonus::GetTypeId()));
			pWriter->SetUInt32("multiplier", mValue);
			pWriter->SetFloat("duration", mEffectDuration);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CScoreMultiplierBonus::Clone(IComponent*& pDestObject) const
	{
		if (CScoreMultiplierBonus* pBonus = dynamic_cast<CScoreMultiplierBonus*>(pDestObject))
		{
			pBonus->mValue = mValue;
			pBonus->mEffectDuration = mEffectDuration;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CScoreMultiplierBonus::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("ScoreMultiplierBonus", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CScoreMultiplierBonus& component = dynamic_cast<CScoreMultiplierBonus&>(editorContext.mComponent);

			/// \note score
			{
				I32 value = static_cast<I32>(component.mValue);

				imguiContext.BeginHorizontal();
				imguiContext.Label("Multiplier:");
				imguiContext.IntField("##Multiplier", value, [&component, &value]() { component.mValue = value; });
				imguiContext.EndHorizontal();
			}

			/// \note duration
			{
				F32 duration = component.mEffectDuration;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Duration:");
				imguiContext.FloatField("##Duration", duration, [&component, &duration]() { component.mEffectDuration = duration; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateScoreMultiplierBonus(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CScoreMultiplierBonus, result);
	}


	/*!
		\brief CScoreMultiplierBonusFactory's definition
	*/

	CScoreMultiplierBonusFactory::CScoreMultiplierBonusFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CScoreMultiplierBonusFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateScoreMultiplierBonus(result);
	}

	E_RESULT_CODE CScoreMultiplierBonusFactory::SetupComponent(CScoreMultiplierBonus* pComponent, const TScoreMultiplierBonusParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateScoreMultiplierBonusFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CScoreMultiplierBonusFactory, result);
	}


	/*!
		class CGodModeBonus's definition
	*/

	CGodModeBonus::CGodModeBonus() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CGodModeBonus::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mEffectDuration = pReader->GetFloat("duration");

		return RC_OK;
	}

	E_RESULT_CODE CGodModeBonus::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CGodModeBonus::GetTypeId()));
			pWriter->SetFloat("duration", mEffectDuration);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CGodModeBonus::Clone(IComponent*& pDestObject) const
	{
		if (CGodModeBonus* pBonus = dynamic_cast<CGodModeBonus*>(pDestObject))
		{
			pBonus->mEffectDuration = mEffectDuration;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CGodModeBonus::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("GodModeBonus", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CGodModeBonus& component = dynamic_cast<CGodModeBonus&>(editorContext.mComponent);

			/// \note duration
			{
				F32 duration = component.mEffectDuration;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Duration:");
				imguiContext.FloatField("##Duration", duration, [&component, &duration]() { component.mEffectDuration = duration; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateGodModeBonus(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CGodModeBonus, result);
	}


	/*!
		\brief CGodModeBonusFactory's definition
	*/

	CGodModeBonusFactory::CGodModeBonusFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CGodModeBonusFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateGodModeBonus(result);
	}

	E_RESULT_CODE CGodModeBonusFactory::SetupComponent(CGodModeBonus* pComponent, const TGodModeBonusParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateGodModeBonusFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CGodModeBonusFactory, result);
	}


	/*!
		class CExpandPaddleBonus's definition
	*/

	CExpandPaddleBonus::CExpandPaddleBonus() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CExpandPaddleBonus::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		mEffectDuration = pReader->GetFloat("duration");
		mExpandCoefficient = pReader->GetFloat("expand_coeff");

		return RC_OK;
	}

	E_RESULT_CODE CExpandPaddleBonus::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CExpandPaddleBonus::GetTypeId()));
			pWriter->SetFloat("duration", mEffectDuration);
			pWriter->SetFloat("expand_coeff", mExpandCoefficient);
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CExpandPaddleBonus::Clone(IComponent*& pDestObject) const
	{
		if (CExpandPaddleBonus* pBonus = dynamic_cast<CExpandPaddleBonus*>(pDestObject))
		{
			pBonus->mEffectDuration = mEffectDuration;
			pBonus->mExpandCoefficient = mExpandCoefficient;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CExpandPaddleBonus::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("ExpandPaddleBonus", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CExpandPaddleBonus& component = dynamic_cast<CExpandPaddleBonus&>(editorContext.mComponent);

			/// \note duration
			{
				F32 duration = component.mEffectDuration;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Duration:");
				imguiContext.FloatField("##Duration", duration, [&component, &duration]() { component.mEffectDuration = duration; });
				imguiContext.EndHorizontal();
			}

			/// \note expandCoeff
			{
				F32 expandCoeff = component.mExpandCoefficient;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Expand Coeff:");
				imguiContext.FloatField("##expandCoeff", expandCoeff, [&component, &expandCoeff]() { component.mExpandCoefficient = expandCoeff; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateExpandPaddleBonus(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CExpandPaddleBonus, result);
	}


	/*!
		\brief CExpandPaddleBonusFactory's definition
	*/

	CExpandPaddleBonusFactory::CExpandPaddleBonusFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CExpandPaddleBonusFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateExpandPaddleBonus(result);
	}

	E_RESULT_CODE CExpandPaddleBonusFactory::SetupComponent(CExpandPaddleBonus* pComponent, const TExpandPaddleBonusParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateExpandPaddleBonusFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CExpandPaddleBonusFactory, result);
	}


	/*!
		class CStickyPaddleBonus's definition
	*/

	CStickyPaddleBonus::CStickyPaddleBonus() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CStickyPaddleBonus::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		return RC_OK;
	}

	E_RESULT_CODE CStickyPaddleBonus::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CStickyPaddleBonus::GetTypeId()));
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CStickyPaddleBonus::Clone(IComponent*& pDestObject) const
	{
		if (CStickyPaddleBonus* pBonus = dynamic_cast<CStickyPaddleBonus*>(pDestObject))
		{
			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CStickyPaddleBonus::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("StickyPaddleBonus", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CStickyPaddleBonus& component = dynamic_cast<CStickyPaddleBonus&>(editorContext.mComponent);

		});
	}

#endif


	IComponent* CreateStickyPaddleBonus(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CStickyPaddleBonus, result);
	}


	/*!
		\brief CStickyPaddleBonusFactory's definition
	*/

	CStickyPaddleBonusFactory::CStickyPaddleBonusFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CStickyPaddleBonusFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateStickyPaddleBonus(result);
	}

	E_RESULT_CODE CStickyPaddleBonusFactory::SetupComponent(CStickyPaddleBonus* pComponent, const TStickyPaddleBonusParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}

		return RC_OK;
	}


	IComponentFactory* CreateStickyPaddleBonusFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CStickyPaddleBonusFactory, result);
	}
}