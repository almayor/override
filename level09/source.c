#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg
{
    char text[140];
    char user[40];
    int len;
} msg_t;

void    secret_backdoor()
{
    char    buf[128];
    fgets(buf, 128, stdin);
    system(buf);
}

void set_username(msg_t *msg)
{
    char buf[128];
    puts(">: Enter your username");
    printf(">>: ");
    fgets(buf, 128, stdin);
    for (int i = 0; i <= 40 && buf[i]; i++)
        msg->user[i] = buf[i];
    printf(">: Welcome, %s", msg->user);
}

void set_msg(msg_t *msg)
{
    char buf[1024];

    puts("Message @Unix-Dude");
    printf(">>: ");
    fgets(buf, 128, stdin);
    strncpy(msg->text, buf, msg->len);
}

void handle_msg()
{
    msg_t msg = {.text = {}, .len = 140};
    set_username(&msg);
    set_msg(&msg);
    puts(">: Msg sent!");
}

int main()
{
    puts("--------------------------------------------\n"
         "|   ~Welcome to l33t-m$n ~    v1337        |\n"
         "--------------------------------------------");
    handle_msg();
}
