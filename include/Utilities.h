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
}