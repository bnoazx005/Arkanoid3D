#include "../include/Components.h"
#include "../include/components/CPaddle.h"
#include "../include/components/CBrick.h"
#include "../include/components/CBall.h"
#include "../include/components/CLevelInfo.h"
#include "../include/components/CDamageable.h"
#include "../include/components/CGravitable.h"
#include "../include/components/Bonuses.h"

namespace TDEngine2
{
	using namespace Game;
	TDE2_REGISTER_UNIQUE_COMPONENT(CLevelInfo);
}

namespace Game
{
	//TDE2_DEFINE_FLAG_COMPONENT(Paddle)

	TDEngine2::E_RESULT_CODE RegisterGameComponents(TDEngine2::TPtr<TDEngine2::IWorld> pWorld
#if TDE2_EDITORS_ENABLED
		, TDEngine2::TPtr<TDEngine2::IEditorsManager> pEditorsManager
#endif 
	)
	{
		TDEngine2::E_RESULT_CODE result = TDEngine2::RC_OK;

		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreatePaddleFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateBrickFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateBallFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateLevelInfoFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateDamageableFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateGravitableFactory(result)));

		/// bonuses
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateScoreBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateScoreMultiplierBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateGodModeBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateExpandPaddleBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateStickyPaddleBonusFactory(result)));

#if TDE2_EDITORS_ENABLED
		result = result | pEditorsManager->RegisterComponentInspector(CPaddle::GetTypeId(), CPaddle::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CBrick::GetTypeId(), CBrick::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CBall::GetTypeId(), CBall::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CLevelInfo::GetTypeId(), CLevelInfo::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CDamageable::GetTypeId(), CDamageable::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CGravitable::GetTypeId(), CGravitable::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CScoreBonus::GetTypeId(), CScoreBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CScoreMultiplierBonus::GetTypeId(), CScoreMultiplierBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CGodModeBonus::GetTypeId(), CGodModeBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CExpandPaddleBonus::GetTypeId(), CExpandPaddleBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CStickyPaddleBonus::GetTypeId(), CStickyPaddleBonus::DrawInspectorGUI);

		/// \todo Register inspectors for the components here
#endif

		return result;
	}
}