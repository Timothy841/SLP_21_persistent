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
  int from_client = open(WKP, O_RDONLY);
  if (from_client == -1){
	mkfifo(WKP, 0644);
	from_client = open(WKP, O_RDONLY);
  }
  read(from_client, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
  remove(WKP);
  *to_client = open(line, O_WRONLY);
  if (*to_client == -1){
  	mkfifo(line, 0644);
  	*to_client = open(line, O_WRONLY);
  }
  strcat(line, "1");
  write(*to_client, line, 100);
  printf("Wrote message \"%s\" to secret pipe.\n", line);
  remove(ACK);
  read(from_client, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
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
  char line[100] = ACK;
  *to_server = open(WKP, O_WRONLY);
  if (*to_server == -1){
    mkfifo(WKP, 0644);
    *to_server = open(WKP, O_WRONLY);
  }
  write(*to_server, line, 100);
  printf("Wrote message \"%s\" to well-known pipe.\n", line);
  remove(WKP);
  int from_server = open(ACK, O_RDONLY);
  if (from_server == -1){
	   mkfifo(ACK, 0644);
     from_server = open(ACK, O_RDONLY);
  }
  read(from_server, line, 100);
  sscanf(line, "%s\n", line);
  printf("Message \"%s\" received.\n", line);
  remove(ACK);
  strcat(line, "2");
  write(*to_server, line, 100);
  printf("Wrote message \"%s\" to well-known pipe.\n", line);
  printf("Connection established\n");
  return from_server;
}
