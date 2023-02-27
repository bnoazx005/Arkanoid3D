/*!
	\file Utilities.h
	\date 13.12.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include <string>


namespace Game
{
	/*!
		\brief Level's loading utilities
	*/

	TDE2_API TDEngine2::TResult<TDEngine2::USIZE> GetCurrLevelIndex(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager);

	TDE2_API void LoadGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, 
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, 
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager,
		TDEngine2::USIZE levelIndex);
	
	TDE2_API bool IsNextGameLevelExists(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, TDEngine2::I32 offset = 1);

	TDE2_API void LoadNextGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, 
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager);

	TDE2_API void LoadPrevGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, 
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager);

	TDE2_API void LoadPaletteLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager);

	TDE2_API void LoadMainMenu(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager,
		TDEngine2::TPtr<TDEngine2::IGameModesManager> pGameModesManager,
		TDEngine2::TPtr<TDEngine2::IDesktopInputContext> pInputContext);

	/*!
		\brief Level's saving utility
	*/

	TDE2_API void SaveCurrentGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager);


	TDE2_API TDEngine2::E_RESULT_CODE RegisterGameResourceTypes(TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, TDEngine2::TPtr<TDEngine2::IFileSystem> pFileSystem);
}


namespace TDEngine2
{
	template <typename T>
	bool ProcessButtonOnClick(TDEngine2::IWorld* pWorld, TDEngine2::TEntityId buttonEntityId, T&& callback)
	{
		TDEngine2::CEntity* pButtonEntity = pWorld->FindEntity(buttonEntityId);
		if (!pButtonEntity)
		{
//			TDE2_ASSERT(false);
			return false;
		}

		TDEngine2::CInputReceiver* pButton = pButtonEntity->GetComponent<TDEngine2::CInputReceiver>();
		if (!pButton)
		{
			TDE2_ASSERT(false);
			return false;
		}

		if (pButton->mCurrState || !pButton->mPrevState)
		{
			return false;
		}

		/// \note Process logic on release of the button
		callback();

		return true;
	}
}