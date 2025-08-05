```c
#include <ctype.h> //Testing and mapping characters
#include <errno.h> //Error library
#include <stdio.h> //Input-output library
#include <stdlib.h> //General-purpose functions
#include <termios.h> //Terminal library.
#include <unistd.h> 

struct termios orig_termios;

//Error handling function. If function returns error code, trigger die() function.
void die(const char *s) { 
  perror(s);
  exit(1);
}

//Return to terminal original attributes
void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) 
    die("tcsetattr");
}

//Disable several byteflags from termios structure to enable raw mode.
void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) die("tcgetattr");
  atexit(disableRawMode);
  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main() {
  enableRawMode();
  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read"); //EAGAIN (Resource temporarily unavailable). Handle empty input operation.
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
  return 0;
}
```

