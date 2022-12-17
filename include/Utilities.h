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
	TDE2_API void LoadGameLevel(TDEngine2::IEngineCore* pEngineCore, const std::string& gameLevelPath);


	TDE2_API TDEngine2::E_RESULT_CODE RegisterGameResourceTypes(TDEngine2::TPtr<TDEngine2::IResourceManager> pResourceManager, TDEngine2::TPtr<TDEngine2::IFileSystem> pFileSystem);
}