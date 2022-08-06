assume cs:code,ds:data

data segment
 db 'dec','Ken Olsen',137,40,'PDP'
data ends

code segment
start:mov ax,data
 mov ds,ax
 mov bx,20
 mov si,0
 mov cx,3
 mov byte ptr ds:[bx].12,38
 add byte ptr ds:[bx].14,70
s:mov byte ptr ds:[bx].16[si],'X'
 inc si
 loop s

 mov ax,4c00h
 int 21h
code ends
end start
