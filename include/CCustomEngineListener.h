#pragma once


#include <TDEngine2.h>


class CCustomEngineListener: public TDEngine2::IEngineListener, public TDEngine2::IEventHandler
{
	public:
		CCustomEngineListener() = default;
		virtual ~CCustomEngineListener() = default;

		/*!
		\brief The event occurs after the engine was initialized

		\return RC_OK if everything went ok, or some other code, which describes an error
		*/

		TDEngine2::E_RESULT_CODE OnStart() override;

		/*!
		\brief The event occurs every frame

		\return RC_OK if everything went ok, or some other code, which describes an error
		*/

		TDEngine2::E_RESULT_CODE OnUpdate(const float& dt) override;

		/*!
		\brief The event occurs before the engine will be destroyed

		\return RC_OK if everything went ok, or some other code, which describes an error
		*/

		TDEngine2::E_RESULT_CODE OnFree() override;

		/*!
			\brief The method is used to inject a pointer to the engine into the object of this type

			\param[in] An instance of the engine's core
		*/

		void SetEngineInstance(TDEngine2::IEngineCore* pEngineCore) override;

		/*!
			\brief The method receives a given event and processes it

			\param[in] pEvent A pointer to event data

			\return RC_OK if everything went ok, or some other code, which describes an error
		*/

		TDE2_API TDEngine2::E_RESULT_CODE OnEvent(const TDEngine2::TBaseEvent* pEvent) override;

		/*!
			\brief The method returns an identifier of a listener

			\return The method returns an identifier of a listener
		*/

		TDE2_API TDEngine2::TEventListenerId GetListenerId() const override;
	protected:
		TDEngine2::IEngineCore*                             mpEngineCoreInstance;

		TDEngine2::TPtr<TDEngine2::IGraphicsContext>        mpGraphicsContext;

		TDEngine2::TPtr<TDEngine2::IWindowSystem>           mpWindowSystem;

		TDEngine2::TPtr<TDEngine2::IResourceManager>        mpResourceManager;

		TDEngine2::TPtr<TDEngine2::IFileSystem>             mpFileSystem;

		TDEngine2::TPtr<TDEngine2::IWorld>                  mpWorld;
		
		TDEngine2::TPtr<TDEngine2::IDesktopInputContext>    mpInputContext;
		
		TDEngine2::TPtr<TDEngine2::ISceneManager>           mpSceneManager;

#if TDE2_EDITORS_ENABLED
		TDEngine2::TPtr<TDEngine2::IEditorWindow>           mpLevelsEditor;
#endif
};