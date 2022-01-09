//******************************************************************************
// INCLUDE
//******************************************************************************
//******************************************************************************
// DEFINE
//******************************************************************************
//******************************************************************************
// TYPEDEF
//******************************************************************************

//-------------------------------------------������ � ������------------------------------
#define SizeFileMemory    0x46CD0
#define SizeDataManch     0x003A
#define PrgName           "//1/home/misha/check1/PRG_FLSh.dat"
#define PrgSegment        0x0913
//----------------------------------------------------------------------------------------

enum bool {false, true};

typedef struct {
	char*           file_name;				        //	��� �����
	FILE*           fp;                       //  ���������� �����
  int             file_size;               	//	������ ����� � ������
	int             file_seek;               	//	������� ��������� ������� � �����
	char            file_eof;                 //	����� �����
	int             file_size_data;           //	������ ����������� ������
	unsigned short  check_summ;               //	����������� ����� (���������)
	unsigned short  *file_data;
} InfoFile;

typedef struct {		// ����� � ����������� ��� �������� �� ��� � ���
	unsigned short  cmd_code;             //	������������� �������
	unsigned short  offset;               //	�������� ������ ������ ������� � ���
	unsigned short  segment;		          //	������� ������ ������ ������� � ���
	unsigned char   num_device;			      //	����� ������� ������� �� ����������
	unsigned char   num_device_download;  //	����� ������� ��� �������� �� ����������
	unsigned int    size_data;            //	������ ����������� ������
	unsigned int    address_ROM;          //	���������� ����� � ���
	unsigned short  check_summ;			      //	����������� ����� (���������)
	char            device_K312_1;			  //	������� ������������ (0 - � �������� �315-1; 1 - ��� ������� �315-1)
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








