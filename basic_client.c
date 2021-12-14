#include "pipe_networking.h"

int main() {

	int to_server;
	int from_server;
	int len;
	char line[100];

	from_server = client_handshake( &to_server );
	printf("Changes 'h' to 'H'\n");
	printf("Type \"exit1\" or \"^C\" to exit client program.\n");
	while (1){
		printf("Input: ");
		fgets(line, 100, stdin);
		sscanf(line, "%s\n", line);
		if (strcmp(line, "exit1") == 0){
			exit(0);
		}
		len = strlen(line) + 1;
		write(to_server, &len, sizeof(int));
		write(to_server, line, 100);
		read(from_server, line, 100);
		printf("Output: %s\n", line);
	}
}
