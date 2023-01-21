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
		TDEngine2::USIZE levelIndex);
	
	TDE2_API bool IsNextGameLevelExists(TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager, TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, TDEngine2::I32 offset = 1);

	TDE2_API void LoadNextGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, 
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager);

	TDE2_API void LoadPrevGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, 
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager);

	TDE2_API void LoadPaletteLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager,
		TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager);

	/*!
		\brief Level's saving utility
	*/

	TDE2_API void SaveCurrentGameLevel(
		TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager,
		TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager);


	TDE2_API TDEngine2::E_RESULT_CODE RegisterGameResourceTypes(TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, TDEngine2::TPtr<TDEngine2::IFileSystem> pFileSystem);
}