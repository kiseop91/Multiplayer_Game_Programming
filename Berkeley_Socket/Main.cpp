#include "PCH.h"
#include <iostream>
#include <thread>
struct character
{
	char name[10];
	int level;
	int score;
	int x, y;
};

int clientNumber = 0; //critical section 처리필요함.

void print(const character& remsg,const int thisclientNumber)
{
	std::cout << thisclientNumber << "번 클라이언트 정보" << std::endl;
	std::cout << "이름 : " << remsg.name << std::endl;
	std::cout << "레벨 : " << remsg.level << std::endl;
	std::cout << "점수 : " << remsg.score << std::endl;
	std::cout << "현재위치 : " << remsg.x << ", " << remsg.y << '\n' << std::endl;
}

void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
{
	clientNumber++; // critical section
	std::cout << clientNumber <<"번 클라이언트가 접속하였습니다!!" << std::endl;
	int thisclientNumber = clientNumber;
	while (true) {
		character msg;
		int size = ClientSocket->Receive(&msg, sizeof(msg));
		if (size < 0) {
			break;
		}
		print(msg, thisclientNumber);
		ClientSocket->Send(&msg, sizeof(msg));

		size = ClientSocket->Receive(&msg, sizeof(msg));
		if (size < 0) {
			break;
		}
	}
	std::cout << thisclientNumber<< "번 클라이언트 접속 종료" <<'\n'<< std::endl;
}

int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	//sockaddr_in addr;
	SocketAddressFactory fac;
	string ip = "127.0.0.1:9190";
	SocketAddress servAddr;
	SocketAddress clientAddr;
	servAddr = *fac.CreateIPv4FromString(ip);

	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);

	ServSock->Bind(servAddr);
	std::cout << "서버를 시작합니다!" << std::endl;
	std::cout << "클라이언트 접속 대기중..." << std::endl;

	ServSock->Listen(5);



	while (true)
	{
		TCPSocketPtr ClientSocket;
		ClientSocket = ServSock->Accept(clientAddr);

		std::thread t1(echo, ServSock, ClientSocket);
		t1.detach();
	}


	WSACleanup();
}