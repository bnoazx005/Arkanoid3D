#include "../include/Utilities.h"
#include "../include/components/CGameInfo.h"
#include "../include/Components.h"


using namespace TDEngine2;

namespace Game
{
	TDE2_API void LoadGameLevel(TDEngine2::IEngineCore* pEngineCore, const std::string& gameLevelPath)
	{
		TPtr<ISceneManager> pSceneManager = pEngineCore->GetSubsystem<ISceneManager>();
		TPtr<IWorld> pWorld = pSceneManager->GetWorld();

		if (CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
		{
			if (TSceneId::Invalid != pGameInfo->mCurrLoadedGameId)
			{
				E_RESULT_CODE result = pSceneManager->UnloadScene(pGameInfo->mCurrLoadedGameId); /// \note Unload the previously loaded level
				TDE2_ASSERT(RC_OK == result);
			}
		}

		/// \note Load a new one
		pSceneManager->LoadSceneAsync(gameLevelPath, [pEngineCore, pWorld](const TResult<TSceneId>& sceneId)
		{
			if (CGameInfo* pGameInfo = pWorld->FindEntity(pWorld->FindEntityWithUniqueComponent<CGameInfo>())->GetComponent<CGameInfo>())
			{
				pGameInfo->mCurrLoadedGameId = sceneId.Get();
			}

			TGameLevelLoadedEvent gameLevelLoadedEvent;

			if (auto pEventManager = pEngineCore->GetSubsystem<IEventManager>())
			{
				pEventManager->Notify(&gameLevelLoadedEvent);
			}
		});
	}
}