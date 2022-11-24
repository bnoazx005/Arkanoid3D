/*!
	\file CGameInfo.h
	\date 04.10.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <TDEngine2.h>


namespace Game
{
	TDE2_API TDEngine2::IComponent* CreateGameInfo(TDEngine2::E_RESULT_CODE& result);


	/*!
		class CGameInfo
	*/

	class CGameInfo : public TDEngine2::CBaseComponent, public TDEngine2::CPoolMemoryAllocPolicy<CGameInfo, 1 << 20>
	{
		public:
			friend TDE2_API TDEngine2::IComponent* CreateGameInfo(TDEngine2::E_RESULT_CODE&);
		public:
			TDE2_REGISTER_COMPONENT_TYPE(CGameInfo)

			/*!
				\brief The method deserializes object's state from given reader

				\param[in, out] pReader An input stream of data that contains information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Load(TDEngine2::IArchiveReader* pReader) override;

			/*!
				\brief The method serializes object's state into given stream

				\param[in, out] pWriter An output stream of data that writes information about the object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Save(TDEngine2::IArchiveWriter* pWriter) override;

	#if TDE2_EDITORS_ENABLED
			TDE2_API static void DrawInspectorGUI(const TDEngine2::TEditorContext& context);
	#endif
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CGameInfo)
		public:
			TDEngine2::TRangeF32 mHorizontalConstraints = TDEngine2::TRangeF32(-4.0f, 4.0f);
			TDEngine2::TRangeF32 mVerticalConstraints = TDEngine2::TRangeF32(-5.0f, 4.0f);

			bool mHasPlayerMissedBall = false;
			bool mIsGodModeEnabled = false;
			bool mIsLaserEnabled = false;

			TDEngine2::U32 mPlayerScore = 0;
			TDEngine2::U32 mScoreMultiplier = 1;

			TDEngine2::U32 mPlayerLives = 3;

			TDEngine2::TSceneId mCurrLoadedGameId = TDEngine2::TSceneId::Invalid;

			TDEngine2::F32 mBonusesSpawnCommonProbability = 0.15f; /// \note The common probability of bonus' spawning
	};


	/*!
		struct TGameInfoParameters

		\brief The structure contains parameters for creation of CGameInfo
	*/

	typedef struct TGameInfoParameters : public TDEngine2::TBaseComponentParameters
	{
		TDEngine2::TRangeF32 mHorizontalConstraints;
		TDEngine2::TRangeF32 mVerticalConstraints;
	} TGameInfoParameters;


	TDE2_DECLARE_COMPONENT_FACTORY(GameInfo, TGameInfoParameters);
}