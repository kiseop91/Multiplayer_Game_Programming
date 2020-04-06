#include "MemoryStream.h"
void OutputMemoryStream::ReallocBuffer(uint64_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//realloc 실패에대한 처리필요
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData,
	size_t inByteCount)
{
	//공간확보, 부족시 2배씩 증가
	uint64_t resultHead = mHead + static_cast<uint64_t>(inByteCount);
	if (resultHead > mCapacity)
	{
		ReallocBuffer(std::max(mCapacity * 2, resultHead));
	}

	//메모리복사
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//해더이동
	mHead = resultHead;
}

//template<typename T>
//void Write(const std::vector<T> inVector)
//{
//	uint64_t elementCount = inVector.size();
//	Write(elementCount);
//	for (const T& element : inVector)
//	{
//		Write(element);
//	}
//}
void InputMemoryStream::Read(void* outData,
	uint64_t inByteCount)
{
	uint64_t resultHead = mHead + inByteCount;
	if (resultHead > mCapacity)
	{
	}

	std::memcpy(outData, mBuffer + mHead, inByteCount);

	mHead = resultHead;
}