#define ADDR_OU                        0x0001
#define SUBADDR_DATA                   0x0001
//----- экспресс тест --------------------------
#define SUBADDR_EXPRESS_TEST					 0x0005
#define NUMWORD_EXPRESS_TEST					 0x0002

//----- инициализация прибора ------------------
#define SUBADDR_INITIALIZATION		     0x0003
#define NUMWORD_INITIALIZATION			   0x0020
#define WORD_INITIALIZATION            0x170A
#define SECURITY_CODE		               0xFFFF

//----- запуск прибора -------------------------
#define SUBADDR_RUN					           0x0002

//----- слова данных ---------------------------
#define WORD_NORM								       0x0001
#define NUM_ALLOWABLE_STARTS				   0x0003
#define WORD_START_DEVICE							 0x01F5

//----- работа с файлом ------------------------
#define SIZE_DATA_LOAD							   0x003A

//----- командные слова ------------------------
#define WRITE_RAM                      0x0100
#define RUN_RAM                        0x0200