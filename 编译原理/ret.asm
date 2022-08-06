assume cs:code,ds:stack

stack segment
 db 16 dup (0)
stack ends

code segment
 mov ax,0 
of:mov ax,4c00h
 int 21h

start:mov ax,stack
 mov ss,ax
 mov sp,16
 mov ax,offset of
 push ax
 ret
code ends
end start
