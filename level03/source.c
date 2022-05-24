#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void decrypt(char arg) {
	char buffer[] = "Q}|u`sfg~sf{}|a3";

	size_t len = strlen(s1);
	for (size_t i = 0; i < len; ++i) {
		buffer[i] = buffer[i] ^ arg;
	}
	if (!strncmp("Congratulations!", buffer, 17)) {
		system("/bin/sh");
	} else {
		puts("\nInvalid Password");
	}
}

void test(int arg1, int arg2) {
	int res = arg2 - arg1;

	// this was originally written as a switch statement
	if ((res >= 0x01 && res <= 0x09) ||
		(res >= 0x10 && res <= 0x15)) {
		decrypt(res);
	} else
	{
		decrypt(rand());
	}
}

int main() {
	int val;

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");

	printf("Password:");
	scanf("%d", &val);
	test(val, 0x1337d00d); // 322424845

	return 0;
}
