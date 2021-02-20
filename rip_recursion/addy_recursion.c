/* RIP recursion */

#include <stdio.h>
#include <inttypes.h>

/* gdbenv:
		Breakpoint 1, main () at ptr.c:20
		20              printf("RIP: 0x%lx\n", rip - 12);
		(gdb) n
		RIP: 0x8001149
		21              uint64_t (*mainptr)() = (uint64_t (*)())rip;
		(gdb) p/x &main
		$1 = 0x8001149
		(gdb)
*/

int main(void)	/* 0x8001149 */
{
	uint64_t rip;
	/* 
	   	0x0000000008001149 <+0>:     endbr64					   # <main>
   		0x000000000800114d <+4>:     push   %rbp
   		0x000000000800114e <+5>:     mov    %rsp,%rbp
   		0x0000000008001151 <+8>:     sub    $0x10,%rsp
   		0x0000000008001155 <+12>:    lea    -0x7(%rip),%rax        # 0x8001155 <main+12>

		RIP is <main+12> (0xc) when we read it, so we uglily substract it from uint64_t rip variable
   	*/
	asm volatile("1: lea 1b(%%rip), %0;" : "=a"(rip));	/* 0x8001155 */
	printf("RIP: 0x%lx\n", rip - 12);
	uint64_t (*mainptr)() = (uint64_t (*)())rip;
	mainptr();
	return 0;
}