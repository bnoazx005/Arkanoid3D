#include "../include/Utilities.h"
#include "../include/components/CGameInfo.h"
#include "../include/components/CLevelSettings.h"
#include "../include/Components.h"
#include "../include/CGameLevelsCollection.h"
#include "../include/GameModes.h"
#include <utils/CFileLogger.h>


using namespace TDEngine2;

namespace Game
{
	static const std::string GameLevelsCollectionPath = "ProjectResources/GameLevelsCollection.asset";


	TDE2_API void LoadGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager,
		TDEngine2::USIZE levelIndex)
	{
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		const TResourceId gameLevelsCollectionHandle = pResourceManager->Load<CGameLevelsCollection>(GameLevelsCollectionPath);
		if (TResourceId::Invalid == gameLevelsCollectionHandle)
		{
			TDE2_ASSERT(false);
			return;
		}

		auto pLevelsCollection = pResourceManager->GetResource<CGameLevelsCollection>(gameLevelsCollectionHandle);
		if (!pLevelsCollection)
		{
			TDE2_ASSERT(false);
			return;
		}

		auto findLevelResult = pLevelsCollection->GetLevelPathByIndex(levelIndex);
		if (findLevelResult.HasError())
		{
			TDE2_ASSERT(false);
			return;
		}

		/// \note Enable loading screen 
		if (pGameModesManager)
		{
			E_RESULT_CODE result = pGameModesManager->PushMode(TPtr<IGameMode>(CreateLoadingGameMode(pGameModesManager.Get(),
				{
					nullptr,
					pSceneManager,
					pEventManager
				}, result)));

			TDE2_ASSERT(RC_OK == result);
		}

		/// \note Load a new one
		pSceneManager->LoadSceneAsync(findLevelResult.Get(), [pSceneManager, pWorld, pEventManager, pGameModesManager](const TResult<TSceneId>& sceneId)
		{
			CEntity* pLevelSettingsEntity = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CLevelSettings>());

			if (CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
			{
				const TSceneId prevLoadedSceneId = pGameInfo->mCurrLoadedGameId;
				pGameInfo->mCurrLoadedGameId = sceneId.Get();

				if (TSceneId::Invalid != prevLoadedSceneId)
				{
					E_RESULT_CODE result = pSceneManager->UnloadScene(prevLoadedSceneId); /// \note Unload the previously loaded level
					TDE2_ASSERT(RC_OK == result);
				}

				if (pLevelSettingsEntity)
				{
					CLevelSettings* pSettingsData = pLevelSettingsEntity->GetComponent<CLevelSettings>();
					
					pGameInfo->mHorizontalConstraints = pSettingsData->mHorizontalConstraints;
					pGameInfo->mVerticalConstraints = pSettingsData->mVerticalConstraints;
				}
				else
				{
					TDE2_ASSERT("[LoadGameLevel] LevelSettings component wasn't found in the level");
				}
			}

			TGameLevelLoadedEvent gameLevelLoadedEvent;
			pEventManager->Notify(&gameLevelLoadedEvent);

			/// \note Disable the loading screen 
			if (pGameModesManager)
			{
				E_RESULT_CODE result = pGameModesManager->PopMode();
				TDE2_ASSERT(RC_OK == result);
			}
		});
	}


	TResult<USIZE> GetCurrLevelIndex(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager)
	{
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		auto getSceneResult = pSceneManager->GetScene(pGameInfo->mCurrLoadedGameId);
		if (getSceneResult.HasError())
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		auto pScene = getSceneResult.Get();
		if (!pScene)
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		const TResourceId gameLevelsCollectionHandle = pResourceManager->Load<CGameLevelsCollection>(GameLevelsCollectionPath);
		if (TResourceId::Invalid == gameLevelsCollectionHandle)
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		auto pLevelsCollection = pResourceManager->GetResource<CGameLevelsCollection>(gameLevelsCollectionHandle);
		if (!pLevelsCollection)
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		auto findLevelResult = pLevelsCollection->FindLevelIndex(pScene->GetScenePath());
		if (findLevelResult.HasError())
		{
			TDE2_ASSERT(false);
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		return Wrench::TOkValue<USIZE>(findLevelResult.Get());
	}


	bool IsNextGameLevelExists(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, I32 offset)
	{
		const TResourceId gameLevelsCollectionHandle = pResourceManager->Load<CGameLevelsCollection>(GameLevelsCollectionPath);
		if (TResourceId::Invalid == gameLevelsCollectionHandle)
		{
			TDE2_ASSERT(false);
			return false;
		}

		auto pLevelsCollection = pResourceManager->GetResource<CGameLevelsCollection>(gameLevelsCollectionHandle);
		if (!pLevelsCollection)
		{
			TDE2_ASSERT(false);
			return false;
		}

		const I32 nextLevelIndex = static_cast<I32>(GetCurrLevelIndex(pSceneManager, pResourceManager).Get()) + offset;

		/// \note Last level is a palette
		return nextLevelIndex >= 0 && nextLevelIndex < pLevelsCollection->GetLevelsCount() - 1;
	}

	void LoadNextGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager)
	{
		if (!IsNextGameLevelExists(pSceneManager, pResourceManager, 1))
		{
			LOG_ERROR("[LoadNextGameLevel] Coudn't load next level");
			return;
		}

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, pGameModesManager, GetCurrLevelIndex(pSceneManager, pResourceManager).Get() + 1);
	}

	void LoadPrevGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager)
	{
		if (!IsNextGameLevelExists(pSceneManager, pResourceManager, -1))
		{
			LOG_ERROR("[LoadNextGameLevel] Coudn't load previous level");
			return;
		}

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, pGameModesManager, GetCurrLevelIndex(pSceneManager, pResourceManager).Get() - 1);
	}

	void LoadPaletteLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager)
	{
		const TResourceId gameLevelsCollectionHandle = pResourceManager->Load<CGameLevelsCollection>(GameLevelsCollectionPath);
		if (TResourceId::Invalid == gameLevelsCollectionHandle)
		{
			TDE2_ASSERT(false);
		}

		auto pLevelsCollection = pResourceManager->GetResource<CGameLevelsCollection>(gameLevelsCollectionHandle);
		if (!pLevelsCollection)
		{
			TDE2_ASSERT(false);
		}

		auto findLevelResult = pLevelsCollection->FindLevelIndex("ProjectResources/Scenes/Palette.scene");
		if (findLevelResult.HasError())
		{
			TDE2_ASSERT(false);
		}

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, nullptr, findLevelResult.Get());
	}

	void LoadMainMenu(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager, 
		TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext)
	{
		E_RESULT_CODE result = RC_OK;
		result = result | pGameModesManager->SwitchMode(TPtr<IGameMode>(CreateMainMenuGameMode(pGameModesManager.Get(),
			{
				pInputContext,
				pSceneManager,
				pEventManager
			}, result)));

		TDE2_ASSERT(RC_OK == result);

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, pGameModesManager, 0);
	}


	/*!
		\brief Save level's utility function
	*/

	void SaveCurrentGameLevel(TPtr<ISceneManager> pSceneManager, TPtr<IResourceManager> pResourceManager)
	{
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>();
		if (!pGameInfo)
		{
			TDE2_ASSERT(false);
			return;
		}

		auto getSceneResult = pSceneManager->GetScene(pGameInfo->mCurrLoadedGameId);
		if (getSceneResult.HasError())
		{
			TDE2_ASSERT(false);
			return;
		}

		auto pScene = getSceneResult.Get();
		if (!pScene)
		{
			TDE2_ASSERT(false);
			return;
		}

		E_RESULT_CODE result = pSceneManager->SaveSceneChunk(pScene->GetScenePath(), pSceneManager->GetSceneId(pScene->GetName()));
		if (RC_OK != result)
		{
			TDE2_ASSERT(false);
			return;
		}

		LOG_MESSAGE(Wrench::StringUtils::Format("[SaveCurrentGameLevel] The current game level \"{0}\" successfully saved", pScene->GetName()));
	}


	TDE2_API TDEngine2::E_RESULT_CODE RegisterGameResourceTypes(TPtr<IResourceManager> pResourceManager, TPtr<IFileSystem> pFileSystem)
	{
		E_RESULT_CODE result = RC_OK;

		pResourceManager->RegisterFactory(CreateGameLevelsCollectionFactory(pResourceManager.Get(), result));
		pResourceManager->RegisterLoader(CreateGameLevelsCollectionLoader(pResourceManager.Get(), pFileSystem.Get(), result));

		return result;
	}
}