#include "SocketAddress.h"

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	GetAsSockAddrIn()->sin_port = htons(inPort);
}

 SocketAddress::SocketAddress(const sockaddr & inSockAddr)
{
	memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
}

size_t SocketAddress::GetSize() const { return sizeof(sockaddr); }
