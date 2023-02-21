#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;

	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//여기까지가 Winsock 초기화

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSockAddr;
	ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_port = htons(4000);
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	//여기까지가 Socket (소켓을 만들어 줘)
	//IPv4 사용할거고 4000번 포트 사용할거야

	Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	//여기까지 bind

	Result = listen(ServerSocket, 0);
	//여기까지 liten

	SOCKADDR_IN ClientSockAddr;
	ZeroMemory(&ServerSockAddr, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	int ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	//여기까지 Accept

	const char* Message = "Take My Money";
	int SendBytes = send(ClientSocket, Message, strlen(Message) + 1, 0);
	if (SendBytes == 0)
	{
		cout << "Connect Close.";

		return -1;
	}
	else if (SendBytes < 0)
	{
		cout << "error close." << GetLastError() << endl;

		return -1;
	}
	//여기까지가 Send/Recv인데 Recv는 아직...

	closesocket(ClientSocket);
	closesocket(ServerSocket);
	//여기까지 close (다 썻으면 닫아줘야지)

	WSACleanup();
	//여기까지 Winsock 닫기

	return 0;

}