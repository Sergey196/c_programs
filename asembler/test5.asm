section	.text
   global _start        ; должно быть объявлено для линкера (ld)
	
_start:                 ; сообщаем линкеру входную точку 
   mov	edx,9		    ; длина сообщения 
   mov	ecx, stars	    ; сообщение для вывода на экран
   mov	ebx,1		    ; файловый дескриптор (stdout)
   mov	eax,4		    ; номер системного вызова (sys_write)
   int	0x80		    ; вызов ядра
   
   mov	edx,1		      ; длина сообщения 
   mov	ecx,ebdler        ; сообщение для вывода на экран
   mov	ebx,1		      ; файловый дескриптор (stdout)
   mov	eax,4		      ; номер системного вызова (sys_write)
   int	0x80	
 
   mov	eax,1		    ; номер системного вызова (sys_exit)
   int	0x80		    ; вызов ядра 
 
section	.data
stars   times 9 db '*'
ebdler DB 0xa
