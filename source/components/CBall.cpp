#include "../../include/components/CBall.h"
#include <editor/Inspectors.h>
#include <core/IImGUIContext.h>


namespace Game
{
	using namespace TDEngine2;


	CBall::CBall() :
		CBaseComponent()
	{
	}

	E_RESULT_CODE CBall::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_FAIL;
		}


		return RC_OK;
	}

	E_RESULT_CODE CBall::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_FAIL;
		}

		pWriter->BeginGroup("component");
		{
			pWriter->SetUInt32("type_id", static_cast<U32>(CBall::GetTypeId()));
			pWriter->SetFloat("speed", mSpeed);

		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CBall::Clone(IComponent*& pDestObject) const
	{
		if (auto pComponent = dynamic_cast<CBall*>(pDestObject))
		{
			pComponent->mDirection = mDirection;
			pComponent->mIsMoving = mIsMoving;
			pComponent->mSpeed = mSpeed;

			return RC_OK;
		}

		return RC_FAIL;
	}

#if TDE2_EDITORS_ENABLED

	void CBall::DrawInspectorGUI(const TEditorContext& context)
	{
		CDefaultInspectorsRegistry::DrawInspectorHeader("Ball", context, [](const TEditorContext& editorContext)
		{
			IImGUIContext& imguiContext = editorContext.mImGUIContext;
			CBall& component = dynamic_cast<CBall&>(editorContext.mComponent);

			/// \note Speed of the Ball
			{
				F32 speed = component.mSpeed;

				imguiContext.BeginHorizontal();
				imguiContext.Label("Speed:");
				imguiContext.FloatField("##Speed", speed, [&component, &speed]() { component.mSpeed = speed; });
				imguiContext.EndHorizontal();
			}
		});
	}

#endif


	IComponent* CreateBall(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponent, CBall, result);
	}


	/*!
		\brief CBallFactory's definition
	*/

	CBallFactory::CBallFactory() :
		CBaseComponentFactory()
	{
	}

	IComponent* CBallFactory::CreateDefault() const
	{
		E_RESULT_CODE result = RC_OK;
		return CreateBall(result);
	}

	E_RESULT_CODE CBallFactory::SetupComponent(CBall* pComponent, const TBallParameters& params) const
	{
		if (!pComponent)
		{
			return RC_INVALID_ARGS;
		}



		return RC_OK;
	}


	IComponentFactory* CreateBallFactory(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IComponentFactory, CBallFactory, result);
	}
}