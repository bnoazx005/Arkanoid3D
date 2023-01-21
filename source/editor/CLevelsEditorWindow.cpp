#include "../../include/editor/CLevelsEditorWindow.h"
#include "../../include/components/CGameInfo.h"
#include "../../include/Utilities.h"
#include <core/IImGUIContext.h>
#include <scene/ISceneManager.h>
#include <scene/IScene.h>
#include <ecs/IWorld.h>


#if TDE2_EDITORS_ENABLED

using namespace TDEngine2;


namespace Game
{
	struct TActionKeyBindings
	{
		static constexpr E_KEYCODES mLoadPrevGameLevel = E_KEYCODES::KC_Q;
		static constexpr E_KEYCODES mLoadNextGameLevel = E_KEYCODES::KC_E;
		static constexpr E_KEYCODES mSaveCurrentLevel = E_KEYCODES::KC_F5;
	};


	class CLevelsListWindow
	{
		public:
			explicit CLevelsListWindow(const TLevelsEditorParams& params) :
				mpSceneManager(params.mpSceneManager),
				mpResourceManager(params.mpResourceManager),
				mpEventManager(params.mpEventManager),
				mpInputContext(params.mpInputContext),
				mpWorld(params.mpSceneManager->GetWorld().Get())
			{
			}

			void SetEnabled(bool value) { mIsEnabled = value; }

			void Draw(IImGUIContext* pImGUIContext)
			{
				const TVector2 windowSizes(pImGUIContext->GetWindowWidth(), pImGUIContext->GetWindowHeight());

				static const IImGUIContext::TWindowParams params
				{
					ZeroVector2,
					TVector2(windowSizes.x * 0.6f, windowSizes.y * 0.25f),
					TVector2(windowSizes.x * 0.6f, windowSizes.y * 0.25f),
				};

				if (pImGUIContext->BeginWindow("Levels", mIsEnabled, params))
				{
					const TVector2 buttonSizes(pImGUIContext->GetWindowWidth() * 0.15f, 25.f);

					pImGUIContext->BeginHorizontal();
					
					const TVector2 cursorPos = pImGUIContext->GetCursorScreenPos();

					if (IsNextGameLevelExists(mpSceneManager, mpResourceManager, -1) &&
						(mpInputContext->IsKeyPressed(TActionKeyBindings::mLoadPrevGameLevel) || pImGUIContext->Button("<", buttonSizes))) /// \note Load prev level
					{
						LoadPrevGameLevel(mpSceneManager, mpResourceManager, mpEventManager);
					}

					auto pGameInfoEntity = mpWorld->FindEntity(mpWorld->FindEntityWithUniqueComponent<CGameInfo>());
					auto sceneResult = mpSceneManager->GetScene(pGameInfoEntity->GetComponent<CGameInfo>()->mCurrLoadedGameId);

					if (sceneResult.IsOk())
					{
						pImGUIContext->Label(sceneResult.Get()->GetName());
					}
					else
					{
						pImGUIContext->Label("<<EMPTY>>");
					}

					const TVector2 currCursorPos = pImGUIContext->GetCursorScreenPos();
					pImGUIContext->SetCursorScreenPos(cursorPos + TVector2(pImGUIContext->GetWindowWidth() - buttonSizes.x - 10.f, 0.0f));

					if (IsNextGameLevelExists(mpSceneManager, mpResourceManager, 1) && 
						(mpInputContext->IsKeyPressed(TActionKeyBindings::mLoadNextGameLevel) || pImGUIContext->Button(">", buttonSizes))) /// \note Load next level
					{
						LoadNextGameLevel(mpSceneManager, mpResourceManager, mpEventManager);
					}

					pImGUIContext->SetCursorScreenPos(currCursorPos);

					pImGUIContext->EndHorizontal();

					/// \note Game level's logic here
					if (mpInputContext->IsKeyPressed(TActionKeyBindings::mSaveCurrentLevel) || pImGUIContext->Button("Save", TVector2(pImGUIContext->GetWindowWidth(), 25.f)))
					{
						SaveCurrentGameLevel(mpSceneManager, mpResourceManager);
					}
				}

				pImGUIContext->EndWindow();

			}
		private:
			TPtr<ISceneManager>        mpSceneManager = nullptr;
			TPtr<IResourceManager>     mpResourceManager = nullptr;
			TPtr<IEventManager>        mpEventManager = nullptr;
			TPtr<IDesktopInputContext> mpInputContext = nullptr;
			IWorld*                    mpWorld = nullptr;

			bool                       mIsEnabled = false;
	};


	CLevelsEditorWindow::CLevelsEditorWindow() :
		CBaseEditorWindow()
	{
	}

	CLevelsEditorWindow::~CLevelsEditorWindow()
	{
	}

	E_RESULT_CODE CLevelsEditorWindow::Init(const TLevelsEditorParams& params)
	{
		if (mIsInitialized)
		{
			return RC_OK;
		}

		mpSceneManager = params.mpSceneManager;
		mpEventManager = params.mpEventManager;
		mpResourceManager = params.mpResourceManager;
		mpInputContext = params.mpInputContext;

		mpLevelsList = std::make_unique<CLevelsListWindow>(params);

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

		mpLevelsList->SetEnabled(isEnabled);
		mpLevelsList->Draw(mpImGUIContext);

		if (mpImGUIContext->BeginWindow("Levels Editor", isEnabled, params))
		{
		}

		mpImGUIContext->EndWindow();

		mIsVisible = isEnabled;
	}


	TDE2_API IEditorWindow* CreateLevelsEditorWindow(const TLevelsEditorParams& params, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(IEditorWindow, CLevelsEditorWindow, result, params);
	}
}

#endif