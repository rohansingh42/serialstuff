//#include <stdio.h>      // standard input / output functions
//#include <stdlib.h>
//#include <string>     // string function definitions
//#include <unistd.h>     // UNIX standard function definitions
//#include <fcntl.h>      // File control definitions
//#include <errno.h>      // Error number definitions
//#include <termios.h>    // POSIX terminal control definitions
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
#include <SerialStream.h>
//#include <SerialStreamBuf.h>
#include <iostream>

#define MODEMDEVICE "/dev/ttyACM0"

using namespace LibSerial;

int main()
{
int res, cnt;
struct termios oldtio,newtio;
char buf[6];
char airspeedX[3];
char airspeedY[3];
unsigned char c='D';
int ii = 0;
float flowvec[3];
bool STOP =false;


int baudrate = 9600;


// Open serial port
// O_RDWR - Read and write
// O_NOCTTY - Ignore special chars like CTRL-C

//std::string portStr = "/dev/ttyS1";
std::string path = "/dev/ttyACM0";

SerialStream flowPort;

flowPort.Open(path);

flowPort.SetBaudRate( SerialStreamBuf::BAUD_9600 ) ;

flowPort.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;

flowPort.SetNumOfStopBits(1) ;

flowPort.SetParity( SerialStreamBuf::PARITY_ODD ) ;

flowPort.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_HARD ) ;

std::cout<<flowPort.IsOpen();

//while (STOP == false) 
{       
	flowPort>>c;//.read(buf,6);
	std::cout<<c;
	//res = read(flowPort,buf,1);   
	//buf[res]=0;               
	//printf(":%s:%d\n", buf, res);
	/*if (c == 'a') 
	{
		cnt = 0;
	}
	else if (c == 'z') 
	{
		if (cnt == 4) 
		{
			for (ii=0; ii<2; ii++) 
			{
				airspeedX[ii] = buf[ii];
				airspeedY[ii] = buf[ii+2];
			}
			airspeedX[2] = '\0';
			airspeedY[2] = '\0';

			flowvec[0] = ((atoi(airspeedX)-50.0f)/5.0f); 
			flowvec[1] = (atoi(airspeedY)-50.0f)/5.0f; 

			STOP = true;
		}
	}
	else 
	{
	buf[cnt] = c;
	cnt += 1;
	}*/
} 


  return 0;
}
