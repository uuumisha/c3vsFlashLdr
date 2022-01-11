//******************************************************************************
// INCLUDE
//******************************************************************************
//******************************************************************************
// DEFINE
//******************************************************************************
//******************************************************************************
// TYPEDEF
//******************************************************************************

//-------------------------------------------работа с файлом------------------------------
#define SizeFileMemory    0x46CD0
#define SizeDataManch     0x003A
#define PrgName           "//1/home/misha/check1/PRG_FLSh.dat"
#define PrgSegment        0x0913
//----------------------------------------------------------------------------------------

enum bool {false, true};

typedef struct {
	char*           file_name;				        //	Имя файла
	FILE*           fp;                       //  Дескриптор файла
  int             file_size;               	//	Размер Файла в байтах
	int             file_seek;               	//	Текущее положение каретки в файле
	char            file_eof;                 //	Конец файла
	int             file_size_data;           //	Размер загруженных данных
	unsigned short  check_summ;               //	Контрольная сумма (сигнатура)
	unsigned short  *file_data;
} InfoFile;

typedef struct {		// Шапка с информацией для загрузки из ОЗУ в ПЗУ
	unsigned short  cmd_code;             //	Идентификатор команды
	unsigned short  offset;               //	Смещение адреса начала массива в ОЗУ
	unsigned short  segment;		          //	Сегмент адреса начало массива в ОЗУ
	unsigned char   num_device;			      //	Номер первого прибора на магистрале
	unsigned char   num_device_download;  //	Номер прибора для загрузки на магистрале
	unsigned int    size_data;            //	Размер загружаемых данных
	unsigned int    address_ROM;          //	Физический адрес в ПЗУ
	unsigned short  check_summ;			      //	Контрольная сумма (сигнатура)
	char            device_K312_1;			  //	Признак конфигурации (0 - с прибором К315-1; 1 - без прибора К315-1)
} InfoData;
//******************************************************************************
// GLOBAL VARS
//******************************************************************************
//******************************************************************************
// GLOBAL PROTO
char DownloadPRG();
size_t FileSize(FILE *fp);
char ExpressTest();
char InitializationDevice();
char FileOpen(char *name);
void FileClose();

char ReadIMG(InfoFile *infoFile_IMG);
char DownloadIMG(InfoFile *infoFile_IMG);
void Offset_beginningArray(unsigned int offset_beginningArray, unsigned short *offset, unsigned short *beginningArray);
char DownloadinfoDataIMG(InfoFile *infoFile_IMG, InfoData *infoData_IMG);
int  ResultReturnWord (unsigned short word);

//******************************************************************************
//******************************************************************************
// MACRO
//******************************************************************************
//******************************************************************************
// END OF FILE
//******************************************************************************








