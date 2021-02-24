global _start

section .data
    strz    db  "[ASM-16]: ", 0x0 ; 0xa ; 0xa - newline term
    len     equ $ - strz
    deflen  db  16

buffer: times 16 db 0

section .text

_start:
    push    ebp
    mov     ebp, esp
    call    readin
    xor     eax, eax
    call    printmsg
    xor     ebx, ebx    ; return 0
    mov     eax, 0x1    ; sys_exit = 1
    pop     ebp
    int     0x80        ; syscall

; omit - dbgfunc
retfunc:
    push    ebp
    mov     ebp, esp
    mov     eax, 39
    pop     ebp
    ret

dbgprint:
    push    ebp
    mov     ebp,    esp

    mov     eax,    0x4     ; sys_write
    mov     ebx,    0x1     ; stdout
    mov     ecx,    strz    ; string
    mov     edx,    len     ; strlen

    int     0x80            ; call kernel
    pop     ebp
    ret

printmsg:
    push    ebp
    mov     ebp, esp
    
    mov     eax, 0x4    ; syscall (sys_write)
    mov     ebx, 0x1    ; stdout = 1

    mov     ecx, buffer ; string
    
    mov     edx, 16     ; strlen
    
    int     0x80        ; call kernel
    pop     ebp
    ret

readin:
    push    ebp
    mov     ebp,        esp

    call    dbgprint

    mov     eax,        0x3    ; syscall (sys_read)
    mov     ebx,        0x0    ; stdin = 0?

    mov     ecx,        buffer ; input buffer
    mov     edx,        16     ; size to read

    int     0x80                ; call kernel

    pop     ebp
    ret
