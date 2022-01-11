//==============================================================================
// File        : main.c
// Project     : Loader KREDO RAM
// Revision    : $Revision$
// Author      : NIL-1112
// Date        : $Date$ 26/05/2021
// Description : main
//==============================================================================
//******************************************************************************
//INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "inc/flashldr.h"
#include "inc/options.h"
#include "inc/tmk_kk.h"
#include "inc/milstd_def.h"
//******************************************************************************
//******************************************************************************
// GLOBAL VARS
_option option;
extern int errorCode; // код ошибки
extern int counterError;
//******************************************************************************
//******************************************************************************
// LOCAL DEFINE
#define LOAD_ADDR   0x1000
#define START_ADDR  0x1000
//******************************************************************************
//******************************************************************************
// LOCAL TYPEDEF
//******************************************************************************
//******************************************************************************
// LOCAL VARS
//******************************************************************************
//******************************************************************************
// LOCAL PROTO
//******************************************************************************
//******************************************************************************
// LOCAL MACRO
//******************************************************************************
//******************************************************************************
// FUNCTIONS
void GetOptions(int argc, char** argv);  //Загрузка начальных параметров
void PrintResult(char result);           //Отображение результатов работы функций
//******************************************************************************
//------------------------------------------------------------------------------
//MAIN
//------------------------------------------------------------------------------
int main(int argc, char * argv[]) {
  
  InfoFile infoFile_IMG;
	InfoData infoData_IMG;
  
  //Загрузка начальных параметров
  GetOptions(argc,argv);
  
  if(option.verbose)
    printf("Flash Loader [%s %s]\n",__DATE__,__TIME__);
  
  // Открываем TMK элкуса 
  errorCode = IniTmk_KK(option.tmkPath, option.base);
  if(option.verbose)
    PrintResult(errorCode);
  if(errorCode != TMK_OPEN_OK)  return(EXIT_FAILURE);
  
  // определение полей структуры для загрузки образа во FLASH
  infoData_IMG.device_K312_1        = false;
	infoData_IMG.num_device           = option.currDevice;
	infoData_IMG.num_device_download  = option.loadDevice;
	infoData_IMG.address_ROM          = option.flashAddr;
  infoData_IMG.cmd_code             = WRITE_RAM;
  infoData_IMG.offset               = 0x0000;
  infoData_IMG.segment              = 0x2000;
  
  // определение полей структуры для загрузки образа в ОЗУ
	infoFile_IMG.file_name      = option.fileName;
  infoFile_IMG.file_size      = 0;
  infoFile_IMG.file_seek      = 0;
  infoFile_IMG.file_eof       = false;
  infoFile_IMG.file_size_data = 0;
  infoFile_IMG.check_summ     = 0;
  infoFile_IMG.file_data      = (unsigned short *)malloc(SizeFileMemory);
  infoFile_IMG.fp = fopen(infoFile_IMG.file_name,"rb");
  
  if(infoFile_IMG.fp == NULL) {
    printf("Error open IMG\n");
    free(infoFile_IMG.file_data); 
    return true;
  }
  infoFile_IMG.file_size = FileSize(infoFile_IMG.fp);
    
  // Открываем файл программатора для чтения
  errorCode = FileOpen(PrgName);
  if(option.verbose)
    PrintResult(errorCode);
  
  if(errorCode != FILE_OPEN_OK)   {
    free(infoFile_IMG.file_data);
    return(EXIT_FAILURE);
  }
  
  // Инициализация прибора и перевод в технологический режим
  errorCode = InitializationDevice(); 
  if(option.verbose)
    PrintResult(errorCode);
  if(errorCode != INITIALIZATION_DEVICE_OK) { 
    FileClose(); 
    CloseTmk();
    free(infoFile_IMG.file_data);
    return(EXIT_FAILURE); 
  }
  
  // Загрузка программатора в ОЗУ прибора
  errorCode = DownloadPRG();
  if(option.verbose)
    PrintResult(errorCode);
  if(errorCode != PRG_LOAD_OK) { 
    FileClose(); 
    CloseTmk();
    free(infoFile_IMG.file_data);
    return(EXIT_FAILURE); 
  }
  
  if(option.verbose)
      printf("\n");
  
  // Загрузка образа во flash прибора
  while (!infoFile_IMG.file_eof && counterError < 3) {
		if (!ReadIMG(&infoFile_IMG)) {
			infoFile_IMG.file_eof = true;
      free(infoFile_IMG.file_data);
			PrintResult(errorCode);
      return errorCode;
		}
    if(option.verbose)
      printf("%d bytes started download\n", infoFile_IMG.file_size_data);
		DownloadinfoDataIMG(&infoFile_IMG, &infoData_IMG);
		if (!DownloadIMG(&infoFile_IMG)) {
      free(infoFile_IMG.file_data);
			PrintResult(errorCode);
      return errorCode;
		}
	}
  
  if(option.verbose)
    printf("\nFile %s successfully loaded into FLASH.", option.fileName);
  FileClose();
  CloseTmk();
  free(infoFile_IMG.file_data);
  return(EXIT_SUCCESS);
}
//------------------------------------------------------------------------------
//END MAIN
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Анализ аргументов 
//------------------------------------------------------------------------------
void GetOptions(int argc, char** argv) {
  int errflag = 0;
  int arg;
  
  option.flashAddr    = 0xffe90000;     // -a адрес во флеше
  option.currDevice   = 0x1;            // -c Имя текущего прибора
  option.loadDevice   = 0x1;            // -l Имя прошиваемого прибора
  option.base         = false;          // -b Выбор основная / резервная шина КК
  option.tmkPath      = NULL;           // -t путь к tmk (/dev/tmk0 по умолчанию)
  option.verbose      = true;           // -v Вывод хода работы программы
  option.fileName     = NULL;           // -f Имя файла
  
  while((arg = getopt(argc, argv, "a:c:l:t:vf:b")) != -1) { 
    switch( arg ) {
      case 'a': option.flashAddr    =  strtoul(optarg, NULL, 16); break;
      case 'c': option.currDevice   =  strtoul(optarg, NULL, 16); break;
      case 'l': option.loadDevice   =  strtoul(optarg, NULL, 16); break;
      case 'b': option.base         =  true;                      break;
      case 't': option.tmkPath      =  strdup(optarg);            break;
      case 'v': option.verbose      =  false;                     break;
      case 'f': option.fileName     =  strdup(optarg);            break;
      case '?': ++errflag;                                        break;
    }
  }
  
  if(option.tmkPath==NULL) {
    option.tmkPath=strdup("/dev/tmk1");
  }
  
  if(option.fileName==NULL) {
    option.fileName=strdup("img.dat");
  }
  
  if(option.verbose) {
    printf("\n");
    printf("FlashAddr:     %x\n", option.flashAddr);
    printf("CurrentDevice: %x\n", option.currDevice);
    printf("LoadDevice:    %x\n", option.loadDevice);
    printf("Base:          %d\n", option.base);
    printf("tmkPath:       %s\n", option.tmkPath);
    printf("Verbose:       %d\n", option.verbose);  
    printf("FileName:      %s\n", option.fileName);
  }
  
  return;
}  
//------------------------------------------------------------------------------
//END Анализ аргументов 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Print Error
//------------------------------------------------------------------------------

void PrintResult(char result) {
  switch(result) {
    case FILE_OPEN_OK:                  printf("OPEN FILE OK\n");                   break;
    case FILE_OPEN_FAIL:                printf("OPEN FILE ERROR\n");                break;
    case EXPRESS_TEST_OK:               printf("EXPRESS TEST OK\n");                break;
    case EXPRESS_TEST_FAIL:             printf("EXPRESS TEST ERROR\n");             break;
    case INITIALIZATION_DEVICE_OK:      printf("INITIALIZATION DEVICE OK\n");       break;
    case INITIALIZATION_DEVICE_FAIL:    printf("INITIALIZATION DEVICE ERROR\n");    break;
    case PRG_LOAD_OK:                   printf("PRG LOAD OK\n");                    break;
    case PRG_LOAD_FAIL:                 printf("PRG LOAD FAIL\n");                  break;
    case RUN_OK:                        printf("RUN OK\n");                         break;
    case RUN_FAIL:                      printf("RUN FAIL\n");                       break;
    case TMK_OPEN_OK:                   printf("TMK OPEN OK\n");                    break;
    case TMK_OPEN_FAIL:                 printf("TMK OPEN ERROR\n");                 break;
    default:                            printf("UNDEFINED ERROR CODE\n");           break;
  }
}
//------------------------------------------------------------------------------
//END Print Error
//------------------------------------------------------------------------------
