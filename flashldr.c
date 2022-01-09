//==============================================================================
// File        : obrazldr.c
// Project     : Loader KREDO RAM
// Revision    : $Revision$
// Author      : NIL-1112
// Date        : $Date$ 26/05/2021
// Description : functions loader KREDO RAM
//==============================================================================
//******************************************************************************
//INCLUDE
#include <stdio.h>
#include "inc/flashldr.h"
#include "inc/tmk_kk.h"
#include "inc/options.h"
#include "inc/milstd_def.h"
#include "inc/ctrlsumm.h"
//******************************************************************************
//******************************************************************************
// GLOBAL VARS
extern _option option;
//******************************************************************************
//******************************************************************************
// LOCAL DEFINE
//******************************************************************************
//******************************************************************************
// LOCAL TYPEDEF
//******************************************************************************
//******************************************************************************
// LOCAL VARS
static unsigned short cntErrAccess;
static FILE *fp;
int errorCode = 0;
int counterError = 0;
//******************************************************************************
//******************************************************************************
// LOCAL PROTO
//******************************************************************************
//******************************************************************************
// LOCAL MACRO
//******************************************************************************
//******************************************************************************
// FUNCTIONS
//******************************************************************************

//------------------------------------------------------------------------------
// Загрузка файла в ОЗУ
//------------------------------------------------------------------------------
char DownloadPRG() {
  size_t n;
	unsigned short offset;
	unsigned short segment;
	unsigned short massWords[32];
  
  offset = 0x0000;
  segment = PrgSegment;
  
  while((n = fread(&massWords[3], 1, SIZE_DATA_LOAD, fp))) {
		if (offset > 0xFF00) {
			offset -= 0xFF00;
			segment += 0x0FF0;
		}
		massWords[0] = WRITE_RAM;
		massWords[1] = offset;
		massWords[2] = segment;
    
    if(KKOU(ADDR_OU, SUBADDR_DATA, massWords, n/2 + 3)) return PRG_LOAD_FAIL;
    offset += SIZE_DATA_LOAD;
	}
	return PRG_LOAD_OK;
}

char FileOpen(char *fname) {
  fp = fopen(fname,"rb");
  if(fp == NULL)
    return FILE_OPEN_FAIL;
  else
    return FILE_OPEN_OK;
}

void FileClose() {
  fclose(fp);
}

//------------------------------------------------------------------------------
// Экспресс тест прибора
//------------------------------------------------------------------------------
char ExpressTest() {
  unsigned short massWords[NUMWORD_EXPRESS_TEST];
  if(OUKK(ADDR_OU, SUBADDR_EXPRESS_TEST, massWords, NUMWORD_EXPRESS_TEST))
    return EXPRESS_TEST_FAIL;
	cntErrAccess = massWords[1];
	if(massWords[0] == WORD_NORM) 
		return EXPRESS_TEST_OK;
	return EXPRESS_TEST_FAIL;
}

//------------------------------------------------------------------------------
// Инициализация прибора
//------------------------------------------------------------------------------
char InitializationDevice() {
  int i;
  unsigned short massWords[32];
  unsigned short numberStartsDevice;
  
	if (ExpressTest() != EXPRESS_TEST_OK) {
		return EXPRESS_TEST_FAIL;
	}
	numberStartsDevice = cntErrAccess;
	delay(1000);	

	massWords[0] = WORD_INITIALIZATION;
	for (i = 1; i < NUMWORD_INITIALIZATION; i++) {
		massWords[i] = SECURITY_CODE;
	}

	while (numberStartsDevice < NUM_ALLOWABLE_STARTS) {
    if(KKOU(ADDR_OU, SUBADDR_INITIALIZATION, massWords, NUMWORD_INITIALIZATION))
      return INITIALIZATION_DEVICE_FAIL;
    delay(1000);  
		if (ExpressTest() != EXPRESS_TEST_OK) {
			return EXPRESS_TEST_FAIL;
		}
		if (numberStartsDevice == cntErrAccess) { 
			return INITIALIZATION_DEVICE_OK;
		}
		numberStartsDevice = cntErrAccess;
	} 
	return INITIALIZATION_DEVICE_FAIL;
}

//------------------------------------------------------------------------------
//Вернуть размер файла
//------------------------------------------------------------------------------
size_t FileSize( FILE *fp ) {
    size_t size_of_file;
    fseek(fp, 0L, SEEK_END);
    size_of_file = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size_of_file;
}

char ReadIMG(InfoFile *infoFile_IMG) { // Открытие файла и заполнение структуры
	size_t n;
//-------------------------------------Считываем данные из файла-------------------------
  n = fread((char *)infoFile_IMG->file_data, 1, SizeFileMemory, infoFile_IMG->fp);
  
  infoFile_IMG->file_size_data = n;
  infoFile_IMG->file_seek += n;
  
  if(n == SizeFileMemory)
    infoFile_IMG->file_eof = false;
  else
    infoFile_IMG->file_eof = true;
  
	infoFile_IMG->check_summ = SumSign((char *)infoFile_IMG->file_data, infoFile_IMG->file_size_data);
	infoFile_IMG->file_size -= infoFile_IMG->file_size_data;
	//---------------------------------------------------------------------------------------
	return true;
}

char DownloadIMG(InfoFile *infoFile_IMG) {
	unsigned short commandCode = WRITE_RAM;
	unsigned int offset_beginningArray = 0x00020040;
	unsigned short offset = 0;
	unsigned short beginningArray = 0;
	int memoryShift = 0;
	unsigned short wordsData[32];
  int i;
  short cnt = 0;

	while (infoFile_IMG->file_size_data > SizeDataManch) {
		Offset_beginningArray(offset_beginningArray, &offset, &beginningArray);
		wordsData[0] = commandCode;
		wordsData[1] = offset;
		wordsData[2] = beginningArray;
		for (i = 0; i < 29; i++) {
			wordsData[i + 3] = infoFile_IMG->file_data[i + memoryShift];
		}
		if(KKOU(1, 1, wordsData, 32)) {
		  errorCode=ErrorTMK_SetData;
      return false;
    }
		offset_beginningArray += SizeDataManch;
		memoryShift += SizeDataManch/2;
		infoFile_IMG->file_size_data -= SizeDataManch;
    
    if(option.verbose && (cnt == 500)) {
      //printf(".");
      cnt = 0;
    }
    cnt++;
	}
	infoFile_IMG->file_size_data /= 2;
	for (i = 0; i < infoFile_IMG->file_size_data; i++) {
		wordsData[i + 3] = infoFile_IMG->file_data[i + memoryShift];
	}
	Offset_beginningArray(offset_beginningArray, &offset, &beginningArray);
	wordsData[0] = commandCode;
	wordsData[1] = offset;
	wordsData[2] = beginningArray;
	if(KKOU(1, 1, wordsData, infoFile_IMG->file_size_data + 3)) {
    errorCode=ErrorTMK_SetData;
	  return false;
	}

	wordsData[0] = RUN_RAM;
	wordsData[1] = 0;
	wordsData[2] = PrgSegment;
	if(KKOU(1, 2, wordsData, 3)){
	  errorCode=ErrorTMK_SetData;
	  return false;
	}

	if(OUKK(1, 7, wordsData, 2)){
	  errorCode=ErrorTMK_SetData;
	  return false;
	}
	while (!wordsData[0]) {
		delay(1000); 
		if(OUKK(1, 7, wordsData, 2)){
		  errorCode=ErrorTMK_SetData;
		  return false;
		}
	}
	if (ResultReturnWord(wordsData[1]))
		return true;
	else {
		counterError++;
		infoFile_IMG->file_seek -= infoFile_IMG->file_size_data;
		infoFile_IMG->file_eof = false;
	}
	return false;
}

void Offset_beginningArray(unsigned int offset_beginningArray, unsigned short *offset, unsigned short *beginningArray) {
	*offset = offset_beginningArray;
	*beginningArray = offset_beginningArray >> 16;
	*beginningArray <<= 12;
}

char DownloadinfoDataIMG(InfoFile *infoFile_IMG, InfoData *infoData_IMG) {
	unsigned short wordsData[32];
	unsigned short device;

	infoData_IMG->size_data = infoFile_IMG->file_size_data;
	infoData_IMG->check_summ = infoFile_IMG->check_summ;
	
	device = infoData_IMG->num_device_download;
	device <<= 8;
	device += infoData_IMG->num_device;

	wordsData[0] = infoData_IMG->cmd_code;
	wordsData[1] = infoData_IMG->offset;
	wordsData[2] = infoData_IMG->segment;
	wordsData[3] = device;
	wordsData[4] = infoFile_IMG->file_size_data;
	wordsData[5] = infoFile_IMG->file_size_data>>16;
	wordsData[6] = infoData_IMG->address_ROM;
	wordsData[7] = infoData_IMG->address_ROM>>16;
	wordsData[8] = infoData_IMG->check_summ;
	wordsData[9] = infoData_IMG->cmd_code>>8;
	
	if(KKOU(1, 1, wordsData, 10)){
	  errorCode=ErrorTMK_SetData;
	  return false;
	}

	infoData_IMG->address_ROM += infoFile_IMG->file_size_data;

	return true;
}

int ResultReturnWord (unsigned short word) {
	switch (word) {
		case 0x1F:
			return true;
		case 0x11:
			errorCode = ErrorCheckSumm;
			return false;
		case 0x0:
			errorCode = ErrorMKIO;
			return false;
		default:
			return false;
	}
}