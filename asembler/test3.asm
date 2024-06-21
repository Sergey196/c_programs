section	.text
   global _start    ; необходимо для линкера (ld)
   
section .data                        
num: dd 1234567890
str: db '0000000000',0x0a
strlen equ $ - str
    
	
_start:	            ; сообщает линкеру стартовую точку
   mov ebx,[num]
   mov eax,str
   mov edi,eax
   call inttostr

   mov	edx,strlen  ; длина строки 
   mov	ecx,str     ; строка
   mov	ebx,1       ; дескриптор файла (stdout)
   mov	eax,4       ; номер системного вызова (sys_write)
   int  80h         ; вызов ядра
	
   mov	eax,1       ; номер системного вызова (sys_exit)
   int  80h         ; вызов ядра 
 
inttostr:
;ebx=num
;edi=str
   mov ecx,1000000000
   call inttostr_digit
   mov ecx,100000000
   call inttostr_digit
   mov ecx,10000000
   call inttostr_digit
   mov ecx,1000000
   call inttostr_digit
   mov ecx,100000
   call inttostr_digit
   mov ecx,10000
   call inttostr_digit
   mov ecx,1000
   call inttostr_digit
   mov ecx,100
   call inttostr_digit
   mov ecx,10
   call inttostr_digit
   mov ecx,1
   ;call inttostr_digit
   ;ret
  
inttostr_digit:
;ebx=num, ecx=divisor
;edi=str
   mov al,'0'-1
inttostr_digit0:
   inc al
   sub ebx,ecx
   jnc inttostr_digit0
   add ebx,ecx
   stosb
   ret
   
 
