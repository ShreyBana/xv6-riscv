#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#define LIMIT 10000

void ping_pong(int fd_r, int fd_w) {
  int cnt = 0;
  char buf = 'p'; // 1 byte
  while (cnt < LIMIT && read(fd_r, &buf, 1)) {
    /* printf("recieved %s\n", exchange_str(buf[0])); */
    cnt++;
    write(fd_w, &buf, 1);
  }
  close(fd_r);
}

int* mk_pipe(char* name) {
  int* p = malloc(2 * sizeof(int));
  if(pipe(p) == 0) {
    printf("created pipe %s\n", name);
  }

  return p;
}

long long current_millis() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
  long long milliseconds = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

  return milliseconds;
}

int main() {
  int* ping_p = mk_pipe("PING");
  int* pong_p = mk_pipe("PONG");

  if (fork() == 0) {
    // The child reads PINGs & writes PONGs.
    ping_pong(ping_p[0], pong_p[1]);
  } else {
    char fb = 'p';
    write(ping_p[1], &fb, 1);
    long long start_time = current_millis();
    // Vice-versa for the parent.
    ping_pong(pong_p[0], ping_p[1]);
    long long delta = current_millis() - start_time;
    printf("exchanges/sec: %lld\n", LIMIT/delta);
  }

  return 0;
}
