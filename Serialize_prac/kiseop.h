#pragma once
#include "MemoryStream.h"

class kiseop
{
private:

	char name;
	int age;
	std::vector<uint64_t> v;
public:
	kiseop(int age = 0, char name = ' ')
		:age(age), name(name)
	{}
	void init()
	{
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
	}
	void print()
	{
		std::cout << "나이 : " << age << "   이름 : " << name << std::endl;
		for (auto x : v)
			std::cout << x;
	}
	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(&age, sizeof(age));
		inStream.Read(&name, sizeof(name));
		inStream.Read(v);
	}
	void Write(OutputMemoryStream& outStream)
	{
		outStream.Write(&age, sizeof(age));
		outStream.Write(&name, sizeof(name));
		outStream.Write(v);
	}
};