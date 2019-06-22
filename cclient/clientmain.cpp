#include "PCH.h"
#include <iostream>
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

	while (true)
	{
		char msg[30];
		std::cout << "send > ";
		std::cin >> msg;

		if (msg[0] == '1')
			clientSock->~TCPSocket();

		clientSock->Send(msg, sizeof(msg));
		char remsg[30];
		clientSock->Receive(remsg, sizeof(msg));
		std::cout << "server : " << remsg << std::endl;
	}

	WSACleanup();

	return 0;
}