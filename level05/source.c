#include <stdio.h>

int main()
{
    int a = 0;
    char buff[100]; //0x64 = 100
    fgets(&buff, 100, stdin);
    do{
        if ('@' < buff[a] && buff[a] < '[')
            buff[a] = tolower(buff[a]);
        if (a >= strlen(buff))
        {
            printf(buff);
            exit(0);
        }
    a += 1;
    }while(1);
}
