#include "../include/CGameLevelsCollection.h"


using namespace TDEngine2;

namespace Game
{
	struct TGameLevelsCollectionArchiveKeys
	{
		static const std::string mCollectionKey;
		static const std::string mLevelPathKey;
	};

	const std::string TGameLevelsCollectionArchiveKeys::mCollectionKey = "collection";
	const std::string TGameLevelsCollectionArchiveKeys::mLevelPathKey = "level_path";


	CGameLevelsCollection::CGameLevelsCollection() :
		CBaseResource()
	{
	}

	E_RESULT_CODE CGameLevelsCollection::Init(IResourceManager* pResourceManager, const std::string& name)
	{
		E_RESULT_CODE result = _init(pResourceManager, name);

		if (result != RC_OK)
		{
			return result;
		}

		mIsInitialized = true;

		return RC_OK;
	}

	E_RESULT_CODE CGameLevelsCollection::Reset()
	{
		mGameLevels.clear();
		return RC_OK;
	}

	E_RESULT_CODE CGameLevelsCollection::Save(IArchiveWriter* pWriter)
	{
		if (!pWriter)
		{
			return RC_INVALID_ARGS;
		}

		pWriter->BeginGroup("meta");
		{
			pWriter->SetString("resource_type", "game_levels_collection");
			pWriter->SetUInt16("version_tag", mVersionTag);
		}
		pWriter->EndGroup();

		pWriter->BeginGroup(TGameLevelsCollectionArchiveKeys::mCollectionKey, true);
		{
			for (auto&& levelPath : mGameLevels)
			{
				pWriter->BeginGroup(Wrench::StringUtils::GetEmptyStr());
				{
					pWriter->SetString(TGameLevelsCollectionArchiveKeys::mLevelPathKey, levelPath);
				}
				pWriter->EndGroup();
			}
		}
		pWriter->EndGroup();

		return RC_OK;
	}

	E_RESULT_CODE CGameLevelsCollection::Load(IArchiveReader* pReader)
	{
		if (!pReader)
		{
			return RC_INVALID_ARGS;
		}

		mGameLevels.clear();

		pReader->BeginGroup(TGameLevelsCollectionArchiveKeys::mCollectionKey);
		{
			while (pReader->HasNextItem())
			{
				pReader->BeginGroup(Wrench::StringUtils::GetEmptyStr());
				{
					mGameLevels.emplace_back(pReader->GetString(TGameLevelsCollectionArchiveKeys::mLevelPathKey));
				}
				pReader->EndGroup();
			}
		}
		pReader->EndGroup();

		return RC_OK;
	}

	TDE2_API TDEngine2::TResult<TDEngine2::USIZE> CGameLevelsCollection::FindLevelIndex(const std::string& levelPath) const
	{
		auto it = std::find(mGameLevels.cbegin(), mGameLevels.cend(), levelPath);
		if (it == mGameLevels.cend())
		{
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		return Wrench::TOkValue<USIZE>(std::distance(mGameLevels.cbegin(), it));
	}

	TDEngine2::TResult<std::string> CGameLevelsCollection::GetLevelPathByIndex(TDEngine2::USIZE index) const
	{
		if (index >= mGameLevels.size())
		{
			return Wrench::TErrValue<E_RESULT_CODE>(RC_FAIL);
		}

		return Wrench::TOkValue<std::string>(mGameLevels[index]);
	}

	const std::vector<std::string>& CGameLevelsCollection::GetLevels() const
	{
		return mGameLevels;
	}

	TDEngine2::USIZE CGameLevelsCollection::GetLevelsCount() const
	{
		return mGameLevels.size();
	}

	const TPtr<IResourceLoader> CGameLevelsCollection::_getResourceLoader()
	{
		return mpResourceManager->GetResourceLoader<CGameLevelsCollection>();
	}


	TDE2_API CGameLevelsCollection* CreateGameLevelsCollection(IResourceManager* pResourceManager, const std::string& name, E_RESULT_CODE& result)
	{
		return CREATE_IMPL(CGameLevelsCollection, CGameLevelsCollection, result, pResourceManager, name);
	}


	TDE2_DEFINE_DEFAULT_RESOURCE_LOADER(GameLevelsCollection)
	TDE2_DEFINE_DEFAULT_RESOURCE_FACTORY(GameLevelsCollection)
}