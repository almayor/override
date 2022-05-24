"\nInvalid Password"
"/bin/sh"
"Congratulations!"

"%d"
"%u"

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test(uint arg1, uint arg2) {
	uint res = arg2 - arg1;
	switch (res) {
		case 0x1:
			decrypt(res);
			break;
		case 0x2:
			decrypt(res);
			break;
		case 0x3:
			decrypt(res);
			break;
		case 0x4:
			decrypt(res);
			break;
		case 0x5:
			decrypt(res);
			break;
		case 0x6:
			decrypt(res);
			break;
		case 0x7:
			decrypt(res);
			break;
		case 0x8:
			decrypt(res);
			break;
		case 0x9:
			decrypt(res);
			break;
		case 0x10:
			decrypt(res);
			break;
		case 0x11:
			decrypt(res);
			break;
		case 0x12:
			decrypt(res);
			break;
		case 0x13:
			decrypt(res);
			break;
		case 0x14:
			decrypt(res);
			break;
		case 0x15:
			decrypt(res);
			break;
		default:
			decrypt(rand());
			break;
	}
}

int main() {
	int val;

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");

	printf("Password:");
	scanf("%d", val);
	test(val, 0x1337d00d);

	return 0;
}
