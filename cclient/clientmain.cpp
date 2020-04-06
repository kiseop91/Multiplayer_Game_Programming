#include <iostream>
#include "PCH.h"
#include "MemoryStream.h"
class Character
{
public:
	int id = -1;
	char name[10];
	int level = 1;
	int score = 0;
	float x = 0, y = 0;
	//int* pointer;
	//vector<int> vec;
	void Write(OutputMemoryStream& inStream) const;
	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(id);
		inStream.Read(name, 10);
		inStream.Read(level);
		inStream.Read(score);
		inStream.Read(x);
		inStream.Read(y);
	}
};
void Character::Write(OutputMemoryStream& inStream) const
{
	inStream.Write(id);
	inStream.Write(name,10);
	inStream.Write(level);
	inStream.Write(score);
	inStream.Write(x);
	inStream.Write(y);
}

void print(const Character& remsg)
{
	std::cout << "--------------------------------------" << std::endl;
	std::cout << '\n' << "�̸� : " << remsg.name << std::endl;
	std::cout << "���� : " << remsg.level << std::endl;
	std::cout << "���� : " << remsg.score << std::endl;
	std::cout << "������ġ : " << remsg.x << ", " << remsg.y << std::endl;
	//std::cout << "�����ʹ�? : " << *remsg.pointer << std::endl;
	std::cout << "--------------------------------------" << std::endl;
}
int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	SocketAddressFactory fac;
	string ip = "222.235.79.120:9190";
	SocketAddress clientAddr;
	clientAddr = *fac.CreateIPv4FromString(ip);

	TCPSocketPtr clientSock = SocketUtil::CreateTCPSocket(INET);


	clientSock->Connect(clientAddr);
	Character tmp;
	std::cout << "\n\n" << " ((�����Է�)) �̸� , ����,  ����, ��ǥ( x, y) "<<std::endl;
	std::cin >> tmp.name >> tmp.level>> tmp.score >> tmp.x >> tmp.y;
	std::cout << "\n\n" << "---------------------------------------------" << "\n\n";
	//tmp.pointer = new int(5);
	while (true)
	{
		OutputMemoryStream out;
		tmp.Write(out);
		char* Buffer = static_cast<char*>(malloc(1470));
		memcpy(Buffer, out.GetBufferPtr(), out.GetLength());

		clientSock->Send(Buffer, out.GetLength()); // 6�� 28�� ������� �۾�����.
		int siz = clientSock->Receive(Buffer, 1470);
		InputMemoryStream in(Buffer,siz);
		tmp.Read(in);
		print(tmp);

		std::cout << '\n' << "�̵��� ��ǥ�� �Է��ϼ��� (x, y)";
		std::cin >> tmp.x >> tmp.y;
		tmp.Write(out);
		clientSock->Send(Buffer, siz);
	}

	WSACleanup();
	return 0;
}