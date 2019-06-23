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
	std::cout << "--------------------------------------" << std::endl;
	std::cout << '\n' << "이름 : " << remsg.name << std::endl;
	std::cout << "레벨 : " << remsg.level << std::endl;
	std::cout << "점수 : " << remsg.score << std::endl;
	std::cout << "현재위치 : " << remsg.x << ", " << remsg.y << std::endl;
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
	character tmp;
	std::cout << "\n\n" << " 정보입력, 아이디, 레벨, 점수, 시작 위치(x,y) ";
	std::cin >> tmp.name >> tmp.level >> tmp.score >> tmp.x >> tmp.y;
	std::cout << "\n\n" << "---------------------------------------------" << "\n\n";
	while (true)
	{
		clientSock->Send(&tmp, sizeof(tmp));
		clientSock->Receive(&tmp, sizeof(tmp));
		print(tmp);

		std::cout <<'\n'<< "이동할 좌표를 입력하세요 (x, y)";
		std::cin >> tmp.x >> tmp.y;
		clientSock->Send(&tmp, sizeof(tmp));
	}

	WSACleanup();
	return 0;
}