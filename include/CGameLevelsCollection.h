/*!
	\file CGameLevelsCollection.h
	\date 17.12.2022
	\author Ildar Kasimov
*/

#pragma once


#include <TDEngine2.h>
#include <string>
#include <vector>


namespace Game
{
	class CGameLevelsCollection;


	/*!
		\brief A factory function for creation objects of GameLevelsCollection's type

		\param[in, out] pResourceManager A pointer to IResourceManager's implementation
		\param[in] name A resource's name
		\param[in] id An identifier of a resource
		\param[out] result Contains RC_OK if everything went ok, or some other code, which describes an error

		\return A pointer to CFont's implementation
	*/

	TDE2_API CGameLevelsCollection* CreateGameLevelsCollection(TDEngine2::IResourceManager* pResourceManager, const std::string& name, TDEngine2::E_RESULT_CODE& result);


	/*!
		class CGameLevelsCollection

		\brief The class contains list of all in-game levels that could be played
	*/

	class CGameLevelsCollection : public TDEngine2::CBaseResource, public TDEngine2::ISerializable
	{
		public:
			friend 	TDE2_API CGameLevelsCollection* CreateGameLevelsCollection(TDEngine2::IResourceManager*, const std::string&, TDEngine2::E_RESULT_CODE&);
		public:
			typedef std::unordered_map<std::string, std::string> TPrefabsToPathHashTable;
		public:
			TDE2_REGISTER_RESOURCE_TYPE(CGameLevelsCollection)
			TDE2_REGISTER_TYPE(CGameLevelsCollection)

			/*!
				\brief The method initializes an internal state of a font

				\param[in, out] pResourceManager A pointer to IResourceManager's implementation
				\param[in] name A resource's name

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API virtual TDEngine2::E_RESULT_CODE Init(TDEngine2::IResourceManager* pResourceManager, const std::string& name);

			/*!
				\brief The method resets current internal data of a resource

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API TDEngine2::E_RESULT_CODE Reset() override;

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

			TDE2_API const std::vector<std::string>& GetLevels() const;
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(CGameLevelsCollection)

			TDE2_API const TDEngine2::TPtr<TDEngine2::IResourceLoader> _getResourceLoader() override;
		private:
			static constexpr TDEngine2::U16 mVersionTag = 0x1;

			std::vector<std::string> mGameLevels;
	};


	TDE2_DECLARE_DEFAULT_RESOURCE_LOADER(GameLevelsCollection)
	TDE2_DECLARE_DEFAULT_RESOURCE_FACTORY(GameLevelsCollection)
}