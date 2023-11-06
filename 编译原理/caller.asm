1    caller:
2        pushl %ebp              #Save old %ebp
3        movl %esp, %ebp         #Set %ebp as frame pointer
4        subl $24, %esp          #Allocate 24 bytes on stack
5        movl $534, -4(%ebp)     #Set arg1 to 534
6        movl $1057, -8(%ebp)    #Set arg2 to 1057
7        leal -8(%ebp), %eax     #Compute &arg2
8        movl %eax, 4(%esp)      #Store on stack
9        leal -4(%ebp), %eax     #Compute &arg1
10       movl %eax, (%esp)       #Store on stack
11       call swap_add           #Call the swap_add function
12       ...


1    swap_add:
2        pushl %ebp              #Save old %ebp
3        movl %esp, %ebp         #Set %ebp as frame pointer
4        pushl %ebx              #Save %ebx

5        movl 8(%ebp), %edx      #Get xp
6        movl 12(%ebp), %ecx     #Get yp
7        movl (%edx), %ebx       #Get x
8        movl (%ecx), %eax       #Get y
9        movl %eax, (%edx)       #Store y at xp
10       movl %ebx, (%ecx)       #Store x at yp
11       addl %ebx, %eax         #Return value = x+y

12       popl %ebx               #Restore %ebx
13       popl %ebp               #Restore %ebp
14       ret                     #Return