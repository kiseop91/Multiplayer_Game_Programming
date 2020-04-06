#pragma once
#include "MemoryStream.h"
class BlockData
{
public:
	int posX;
	int posY;         //Block Position
	int blockType;      //0, softbloc, 1. hardblock, 2. tree, 3, none 4, bush   
	int blockIndex;   //for block image render
	int tileIndex;      //for tile image render
	int innerItem;      //0, range 1.speed 2, bomb drop limit up 3, no Item
	int size;
public:
	BlockData(int);
	BlockData(char _blockType, char _tileIndex, char _blockIndex);
	~BlockData();

public:
	void Write(OutputMemoryStream& outStream);
	void Read(InputMemoryStream& inStream);
	void show();
};//data size =  6 BYTE