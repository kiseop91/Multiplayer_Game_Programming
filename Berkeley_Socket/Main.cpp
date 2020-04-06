#include "PCH.h"
#include <iostream>
#include <thread>
#include <mutex>
#include "MemoryStream.h"
class Player
{
public:
	int id = -1;
	char name[10];
	int level = 1;
	int score = 0;
	float x = 0, y = 0;
	//int* pointer;
	//vector<int> vec;
	void Write(OutputMemoryStream& inStream) const;
	void Read(InputMemoryStream& inStream)
	{
		inStream.Read(id);
		inStream.Read(name, 10);
		inStream.Read(level);
		inStream.Read(score);
		inStream.Read(x);
		inStream.Read(y);
	}
};
void Player::Write(OutputMemoryStream& inStream) const
{
	inStream.Write(id);
	inStream.Write(name, 10);
	inStream.Write(level);
	inStream.Write(score);
	inStream.Write(x);
	inStream.Write(y);
}

int clientNumber = 0; //critical section 처리필요함.
Player c1{ -1,"",0,0,0,0 };


void print(const Player& remsg, const int thisclientNumber)
{
	std::cout << thisclientNumber << "번 클라이언트 정보" << std::endl;
	std::cout << "이름 : " << remsg.name << std::endl;
	std::cout << "레벨 : " << remsg.level << std::endl;
	std::cout << "점수 : " << remsg.score << std::endl;
	std::cout << "현재위치 : " << remsg.x << ", " << remsg.y << '\n' << std::endl;
	//std::cout << "포인터는? : " << *remsg.pointer << std::endl;
}

bool wait = true;
std::mutex mtx;

int fight(Player c) // 승리한 사람의 id를 리턴.
{
	if (c1.id == -1)
	{
		c1 = c;
		return -1;
	}
	else
	{
		if (c1.level > c.level)
		{
			std::cout << c1.name << "님이 승리했습니다." << std::endl;
			return c1.id;
		}
		else
		{
			std::cout << c.name << "님이 승리했습니다." << std::endl;
			return c.id;
		}
		wait = false;
	}
}
void echo(TCPSocketPtr ServSock, TCPSocketPtr ClientSocket)
{
	clientNumber++; // critical section
	std::cout << clientNumber << "번 클라이언트가 접속하였습니다!!" << std::endl;
	int thisclientNumber = clientNumber;
	while (true) {
		Player user;

		char* Buffer = static_cast<char*>(malloc(1470));

		int size = ClientSocket->Receive(Buffer, 1470);
		if (user.id == -1) // 처음 접속할 때 아이디넘버 부여
			user.id = thisclientNumber;
		if (size < 0) {
			break;
		}
		InputMemoryStream in(Buffer, size);
		user.Read(in);
		print(user, thisclientNumber);
		ClientSocket->Send(Buffer, size);

		size = ClientSocket->Receive(Buffer, 1470);
		if (size < 0) {
			break;
		}
	}
	std::cout << thisclientNumber << "번 클라이언트 접속 종료" << '\n' << std::endl;
}

int main()
{
	WSADATA wsaData;
	auto err = WSAStartup(MAKEWORD(2, 2), &wsaData);

	//sockaddr_in addr;
	SocketAddressFactory fac;
	//string ip = "127.0.0.1:9190";
	SocketAddress servAddr(INADDR_ANY, 9190);//중요!
	//SocketAddress servAddr;
	SocketAddress clientAddr;
//	servAddr = *fac.CreateIPv4FromString("222.235.79.120:9190");

	TCPSocketPtr ServSock = SocketUtil::CreateTCPSocket(INET);

	ServSock->Bind(servAddr);
	std::cout << "서버를 시작합니다!" << std::endl;
	std::cout << "클라이언트 접속 대기중..." << std::endl;

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