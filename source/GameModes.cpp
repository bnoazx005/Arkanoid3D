#include "../include/GameModes.h"


using namespace TDEngine2;


namespace Game
{
	/*!
		\brief CPauseGameMode's definition
	*/

	CPauseGameMode::CPauseGameMode() :
		CBaseGameMode("PauseMode")
	{
	}

	void CPauseGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));
	}

	void CPauseGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));
	}

	void CPauseGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreateCoreGameMode(mpOwner, DynamicPtrCast<IInputContext>(mpInputContext), result)));
		}
		
	}


	TDE2_API IGameMode* CreatePauseGameMode(IGameModesManager* pOwner, TPtr<IInputContext> pInputContext, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CPauseGameMode, CPauseGameMode, result, pOwner))
		{
			pMode->mpInputContext = DynamicPtrCast<IDesktopInputContext>(pInputContext);

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}


	/*!
		\brief CCoreGameMode's definition
	*/

	CCoreGameMode::CCoreGameMode() :
		CBaseGameMode("CoreMode")
	{
	}

	void CCoreGameMode::OnEnter()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnEnter, mode: \"{0}\"", mName));
	}

	void CCoreGameMode::OnExit()
	{
		LOG_MESSAGE(Wrench::StringUtils::Format("[BaseGameMode] Invoke OnExit, mode: \"{0}\"", mName));
	}

	void CCoreGameMode::Update(F32 dt)
	{
		E_RESULT_CODE result = RC_OK;

		if (mpInputContext->IsKeyPressed(E_KEYCODES::KC_ESCAPE)) /// \todo Replace with keybindings implementation
		{
			mpOwner->SwitchMode(TPtr<IGameMode>(CreatePauseGameMode(mpOwner, DynamicPtrCast<IInputContext>(mpInputContext), result)));
		}
	}


	TDE2_API IGameMode* CreateCoreGameMode(IGameModesManager* pOwner, TPtr<IInputContext> pInputContext, E_RESULT_CODE& result)
	{
		if (auto pMode = CREATE_IMPL(CCoreGameMode, CCoreGameMode, result, pOwner))
		{
			pMode->mpInputContext = DynamicPtrCast<IDesktopInputContext>(pInputContext);

			return dynamic_cast<IGameMode*>(pMode);
		}

		return nullptr;
	}
}