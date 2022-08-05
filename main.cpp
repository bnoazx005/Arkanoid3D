#define TDE2_DEFINE_ENTRY_POINT
#include <TDEngine2.h>
#include "include/CCustomEngineListener.h"


extern std::string GetProjectSettingsFilePath() { return "ArkanoidGame.project"; }

extern std::unique_ptr<TDEngine2::IEngineListener> GetEngineListener() { return std::make_unique<CCustomEngineListener>(); }
