#include <asm/ioctls.h>
#include <asm/termbits.h>
#include <deque>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include<string>
//#include "ros/ros.h"
//#include "std_msgs/Float32.h"

int main(int argc, char** argv)
{

//ros::init(argc, argv, "betaflight_sonar_node");
//ros::NodeHandle nh("~");

//std::string portStr;
//nh.param("serial_port", portStr, std::string("/dev/ttyUSB0"));

//int baudrate;
//nh.param("baudrate", baudrate, 9600);

//// Publishers
//ros::Publisher fp = nh.advertise<std_msgs::Float32>("sonar", 1);

std::string portStr = "/dev/ttyUSB0";
int sp = open(portStr.c_str(), O_RDWR | O_NOCTTY);
printf("%d",sp);

  struct termios2 uart_config;
  /* Fill the struct for the new configuration */
  ioctl(sp, TCGETS2, &uart_config);

  // Output flags - Turn off output processing
  // no CR to NL translation, no NL to CR-NL translation,
  // no NL to CR translation, no column 0 CR suppression,
  // no Ctrl-D suppression, no fill characters, no case mapping,
  // no local output processing
  //
  uart_config.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR | OFILL | OPOST);

  // Input flags - Turn off input processing
  // convert break to null byte, no CR to NL translation,
  // no NL to CR translation, don't mark parity errors or breaks
  // no input parity check, don't strip high bit off,
  // no XON/XOFF software flow control
  //
  uart_config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK
      | ISTRIP | IXON);

  //
  // No line processing:
  // echo off
  // echo newline off
  // canonical mode off,
  // extended input processing off
  // signal chars off
  //
  uart_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

  // Turn off character processing
  // Turn off odd parity
  uart_config.c_cflag &= ~(CSIZE | PARODD | CBAUD);

  // Enable parity generation on output and parity checking for input.
  uart_config.c_cflag |= PARENB;
  // Set two stop bits, rather than one.
  uart_config.c_cflag |= CSTOPB;
  // No output processing, force 8 bit input
  uart_config.c_cflag |= CS8;
  // Enable a non standard baud rate
  uart_config.c_cflag |= BOTHER;

  // Set custom baud rate of 100'000 bits/s necessary for sbus
  const speed_t spd = 100000;
  uart_config.c_ispeed = spd;
  uart_config.c_ospeed = spd;

return 0;
}
