assume cs:code

code segment 
 jmp s
 mov ax,0
 mov bx,0
 mov cx,0
s:mov dx,0
 
 mov ax,4c00h
 int 21h
code ends
end
