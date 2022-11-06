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

		}
		pWriter->EndGroup();

		return RC_OK;
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
				F32 score = component.mScoreToAdd;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Score:");
				imguiContext.FloatField("##Score", score, [&component, &score]() { component.mScoreToAdd = score; });
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
}