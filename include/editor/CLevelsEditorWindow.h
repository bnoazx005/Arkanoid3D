/*!
	\file CLevelsEditorWindow.h
	\date 06.12.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <editor/IEditorWindow.h>
#include <scene/ISceneManager.h>
#include <core/IEventManager.h>
#include <core/IResourceManager.h>
#include <core/IInputContext.h>


#if TDE2_EDITORS_ENABLED


namespace TDEngine2
{
	class IPhysics3DSystem;
}


namespace Game
{
	class CLevelsListWindow;
	class CPaletteWindow;


	struct TLevelsEditorParams
	{
		TDEngine2::TPtr<TDEngine2::ISceneManager>        mpSceneManager;
		TDEngine2::TPtr<TDEngine2::IEventManager>        mpEventManager;
		TDEngine2::TPtr<TDEngine2::IResourceManager>     mpResourceManager;
		TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext;
		TDEngine2::IPhysics3DSystem*                     mp3DPhysicsSystem;
	};


	/*!
		\brief A factory function for creation objects of CLevelsEditorWindow's type

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to IEditorWindow's implementation
	*/

	TDE2_API TDEngine2::IEditorWindow * CreateLevelsEditorWindow(const TLevelsEditorParams& params, TDEngine2::E_RESULT_CODE & result);


	/*!
		class CLevelsEditorWindow

		\brief The class is an implementation of a window for in-game level editor
	*/

	class CLevelsEditorWindow : public TDEngine2::CBaseEditorWindow
	{
		public:
			friend TDE2_API TDEngine2::IEditorWindow* CreateLevelsEditorWindow(const TLevelsEditorParams& params, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method initializes internal state of the editor

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API virtual TDEngine2::E_RESULT_CODE Init(const TLevelsEditorParams& params);

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS_NO_DCTR(CLevelsEditorWindow)
			~CLevelsEditorWindow() override;

			/*!
				\brief The method should be should be implemented in all derived classes. It's called
				once per frame only if the editor's window is visible
			*/

			TDE2_API void _onDraw() override;
		
		private:
			TDEngine2::TPtr<TDEngine2::ISceneManager>        mpSceneManager;
			TDEngine2::TPtr<TDEngine2::IEventManager>        mpEventManager;
			TDEngine2::TPtr<TDEngine2::IResourceManager>     mpResourceManager;
			TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext;
			TDEngine2::IPhysics3DSystem*                     mp3DPhysicsSystem = nullptr;

			std::unique_ptr<CLevelsListWindow> mpLevelsList = nullptr;
	};
}

#endif