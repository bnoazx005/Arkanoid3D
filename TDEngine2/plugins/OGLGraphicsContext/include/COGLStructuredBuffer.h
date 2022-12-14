/*!
	\file COGLStructuredBuffer.h
	\date 27.07.2022
	\authors Kasimov Ildar
*/

#pragma once


#include <graphics/IStructuredBuffer.h>
#include <core/CBaseObject.h>


namespace TDEngine2
{
	class IBuffer;
	class IGraphicsContext;


	/*!
		\brief A factory function for creation objects of COGLStructuredBuffer's type

		\return A pointer to COGLStructuredBuffer's implementation
	*/

	TDE2_API IStructuredBuffer* CreateOGLStructuredBuffer(const TStructuredBuffersInitParams& params, E_RESULT_CODE& result);


	/*!
		class COGLStructuredBuffer

		\brief The class implements a functionality of a hardware SSBOs for OGL GAPI
	*/


	class COGLStructuredBuffer : public IStructuredBuffer, public CBaseObject
	{
		public:
			friend TDE2_API IStructuredBuffer* CreateOGLStructuredBuffer(const TStructuredBuffersInitParams&, E_RESULT_CODE&);
		public:
			/*!
				\brief The method initializes an object

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Init(const TStructuredBuffersInitParams& params) override;

			/*!
				\brief The method locks a buffer to provide safe data reading/writing

				\param[in] mapType A way the data should be processed during a lock

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Map(E_BUFFER_MAP_TYPE mapType) override;

			/*!
				\brief The method unlocks a buffer, so GPU can access to it after that operation
			*/

			TDE2_API void Unmap() override;

			/*!
				\brief The method writes data into a buffer

				\param[in] pData A pointer to data, which should be written
				\param[in] count A size of data in bytes

				\return RC_OK if everything went ok, or some other code, which describes an error
			*/

			TDE2_API E_RESULT_CODE Write(const void* pData, USIZE size) override;

			/*!
				\brief The method returns a pointer to buffer's data

				\return The method returns a pointer to buffer's data
			*/

			TDE2_API void* Read() override;

			/*!
				\brief The method binds current Structured buffer to a pipeline

				\param[in] slot A binding slot's index

				\param[in] stride A size of a single Structured entry
			*/

			TDE2_API void Bind(U32 slot) override;

			/*!
				\brief The method returns an internal data of a buffer, which
				contains low-level platform specific buffer's handlers

				\return The method returns an internal data of a buffer, which
				contains low-level platform specific buffer's handlers
			*/

			TDE2_API const TBufferInternalData& GetInternalData() const override;

			/*!
				\brief The method returns buffer's size in bytes

				\return The method returns buffer's size in bytes
			*/

			TDE2_API USIZE GetSize() const override;

			/*!
				\return The method returns an amount of occupied buffer's bytes
			*/

			TDE2_API USIZE GetUsedSize() const override;

			TDE2_API USIZE GetStrideSize() const override;
		protected:
			DECLARE_INTERFACE_IMPL_PROTECTED_MEMBERS(COGLStructuredBuffer)

		protected:
			TPtr<IBuffer>              mpBufferImpl = nullptr;

			USIZE                      mStructuredElementStride;
			USIZE                      mElementsCount;

			bool                       mIsWriteable = false;

			E_STRUCTURED_BUFFER_TYPE   mType;

			U32      mCurrUsedSlot;
	};
}