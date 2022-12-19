#include "../include/Utilities.h"
#include "../include/components/CGameInfo.h"
#include "../include/components/CLevelBoundaries.h"
#include "../include/Components.h"
#include "../include/CGameLevelsCollection.h"


using namespace TDEngine2;

namespace Game
{
	static const std::string GameLevelsCollectionPath = "ProjectResources/GameLevelsCollection.asset";


	TDE2_API void LoadGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, 
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

		/// \note Load a new one
		pSceneManager->LoadSceneAsync(findLevelResult.Get(), [pSceneManager, pWorld, pEventManager](const TResult<TSceneId>& sceneId)
		{
			CEntity* pLevelBoundariesEntity = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CLevelBoundaries>());

			if (CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
			{
				const TSceneId prevLoadedSceneId = pGameInfo->mCurrLoadedGameId;
				pGameInfo->mCurrLoadedGameId = sceneId.Get();

				if (TSceneId::Invalid != prevLoadedSceneId)
				{
					E_RESULT_CODE result = pSceneManager->UnloadScene(prevLoadedSceneId); /// \note Unload the previously loaded level
					TDE2_ASSERT(RC_OK == result);
				}

				if (pLevelBoundariesEntity)
				{
					CLevelBoundaries* boundariesData = pLevelBoundariesEntity->GetComponent<CLevelBoundaries>();
					
					pGameInfo->mHorizontalConstraints = boundariesData->mHorizontalConstraints;
					pGameInfo->mVerticalConstraints = boundariesData->mVerticalConstraints;
				}
				else
				{
					TDE2_ASSERT("[LoadGameLevel] LevelBoundaries component wasn't found in the level");
				}
			}

			TGameLevelLoadedEvent gameLevelLoadedEvent;
			pEventManager->Notify(&gameLevelLoadedEvent);
		});
	}


	static TResult<USIZE> GetCurrLevelIndex(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager)
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

		return nextLevelIndex >= 0 && nextLevelIndex < pLevelsCollection->GetLevelsCount();
	}

	void LoadNextGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager)
	{
		if (!IsNextGameLevelExists(pSceneManager, pResourceManager, 1))
		{
			LOG_ERROR("[LoadNextGameLevel] Coudn't load next level");
			return;
		}

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, GetCurrLevelIndex(pSceneManager, pResourceManager).Get() + 1);
	}

	void LoadPrevGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager)
	{
		if (!IsNextGameLevelExists(pSceneManager, pResourceManager, -1))
		{
			LOG_ERROR("[LoadNextGameLevel] Coudn't load previous level");
			return;
		}

		LoadGameLevel(pSceneManager, pResourceManager, pEventManager, GetCurrLevelIndex(pSceneManager, pResourceManager).Get() - 1);
	}



	TDE2_API TDEngine2::E_RESULT_CODE RegisterGameResourceTypes(TPtr<IResourceManager> pResourceManager, TPtr<IFileSystem> pFileSystem)
	{
		E_RESULT_CODE result = RC_OK;

		pResourceManager->RegisterFactory(CreateGameLevelsCollectionFactory(pResourceManager.Get(), result));
		pResourceManager->RegisterLoader(CreateGameLevelsCollectionLoader(pResourceManager.Get(), pFileSystem.Get(), result));

		return result;
	}
}