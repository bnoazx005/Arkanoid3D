#include "../include/CCustomEngineListener.h"
#include <TDEngine2.h>
#include <iostream>


using namespace TDEngine2;


E_RESULT_CODE CCustomEngineListener::OnStart()
{
	mpWorld = mpSceneManager->GetWorld();

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

	mpSceneManager->LoadSceneAsync("Resources/Scenes/TestPlayground.scene", [](auto)
	{

	});

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
