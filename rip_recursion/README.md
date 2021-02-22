# C recursion using RIP register

`gcc -g addy_recursion.c`

```
/* 
disasm:
         0x0000000008001149 <+0>:     endbr64                       # <main>
         0x000000000800114d <+4>:     push   %rbp
         0x000000000800114e <+5>:     mov    %rsp,%rbp
         0x0000000008001151 <+8>:     sub    $0x10,%rsp
         0x0000000008001155 <+12>:    lea    -0x7(%rip),%rax        # 0x8001155 <main+12>

      RIP is <main+12> (0xc) when we read it, so we uglily substract 12 from (uint64_t rip) address value


gdbenv:
        Breakpoint 1, main () at ptr.c:20
        20                        printf("RIP: 0x%lx\n", rip - 12);
        (gdb) n
        RIP: 0x8001149
        21                        uint64_t (*mainptr)() = (uint64_t (*)())rip - 12;
        (gdb) p/x &main
        $1 = 0x8001149
        (gdb)
*/
```
