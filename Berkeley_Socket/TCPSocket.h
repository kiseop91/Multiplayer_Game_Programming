#pragma once
//2018-05-15
//자료형 안정성을 보강한 TCPSocket 클래스
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
