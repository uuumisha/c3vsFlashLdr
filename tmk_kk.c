
/****************************************************************************/
/*      Функции для работы с КК драйвера Элкус. ОС QNX 4.25                 */
/****************************************************************************/

#include "inc/tmk_driver.h"
#include "inc/tmk_kk.h"
#include "inc/options.h"

static pid_t Proxy_tmk;					        // pid для работы с драйвером ТМК
static TTmkProxyData interruptInfo;   	// структура для чтения информации о прерывании

// Функция инициализации адаптера в режим контроллера канала
char	IniTmk_KK(char *path, unsigned char base) {
	int rez;
	
	// Задание конфигурации платы 
	rez=tmkconfig(0, path);
	if (rez) {
		return TMK_OPEN_FAIL;
	}
	
	// Захват ресурсов
	tmk_lock();
	
	// Установка режима КК
	rez=tmkdefmode(BC_MODE);
	if (rez) {
		return TMK_OPEN_FAIL;
	}
	
	// Формирование прокси для работы с драйвером TMK1553B
	Proxy_tmk=qnx_proxy_attach(0,0,0,0);
	tmkdefproxy(Proxy_tmk);
	tmkproxymode(TMK_PROXY_BUFFERED); 
	
	// Сброс KK
	bcreset();
	bcdefirqmode(0);
  
  // Выбор основной или резервной шины
  if(base)  bcdefbus(BUS_B);
  else      bcdefbus(BUS_A);

	return TMK_OPEN_OK;

}

// Завершение работы с драйвером
void CloseTmk() {
	tmkdone(ALL_TMKS);
}

// Функция обмена КК -> ОУ
char KKOU(unsigned short addr, unsigned short subAddr, unsigned short *mass, unsigned short numberOfWords) {
	unsigned short answ;
	bcputw(0, CW(addr, RT_RECEIVE, subAddr, numberOfWords));
	bcputblk(1, mass, numberOfWords);
	bcstart(bcgetbase(), DATA_BC_RT);
  
  Receive(Proxy_tmk,0,0);
  tmkgetpxd(&interruptInfo);
  if(!interruptInfo.bc.wResult)
    return 0;
  else
    return 1;
}

// Функция обмена ОУ -> КК
char OUKK(unsigned short addr, unsigned short subAddr, unsigned short *mass, unsigned short numberOfWords) {
	bcputw(0, CW(addr, RT_TRANSMIT, subAddr, numberOfWords));
	bcstart(bcgetbase(), DATA_RT_BC);
	
  Receive(Proxy_tmk,0,0);
  tmkgetpxd(&interruptInfo);
  if(!interruptInfo.bc.wResult) {
    bcgetblk(2, mass, numberOfWords);
    return 0;
  }
  else
    return 1;
}