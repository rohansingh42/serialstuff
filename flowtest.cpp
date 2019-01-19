#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SerialStream.h>

#define MODEMDEVICE "/dev/ttyACM0"

using namespace LibSerial;

int main()
{
int flowPort, res, cnt;
struct termios oldtio,newtio;
char buf[255];
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
char* path = "/dev/ttyACM0";
flowPort = open(path, O_RDWR | O_NOCTTY);
printf("%djj",flowPort);
SerialStream t;

memset(&newtio,0,sizeof(newtio)); // clear struct for new port settings

cfsetispeed(&newtio, baudrate); // Input port speed
cfsetospeed(&newtio, baudrate); // Output port speed

//newtio.c_cflag &= ~PARENB; // no parity bit
//newtio.c_cflag &= ~CSTOPB; // 1 stop bit
//newtio.c_cflag &= ~CSIZE; // Only one stop bit
//newtio.c_cflag |= CS8; // 8 bit word

newtio.c_iflag = 0; // Raw output since no parity checking is done
newtio.c_oflag = 0; // Raw output
newtio.c_lflag = 0; // Raw input is unprocessed
//newtio.c_cflag = 0;

newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */

tcflush(flowPort, TCIFLUSH);
tcsetattr(flowPort, TCSANOW, &newtio);


if (flowPort) 
{
	while (STOP == false) 
	{       
		res = read(flowPort,buf,1);   
		buf[res]=0;               
		printf(":%s:%d\n", buf, res);
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
}

  return 0;
}
