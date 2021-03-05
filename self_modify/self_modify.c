#include <stdio.h>
#include <unistd.h>     /* getpagesize() */
#include <sys/mman.h>	/* mprotect() */

static int rw = 0;

int unlock_text_segment(void *addr) {
	if (rw == 1) { return 0; }

	int page_size = getpagesize();
	addr -= (unsigned long)addr % page_size;
	
	printf("[mprotect]: setting rw on %lx / sz: %d\n", (unsigned long)addr, page_size);
	
	int chmemm = mprotect(addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC);
	if (chmemm != 0) {
 		printf("[E%d]: failed to set rw on text segment\n", chmemm);
		return 1;
	}
	rw = 1;	
}	

int main(void) {
	int x = 4;
	int y = 2;
	int eax_val = x + y;
	
	unsigned char (*mainptr)() = main;		/* we could set this directly to <main+0x21>, but i needed <main> address, for other things that i removed from here.. */
	unsigned char *xptr = *mainptr + 0x21;	        /* points to {0x01}[0xd0] 'add eax, edx' , we're gonna change this to: {0x01}[0xc0] 'add eax, eax' */
	
	unlock_text_segment(mainptr);			/* unlock text segment */
	
	printf("[%p - opcode: 0x%02hhx] sz: %zu byte\n", xptr, *xptr, sizeof(*xptr));
	printf("[mem]: x = { %d } | y = { %d } | (x + y) -> z_value: %d\n", x, y, eax_val);
	if (*xptr == 0xd0) {
		printf("[op]: changing opcode 0x%02hhx to 0xc0 { 'add eax, edx' -> 'add eax, eax' }..\n", *xptr);
		*xptr = 0xc0;				/* change edx to eax d0 -> c0 */
		main();					/* jump to main() */
	}
	return 0;
}
