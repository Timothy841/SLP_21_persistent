#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client
  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char line[100];
  char pipe[100];
  mkfifo(WKP, 0644);
  int from_client = open(WKP, O_RDONLY);
  read(from_client, line, 100);
  remove(WKP);
  sscanf(line, "%s\n", line);
  strcpy(pipe, line);
  mkfifo(line, 0644);
  *to_client = open(line, O_WRONLY);
  strcat(line, "1");
  write(*to_client, line, 100);
  remove(pipe);
  read(from_client, line, 100);
  if (strcmp(line, strcat(pipe, "12"))){
    printf("Connection unsecure.\n");
    exit(0);
  }
  sscanf(line, "%s\n", line);
  printf("Connection established\n");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char line[100];
  snprintf(line, 100, "%d", getpid());
  char pipe[100];
  strcpy(pipe, line);
  mkfifo(WKP, 0644);
  *to_server = open(WKP, O_WRONLY);
  write(*to_server, line, 100);
  mkfifo(pipe, 0644);
  int from_server = open(pipe, O_RDONLY);
  read(from_server, line, 100);
  sscanf(line, "%s\n", line);
  if (strcmp(line, strcat(pipe, "1"))){
    printf("Connection unsecure.\n");
    exit(0);
  }
  strcat(line, "2");
  write(*to_server, line, 100);
  printf("Connection established\n");
  printf("%d %d\n", *to_server, from_server);
  return from_server;
}
