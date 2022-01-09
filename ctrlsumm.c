
unsigned int FSign(unsigned short int* piTopAr, unsigned long lLengthAr);

typedef struct {
	unsigned bit0   : 1;
	unsigned        : 5;
	unsigned bit6   : 1;
	unsigned        : 1;
	unsigned bit8   : 1;
	unsigned        : 2;
	unsigned bit11  : 1;
	unsigned        : 3;
	unsigned bit15  : 1;
} FLD;

typedef union {
	FLD fld;
	unsigned int iSdv;
} R_SDV;

typedef struct {
	unsigned bit0 : 1;
	unsigned      : 15;
} DIG;

typedef union {
	DIG dig;
	unsigned int iDig;
} DIG_S;

unsigned int SumSign(char *uka, unsigned int fsize) {
	unsigned short *uks, size1;
	int j = 0, j1, j2;
	unsigned int size, ksum;
  unsigned short int *bks;
  
  bks = (unsigned short int*)malloc(20000*2);
	uks = (unsigned short *)uka;
	ksum = j = 0;
	size = (fsize) / 2;
	size1 = (unsigned short)size;
	j1 = size / 16384;
	if (j1>0) {
		if ((size - j1 * 16384)>0) j1++;
		j2 = j1; size1 = 16384;
	}
	else j2 = 1;
	for (j = 0; j<j2; j++) {
		bks[j] = (unsigned int)FSign(uks, size1);
		uks += size1;
		size -= 16384;
		if (size<16384)
			size1 = (unsigned short)size;
	}
	ksum = FSign(bks, j2);
  free(bks);
  return(ksum & 0xffff);
}

unsigned int FSign(unsigned short int* piTopAr, unsigned long lLengthAr) {
	DIG_S DigS;
	R_SDV Rsdv;

	unsigned long MemCnt;
	unsigned short int BitCnt;
	unsigned short int* pMem;
	Rsdv.iSdv = 0;
	for (BitCnt = 0; BitCnt<16; BitCnt++) {
		for (pMem = piTopAr, MemCnt = 0; MemCnt<lLengthAr; MemCnt++, pMem++) {
			DigS.iDig = *pMem;
			DigS.iDig >>= BitCnt;
			DigS.dig.bit0 = DigS.dig.bit0^Rsdv.fld.bit6^Rsdv.fld.bit8^Rsdv.fld.bit11^Rsdv.fld.bit15;
			Rsdv.iSdv <<= 1;
			Rsdv.fld.bit0 = DigS.dig.bit0;
		}
	}
	return Rsdv.iSdv;
}
