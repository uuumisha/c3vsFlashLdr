#define FILE_OPEN_OK                    0
#define FILE_OPEN_FAIL                  1
#define EXPRESS_TEST_OK                 2
#define EXPRESS_TEST_FAIL               3
#define INITIALIZATION_DEVICE_OK        4
#define INITIALIZATION_DEVICE_FAIL      5
#define PRG_LOAD_OK                     6
#define PRG_LOAD_FAIL                   7
#define RUN_OK                          8
#define RUN_FAIL                        9
#define TMK_OPEN_OK                     10
#define TMK_OPEN_FAIL                   11
#define IMG_FILE_OPEN_OK                12
#define IMG_FILE_OPEN_FAIL              13


// ошибки работы программы
#define ErrorExpressTest                0x1001 // Ошибка экспресс теста прибора
#define ErrorStartTR                    0x1002 // Ошибка перехода в технологический режим

#define ErrorOpenDrvManchester          0x2001 // Ошибка подключения к манчестерскому каналу
#define ErrorOpenFile                   0x2020 

#define ErrorCheckSumm                  0x2030 
#define ErrorMKIO                       0x2031 
#define ErrorTMK_SetData                0x2051 

typedef struct {
  unsigned long flashAddr;
  unsigned char currDevice;
  unsigned char loadDevice;
  unsigned char base;
  unsigned char verbose;
  char *tmkPath;
  char *fileName;
} _option;