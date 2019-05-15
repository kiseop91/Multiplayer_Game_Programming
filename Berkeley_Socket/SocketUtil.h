#pragma once
#include <WinSock2.h>
#include "TCPSocket.h"
enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
	//UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily)

	TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily)
	{
		SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
		if (s != INVALID_SOCKET)
			return TCPSocketPtr(new TCPSocket(s));

		//_STL_REPORT_ERROR(L"SocketUtil::CreateTCPSocket");
		return nullptr;
	}
};



