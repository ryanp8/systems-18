#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void process_string(char* str);

int main() {

  int pw_fds[2];
  int cw_fds[2];

  pipe(pw_fds);
  pipe(cw_fds);

  // printf("pw pipe created. fd[READ]: %d, fd[WRITE]: %d\n", pw_fds[READ], pw_fds[WRITE]);

  int f = fork();
  
  if (f) {
    close(pw_fds[READ]);
    close(cw_fds[WRITE]);
    while (1) {
      printf("input: ");
      char buf[1024];
      fgets(buf, sizeof(buf), stdin);
      write(pw_fds[WRITE], buf, strlen(buf));
     }
  }
  else {
    close(pw_fds[WRITE]);
    close(cw_fds[READ]);
    char input_buf[1024];
    while(read(pw_fds[READ], input_buf, sizeof(input_buf))) {
      process_string(input_buf);
      write(cw_fds[WRITE], input_buf, strlen(input_buf));
    }
  }
  
  return 0;
}


void process_string(char *str) {
  str[0] = '$';
}
