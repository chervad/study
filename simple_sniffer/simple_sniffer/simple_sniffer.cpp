#include <windows.h>
#include <winsock.h>
#include <iostream>

#define SIO_RCVALL 0x98000001

int main()
{
	u_long RS_Flag = 1;
	SOCKET socket;
	ioctlsocket(socket, SIO_RCVALL, &RS_Flag);
    std::cout << "Hello World!\n"; 
	system("PAUSE");
}
