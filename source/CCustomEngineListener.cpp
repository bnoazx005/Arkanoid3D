#include "../include/CCustomEngineListener.h"
#include "../include/Components.h"
#include "../include/systems/CPaddleControlSystem.h"
#include "../include/systems/CBallUpdateSystem.h"
#include "../include/systems/CDamageablesUpdateSystem.h"
#include "../include/systems/CCollectingSystem.h"
#include "../include/systems/CGravityUpdateSystem.h"
#include "../include/systems/BonusCollectSystems.h"
#include "../include/systems/CStickyBallsProcessSystem.h"
#include "../include/systems/CPowerUpSpawnSystem.h"
#include "../include/systems/CProjectilesPoolSystem.h"
#include "../include/systems/CGameUIUpdateSystem.h"
#include "../include/components/CGameInfo.h"
#include <TDEngine2.h>
#include <iostream>


using namespace TDEngine2;
using namespace Game;


namespace Game
{
	static E_RESULT_CODE RegisterGameSystems(TPtr<IWorld> pWorld, TPtr<IDesktopInputContext> pInputContext, TPtr<IEventManager> pEventManager, TPtr<ISceneManager> pSceneManager)
	{
		TDEngine2::E_RESULT_CODE result = TDEngine2::RC_OK;

		pWorld->RegisterSystem(Game::CreatePaddleControlSystem(pInputContext, pSceneManager, result));
		pWorld->RegisterSystem(Game::CreateBallUpdateSystem(pEventManager, pInputContext, result));
		pWorld->RegisterSystem(Game::CreateDamageablesUpdateSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateGravityUpdateSystem(result));
		pWorld->RegisterSystem(Game::CreateStickyBallsProcessSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreatePowerUpSpawnSystem(pEventManager, pSceneManager, result));

		// bonuses' systems
		pWorld->RegisterSystem(Game::CreateAddScoreBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateScoreMultiplierBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateGodModeBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateExpandPaddleBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateStickyPaddleBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateExtraLifeBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateLaserBonusCollectSystem(pEventManager, result));
		pWorld->RegisterSystem(Game::CreateMultipleBallsBonusCollectSystem(pEventManager, pSceneManager, result));

		pWorld->RegisterSystem(Game::CreateProjectilesPoolSystem(result));
		pWorld->RegisterSystem(Game::CreateGameUIUpdateSystem(pEventManager, result));

		return result;
	}
}


E_RESULT_CODE CCustomEngineListener::OnStart()
{
	mpWorld = mpSceneManager->GetWorld();

	Game::RegisterGameComponents(mpWorld, mpEngineCoreInstance->GetSubsystem<IEditorsManager>());
	Game::RegisterGameSystems(mpWorld, mpInputContext, mpEngineCoreInstance->GetSubsystem<IEventManager>(), mpEngineCoreInstance->GetSubsystem<ISceneManager>());

	/// \todo Replace this later with scene's configurable solution
	if (auto pMainScene = mpSceneManager->GetScene(MainScene).Get())
	{
		auto&& cameras = mpWorld->FindEntitiesWithComponents<CPerspectiveCamera>();
		if (!cameras.empty())
		{
			if (auto pCameraEntity = mpWorld->FindEntity(cameras.front()))
			{
				/// \todo The camera's transformations implementation is horrible should be revisited later
#if 0
				if (auto pCameraTransform = pCameraEntity->GetComponent<CTransform>())
				{
					pCameraTransform->SetPosition(TVector3(0.0f, 5.f, -2.0f));
					pCameraTransform->SetRotation(TVector3(99.182f, 0.0f, 0.0f));
				}
#endif

				if (auto pCamerasContextEntity = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<CCamerasContextComponent>()))
				{
					if (auto pCamerasContext = pCamerasContextEntity->GetComponent<CCamerasContextComponent>())
					{
						pCamerasContext->SetActiveCameraEntity(pCameraEntity->GetId());
					}
				}
			}			
		}
	}

	mpSceneManager->LoadSceneAsync("Resources/Scenes/PlayerScene.scene", [this](const TResult<TSceneId>& sceneId)
	{
		auto&& pEventManager = mpEngineCoreInstance->GetSubsystem<IEventManager>();

		if (CGameInfo* pGameInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
		{
			pGameInfo->mCurrLoadedGameId = sceneId.Get();

			{
				TScoreChangedEvent scoreChangedEvent;
				scoreChangedEvent.mNewPlayerScore = pGameInfo->mPlayerScore;

				pEventManager->Notify(&scoreChangedEvent);
			}

			{
				TLivesChangedEvent livesChangedEvent;
				livesChangedEvent.mPlayerLives = pGameInfo->mPlayerLives;

				pEventManager->Notify(&livesChangedEvent);
			}
		}
	});

	mpSceneManager->LoadSceneAsync("Resources/Scenes/TestPlayground.scene", nullptr);

	return RC_OK;
}

E_RESULT_CODE CCustomEngineListener::OnUpdate(const float& dt)
{
	return RC_OK;
}

E_RESULT_CODE CCustomEngineListener::OnFree()
{
	return RC_OK;
}

void CCustomEngineListener::SetEngineInstance(IEngineCore* pEngineCore)
{
	if (!pEngineCore)
	{
		return;
	}

	mpEngineCoreInstance = pEngineCore;

	mpGraphicsContext = mpEngineCoreInstance->GetSubsystem<IGraphicsContext>();
	mpWindowSystem    = mpEngineCoreInstance->GetSubsystem<IWindowSystem>();
	mpResourceManager = mpEngineCoreInstance->GetSubsystem<IResourceManager>();
	mpInputContext    = mpEngineCoreInstance->GetSubsystem<IDesktopInputContext>();
	mpFileSystem      = mpEngineCoreInstance->GetSubsystem<IFileSystem>();
	mpSceneManager    = mpEngineCoreInstance->GetSubsystem<ISceneManager>();
}
