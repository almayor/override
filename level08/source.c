#include <stdlib.h>
#include <stdio.h>

//file at rbp-0x118
//s at rbp-0x120
//filepath at rbp-0x128
void log_wrapper(FILE* file, char *s, char *filepath) {
	char buf[255]; //at rbp-0x110
	strcpy(buf, s);
	snprinf(buf + strlen(buf), 255 - 1 - strlen(buf), filepath);
	buf[strcspn(buf, "\n")] = 0;
	fprintf(file, "LOG: %s\n", buf);
}

//argc at rbp-0x94
//argv at rbp-0xa0
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s filename\n", argv[0]);
	}
	
	FILE *log = fopen("./backups/.log", "w"); //at rbp-0x88
	if (log == NULL) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(log, "Starting back up: ", argv[1]);
	
	FILE *file = fopen(argv[1], "r"); //at rbp-0x80
	if (file == NULL) {
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}

	char buf[100];
	strcpy(buf, "./backups/");
	strncat(buf, argv[1], 100 - 1 - strlen("./backups/"));

	//at rbp-0x78
	int fid = open(buf, O_EXCL | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (fid < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	char c; //at rbp-0x71
	do {
		c = fgets(file);
	} while (c != EOF);
	log_wrapper(log, "Finished back up ", argv[1]);

	fclose(file);
	close(fid);

	return 0;
}
