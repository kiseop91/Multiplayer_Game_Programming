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

void print(const character& remsg)
{
	std::cout << "�̸� : " << remsg.name << std::endl;
	std::cout << "���� : " << remsg.level << std::endl;
	std::cout << "���� : " << remsg.score << std::endl;
	std::cout << "������ġ : " << remsg.x << ", " << remsg.y << std::endl;
}

void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
{
	std::cout << "Ŭ���̾�Ʈ�� �����Ͽ����ϴ�!!" << std::endl;
	while (true) {
		character msg;
		int size = ClientSocket->Receive(&msg, 100);
		if (size < 0) {
			break;
		}
		print(msg);
		ClientSocket->Send(&msg, sizeof(msg));
	}
	std::cout << "Ŭ���̾�Ʈ ���� ����" << std::endl;
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
	std::cout << "������ �����մϴ�!" << std::endl;
	std::cout << "Ŭ���̾�Ʈ ���� �����..." << std::endl;

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