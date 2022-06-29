#include <string.h>
#include <stdio.h>
#include <stdint.h>

void clear_stdin(void)
{
    char x = 0;
    while(1)
    {
        x = getchar();
        if(x == '\n' || x == EOF)
            break;
    }
}

unsigned int get_unum()
{
  unsigned int i;

  fflush(stdout);
  scanf("%u", &i);
  clear_stdin();
  return i;
}

int read_number(unsigned int *arr)
{
  int i;

  printf(" Index: ");
  i = get_unum();
  printf(" Number at data[%u] is %u\n", i, arr(i * 4));
  return 0;
}

int store_number(unsigned int *arr)
{
  unsigned int  value;
  unsigned int  i;
  int           ret;

  printf(" Number: ");
  value = get_unum();
  printf(" Index: ");
  i = get_unum();

  if ((i % 3 == 0) || (value >> 0x18 == 0xb7))
  {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    ret = 1;
  }
  else
  {
    arr[i * 4] = value;
    ret = 0;
  }
  return ret;
}

int main(int argc, char **argv, char **env)
{
  char          cmd[20];
  int           ret;
  char          arr[100];

  while (*argv)
  {
    memset(*argv, 0, strlen(*argv));
    argv += 1;
  }

  while (*env)
  {
    memset(*env, 0, strlen(*env));
    env += 1;
  }

  puts("----------------------------------------------------\n"
       "  Welcome to wil\'s crappy numbersstorage service!  \n"
       "----------------------------------------------------\n"
       " Commands:                                          \n"
       "    store - store a number into the data storage    \n"
       "    read  - read a number from the data storage     \n"
       "    quit  - exit the program                        \n"
       "----------------------------------------------------\n"
       "   wil has reserved some storage :>                 \n"
       "----------------------------------------------------\n"
      );
  do
  {
    printf("Input command: ");
    ret = 1;

    fgets(cmd, 0x14, stdin);
    if (!strcmp(cmd, "store"))
      ret = store_number(arr);
    else if (!strcmp(cmd, "read"))
      ret = read_number(arr);
    else if (!strcmp(cmd, "quit"))
      return 0;

    if (ret)
      printf(" Failed to do %s command\n", cmd);
    else
      printf(" Completed %s command successfully\n", cmd);

  } while (1);
}
