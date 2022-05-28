#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial)
{
	size_t s = strcspn(login, "\n");
	login[s] = 0;
	size_t len = strnlen(login, 32); // at ebp-0xc;
	if (len <= 5) {
		return 1;
	}
	if (ptrace(0, 0, NULL, 0) == -1) {
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return 1;
	}

	int hash = (login[3] ^ 0x1337) + 0x5eeded; // at ebp-0x10
	const int key = 0x88233b2b;

	int tmp1, tmp2, tmp3, tmp4, tmp5;
	long long tmpl;
	size_t i = 0;
	for (i = 0; i < len; ++i) { // at ebp-0x14
		if (login[i] <= 0x1f) { // non-printable characters
			return 1;
		}
		tmp1 = hash ^ login[i];
		tmpl = (long)tmp1 * (long)key;
		tmp2 = (tmpl >> 32);
		tmp3 = (tmp1 - tmp2) / 2;
		tmp4 = (tmp3 + tmp2) / 1024;
		tmp5 = tmp4 * 0x539;
		hash += tmp1 - tmp5;
	}

	printf("%d\n", hash);

	if (serial == hash) {
		return 0;
	} else {
		return 1;
	}
}

int main()
{
	char login[0x20]; // at esp+0x2c
	unsigned int serial; // at esp+0x28

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(login, 0x20, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial);
	
	if (!auth(login, serial))
	{
		puts("Authenticated!");
		system("/bin/sh");
		return 0;
	}

	return 1;
}