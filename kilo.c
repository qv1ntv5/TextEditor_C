#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
struct termios orig_termios;

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){ 
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
  enableRawMode();
  char c[10] = {0};
  c[9]='\n';
  read(STDIN_FILENO, c, 9);
  printf("You printed: %s\n",c);
  return 0;
}