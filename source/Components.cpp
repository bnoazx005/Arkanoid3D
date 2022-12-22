#include "../include/Components.h"
#include "../include/components/CPaddle.h"
#include "../include/components/CBrick.h"
#include "../include/components/CBall.h"
#include "../include/components/CGameInfo.h"
#include "../include/components/CDamageable.h"
#include "../include/components/CGravitable.h"
#include "../include/components/Bonuses.h"
#include "../include/components/CLevelSettings.h"

namespace TDEngine2
{
	using namespace Game;
	TDE2_REGISTER_UNIQUE_COMPONENT(CGameInfo);
}

namespace Game
{
	TDE2_DEFINE_FLAG_COMPONENT(Projectile)
	TDE2_DEFINE_FLAG_COMPONENT(PlayerPositioner)

	TDE2_DEFINE_FLAG_COMPONENT(LivesLabel)
	TDE2_DEFINE_FLAG_COMPONENT(ScoreLabel)


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
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateGameInfoFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateDamageableFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateGravitableFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateProjectileFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreatePlayerPositionerFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateLevelSettingsFactory(result)));

		/// bonuses
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateScoreBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateScoreMultiplierBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateGodModeBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateExpandPaddleBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateStickyPaddleBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateExtraLifeBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateLaserBonusFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateMultipleBallsBonusFactory(result)));
		
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateLivesLabelFactory(result)));
		result = result | pWorld->RegisterComponentFactory(TDEngine2::TPtr<TDEngine2::IComponentFactory>(CreateScoreLabelFactory(result)));

#if TDE2_EDITORS_ENABLED
		result = result | pEditorsManager->RegisterComponentInspector(CPaddle::GetTypeId(), CPaddle::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CBrick::GetTypeId(), CBrick::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CBall::GetTypeId(), CBall::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CGameInfo::GetTypeId(), CGameInfo::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CDamageable::GetTypeId(), CDamageable::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CGravitable::GetTypeId(), CGravitable::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CLevelSettings::GetTypeId(), CLevelSettings::DrawInspectorGUI);

		result = result | pEditorsManager->RegisterComponentInspector(CScoreBonus::GetTypeId(), CScoreBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CScoreMultiplierBonus::GetTypeId(), CScoreMultiplierBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CGodModeBonus::GetTypeId(), CGodModeBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CExpandPaddleBonus::GetTypeId(), CExpandPaddleBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CStickyPaddleBonus::GetTypeId(), CStickyPaddleBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CExtraLifeBonus::GetTypeId(), CExtraLifeBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CLaserBonus::GetTypeId(), CLaserBonus::DrawInspectorGUI);
		result = result | pEditorsManager->RegisterComponentInspector(CMultipleBallsBonus::GetTypeId(), CMultipleBallsBonus::DrawInspectorGUI);

		/// \todo Register inspectors for the components here
#endif

		return result;
	}
}