#ifndef _ELVEES_PCI_BITS_H
#define _ELVEES_PCI_BITS_H

/*-----------------------------------------------------------------------------
 *
 * Регистры интерфейсов Space Wire
 */

/*
 * Маски для установки отдельных полей регистров
 */

/* STATUS */
#define MC_SWIC_DC_ERR		0x00000001	/* Признак ошибки рассоединения */
#define MC_SWIC_P_ERR		0x00000002	/* Признак ошибки четности */
#define MC_SWIC_ESC_ERR		0x00000004	/* Признак ошибки в ESC-последовательности */
#define MC_SWIC_CREDIT_ERR	0x00000008	/* Признак ошибки кредитования */
#define MC_SWIC_DS_STATE	0x000000E0	/* Состояние DS-макроячейки */
#define MC_SWIC_RX_BUF_FULL	0x00000100	/* Буфер приема полон */
#define MC_SWIC_RX_BUF_EMPTY	0x00000200	/* Буфер приема пуст */
#define MC_SWIC_TX_BUF_FULL	0x00000400	/* Буфер передачи полон */
#define MC_SWIC_TX_BUF_EMPTY	0x00000800	/* Буфер передачи пуст */
#define MC_SWIC_GOT_FIRST_BIT	0x00001000	/* Признак получения первого бита */
#define MC_SWIC_CONNECTED	0x00002000	/* Признак установленного соединения */
#define MC_SWIC_GOT_TIME	0x00004000	/* Принят маркер времени из сети */
#define MC_SWIC_GOT_INT		0x00008000	/* Принят код распределенного прерывания из сети */
#define	MC_SWIC_GOT_POLL	0x00010000	/* Принят poll-код из сети */
#define MC_SWIC_FL_CONTROL	0x00020000	/* Признак занятости передачей управляющего кода */
#define MC_SWIC_IRQ_LINK	0x00040000	/* Состояние запроса прерырывания LINK */
#define MC_SWIC_IRQ_TIM		0x00080000	/* Состояние запроса прерырывания TIM */
#define MC_SWIC_IRQ_ERR		0x00100000	/* Состояние запроса прерырывания ERR */

/* Значения поля DS_STATE регистра STATUS */
#define MC_SWIC_DS_ERROR_RESET	0
#define MC_SWIC_DS_ERROR_WAIT	1
#define MC_SWIC_DS_READY	2
#define MC_SWIC_DS_STARTED	3
#define MC_SWIC_DS_CONNECTING	4
#define MC_SWIC_DS_RUN		5

/* RX_CODE */
#define MC_SWIC_TIME_CODE	0x000000FF	/* Значение маркера времени, принятого из сети последним */
#define MC_SWIC_INT_CODE	0x0000FF00	/* Значение кода распределенного прерывания, принятого из сети последним */
#define MC_SWIC_POLE_CODE	0x00FF0000	/* Значение poll-кода, принятого из сети последним */

/* MODE_CR */
#define MC_SWIC_LinkDisabled	0x00000001	/* Установка LinkDisabled для блока DS-кодирования */
#define MC_SWIC_AutoStart	0x00000002	/* Установка AutoStart для блока DS-кодирования */
#define MC_SWIC_LinkStart	0x00000004	/* Установка LinkStart для блока DS-кодирования */
#define MC_SWIC_RX_RST		0x00000008	/* Установка блока приема в начальное состояние */
#define MC_SWIC_TX_RST		0x00000010	/* Установка блока передачи в начальное состояние */
#define MC_SWIC_DS_RST		0x00000020	/* Установка DS-макроячейки в начальное состояние */
#define MC_SWIC_SWCORE_RST	0x00000040	/* Установка контроллера в начальное состояние */
#define MC_SWIC_WORK_TYPE	0x00000100	/* Тип режима работы */
#define MC_SWIC_TIMING_WR_EN	0x00004000	/* Разрешение записи в поле TIMING регистра TX_SPEED */
#define MC_SWIC_AUTO_TX_SPEED	0x00008000	/* Признак автоматического установления скорости передачи 
						   после соединения (см. Спецификацию!!!) */
#define MC_SWIC_LINK_MASK	0x00040000	/* Маска прерывания LINK */
#define MC_SWIC_TIM_MASK	0x00080000	/* Маска прерывания TIM */
#define MC_SWIC_ERR_MASK	0x00100000	/* Маска прерывания ERR */

/* TX_SPEED */
#define MC_SWIC_TX_SPEED_PRM_MASK	0xFF		/* Маска коэффициента умножения TX_PLL */
#define MC_SWIC_TX_SPEED_PRM(x)	((x) & 0xFF)		/* Установка коэффициента умножения TX_PLL */
#define MC_SWIC_PLL_TX_EN	0x00000100		/* Разрешение работы TX_PLL */
#define MC_SWIC_LVDS_EN		0x00000200		/* Разрешение работы приемопередатчиков LVDS */
#define MC_SWIC_TX_SPEED_CON(x)	(((x) & 0xFF) << 10)	/* Скорость передачи данных при установлении соединения */
#define MC_SWIC_TIMING(x)	(((x) & 0xF) << 20)	/* В это поле необходимо записать код, равный тактовой 
							   частоте работы CPU, деленной на 10*/

/* TX_CODE */
#define MC_SWIC_TXCODE		0x0000001F	/* Управляющий код (содержимое) */
#define MC_SWIC_CODETYPE	0x000000E0	/* Признак кода управления */

/* Значение поля CODETYPE регистра TX_CODE */
#define MC_SWIC_CODETYPE_TIME	2
#define MC_SWIC_CODETYPE_INT	3
#define MC_SWIC_CODETYPE_POLL	5

/* Прерывания для SWIC */
#define MC_SWIC0_IRQ		5
#define MC_SWIC0_TX_DESC_IRQ	0
#define MC_SWIC0_TX_DATA_IRQ	1
#define MC_SWIC0_RX_DESC_IRQ	2
#define MC_SWIC0_RX_DATA_IRQ	3
#define MC_SWIC1_IRQ		6
#define MC_SWIC1_TX_DESC_IRQ	15
#define MC_SWIC1_TX_DATA_IRQ	16
#define MC_SWIC1_RX_DESC_IRQ	17
#define MC_SWIC1_RX_DATA_IRQ	18

/*
 * Регистры DMA
 */

/* Регистр CSR для каналов DMA */
#define MC_DMA_CSR_RUN		0x00000001	/* Состояние работы канала DMA */
#define MC_DMA_CSR_DIR		0x00000002	/* Направление передачи для каналов MEM_CH */
#define MC_DMA_CSR_WN(n)	((n) << 2)	/* Установка длины пачки */
#define MC_DMA_CSR_EN64		0x00000040	/* Передача 64-разрядных данных (для MEM_CH) */
#define MC_DMA_CSR_IPD		0x00000040	/* Запрет прерывания по запросу от порта при выключенном канале DMA(RUN=0) */
#define MC_DMA_CSR_START_DSP	0x00000080	/* Разрешение запуска DSP (для MEM_CH) */
#define MC_DMA_CSR_MODE		0x00000100	/* Режим модификация адреса регистра IR0 */
#define MC_DMA_CSR_2D		0x00000200	/* Режим модификации адреса регистра IR1 */
#define MC_DMA_CSR_CHEN		0x00001000	/* Признак разрешения самоинициализации */
#define MC_DMA_CSR_IM		0x00002000	/* Маска прерывания при окончании передачи блока */
#define MC_DMA_CSR_END		0x00004000	/* Признак завершения передачи блока данных */
#define MC_DMA_CSR_DONE		0x00008000	/* Признак завершения передачи цепочки блоков данных */
#define MC_DMA_CSR_WCX_MASK	0xffff0000	/* Маска счетчика слов */
#define MC_DMA_CSR_WCX(n)	((n) << 16)	/* Установка счетчика слов */

/* Регистр OR для каналов DMA типа MEM_CH */
#define MC_DMA_OR0(n)		(n)		/* Приращение регистра IR0 (в словах) */
#define MC_DMA_OR1(n)		((n) << 16)	/* Приращение регистра IR1 (в словах) */


/* Псевдорегистр управления RUN */
#define MC_DMA_RUN		0x00000001	/* Управление битом RUN */


/*--------------------------------------
 * Регистры контроллера Ethernet
 */
/*
 * MAC_CONTROL - управление MAC
 */
#define MAC_CONTROL_FULLD		(1 << 0) 	/* дуплексный режим */
#define MAC_CONTROL_EN_TX_DMA		(1 << 1) 	/* разрешение передающего TX DMА */
#define MAC_CONTROL_EN_TX		(1 << 2) 	/* разрешение передачи */
#define MAC_CONTROL_IRQ_TX_DONE		(1 << 3) 	/* прерывание от передачи */
#define MAC_CONTROL_EN_RX		(1 << 4) 	/* разрешение приема */
#define MAC_CONTROL_LOOPBACK		(1 << 5) 	/* режим зацикливания */
#define MAC_CONTROL_FULLD_RX		(1 << 6) 	/* тестовый режим приема */
#define MAC_CONTROL_IRQ_RX_DONE		(1 << 7) 	/* прерывание по приёму */
#define MAC_CONTROL_IRQ_RX_OVF		(1 << 8) 	/* прерывание по переполнению */
#define MAC_CONTROL_CP_TX		(1 << 9) 	/* сброс передающего TX_FIFO */
#define MAC_CONTROL_RST_TX		(1 << 10) 	/* сброс блока передачи */
#define MAC_CONTROL_CP_RX		(1 << 11) 	/* сброс принимающего RX_FIFO */
#define MAC_CONTROL_RST_RX		(1 << 12) 	/* сброс блока приема */

/*
 * IFS_COLL_MODE - режим обработки коллизии
 */
#define IFS_COLL_MODE_ATTEMPT_NUM(n)	((n) & 15)	/* Количество попыток повторных передач */
#define IFS_COLL_MODE_EN_CW		(1 << 4)	/* Разрешение отслеживания окна коллизии */
#define IFS_COLL_MODE_TM_BACKOFF	(1 << 7)	/* Тестовый режим */
#define IFS_COLL_MODE_COLL_WIN(n)	((n) << 8)	/* Размер окна коллизии */
#define IFS_COLL_MODE_JAMB(n)		((n) << 16)	/* Байт jam-сообщения */
#define IFS_COLL_MODE_IFS(n)		((n) << 24)	/* Межкадровый интервал */

/*
 * TX_FRAME_CONTROL - управление передачей кадра
 */
#define TX_FRAME_CONTROL_LENGTH(n)	((n) & 0xfff)	/* Число байт данных */
#define TX_FRAME_CONTROL_TYPE_EN	(1 << 12) 	/* Поле длины задаёт тип */
#define TX_FRAME_CONTROL_FCS_CLT_EN	(1 << 13) 	/* Контрольная сумма из регистра */
#define TX_FRAME_CONTROL_DISENCAPFR	(1 << 14) 	/* Запрет формирования кадра в блоке передачи */
#define TX_FRAME_CONTROL_DISPAD		(1 << 15) 	/* Запрет заполнителей */
#define TX_FRAME_CONTROL_TX_REQ		(1 << 16) 	/* Передача кадра */

/*
 * STATUS_TX - статус передачи кадра
 */
#define STATUS_TX_ONTX_REQ		(1 << 0)	/* Выполняется запрос передачи */
#define STATUS_TX_ONTRANSMIT		(1 << 1)	/* Выполняется передача кадра */
#define STATUS_TX_BUSY			(1 << 2)	/* Среда передачи занята */
#define STATUS_TX_DONE			(1 << 3)	/* Передача завершена */
#define STATUS_TX_TRANSMIT_DISABLED	(1 << 4)	/* Передача не разрешена */
#define STATUS_TX_NOT_ENOUGH_DATA	(1 << 5)	/* Мало данных в TX FIFO */
#define STATUS_TX_TRANSMIT_OK		(1 << 6)	/* Передача кадра успешно выполнена */
#define STATUS_TX_EXCESSIVE_COLL	(1 << 7)	/* Повторная передача не удалась */
#define STATUS_TX_LATE_COLL		(1 << 8)	/* Поздняя коллизия */
#define STATUS_TX_ONCOL			(1 << 11)	/* Коллизия в среде передачи */
#define STATUS_TX_COLL_NUM(s)		((s) >> 12 & 15) /* Счетчик попыток повторных передач */
#define STATUS_TX_TXW(s)		((s) >> 16 & 0x3ff) /* Число слов в TX FIFO */
#define STATUS_TX_BITS			"\20"\
"\1ONTX_REQ\2ONTRANSMIT\3BUSY\4DONE\5DISABLED\6NDATA\7TXOK\10EXCCOLL"\
"\11LATECOLL\14ONCOL"

/*
 * RX_FRAME_CONTROL - управление приемом кадра
 */
#define RX_FRAME_CONTROL_DIS_RCV_FCS	(1 << 0) 	/* Отключение сохранения контрольной суммы */
#define RX_FRAME_CONTROL_DIS_PAD_DEL	(1 << 1) 	/* Отключение удаления заполнителей */
#define RX_FRAME_CONTROL_ACC_TOOSHORT	(1 << 2) 	/* Прием коротких кадров */
#define RX_FRAME_CONTROL_DIS_TOOLONG	(1 << 3) 	/* Отбрасывание слишком длинных кадров */
#define RX_FRAME_CONTROL_DIS_FCSCHERR	(1 << 4) 	/* Отбрасывание кадров с ошибкой контрольной суммы */
#define RX_FRAME_CONTROL_DIS_LENGTHERR	(1 << 5) 	/* Отбрасывание кадров с ошибкой длины */
#define RX_FRAME_CONTROL_DIS_BC		(1 << 6) 	/* Запрещение приема кадров с широковещательным адресом */
#define RX_FRAME_CONTROL_EN_MCM		(1 << 7) 	/* Разрешение приема кадров с групповым адресом по маске */
#define RX_FRAME_CONTROL_EN_MCHT	(1 << 8) 	/* Разрешение приема кадров с групповым адресом по хеш-таблице */
#define RX_FRAME_CONTROL_EN_ALL		(1 << 9) 	/* Разрешение приема кадров с любым адресом */

/*
 * STATUS_RX - статус приема кадра
 */
#define STATUS_RX_RCV_DISABLED		(1 << 0)		/* Приём не разрешён */
#define STATUS_RX_ONRECEIVE		(1 << 1)		/* Выполняется приём кадра */
#define STATUS_RX_DONE			(1 << 3)		/* Есть кадры в RX FIFO */
#define STATUS_RX_NUM_FR(s)		((s) >> 4 & 0x7f)	/* Число принятых кадров */
#define STATUS_RX_STATUS_OVF		(1 << 11)		/* Переполнение FIFO статусов */
#define STATUS_RX_RXW(s)		((s) >> 12 & 0x3ff)	/* Число слов в RX FIFO */
#define STATUS_RX_FIFO_OVF		(1 << 23)		/* Переполнение FIFO данных */
#define STATUS_RX_NUM_MISSED(s)		((s) >> 24 & 0x3f)	/* Число пропущенных кадров */
#define STATUS_RX_BITS			"\30"\
"\1DISABLED\2ONRECEIVE\4DONE\14STATUS_OVF\30FIFO_OVF"

/*
 * RX_FRAME_STATUS_FIFO - FIFO статусов принятых кадров
 */
#define RX_FRAME_STATUS_LEN(s)		((s) & 0xfff)	/* Число байт в принятом кадре */
#define RX_FRAME_STATUS_OK		(1 << 12)	/* Кадр принят без ошибок */
#define RX_FRAME_STATUS_LENGTH_ERROR	(1 << 13)	/* Ошибка длины данных */
#define RX_FRAME_STATUS_ALIGN_ERROR	(1 << 14)	/* Ошибка выравнивания */
#define RX_FRAME_STATUS_FRAME_ERROR	(1 << 15)	/* Ошибка формата кадра */
#define RX_FRAME_STATUS_TOO_LONG	(1 << 16)	/* Слишком длинный кадр */
#define RX_FRAME_STATUS_TOO_SHORT	(1 << 17)	/* Слишком короткий кадр */
#define RX_FRAME_STATUS_DRIBBLE_NIBBLE	(1 << 18)	/* Нечётное число полубайт */
#define RX_FRAME_STATUS_LEN_FIELD	(1 << 19)	/* Распознавание поля LENGTH */
#define RX_FRAME_STATUS_FCS_DEL		(1 << 20)	/* Удаление поля FCS */
#define RX_FRAME_STATUS_PAD_DEL		(1 << 21)	/* Удаление поля PAD */
#define RX_FRAME_STATUS_UC		(1 << 22)	/* Распознавание адреса MAC */
#define RX_FRAME_STATUS_MCM		(1 << 23)	/* Групповой адрес по маске */
#define RX_FRAME_STATUS_MCHT		(1 << 24)	/* Групповой адрес по хэш-таблице */
#define RX_FRAME_STATUS_BC		(1 << 25)	/* Широковещательный адрес */
#define RX_FRAME_STATUS_ALL		(1 << 26)	/* Приём кадров с любым адресом */

/*
 * MD_MODE - режим работы порта MD
 */
#define MD_MODE_DIVIDER(n)		((n) & 0xff)	/* делитель для частоты MDC */
#define MD_MODE_RST			(1 << 8)	/* сброс порта PHY */

/*
 * MD_CONTROL - управление порта MD
 */
#define MD_CONTROL_DATA(n)		((n) & 0xffff)		/* данные для записи */
#define MD_CONTROL_REG(n)		(((n) & 0x1f) << 16)	/* адрес регистра PHY */
#define MD_CONTROL_PHY(n)		(((n) & 0x1f) << 24)	/* адрес PHY */
#define MD_CONTROL_IRQ(n)		(1 << 29)		/* нужно прерывание */
#define MD_CONTROL_OP_READ		(1 << 30)		/* операция чтения */
#define MD_CONTROL_OP_WRITE		(2 << 30)		/* операция записи */

/*
 * MD_STATUS - статус порта MD
 */
#define MD_STATUS_DATA			0xffff		/* прочитанные данные */
#define MD_STATUS_BUSY			(1 << 29)	/* порт занят */
#define MD_STATUS_END_READ		(1 << 30)	/* завершилась операция чтения */
#define MD_STATUS_END_WRITE		(1 << 31)	/* завершилась операция записи */


/*-------------------------------------------
 * Регистры PCI
 */

/*
 * Состояние и управление (STATUS/COMMAND)
 */
#define MC_PCI_COMMAND_MEMORY		    0x00000002	/* Разрешение выполнение в режиме Target команд Memory Read, Memory Write */
#define MC_PCI_COMMAND_MASTER		    0x00000004	/* Разрешение работы на шине PCI в режиме Master  */
#define MC_PCI_COMMAND_PARITY		    0x00000040	/* Разрешение формирование сигнала PERR */
#define MC_PCI_COMMAND_IDISABLE	        0x00000400	/* Запрещение формирования сигнала прерывания */
#define MC_PCI_STATUS_ISTATUS  	        0x00080000	/* Наличие незамаскированных прерываний */
#define MC_PCI_STATUS_FASTB2B  	        0x00800000	/* Отражает способность PMSC выполнять транзакции типа  “Fast Back-to-Back” */
#define MC_PCI_STATUS_PARITY		    0x01000000	/* Признак выдачи или приема сигнала PERR в режиме Master */
#define MC_PCI_STATUS_DEVSEL_MASK	    0x06000000	/* DEVSEL timing = 01 (medium) */
#define MC_PCI_STATUS_SIG_TARGET_ABORT  0x08000000	/* Signaled Target Abort */
#define MC_PCI_STATUS_TARGET_ABORT	    0x10000000	/* Признак завершения обмена по условию Target-abort */
#define MC_PCI_STATUS_MASTER_ABORT	    0x20000000	/* Признак завершения обмена по условию Master-abort */
#define MC_PCI_STATUS_DETECTED_PARITY	0x80000000	/* Ошибка четности при приме данных из PCI */

/*
 * Latency Timer
 */
#define MC_PCI_MLT(x)               ((x) << 8)  /* Время в тактах PCLK, отведенное для выполнения транзакции в режиме Master. */

/*
 * Interrupt Line
 */
#define MC_PCI_INTR_LINE(x)         (x)
#define MC_PCI_GET_INTR_PIN(r)      (((r) >> 8) & 0xFF)
#define MC_PCI_GET_MIN_GNT(r)       (((r) >> 16) & 0xFF)
#define MC_PCI_GET_MIN_LAT(r)       (((r) >> 24) & 0xFF)

/* 
 * Управление шиной PCI (CSR_PCI)
 */
#define MC_PCI_CSR_PCI_WNT(n)       (n)         /* Количество слов, которое должно накопиться в буфере WFIFO для передачи
                                                   очередной порции данных в коммутатор SWITCH в режиме Target */
#define MC_PCI_CSR_PCI_SEL_TS_LAT   0x00000010  /* Разрешение изменения параметра ”Target Subsequent Latency” */
#define MC_PCI_CSR_PCI_SEL_TI_LAT   0x00000020  /* Разрешение изменения параметра ”Target Initial Latency” */
#define MC_PCI_CSR_PCI_TEST_PERR    0x00000040  /* Режим формирования выходного сигнала nPERR */
#define MC_PCI_CSR_PCI_TEST_PAR     0x00000080  /* Режим формирования выходного сигнала PAR */
#define MC_PCI_CSR_PCI_TS_LAT(n)    ((n) << 8)  /* Target Subsequent Latency в тактах PCLK */
#define MC_PCI_CSR_PCI_TI_LAT(n)    ((n) << 12) /* Target Initial Latency в тактах PCLK */
#define MC_PCI_CSR_PCI_TGT_PAR_STOP 0x00010000  /* Разрешение завершения транзакции в режиме Target установкой признака Signaled Target Abort */
#define MC_PCI_CSR_PCI_TGT_DPEA     0x00040000  /* Устанавливается в 1 в режиме Target, если в фазе адреса обнаружена ошибка чётности */
#define MC_PCI_CSR_PCI_TGT_DPED     0x00080000  /* Устанавливается в 1, если обнаружена ошибка чётности в фазе данных 
                                                   при выполнении записи на шине PCI в режиме Target */
#define MC_PCI_CSR_PCI_MST_PAR_STOP 0x00100000  /* Разрешение прекращения передачи блока данных и формирования прерывания MASTER _ERROR */
#define MC_PCI_CSR_PCI_MST_DPEWR    0x00400000  /* Обнаружен низкий уровень сигнала nPERR при выполнении записи на шине PCI в режиме Master */
#define MC_PCI_CSR_PCI_MST_DPERD    0x00800000  /* Обнаружена ошибка чётности при выполнении чтения на шине PCI в режиме Master */
#define MC_PCI_CSR_PCI_MST_BREAK    0x01000000  /* Программный останов передачи блока данных */
#define MC_PCI_CSR_PCI_BREAK_DONE   0x02000000  /* Состояние признака Break Done в регистре CSR_MASTER */
#define MC_PCI_CSR_PCI_NO_GNT       0x04000000  /* Состояние признака No Gnt в регистре STATUS_MASTER */
#define MC_PCI_CSR_PCI_NO_TRDY      0x08000000  /* Состояние признака No Trdy в регистре STATUS_MASTER */
#define MC_PCI_CSR_PCI_TGT_ABORT    0x10000000  /* Состояние признака Received Target Abort в регистре Status/Command */
#define MC_PCI_CSR_PCI_MST_ABORT    0x20000000  /* Состояние признака Reсeived Master Abort в регистре Status/Command */
#define MC_PCI_CSR_PCI_WR_PAR_ERR   0x40000000  /* Ошибка при выполнении записи на шине PCI. */
#define MC_PCI_CSR_PCI_RD_PAR_ERR   0x80000000  /* Ошибка при выполнении чтения на шине PCI. */

/*
 * Состояние и управление обменом в режиме Master (CSR_MASTER)
 */
#define MC_PCI_CSR_MASTER_RUN		    0x00000001	/* Состояние работы канала DMA */
#define MC_PCI_CSR_MASTER_CMD		    0x0000001e	/* Тип команды обмена в режиме Master */
#define MC_PCI_CSR_MASTER_IOREAD	    0x00000004	/* I/O Read */
#define MC_PCI_CSR_MASTER_IOWRITE	    0x00000006	/* I/O Write */
#define MC_PCI_CSR_MASTER_MEMREAD	    0x0000000c	/* Memory Read */
#define MC_PCI_CSR_MASTER_MEMWRITE	    0x0000000e	/* Memory Write */
#define MC_PCI_CSR_MASTER_CFGREAD	    0x00000014	/* Configuration Read */
#define MC_PCI_CSR_MASTER_CFGWRITE	    0x00000016	/* Configuration Write */
#define MC_PCI_CSR_MASTER_SEL_IRD_LAT   0x00000020  /* Разрешение изменения параметра  ”nIRDY Latency” */
#define MC_PCI_CSR_MASTER_SEL_MS_LAT    0x00000040  /* Разрешение изменения параметра  ”Master Subsequent Latency” */
#define MC_PCI_CSR_MASTER_SEL_MI_LAT    0x00000080  /* Разрешение изменения параметра  ”Master Initial Latency” */
#define MC_PCI_CSR_MASTER_WNM(n)        ((n) << 8)  /* Количество слов, которое должно накопиться в буфере WFIFO 
                                                       для передачи очередной порции данных в коммутатор SWITCH 
                                                       в режиме Master. */
#define MC_PCI_CSR_MASTER_WINDOW        0x00001000  /* Индикатор выполнения обмена через адресное окно. */
#define MC_PCI_CSR_MASTER_BREAK_DONE    0x00002000  /* Индикатор выполнения программного останова передачи блока данных. */
#define MC_PCI_CSR_MASTER_FATAL_ERR     0x00004000  /* Индикатор останова передачи  блока данных по фатальной ошибке. */
#define MC_PCI_CSR_MASTER_DONE		    0x00008000	/* Признак завершения передачи */
#define MC_PCI_CSR_MASTER_WC(n)	        ((n) << 16)	/* Счетчик слов DMA обмена */

/*
 * STATUS_MASTER
 */
#define MC_PCI_STATUS_MASTER_WCC(n)     (n)             /* Текущий размер блока данных */
#define MC_PCI_STATUS_MASTER_RUN        0x00010000      /* Состояние признака RUN в регистре CSR_MASTER */
#define MC_PCI_STATUS_MASTER_TRDY_OUT   0x00100000      /* Транзакция завершена с признаком TRDY OUT */
#define MC_PCI_STATUS_MASTER_IRDY_OUT   0x00200000      /* Транзакция завершена с признаком IRDY OUT */
#define MC_PCI_STATUS_MASTER_TIMEOUT    0x00400000      /* Транзакция завершена с признаком Timeout */
#define MC_PCI_STATUS_MASTER_RETRY      0x00800000      /* Транзакция завершена с признаком Retry */
#define MC_PCI_STATUS_MASTER_DISCONN    0x01000000      /* Транзакция завершена с признаком Disconnect */
#define MC_PCI_STATUS_MASTER_BREAK_DONE 0x02000000      /* Состояние признака Break Done в регистре CSR_MASTER */
#define MC_PCI_STATUS_MASTER_NO_GNT     0x04000000      /* Признак отсутствия сигнала nGNT в течение 4095 тактов 
                                                           шины PCI после установки сигнала nREQ */
#define MC_PCI_STATUS_MASTER_NO_TRDY    0x08000000      /* Транзакция завершена с признаком NO TRDY */
#define MC_PCI_STATUS_MASTER_TARGET_ABORT   0x10000000  /* Состояние признака Received Target Abort в регистре Status/Command */
#define MC_PCI_STATUS_MASTER_MASTER_ABORT   0x20000000  /* Состояние признака Reсeived Master Abort в регистре Status/Command */
#define MC_PCI_STATUS_MASTER_WR_PAR_ERR     0x40000000  /* Ошибка при выполнении записи на шине PCI. */
#define MC_PCI_STATUS_MASTER_RD_PAR_ERR     0x80000000  /* Ошибка при выполнении чтения на шине PCI. */

/*
 * TMR_PCI
 */
#define MC_PCI_TMR_PCI_IRD_LAT(n)       (n)             /* nIRDY Latency  в тактах PCLK */
#define MC_PCI_TMR_PCI_MS_LAT(n)        ((n) << 4)      /* Master Subsequent Latency в тактах PCLK */
#define MC_PCI_TMR_PCI_MI_LAT(n)        ((n) << 8)      /* Master Initial Latency в тактах PCLK */
#define MC_PCI_TMR_PCI_WATERMARK(n)     ((n) << 16)     /* Пороговое значение для формирования прерывания WMARK */

/*
 * CSR_WIN
 */
#define MC_PCI_CSR_WIN_CMD		        0x0000001e	/* Тип команды при обмене через адресное окно */
#define MC_PCI_CSR_WIN_IOREAD	        0x00000004	/* I/O Read */
#define MC_PCI_CSR_WIN_IOWRITE	        0x00000006	/* I/O Write */
#define MC_PCI_CSR_WIN_MEMREAD	        0x0000000c	/* Memory Read */
#define MC_PCI_CSR_WIN_MEMWRITE	        0x0000000e	/* Memory Write */
#define MC_PCI_CSR_WIN_CFGREAD	        0x00000014	/* Configuration Read */
#define MC_PCI_CSR_WIN_CFGWRITE	        0x00000016	/* Configuration Write */
#define MC_PCI_CSR_WIN_SEL_NCBE         0x00000020  /* Выбор nCBE */
#define MC_PCI_CSR_WIN_SEL_ADR          0x00000040  /* Выбор адреса */
#define MC_PCI_CSR_WIN_SEL_MIL          0x00000080  /* Выбор параметра ”Master Initial Latency” */
#define MC_PCI_CSR_WIN_MIL_WIN(n)       ((n) << 12) /* Значение ”Master Initial Latency”в тактах PCLK */
#define MC_PCI_CSR_WIN_MASK_DPE         0x00010000  /* Разрешение формирования  прерывания  MASTER _ERROR */
#define MC_PCI_CSR_WIN_NCBE_WIN(n)      ((n) << 20) /* если SEL_nCBE=1, то состояние этого поля передается на выводы nCBE[3:0] в фазе данных */
#define MC_PCI_CSR_WIN_AR_WIN(n)        ((n) << 24) /* если SEL_ ADR=1, то состояние этого поля передается на выводы AD[31:24] в фазе адреса */

#endif /* _IO_ELVEES_H */
