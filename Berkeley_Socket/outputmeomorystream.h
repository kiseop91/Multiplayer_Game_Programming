#pragma once
class OutputMemoryStream
{
public:
	OutputMemoryStream() :
	mBuffer(nullptr), mHead(0),mCapacity(0)
	{
		ReallocBuffer(32);
	}
	~OutputMemoryStream()
	{std::free(mBuffer);}

	void Write(const void* inData, size_t inByteCount);

	template<typename T>
	void Write(const T& inData)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value, "원시 타입만 지원합니다.");
		Write(&inData, sizeof(inData));
	}

private:
	void ReallocBuffer(uint32_t inNewLength);
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(std::max(mCapacity * 2, resultHead));

	std::memcpy(mBuffer + mHead, inData, inByteCount);
	mHead = resultHead;
}

/////////////////////////
class InputMemoryStream
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount):
		mCapacity(inByteCount),mHead(0)
	{
		mBuffer = inBuffer;
	}
	~InputMemoryStream()
	{ std::free(mBuffer); }

	uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }

	void Read(void* outData, uint32_t inByteCount)
	{
		uint32_t resultHead = mHead + inByteCount;
		if (resultHead > mCapacity)
		{}//에러 컨트롤 필요.
		std::memcpy(outData, mBuffer + mHead, inByteCount);
		mHead = resultHead;
	}

	template< typename T > void Read(T& outData)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Read only supports primitive data types");
		Read(&outData, sizeof(outData));
	}

	void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
	void Read(int32_t& outData) { Read(&outData, sizeof(outData)); }

private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
