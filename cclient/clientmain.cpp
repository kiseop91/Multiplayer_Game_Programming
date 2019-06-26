#include "PCH.h"
#include <iostream>

class Character
{
public:
	int id = -1;
	char name[10];
	int level = 1;
	int score = 0;
	int x = 0, y = 0;
	//int* pointer;
	//vector<int> vec;
};
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
	string ip = "127.0.0.1:9190";
	SocketAddress clientAddr;
	clientAddr = *fac.CreateIPv4FromString(ip);

	TCPSocketPtr clientSock = SocketUtil::CreateTCPSocket(INET);


	clientSock->Connect(clientAddr);
	Character tmp;
	std::cout << "\n\n" << " ((�����Է�)) �̸� , ���� ";
	std::cin >> tmp.name >> tmp.level; //>> tmp.score >> tmp.x >> tmp.y;
	std::cout << "\n\n" << "---------------------------------------------" << "\n\n";
	//tmp.pointer = new int(5);
	while (true)
	{
		clientSock->Send(&tmp, sizeof(tmp));
		clientSock->Receive(&tmp, sizeof(tmp));
		print(tmp);

		std::cout << '\n' << "�̵��� ��ǥ�� �Է��ϼ��� (x, y)";
		std::cin >> tmp.x >> tmp.y;
		clientSock->Send(&tmp, sizeof(tmp));
	}

	WSACleanup();
	return 0;
}