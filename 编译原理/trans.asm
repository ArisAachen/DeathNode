assume cs:code,ds:data

data segment
 db 'welcome to masm!'
data ends

code segment 
start:mov ax,data
 mov ds,ax
 mov si,0
 mov cx,16
 call trans
 mov ax,4c00h
 int 21h

trans:and byte ptr ds:[si],11011111b
 inc si
 loop trans
 ret
code ends
end start
