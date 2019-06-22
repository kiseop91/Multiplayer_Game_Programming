#include "PCH.h"

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

	WSACleanup();
}