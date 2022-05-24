В функции decrypt мы видим использование canary для защиты стека в начале функции:

```
mov     eax, dword [gs:0x14]
mov     dword [ebp-0xc {var_10}], eax
xor     eax, eax  {0x0}
```

и в конце:

```
mov     esi, dword [ebp-0xc {var_10}]
xor     esi, dword [gs:0x14]
je      0x8048740
call    __stack_chk_fail
```