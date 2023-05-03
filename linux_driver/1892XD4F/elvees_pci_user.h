#ifndef __USER__H
#define __USER__H

//
// Коды IoControl для драйвера Elvees MCB
//

#define FSCTL_ELVEES_BASE      0xa000

#define _ELVEES_CTL_CODE(_Function, _access)  \
            CTL_CODE(FSCTL_ELVEES_BASE, _Function, METHOD_BUFFERED, _access)

// Чтение области памяти из адресного окна устройства.
// InBuffer должен содержать 32-битное смещение требуемой области памяти от
// начала адресного окна MCB (эквивалентно адресу в Спецификации микросхемы).
// Вызов осуществляет чтение OutputBufferLength байтов.
#define IOCTL_ELVEES_READ_AREA		_ELVEES_CTL_CODE(0x201, FILE_READ_ACCESS)

// Запись массива байтов в адресного окна устройства.
// InBuffer должен содержать 32-битное смещение требуемой области памяти от
// начала адресного окна MCB (эквивалентно адресу в Спецификации микросхемы),
// затем массив байтов для записи. В адресное окно будет записано
// (InputBufferLength - 4) байтов данных.
#define IOCTL_ELVEES_WRITE_AREA		_ELVEES_CTL_CODE(0x202, FILE_WRITE_ACCESS)

// Чтение области памяти из адресного окна устройства с использованием DMA
// (Bus Mastering).
// InBuffer должен содержать 32-битное смещение требуемой области памяти от
// начала адресного окна MCB (эквивалентно адресу в Спецификации микросхемы).
// Вызов осуществляет чтение OutputBufferLength байтов.
#define IOCTL_ELVEES_READ_AREA_DMA	\
	CTL_CODE(FSCTL_ELVEES_BASE, 0x203, METHOD_OUT_DIRECT, FILE_READ_ACCESS)

// Запись массива байтов в адресного окна устройства с использованием DMA
// (Bus Mastering).
// InBuffer должен содержать 32-битное смещение требуемой области памяти от
// начала адресного окна MCB (эквивалентно адресу в Спецификации микросхемы),
// затем массив байтов для записи. В адресное окно будет записано
// (InputBufferLength - 4) байтов данных.
#define IOCTL_ELVEES_WRITE_AREA_DMA	\
	CTL_CODE(FSCTL_ELVEES_BASE, 0x204, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)



#endif // __USER__H
