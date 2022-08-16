// Note that this file will not compile on MacOS as it doesn't provide `prctl`

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/ptrace.h>

int main()
{
	char buf[0x20]; // esp + 0x20 = 0xffffd670 (inside gdb)
	int stat_loc = 0; // esp + 0x1c
	pid_t pid = fork(); // esp + 0xac

	memset(buf, 0, 0x20);

	if (pid == 0)
	{
		// in child
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		ptrace(PT_TRACE_ME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buf); // VULNERABILITY
		return 0;
	}

	while (1)
	{
		wait(&stat_loc);
		
		if (WIFEXITED(stat_loc))
		{
			puts("child is exiting...");
			break;
		}
		if (ptrace(PR_GET_DUMPABLE, pid, 0x2c, 0) != 0xb)
		{
			puts("no exec() for you");
			kill(pid, SIGKILL);
		}
	}

	return 0;
}
