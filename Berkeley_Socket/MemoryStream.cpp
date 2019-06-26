#include "MemoryStream.h"

void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	mBuffer = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void * inData, size_t inByteCount)
{
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(std::max(mCapacity * 2, resultHead));

	std::memcpy(mBuffer + mHead, inData, inByteCount);
	mHead = resultHead;
}

void InputMemoryStream::Read(InputMemoryStream & inStream)
{
	// To Do : ��ü�� �°� ��ǲ��Ʈ�� �����ؾ���.
	//inStream.Read(mHealth);
}

void InputMemoryStream::ReceiveRoboCat(int inSocket, RoboCat * outRoboCat)
{
}
