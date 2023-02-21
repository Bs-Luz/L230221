#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//여기까지 Winsock 초기화

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_port = htons(4000);
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//여기까지 Socket (접속할 서버를 세팅해줌)

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	//여기까지 connect

	char Buffer[1024] = { 0, };
	recv(ServerSocket, Buffer, sizeof(Buffer) - 1, 0);

	cout << Buffer << endl;
	//여기까지가 Recv/Send (Send는 아직...)

	//close는 서버에서 처리 해주기 때문에 안해주는듯...

	WSACleanup();

return 0;
}