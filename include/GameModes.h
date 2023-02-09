/*!
	\file GameStates.h
	\date 04.02.2023
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	struct TStateInitParams
	{
		TDEngine2::TPtr<TDEngine2::IDesktopInputContext> mpInputContext;
		TDEngine2::TPtr<TDEngine2::ISceneManager>        mpSceneManager;
		TDEngine2::TPtr<TDEngine2::IEventManager>        mpEventManager;
	};


	class CCommonGameMode: public TDEngine2::CBaseGameMode
	{
		protected:
			TDE2_API explicit CCommonGameMode(const std::string& name);
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCommonGameMode)

			TDE2_API TDEngine2::E_RESULT_CODE SpawnModeWindow(const std::string& prefabId, bool useMainScene = false);
			TDE2_API TDEngine2::E_RESULT_CODE RemoveModeWindow();
		protected:
			TStateInitParams     mParams;

			TDEngine2::TEntityId mWindowHierarchyRootEntityId;
			TDEngine2::TSceneId  mWindowOwnerSceneId;
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreatePauseGameMode(TDEngine2::IGameModesManager* pOwner, const TStateInitParams& params, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CPauseGameMode

		\brief The class represents a mode which is active when a user taps pause button
	*/

	class CPauseGameMode : public CCommonGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreatePauseGameMode(TDEngine2::IGameModesManager*, const TStateInitParams&, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CPauseGameMode)
		private:
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreateCoreGameMode(TDEngine2::IGameModesManager* pOwner, const TStateInitParams& params, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CCoreGameMode

		\brief The class represents a mode which implements core gameplay state
	*/

	class CCoreGameMode : public CCommonGameMode, public TDEngine2::IEventHandler
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreateCoreGameMode(TDEngine2::IGameModesManager*, const TStateInitParams&, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;

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
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCoreGameMode)
		private:
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreateLevelFinishedGameMode(TDEngine2::IGameModesManager* pOwner, const TStateInitParams& params, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CLevelFinishedGameMode

		\brief The class represents a mode which implements two states 'Game over' and 'Victory'
	*/

	class CLevelFinishedGameMode : public CCommonGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreateLevelFinishedGameMode(TDEngine2::IGameModesManager*, const TStateInitParams&, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CLevelFinishedGameMode)
		private:
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreateMainMenuGameMode(TDEngine2::IGameModesManager* pOwner, const TStateInitParams& params, TDEngine2::E_RESULT_CODE& result);

	/*!
		class CMainMenuGameMode

		\brief The implementation of the main menu of the game
	*/

	class CMainMenuGameMode : public CCommonGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreateMainMenuGameMode(TDEngine2::IGameModesManager*, const TStateInitParams&, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CMainMenuGameMode)
		private:
	};


	/*!
		\brief A factory function for creation objects of CBaseGameMode's type.

		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CBaseGameMode's implementation
	*/

	TDE2_API TDEngine2::IGameMode* CreateLoadingGameMode(TDEngine2::IGameModesManager* pOwner, const TStateInitParams& params, TDEngine2::E_RESULT_CODE& result);

	/*!
		class CLoadingGameMode

		\brief The implementation of a loading screen
	*/

	class CLoadingGameMode : public CCommonGameMode
	{
		public:
			friend TDE2_API TDEngine2::IGameMode* CreateLoadingGameMode(TDEngine2::IGameModesManager*, const TStateInitParams&, TDEngine2::E_RESULT_CODE&);
		public:
			/*!
				\brief The method is invoked when game modes manager activates the state
			*/

			TDE2_API void OnEnter() override;

			/*!
				\brief The method is invoked when a game modes manager is switcher to a new state from the current one
			*/

			TDE2_API void OnExit() override;

			/*!
				\brief The method is invoked at least once per frame when the current mode is active
			*/

			TDE2_API void Update(TDEngine2::F32 dt) override;
		private:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CLoadingGameMode)
		private:
	};

}