assume cs:code

code segment 

start:mov ax,cs
 mov ds,ax
 mov si,offset insert
 
 mov ax,0
 mov es,ax
 mov di,200h
 mov cx,offset insert0end-offset insert

 cld
 rep movsb 

 mov ax,0
 mov es,ax
 mov word ptr es:[0],200h
 mov word ptr es:[2],0 

 mov ax,4c00h
 int 21h
 
insert:jmp short insert0start
 db 'welcome to masm!'
insert0start: mov ax,cs
 mov ds,ax
 mov si,202h
 mov ax,0b800h
 mov ax,es
 mov di,12*160+36*2
 mov cx,16
s:mov al,ds:[si]
 mov es:[di],al
 inc si
 add di,2
 loop s

 mov ax,4c00h
 int 21h
insert0end: nop

code ends

end start
