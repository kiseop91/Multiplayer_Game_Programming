#include "PCH.h"
class OutputMemoryStream
{
public:
	OutputMemoryStream() :
		mBuffer(nullptr), mHead(0), mCapacity(0)
	{
		ReallocBuffer(32);
	}
	OutputMemoryStream() { std::free(mBuffer); }
	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	void Write(const void* inData, size_t inByteCount);
	void Write(uint32_t inData) { Write(&inData, sizeof(inData)); }
	void Write(int32_t inData) { Write(&inData, sizeof(inData)); }

private:
	void ReallocBuffer(uint32_t inNewLength);
	
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

class InputMemoryStream
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount)
		:mCapacity(inByteCount),mHead(0)
	{
	}
	void Read(InputMemoryStream& inStream);
	const uint32_t	 kMaxPacketSize = 1470;
	void ReceiveRoboCat(int inSocket, RoboCat* outRoboCat);

private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};