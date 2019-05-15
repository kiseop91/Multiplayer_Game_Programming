#pragma once
//2018-05-15
//�ڷ��� �������� ������ TCPSocket Ŭ����
#include <memory>
#include <WinSock2.h>
#include "SocketAddress.h"
class TCPSocket;
using TCPSocketPtr = std::shared_ptr<TCPSocket>;

class TCPSocket
{
public:
	~TCPSocket();
	int connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress);
	int Listen(int inBackLog = 32);
	TCPSocketPtr Accept(SocketAddress& inFromAddress);
	int Send(const void* inData, int inLen);
	int Receive(void* inBuffer, int inLen);

private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	SOCKET mSocket;
};
