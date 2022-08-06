assume cs:code

code segment
 mov ax,86a1h
 mov dx,1
 mov bx,100
 div bx

 mov ax,1000h
 mov bh,1
 div dh
 mov ax,4c00h
 int 21h
code ends
end
