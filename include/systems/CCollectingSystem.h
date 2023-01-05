/*!
	\file CCollectingSystem.h
	\date 28.10.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include "../components/CPaddle.h"


namespace Game
{
	template <typename T>
	class CCollectingSystem : public TDEngine2::CBaseSystem, public TDEngine2::IEventHandler
	{
		public:
			TDE2_SYSTEM(CCollectingSystem);

			/*!
				\brief The method initializes an inner state of a system

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API virtual TDEngine2::E_RESULT_CODE Init(TDEngine2::TPtr<TDEngine2::IEventManager> pEventManager, TDEngine2::TPtr<TDEngine2::ISceneManager> pSceneManager = nullptr)
			{
				if (mIsInitialized)
				{
					return TDEngine2::RC_FAIL;
				}

				if (!pEventManager)
				{
					return TDEngine2::RC_INVALID_ARGS;
				}

				pEventManager->Subscribe(TDEngine2::TOn3DCollisionRegisteredEvent::GetTypeId(), this);

				mpEventManager = pEventManager;
				mpSceneManager = pSceneManager;

				mIsInitialized = true;

				return TDEngine2::RC_OK;
			}

			/*!
				\brief The method inject components array into a system

				\param[in] pWorld A pointer to a main scene's object
			*/

			TDE2_API void InjectBindings(TDEngine2::IWorld* pWorld) override
			{
				mpWorld = pWorld;
			}

			/*!
				\brief The main method that should be implemented in all derived classes.
				It contains all the logic that the system will execute during engine's work.

				\param[in] pWorld A pointer to a main scene's object

				\param[in] dt A delta time's value
			*/

			TDE2_API void Update(TDEngine2::IWorld* pWorld, TDEngine2::F32 dt) override
			{
				if (!mIsEffectActive)
				{
					return;
				}

				if (mCurrTimer < 1e-3f)
				{
					_onCollectableEffectFinished();
					return;
				}

				mCurrTimer -= dt;
			}

			/*!
				\brief The method receives a given event and processes it

				\param[in] pEvent A pointer to event data

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE OnEvent(const TDEngine2::TBaseEvent* pEvent) override
			{
				const TDEngine2::TOn3DCollisionRegisteredEvent* pCollisionEvent = dynamic_cast<const TDEngine2::TOn3DCollisionRegisteredEvent*>(pEvent);
				if (!pCollisionEvent)
				{
					return TDEngine2::RC_FAIL;
				}

				TDEngine2::CEntity* pEntity0 = mpWorld->FindEntity(pCollisionEvent->mEntities[0]);
				TDEngine2::CEntity* pEntity1 = mpWorld->FindEntity(pCollisionEvent->mEntities[1]);

				if (!pEntity0 || !pEntity1 || TDEngine2::TOn3DCollisionRegisteredEvent::E_COLLISION_EVENT_TYPE::ON_ENTER != pCollisionEvent->mType)
				{
					return TDEngine2::RC_OK;
				}

				if (!GetValidPtrOrDefault(pEntity0->GetComponent<CPaddle>(), pEntity1->GetComponent<CPaddle>()))
				{
					return TDEngine2::RC_OK;
				}

				TDEngine2::CEntity* pCollectableEntity = pEntity0;

				T* pCollectable = pCollectableEntity->GetComponent<T>();
				if (!pCollectable)
				{
					pCollectable = pEntity1->GetComponent<T>();
					pCollectableEntity = pEntity1;
				}

				if (pCollectable)
				{
					_onApplyCollectable(pCollectable);

					AddDefferedCommand([this, id = pCollectableEntity->GetId()]
					{
						mpWorld->Destroy(id);
					});
				}				

				return TDEngine2::RC_OK;
			}

			/*!
				\brief The method returns an identifier of a listener

				\return The method returns an identifier of a listener
			*/

			TDE2_API TDEngine2::TEventListenerId GetListenerId() const override
			{
				return TDEngine2::TEventListenerId(GetTypeId());
			}
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CCollectingSystem)

			TDE2_API virtual void _onApplyCollectable(const T* pCollectable) = 0;
			
			TDE2_API virtual void _onCollectableEffectFinished() 
			{
				mIsEffectActive = false;
			}

		protected:
			TDEngine2::IWorld* mpWorld = nullptr; 
			TDEngine2::TPtr<TDEngine2::IEventManager> mpEventManager = nullptr;
			TDEngine2::TPtr<TDEngine2::ISceneManager> mpSceneManager = nullptr;

			TDEngine2::F32 mCurrTimer = 0.0f;
			bool           mIsEffectActive = false;
	};


	template <typename T>
	CCollectingSystem<T>::CCollectingSystem() :
		CBaseSystem()
	{
	}
}