#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

HANDLE hComm;

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main(){

	char a = 10;
	DWORD dNoOFBytestoWrite = sizeof(a);         // No of bytes to write into the port
	DWORD dNoOfBytesWritten = 0;     // No of bytes written to the port

	DCB dcbSerialParams = { 0 }; // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	dcbSerialParams.BaudRate = CBR_115200;  // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None

	SetCommState(hComm, &dcbSerialParams);

	printf("Opening serial port...\n");
	hComm = CreateFile(
	             "\\\\.\\COM7", GENERIC_READ|GENERIC_WRITE, 0, 0,
	             OPEN_EXISTING, 0, NULL );
	if (hComm == INVALID_HANDLE_VALUE)
	{
	         printf("Error\n");
	         return 1;
	    }
	    else printf("OK\n");

	BOOL Status;
/*
	while(a < 75){
	    if(WriteFile(hComm, &a, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL) == 0){
	    	printf("error");
	    	return -1;
	    }
	    printf("%d\n", a);
	    a++;
	    delay(1500);
	}
*/
	Status = SetCommMask(hComm, EV_RXCHAR);

	DWORD dwEventMask;
	Status = WaitCommEvent(hComm, &dwEventMask, NULL);

	char temp; //Temporary character used for reading
	DWORD NoBytesRead = 1;

	while(1) {
		if(ReadFile( hComm,           //Handle of the Serial port
			             &temp,       //Temporary character
			             sizeof(temp),//Size of TempChar
			             &NoBytesRead,    //Number of bytes read
			             NULL)){
			printf("%d\n", temp);
			WriteFile(hComm, &a, dNoOFBytestoWrite, &dNoOfBytesWritten, NULL);
			a++;
			if(a == 20) a = 0;
		}
	}

	return 0;

}
