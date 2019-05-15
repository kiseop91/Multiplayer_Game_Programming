#pragma once
//2019-05-15
// 자료형 안정성을 위한 SocketAddress 클래스
#include <WinSock2.h>
#include <memory>
class SocketAddress
{
public:

	SocketAddress(uint32_t inAddress, uint16_t inPort);

	SocketAddress(const sockaddr& inSockAddr);

	size_t GetSize() const;

private:
	sockaddr mSockAddr;

	sockaddr_in* GetAsSockAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
};
using SocketAddressPtr = std::shared_ptr<SocketAddress>;
