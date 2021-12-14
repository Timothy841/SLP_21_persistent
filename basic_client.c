#include "pipe_networking.h"


int main() {

	int to_server;
	int from_server;

	from_server = client_handshake( &to_server );
	char line[100];
	printf("Changes 'h' to 'H'\n");
	while (1){
		printf("Input: ");
		fgets(line, 100, stdin);
		write(to_server, line, 100);
		read(from_server, line, 100);
		printf("Output: %s", line);
	}
}
