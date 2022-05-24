#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int num;

	puts("***********************************");
	puts("* \t     -Level00 -\t\t  *");
	printf("Password:");

	scanf("%d", &num);
	if (num == 0x149c) {
		puts("\nAuthenticated!");
		system("/bin/sh");
		return 0;
	}
	else {
		puts("\nInvalid Password!");
		return 1;
	}
}
