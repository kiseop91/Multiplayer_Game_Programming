#include "MemoryStream.h"
#include "kiseop.h"
#include "BlockData.h"
#include <vector>

int intRead(InputMemoryStream& in)
{
	int a = 0;
	in.Read(a);
	BlockData block(2);
	std::cout << a << std::endl;
	for (int i = 0; i < 1; i++)
	{
		block.Read(in);
		std::vector<BlockData> v;
		v.push_back(block);
		std::cout << v.back().posX << (int)block.posY << (int)block.blockIndex << (int)block.blockType << std::endl;
	}
	return 0;
}

int main()
{
	std::vector<BlockData> blocks;
	BlockData block(2);

	block.posX = 1;
	block.posY = 2;
	block.blockType = 3;
	block.blockIndex = 4;
	block.tileIndex = 5;
	block.innerItem = 6;
	blocks.push_back(block);

	BlockData block2(2);

	block2.posX = 11;
	block2.posY = 12;
	block2.blockType = 2;
	block2.blockIndex = 14;
	block2.tileIndex = 54;
	block2.innerItem = 64;

	blocks.push_back(block2);
	

	OutputMemoryStream outStream;
	for (auto block : blocks) {
		block.Write(outStream);
	}
	//block.Write(outStream);

	char* Buffer = static_cast<char*>(malloc(1470));
	memcpy(Buffer, outStream.GetBufferPtr(), outStream.GetLength()); //카피(소켓통신으로 가정)
	
	InputMemoryStream inStream(Buffer, 1470);

	for (int i = 0; i < 2; i++)
	{
		BlockData block(0);
		block.Read(inStream);
		std::cout << block.posX << block.posY << block.blockIndex << block.blockType << std::endl;
		block.show();
	}

	return  0;
}