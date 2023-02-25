#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/select.h>

#define STDIN_FILENO 0

struct termios org_opts;

/** Select to check if stdin has pending input */
int pending_input(void) {
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
  select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &fds);
}

/** Input terminal mode; save old, setup new */
void setup_terminal(void) {
  struct termios new_opts;
  tcgetattr(STDIN_FILENO, &org_opts);
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ISIG | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
}

/** Shutdown terminal mode */
void reset_terminal(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
}

/** Return next input or -1 if none */
int next_input(void) {
  if (!pending_input())
    return -1;
  int rtn = fgetc(stdin);
  printf("Found: %d\n", rtn);
  return(rtn);
}

int main()
{
  setup_terminal();

  printf("Press Q to quit...\n");
  for (;;) {
    int key = next_input();
    if (key != -1) {
      if ((key == 113) || (key == 81)) {
        printf("\nNormal exit\n");
        break;
      }
    }
  }

  reset_terminal();
  return 0;
}
