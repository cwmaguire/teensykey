#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#if defined(OS_LINUX) || defined(OS_MACOSX)
#include <sys/ioctl.h>
#include <termios.h>
#elif defined(OS_WINDOWS)
#include <conio.h>
#endif

#include "hid.h"

static int string_to_int(char*);

int main(int argc, char *argv[])
{
  static const int DEVICE_ID = 0;
  static const int BUFF_SIZE = 64;
	int i, r, num, password_num;
	char buf[BUFF_SIZE];

	// C-based example is 16C0:0480:FFAB:0200
	r = rawhid_open(1, 0x16C0, 0x0480, 0xFFAB, 0x0200);
	if (r <= 0) {
		// Arduino-based example is 16C0:0486:FFAB:0200
		r = rawhid_open(1, 0x16C0, 0x0486, 0xFFAB, 0x0200);
		if (r <= 0) {
			printf("no rawhid device found\n");
			return -1;
		}
	}
	printf("found rawhid device\n");

  if(argc >= 2){
    password_num = string_to_int(argv[1]);
    printf("Rest of string is %s\n", argv[1]);
  }else{
    printf("argc was not >= 1\n");
    return -1;
  }

  printf("\nSending %d\n", password_num);
  buf[0] = (char) password_num;
  for(i = 1; i < BUFF_SIZE; i++){
    buf[i] = 0;
  }
  rawhid_send(0, buf, BUFF_SIZE, 100);

  // check if any Raw HID packet has arrived
  num = rawhid_recv(DEVICE_ID, buf, BUFF_SIZE, 220);
  if (num < 0) {
    printf("\nerror reading, device went offline\n");
    rawhid_close(DEVICE_ID);
    return -1;
  }

  if (num > 0) {
    printf("\nrecv %d bytes with %d length string:\n", num, buf[0]);
    for (i = 1; i <= buf[0]; i++) {
      printf("%c", buf[i]);
    }
    printf("\n");
  }

  return 0;
}

int string_to_int(char *string)
{
  char *tail;
  int number;
  int errno = 0;
  number = strtol(string, &tail, 0);
  if(errno){
    printf("Overflow\n");
  }else{
    string = tail;
  }

  return number;
}
