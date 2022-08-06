assume cs:code ds:data

code segment
 dw 1111h,2222h
 mov bx,0
 mov ax,0
s:add ax,cs:[bx]
 add bx,2
 loop s

 mov ax,4c00h
 int 21h
code ends
end
