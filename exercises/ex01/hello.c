#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    printf("Hello, World!%i\n", y);
    return 0;
}

/*
1. The diff looks like this. So I mean I guess I think this is the code
    related to that line.
+       subq    $16, %rsp
+       movl    $5, -4(%rbp)
        leaq    .LC0(%rip), %rdi
        call    puts@PLT
        movl    $0, %eax
-       popq    %rbp
+       leave

2. Once again, this is the diff. Not really sure what to make of it.
    Many fewer lines of code.
-       .section        .rodata
+       .section        .rodata.str1.1,"aMS",@progbits,1
 .LC0:
        .string "Hello, World!"
-       .text
+       .section        .text.startup,"ax",@progbits
+       .p2align 4,,15
        .globl  main
        .type   main, @function
 main:
-.LFB0:
+.LFB23:
        .cfi_startproc
-       pushq   %rbp
-       .cfi_def_cfa_offset 16
-       .cfi_offset 6, -16
-       movq    %rsp, %rbp
-       .cfi_def_cfa_register 6
-       subq    $16, %rsp
-       movl    $5, -4(%rbp)
        leaq    .LC0(%rip), %rdi
+       subq    $8, %rsp
+       .cfi_def_cfa_offset 16
        call    puts@PLT
-       movl    $0, %eax
-       leave
-       .cfi_def_cfa 7, 8
+       xorl    %eax, %eax
+       addq    $8, %rsp
+       .cfi_def_cfa_offset 8
        ret
        .cfi_endproc
-.LFE0:
+.LFE23:

3. .string changes to the new string arg in printf, printf doesn't get
    optimized to puts, there are some more movl things
   after using the -O2 tag: fewer lines, uses printf_chk now, some movls
    and xorls are added
    
4. it looks like the movl moves things around and addl adds something to
    it and then some movls maybe assign it to y? don't really know what
    else to say
   looks like non-optimized code has way fewere movls, not really sure how
    to conclude anything about how optimization works from that, don't
    have a strong desire to figure any of this out to be honest
*/