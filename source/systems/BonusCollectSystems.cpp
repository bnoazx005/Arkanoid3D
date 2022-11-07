#include "../../include/systems/BonusCollectSystems.h"
#include "../../include/Components.h"
#include "../../include/components/CLevelInfo.h"


using namespace TDEngine2;


namespace Game
{
	/*!
		\brief AddScoreBonusCollectSystem
	*/

	CAddScoreBonusCollectSystem::CAddScoreBonusCollectSystem() :
		CCollectingSystem()
	{
	}

	void CAddScoreBonusCollectSystem::_onApplyCollectable(const CScoreBonus* pCollectable) const
	{
		CLevelInfo* pLevelInfo = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<Game::CLevelInfo>())->GetComponent<CLevelInfo>();
		if (!pLevelInfo)
		{
			return;
		}

		pLevelInfo->mPlayerScore += pCollectable->mScoreToAdd;
	}


	TDE2_API ISystem* CreateAddScoreBonusCollectSystem(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(ISystem, CAddScoreBonusCollectSystem, result, pEventManager);
	}
}