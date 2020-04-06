#include "MemoryStream.h"
void OutputMemoryStream::ReallocBuffer(uint64_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//realloc ���п����� ó���ʿ�
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData,
	size_t inByteCount)
{
	//����Ȯ��, ������ 2�辿 ����
	uint64_t resultHead = mHead + static_cast<uint64_t>(inByteCount);
	if (resultHead > mCapacity)
	{
		ReallocBuffer(std::max(mCapacity * 2, resultHead));
	}

	//�޸𸮺���
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//�ش��̵�
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