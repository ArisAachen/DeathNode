assume cs:code,ds:data

data segment
 db 'BaSic'
data ends

code segment
start:mov ax,data
 mov ds,ax
 mov bx,0 

s:mov al,ds:[bx]
 and al,11011111B
 mov ds:[bx],al
 inc bx

 mov ax,4c00h
 int 21h
code ends
end start
