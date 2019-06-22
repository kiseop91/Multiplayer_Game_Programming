#include "PCH.h"
#include <iostream>

struct character
{
	char name[10];
	int level;
	int score;
	int x, y;
};
void print(const character& remsg)
{
	std::cout << "이름 : " << remsg.name << std::endl;
	std::cout << "레벨 : " << remsg.level << std::endl;
	std::cout << "점수 : " << remsg.score << std::endl;
	std::cout << "현재위치 : " << remsg.x << ", " << remsg.y << std::endl;
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
	character tmp{ "kiseop",99,243,0,0 };
	while (true)
	{
		char msg[30];
		//character tmp{ "kiseop",99,243,0,0 };
		std::cout << "메세지 > ";
		std::cin >> msg;

		clientSock->Send(&tmp, sizeof(tmp));
		if (msg[0] == '1') {
			clientSock->~TCPSocket();
			exit(0);
		}

		//character remsg;
		clientSock->Receive(&tmp, sizeof(tmp));
		print(tmp);
		
		std::cout << "이동할 좌표를 입력하세요 (x, y)"; 
		std::cin >> tmp.x >> tmp.y;
		print(tmp);
		clientSock->Send(&tmp, sizeof(tmp));

	}

	WSACleanup();

	return 0;
}