/*!
	\file CLevelsEditorWindow.h
	\date 06.12.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <editor/IEditorWindow.h>


#if TDE2_EDITORS_ENABLED

namespace Game
{
	/*!
		\brief A factory function for creation objects of CLevelsEditorWindow's type

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to IEditorWindow's implementation
	*/

	TDE2_API TDEngine2::IEditorWindow * CreateLevelsEditorWindow(TDEngine2::E_RESULT_CODE & result);


	/*!
		class CLevelsEditorWindow

		\brief The class is an implementation of a window for in-game level editor
	*/

	class CLevelsEditorWindow : public TDEngine2::CBaseEditorWindow
	{
		public:
			friend TDE2_API TDEngine2::IEditorWindow* CreateLevelsEditorWindow(TDEngine2::E_RESULT_CODE& result);
		public:
			/*!
				\brief The method initializes internal state of the editor

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API virtual TDEngine2::E_RESULT_CODE Init();

		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CLevelsEditorWindow)

			/*!
				\brief The method should be should be implemented in all derived classes. It's called
				once per frame only if the editor's window is visible
			*/

			TDE2_API void _onDraw() override;

	};
}

#endif