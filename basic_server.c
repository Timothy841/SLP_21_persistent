#include "pipe_networking.h"

static void sighandler(int sig){
	if (sig == SIGINT){
		char c[] = "Program exited due to SIGINT.\n";
		printf("%s\n", c);
		exit(0);
	}
}

void change(char *line){
	for (int i = 0; i<strlen(line); i++){
		if (line[i] == 'h'){
			line[i] = 'H';
		}
	}
}

int main() {
	signal(SIGINT, sighandler);
	int to_client;
	int from_client;

	from_client = server_handshake( &to_client );
	char line[100];
	while (1){
		read(from_client, line, 100);
		printf("Received: %s", line);
		change(line);
		if (strcmp(line, "^C") == 0){
			printf("sdfs");
		}
		write(to_client, line, 100);
		printf("Changed and sent back: %s", line);
	}
}
