#include "PCH.h"
#include <iostream>
#include <thread>

void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
{
	std::cout << "클라이언트가 접속하였습니다!!" << std::endl;
	while (true) {
		char msg[30]="";
		int size = ClientSocket->Receive(msg, 30);
		if (size < 0 || msg[0] == '1') {
			break;
		}
		std::cout << "클라이언트 : " << msg << std::endl;
		ClientSocket->Send(msg, size);
	}
	std::cout << "클라이언트 접속 종료" << std::endl;
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