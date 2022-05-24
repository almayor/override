#include <string.h>
#include <stdio.h>

char a_user_name[100];

int verify_user_name(const char *username) {
	puts("verifying username....\n");
	return strncmp(username, "dat_will", 7);
}

int verify_user_pass(const char *password) {
	return strncmp(password, "admin", 5);
}

int main() {
	char a_user_pass[16];
	int ret = 0;

	memset(a_user_pass, 0, 16);

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(a_user_name, 256, stdin);

	ret = verify_user_name(a_user_name);
	if (ret) {
		puts("nope, incorrect username...\n");
		return 1;
	}

	puts("Enter Password: ");
	fgets(a_user_pass, 100, stdin); // BINGO!

	ret = verify_user_pass(a_user_pass);
	if (ret || !ret) {
		puts("nope, incorrect password...\n");
		return 1;
	}

	return 0;
}
