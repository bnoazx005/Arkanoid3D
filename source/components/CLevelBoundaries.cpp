#include "../../include/components/CLevelBoundaries.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CLevelBoundaries::CLevelBoundaries() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CLevelBoundaries::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}

		E_RESULT_CODE result = RC_OK;

		pReader->BeginGroup("horizontal_constraints");
		
		auto horConstraintsResult = LoadVector2(pReader);
		if (horConstraintsResult.HasError())
		{
			result = result | horConstraintsResult.GetError();
		}

		const TVector2 horConstraints = horConstraintsResult.Get();
		mHorizontalConstraints = TRangeF32(horConstraints.x, horConstraints.y);

		pReader->EndGroup();

		pReader->BeginGroup("vertical_constraints");		

		auto vertConstraintsResult = LoadVector2(pReader);
		if (vertConstraintsResult.HasError())
		{
			result = result | vertConstraintsResult.GetError();
		}

		const TVector2 vertConstraints = vertConstraintsResult.Get();
		mVerticalConstraints = TRangeF32(vertConstraints.x, vertConstraints.y);

		pReader->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CLevelBoundaries::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CLevelBoundaries::GetTypeId()));
			
			pWriter->BeginGroup("horizontal_constraints");
			SaveVector2(pWriter, TVector2(mHorizontalConstraints.mLeft, mHorizontalConstraints.mRight));
			pWriter->EndGroup();

			pWriter->BeginGroup("vertical_constraints"); 
			SaveVector2(pWriter, TVector2(mVerticalConstraints.mLeft, mVerticalConstraints.mRight));
			pWriter->EndGroup();
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CLevelBoundaries::Clone(IComponent*& pDestObject) const
	{
		if (auto pComponent = dynamic_cast<CLevelBoundaries*>(pDestObject))
		{
			pComponent->mHorizontalConstraints = mHorizontalConstraints;
			pComponent->mVerticalConstraints = mVerticalConstraints;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CLevelBoundaries::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("LevelBoundaries", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CLevelBoundaries& component = dynamic_cast<CLevelBoundaries&>(editorContext.mComponent);

			/// \note Horizontal constraints
			{
				TVector2 horConstraints = TVector2(component.mHorizontalConstraints.mLeft, component.mHorizontalConstraints.mRight);

				imguiContext.BeginHorizontal();
				imguiContext.Label("Hor Constraints:");
				imguiContext.Vector2Field("##HorConstraints", horConstraints, [&component, &horConstraints]() 
				{ 
					component.mHorizontalConstraints = TRangeF32(horConstraints.x, horConstraints.y);
				});
				imguiContext.EndHorizontal();
			}

			/// \note Vertical constraints
			{
				TVector2 vertConstraints = TVector2(component.mVerticalConstraints.mLeft, component.mVerticalConstraints.mRight);

				imguiContext.BeginHorizontal();
				imguiContext.Label("Vert Constraints:");
				imguiContext.Vector2Field("##VertConstraints", vertConstraints, [&component, &vertConstraints]()
				{
					component.mVerticalConstraints = TRangeF32(vertConstraints.x, vertConstraints.y);
				});
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateLevelBoundaries(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CLevelBoundaries, result);
	}


	/*!
		\brief CLevelBoundariesFactory's definition
	*/

	CLevelBoundariesFactory::CLevelBoundariesFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CLevelBoundariesFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateLevelBoundaries(result);
	}

	E_RESULT_CODE CLevelBoundariesFactory::SetupComponent(CLevelBoundaries* pComponent, const TLevelBoundariesParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateLevelBoundariesFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CLevelBoundariesFactory, result);
	}
}