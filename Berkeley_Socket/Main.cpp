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

int clientNumber = 0; //critical section ó���ʿ���.

void print(const character& remsg,const int thisclientNumber)
{
	std::cout << thisclientNumber << "�� Ŭ���̾�Ʈ ����" << std::endl;
	std::cout << "�̸� : " << remsg.name << std::endl;
	std::cout << "���� : " << remsg.level << std::endl;
	std::cout << "���� : " << remsg.score << std::endl;
	std::cout << "������ġ : " << remsg.x << ", " << remsg.y << '\n' << std::endl;
}

void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
{
	clientNumber++; // critical section
	std::cout << clientNumber <<"�� Ŭ���̾�Ʈ�� �����Ͽ����ϴ�!!" << std::endl;
	int thisclientNumber = clientNumber;
	while (true) {
		character msg;
		int size = ClientSocket->Receive(&msg, sizeof(msg));
		if (size < 0) {
			break;
		}
		print(msg, thisclientNumber);
		ClientSocket->Send(&msg, sizeof(msg));

		size = ClientSocket->Receive(&msg, sizeof(msg));
		if (size < 0) {
			break;
		}
	}
	std::cout << thisclientNumber<< "�� Ŭ���̾�Ʈ ���� ����" <<'\n'<< std::endl;
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