#include "PCH.h"
#include <iostream>
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
	std::cout << "Start Server!" << std::endl;
	std::cout << "Waitng for Client" << std::endl;

	ServSock->Listen(5);

	TCPSocketPtr ClientSocket;
	ClientSocket = ServSock->Accept(clientAddr);
	std::cout << "Connect Client !!" << std::endl;

	while (true)
	{
		char msg[30];
		int size = ClientSocket->Receive(msg, 30);
		std::cout << "client msg : " << msg<<std::endl;
		ClientSocket->Send(msg, size);

	}
	

	WSACleanup();
}