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
			std::is_enum<T>::value, "���� Ÿ�Ը� �����մϴ�.");
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