#include "../../include/editor/CLevelsEditorWindow.h"
#include <core/IImGUIContext.h>


#if TDE2_EDITORS_ENABLED

using namespace TDEngine2;


namespace Game
{
	CLevelsEditorWindow::CLevelsEditorWindow() :
		CBaseEditorWindow()
	{
	}

	E_RESULT_CODE CLevelsEditorWindow::Init()
	{
		if (mIsInitialized)
		{
			return RC_OK;
		}

		mIsInitialized = true;

		return RC_OK;
	}

	void CLevelsEditorWindow::_onDraw()
	{
		bool isEnabled = mIsVisible;

		static const IImGUIContext::TWindowParams params
		{
			ZeroVector2,
			TVector2(300.0f, 300.0f),
			TVector2(500.0f, 300.0f),
		};

		if (mpImGUIContext->BeginWindow("Levels Editor", isEnabled, params))
		{
		}

		mpImGUIContext->EndWindow();

		mIsVisible = isEnabled;
	}


	TDE2_API IEditorWindow* CreateLevelsEditorWindow(E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IEditorWindow, CLevelsEditorWindow, result);
	}
}

#endif