assume cs:code

code segment
 mov ax,1000h
 mov ds,ax
 mov bx,ds:[1]
 
 mov ax,4c00h
 int 21h
code ends
end
