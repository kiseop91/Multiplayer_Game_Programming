#include "BlockData.h"

BlockData::BlockData(int n)
	: posX(n), posY(n), blockType(n), blockIndex(n), tileIndex(n), innerItem(n), size(n)
{
}
BlockData::BlockData(char _blockType, char _tileIndex, char _blockIndex)
	: blockType(_blockType), tileIndex(_tileIndex), blockIndex(_blockIndex)
{
}
BlockData::~BlockData()
{
}
void BlockData::Write(OutputMemoryStream & outStream)
{
	outStream.Write(&posX, sizeof(posX));
	outStream.Write(&posY, sizeof(posY));
	outStream.Write(&blockType, sizeof(blockType));
	outStream.Write(&blockIndex, sizeof(blockIndex));
	outStream.Write(&tileIndex, sizeof(tileIndex));
	outStream.Write(&innerItem, sizeof(innerItem));
}
void BlockData::Read(InputMemoryStream & inStream)
{
	inStream.Read(&posX, sizeof(posX));
	inStream.Read(&posY, sizeof(posY));
	inStream.Read(&blockType, sizeof(blockType));
	inStream.Read(&blockIndex, sizeof(blockIndex));
	inStream.Read(&tileIndex, sizeof(tileIndex));
	inStream.Read(&innerItem, sizeof(innerItem));
}
void BlockData::show()
{
	std::cout << "block position x : " << (int)posX << " y : " << (int)posY << "\n";

	std::cout << "block type : ";
	switch ((int)blockType) {
	case 0:
		std::cout << "soft block\n";
		break;
	case 1:
		std::cout << "hard block\n";
		break;
	case 2:
		std::cout << "tree\n";
		break;
	case 3:
		std::cout << "just tile\n";
		break;
	case 4:
		std::cout << "bush\n";
		break;
	}

	if ((int)blockType == 0) {
		std::cout << "soft block color : ";
		switch ((int)tileIndex) {
		case 0:
			std::cout << "yellow\n";
			break;
		case 1:
			std::cout << "blue\n";
			break;
		case 2:
			std::cout << "orange\n";
			break;
		}

		std::cout << "inner item : ";
		switch ((int)innerItem)
		{
		case 0:
			std::cout << "range up\n";
			break;
		case 1:
			std::cout << "speed up\n";
			break;
		case 2:
			std::cout << "bomb drop limit up\n";
			break;
		case 3:
			std::cout << "no item\n";
		}
	}

	if ((int)blockType == 1) {
		std::cout << "hard block color : ";
		switch ((int)blockIndex) {
		case 0:
			std::cout << "red\n";
			break;
		case 1:
			std::cout << "orange\n";
			break;
		case 2:
			std::cout << "yellow(box)\n";
			break;
		}
	}

	if ((int)blockType == 4) {
		std::cout << "tileType : ";
		switch ((int)tileIndex)
		{
		case 0:
			std::cout << "normal green block\n";
			break;
		case 1:
			std::cout << "heavy green block\n";
			break;
		case 2:
			std::cout << "general road\n";
			break;
		case 3:
			std::cout << "road with center line\n";
			break;
		case 4:
			std::cout << "road with across walk\n";
			break;
		}
	}
}
