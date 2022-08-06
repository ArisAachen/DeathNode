assume cs:code,ds:data

data segment
 db 'welcome to masm!'
 db 16 dup (0)
data ends

code segment
start:mov ax,data
 mov ds,ax
 add ax,16
 mov es,ax
 mov cx,16
 mov si,0
 mov di,0
 cld
 rep movsb
 
 mov ax,4c00h
 int 21h 
code ends
end start
