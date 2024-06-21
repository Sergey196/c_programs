section .text
   global _start          ; должно быть объявлено для линкера (gcc)
	
_start:                   ; сообщаем линкеру входную точку
   mov	edx,1		      ; длина сообщения 
   mov	ecx,number        ; сообщение для вывода на экран
   mov	ebx,1		      ; файловый дескриптор (stdout)
   mov	eax,4		      ; номер системного вызова (sys_write)
   int	0x80		      ; вызов ядра 
 
   mov	eax,1		      ; номер системного вызова (sys_exit)
   int	0x80		      ; вызов ядра
 
section .data
number DW 12345
