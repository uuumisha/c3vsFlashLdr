
/****************************************************************************/
/*      TMKSTAT v3.07 for QNX. ELCUS, 1997,2020.                            */
/*      Messages and constants for driver TMK1553B v3.07 for QNX.           */
/****************************************************************************/

#include <sys/kernel.h>
#include <sys/sendmx.h>
#include <errno.h>

#ifndef __TMKSTAT_H__
#define __TMKSTAT_H__

#define GET_PROXY_MODE 0xFFFF
#define TMK_PROXY_DIRECT 0
#define TMK_PROXY_BUFFERED 1

#define MIN_TMK_TYPE 2
#define MAX_TMK_TYPE 12

#define RTMK         0
#define RTMK1        1
#define TMK400       2
#define TMKMPC       3
#define RTMK400      4
#define TMKX         5
#define TMKXI        6
#define MRTX         7
#define MRTXI        8
#define TA           9
#define TAI          10
#define MRTA         11
#define MRTAI        12

#define ALL_TMKS 0x7FFF
//#define ALL_TMKS 0x00FF

#define GET_TIMEOUT 0xFFFF

#define SWTIMER_OFF   0x0000
#define SWTIMER_ON    0x2400
#define SWTIMER_EVENT 0x8000
#define SWTIMER_RESET 0xFBFF

#define GET_SWTIMER_CTRL 0xFFFF

#define TIMER_RESET 0xFBFF
#define TIMER_OFF   0x0000
#define TIMER_16BIT 0x3400
#define TIMER_32BIT 0x2400
#define TIMER_1US   0x0000
#define TIMER_2US   0x0080
#define TIMER_4US   0x0100
#define TIMER_8US   0x0180
#define TIMER_16US  0x0200
#define TIMER_32US  0x0280
#define TIMER_64US  0x0300
#define TIMER_STOP  0x0380
#define TIMER_SYN   0x0040
#define TIMER_SYND  0x0020
#define TIMER_SA    0x001F

#define TIMER_NOSTOP 0x2000

#define TIMER_MASK  0x37FF
#define TIMER_STEP  0x0380
#define TIMER_BITS  0x3400   

#define GET_TIMER_CTRL 0xFFFF

#define DATA_BC_RT 0x00
#define DATA_BC_RT_BRCST 0x08
#define DATA_RT_BC 0x01
#define DATA_RT_RT 0x02
#define DATA_RT_RT_BRCST 0x0A
#define CTRL_C_A 0x03
#define CTRL_C_BRCST 0x0B
#define CTRL_CD_A 0x04
#define CTRL_CD_BRCST 0x0C
#define CTRL_C_AD 0x05

#define CC_FMT_1 0x00
#define CC_FMT_2 0x01
#define CC_FMT_3 0x02
#define CC_FMT_4 0x03
#define CC_FMT_5 0x05
#define CC_FMT_6 0x04
#define CC_FMT_7 0x08
#define CC_FMT_8 0x0A
#define CC_FMT_9 0x0B
#define CC_FMT_10 0x0C

#define BUS_A 0
#define BUS_B 1
#define BUS_1 0
#define BUS_2 1

#define ERAO_MASK 0x0001
#define MEO_MASK 0x0002
#define IB_MASK 0x0004
#define TO_MASK 0x0008
#define EM_MASK 0x0010
#define EBC_MASK 0x0020
#define DI_MASK 0x0040
#define ELN_MASK 0x0080

#define G1_MASK 0x1000
#define G2_MASK 0x2000

#define S_ERAO_MASK 0x0001
#define S_MEO_MASK 0x0002
#define S_IB_MASK 0x0004
#define S_TO_MASK 0x0008
#define S_EM_MASK 0x0010
#define S_EBC_MASK 0x0020
#define S_DI_MASK 0x0040
#define S_ELN_MASK 0x0080

#define S_G1_MASK 0x1000
#define S_G2_MASK 0x2000

#define NWORDS_MASK 0x001F
#define CMD_MASK 0x041F
#define SUBADDR_MASK 0x03E0
#define CI_MASK 0x03E0
#define HBIT_MASK 0x0200
#define RT_DIR_MASK 0x0400
#define ADDRESS_MASK 0xF800
#define RTFL_MASK 0x0001
#define DNBA_MASK 0x0002
#define SSFL_MASK 0x0004
#define BUSY_MASK 0x0008
#define BRCST_MASK 0x0010
#define NULL_MASK 0x00E0
#define SREQ_MASK 0x0100
#define ERROR_MASK 0x0400

#define SREQ 0x01
#define BUSY 0x02
#define SSFL 0x04
#define RTFL 0x08
#define DNBA 0x10

#define CWB0 0x20
#define CWB1 0x40

#define BC_MODE 0x0000
#define RT_MODE 0x0080
#define MT_MODE 0x0100
#define MRT_MODE 0x0280
#define UNDEFINED_MODE 0xFFFF

#define RT_ENABLE       0x0000
#define RT_DISABLE      0x001F
#define RT_GET_ENABLE   0xFFFF

#define RT_TRANSMIT 0x0400
#define RT_RECEIVE 0x0000

#define RT_ERROR_MASK 0x4000

#define RT_FLAG 0x8000
#define RT_FLAG_MASK 0x8000

#define RT_HBIT_MODE 0x0001
#define MT_HBIT_MODE 0x0001
#define RT_FLAG_MODE 0x0002
#define RT_BRCST_MODE 0x0004
#define RT_DATA_BL 0x2000
#define RT_GENER1_BL 0x0004
#define RT_GENER2_BL 0x4000
#define BC_GENER1_BL 0x0004
#define BC_GENER2_BL 0x4000
#define MT_GENER1_BL 0x0004
#define MT_GENER2_BL 0x4000
#define TMK_IRQ_OFF 0x8000

#define CX_CC_MASK 0x000F
#define CX_CONT_MASK 0x0010
#define CX_BUS_MASK 0x0020
#define CX_SIG_MASK 0x8000
#define CX_INT_MASK 0x0020

#define CX_CONT 0x0010
#define CX_STOP 0x0000
#define CX_BUS_0 0x0000
#define CX_BUS_A 0x0000
#define CX_BUS_1 0x0020
#define CX_BUS_B 0x0020
#define CX_NOSIG 0x0000
#define CX_SIG 0x8000
#define CX_INT 0x0000
#define CX_NOINT 0x0020

#define SX_NOERR 0
#define SX_MEO 1
#define SX_TOA 2
#define SX_TOD 3
#define SX_ELN 4
#define SX_ERAO 5
#define SX_ESYN 6
#define SX_EBC 7

#define SX_ERR_MASK 0x0007
#define SX_IB_MASK 0x0008
#define SX_G1_MASK 0x0010
#define SX_G2_MASK 0x0020
#define SX_K2_MASK 0x0100
#define SX_K1_MASK 0x0200
#define SX_SCC_MASK 0x3C00
#define SX_ME_MASK 0x4000
#define SX_BUS_MASK 0x8000

#define SX_BUS_0 0x0000
#define SX_BUS_A 0x0000
#define SX_BUS_1 0x8000
#define SX_BUS_B 0x8000

#define GET_IO_DELAY 0xFFFF

#define CW(ADDR,DIR,SUBADDR,NWORDS) ((unsigned short)(((ADDR)<<11)|(DIR)|((SUBADDR)<<5)|((NWORDS)&0x1F)))
#define CWM(ADDR,COMMAND) ((unsigned short)(((ADDR)<<11)|(CI_MASK)|(COMMAND)))
#define CWMC(ADDR,CI,COMMAND) ((unsigned short)(((ADDR)<<11)|((CI)&0x03E0)|(COMMAND)))

/*#define CMD_ILLEGAL 0x000*/
#define CMD_DYNAMIC_BUS_CONTROL 0x400
#define CMD_SYNCHRONIZE 0x401
#define CMD_TRANSMIT_STATUS_WORD 0x402
#define CMD_INITIATE_SELF_TEST 0x403
#define CMD_TRANSMITTER_SHUTDOWN 0x404
#define CMD_OVERRIDE_TRANSMITTER_SHUTDOWN 0x405
#define CMD_INHIBIT_TERMINAL_FLAG_BIT 0x406
#define CMD_OVERRIDE_INHIBIT_TERMINAL_FLAG_BIT 0x407
#define CMD_RESET_REMOTE_TERMINAL 0x408
#define CMD_TRANSMIT_VECTOR_WORD 0x410
#define CMD_SYNCHRONIZE_WITH_DATA_WORD 0x011
#define CMD_TRANSMIT_LAST_COMMAND_WORD 0x412
#define CMD_TRANSMIT_BUILT_IN_TEST_WORD 0x413

#ifndef TMK_ERROR_0
#define TMK_ERROR_0 0
#endif

#define TMK_BAD_TYPE     (1 + TMK_ERROR_0)
#define TMK_BAD_IRQ      (2 + TMK_ERROR_0)
#define TMK_BAD_NUMBER   (3 + TMK_ERROR_0)
#define BC_BAD_BUS       (4 + TMK_ERROR_0)
#define BC_BAD_BASE      (5 + TMK_ERROR_0)
#define BC_BAD_LEN       (6 + TMK_ERROR_0)
#define RT_BAD_PAGE      (7 + TMK_ERROR_0)
#define RT_BAD_LEN       (8 + TMK_ERROR_0)
#define RT_BAD_ADDRESS   (9 + TMK_ERROR_0)
#define RT_BAD_FUNC      (10 + TMK_ERROR_0)
#define BC_BAD_FUNC      (11 + TMK_ERROR_0)
#define TMK_BAD_FUNC     (12 + TMK_ERROR_0)
#define TMK_PCI_ERROR    (13 + TMK_ERROR_0)
#define RT_BAD_BUF       (14 + TMK_ERROR_0)

#define TMK_MAX_ERROR    (14 + TMK_ERROR_0)

#define TMK_BAD_MODE 14
#define TMK_OTHER_MODE 15
#define TMK_OTHER_LOCK 16

#define _IO_TMKLL 0x1000

#define SS_TMKDEFMODE 0x01
#define SS_TMKUNDEFMODE 0x02
#define SS_TMKGETMODE 0x03
#define SS_BCRESET 0x04
#define SS_RTRESET 0x05
#define SS_MTRESET 0x06
#define SS_TMKDEFPROXY 0x07
#define SS_TMKMAKEPROXY 0x08
#define SS_TMKGETPXD 0x09
#define SS_BCGETMAXBASE 0x0A
#define SS_MTGETMAXBASE 0x0A
#define SS_BCGETW 0x0B
#define SS_MTGETW 0x0B
#define SS_BCPUTW 0x0C
#define SS_MTPUTW 0x0C
#define SS_BCGETBLK 0x0D
#define SS_MTGETBLK 0X0D
#define SS_BCPUTBLK 0x0E
#define SS_MTPUTBLK 0X0E
#define SS_BCDEFBUS 0x0F
#define SS_BCGETBUS 0x10
#define SS_BCSTART 0x11
#define SS_BCSTARTX 0x12
#define SS_MTSTARTX 0x12
#define SS_BCGETANSW 0x13
#define SS_BCDEFLINK 0x14
#define SS_MTDEFLINK 0x14
#define SS_BCGETLINK 0x15
#define SS_MTGETLINK 0x15
#define SS_BCSTOP 0x16
#define SS_MTSTOP 0x16
#define SS_BCGETSTATE 0x17
#define SS_MTGETSTATE 0x17
#define SS_RTGETMAXPAGE 0x18
#define SS_RTDEFPAGE 0x19
#define SS_RTGETPAGE 0x1A
#define SS_RTDEFPAGEPC 0x1B
#define SS_RTDEFPAGEBUS 0x1C
#define SS_RTGETPAGEPC 0x1D
#define SS_RTGETPAGEBUS 0x1E
#define SS_RTDEFADDRESS 0x1F
#define SS_RTGETADDRESS 0x20
#define SS_RTGETW 0x21
#define SS_RTPUTW 0x22
#define SS_RTGETBLK 0x23
#define SS_RTPUTBLK 0x24
#define SS_RTSETANSWBITS 0x25
#define SS_RTCLRANSWBITS 0x26
#define SS_RTGETANSWBITS 0x27
#define SS_RTGETFLAGS 0x28
#define SS_RTPUTFLAGS 0x29
#define SS_RTSETFLAG 0x2A
#define SS_RTCLRFLAG 0x2B
#define SS_RTGETFLAG 0x2C
#define SS_RTGETSTATE 0x2D
#define SS_RTBUSY 0x2E
#define SS_RTLOCK 0x2F
#define SS_RTUNLOCK 0x30
#define SS_RTGETCMDDATA 0x31
#define SS_RTPUTCMDDATA 0x32
#define SS_RTDEFMODE 0x33
#define SS_RTGETMODE 0x34
#define SS_TMKSETCWBITS 0x35
#define SS_TMKCLRCWBITS 0x36
#define SS_TMKGETCWBITS 0x37
#define SS_MTGETSW 0x38
#define SS_TMK_LOCK 0x39
#define SS_TMK_UNLOCK 0x3A
#define SS_RTARB_LOCK 0x3B
#define SS_RTARB_UNLOCK 0x3C
#define SS_RTANSW_LOCK 0x3D
#define SS_RTANSW_UNLOCK 0x3E
#define SS_BC_DEF_TLDW 0x3F
#define SS_BC_ENABLE_DI 0x40
#define SS_BC_DISABLE_DI 0x41
#define SS_BCDEFIRQMODE 0x42
#define SS_MTDEFIRQMODE 0x42
#define SS_BCGETIRQMODE 0x43
#define SS_MTGETIRQMODE 0x43
#define SS_RTDEFIRQMODE 0x44
#define SS_RTGETIRQMODE 0x45
#define SS_TMKGETINFO 0x46
#define SS_BCDEFMINBASE 0x47
#define SS_BCGETMINBASE 0x48
#define SS_TMKPROXYMODE 0x49
#define SS_TMKTIMER 0x4A
#define SS_TMKGETTIMER 0x4B
#define SS_TMKGETTIMERL 0x4C
#define SS_BCGETMSGTIME 0x4D
#define SS_MTGETMSGTIME 0x4E
#define SS_RTGETMSGTIME 0x4F
#define SS_TMKGETHWVER 0x50
#define SS_TMKGETVERSION 0x51
#define SS_RTENABLE 0x52
#define SS_MRTGETMAXN 0x53
//#define SS_MRTCONFIG 0x55 ?
//#define SS_MRTSELECTED 0x56 ?
#define SS_MRTGETSTATE 0x54
#define SS_MRTDEFBRCSUBADDR0 0x55
#define SS_MRTRESET 0x56
#define SS_TMKGETPXTIME 0x57
#define SS_TMKSWTIMER 0x58
#define SS_TMKGETSWTIMER 0x59
#define SS_TMKTIMEOUT 0x5A

#define SS_TMK_MAX_SERVICE 0x5A

typedef struct
{
  short int nInt;
  unsigned short wMode;
  union
  {
    struct
    {
      unsigned short wResult;
      unsigned short wAW1;
      unsigned short wAW2;
    } bc;
    struct
    {
      unsigned short wBase;
      unsigned short wResultX;
    } bcx;
    struct
    {
      unsigned short wStatus;
      unsigned short wCmd;
    } rt;
    struct
    {
      unsigned short wBase;
      unsigned short wResultX;
    } mt;
  };
} TTmkProxyData;  

struct _tmk_msg_header
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};

struct _bc_msg_header
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};

struct _bc_a_msg_header
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
};

struct _rt_msg_header
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};

struct _rt_a_msg_header
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};

struct __tmk_lock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmk_lock_reply
{
  short int status;
};
struct __tmk_unlock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmk_unlock_reply
{
  short int status;
};
struct __rtarb_lock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtarb_lock_reply
{
  short int status;
};
struct __rtarb_unlock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtarb_unlock_reply
{
  short int status;
};
struct __rtansw_lock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtansw_lock_reply
{
  short int status;
};
struct __rtansw_unlock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtansw_unlock_reply
{
  short int status;
};
struct __tmkdefmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wMode;
};
struct __tmkdefmode_reply
{
  short int status;
};
struct __tmkundefmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkundefmode_reply
{
  short int status;
};
struct __tmkgetmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetmode_reply
{
  short int status;
  unsigned short wMode;
};
struct __bcreset
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcreset_reply
{
  short int status;
};
struct __rtreset
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtreset_reply
{
  short int status;
};
struct __mtreset
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __mtreset_reply
{
  short int status;
};
struct __tmkdefproxy
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  mpid_t Proxy;
};
struct __tmkdefproxy_reply
{
  short int status;
};
struct __tmkmakeproxy
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  mpid_t ProcessId;
};
struct __tmkmakeproxy_reply
{
  short int status;
  mpid_t Proxy;
};
struct __tmkgetpxd
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetpxd_reply
{
  short int status;
  TTmkProxyData data;
};
struct __bcgetmaxbase
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcgetmaxbase_reply
{
  short int status;
  unsigned short wMaxBase;
};
struct __bcgetw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wAddr;
};
struct __bcgetw_reply
{
  short int status;
  unsigned short wData;
};
struct __bcputw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wAddr;
  unsigned short wData;
};
struct __bcputw_reply
{
  short int status;
};
struct __bcgetblk
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wAddr;
  unsigned short wLen;
};
struct __bcgetblk_reply
{
  short int status;
  char data[1];
};
struct __bcputblk
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wAddr;
  unsigned short wLen;
  char data[1];
};
struct __bcputblk_reply
{
  short int status;
};
struct __bcdefbus
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBus;
};
struct __bcdefbus_reply
{
  short int status;
};
struct __bcgetbus
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcgetbus_reply
{
  short int status;
  unsigned short wBus;
};
struct __bcstart
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wCtrlCode;
};
struct __bcstart_reply
{
  short int status;
};
struct __bcstartx
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wCtrlCode;
};
struct __bcstartx_reply
{
  short int status;
};
struct __bcgetansw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wCtrlCode;
};
struct __bcgetansw_reply
{
  short int status;
  union
  {
    struct waws
    {
      unsigned short AW1;
      unsigned short AW2;
    } w;
    struct laws
    {
      unsigned long AWs;
    } l;
  };
};
struct __bcdeflink
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
  unsigned short wNextBase;
  unsigned short wCtrlCode;
};
struct __bcdeflink_reply
{
  short int status;
};
struct __bcgetlink
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
};
struct __bcgetlink_reply
{
  short int status;
  union
  {
    struct wlinks
    {
      unsigned short NextBase;
      unsigned short CtrlCode;
    } w;
    struct llinks
    {
      unsigned long Link;
    } l;
  };
};
struct __bcstop
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcstop_reply
{
  short int status;
};
struct __bcgetstate
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcgetstate_reply
{
  short int status;
  union
  {
    struct wstates
    {
      unsigned short StartBase;
      unsigned short IDontRemember;
    } w;
    struct lstates
    {
      unsigned long State;
    } l;
  };
};
struct __rtgetmaxpage
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetmaxpage_reply
{
  short int status;
  unsigned short wMaxPage;
};
struct __rtdefpage
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wPage;
};
struct __rtdefpage_reply
{
  short int status;
};
struct __rtgetpage
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetpage_reply
{
  short int status;
  unsigned short wPage;
};
struct __rtdefpagepc
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wPage;
};
struct __rtdefpagepc_reply
{
  short int status;
};
struct __rtgetpagepc
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetpagepc_reply
{
  short int status;
  unsigned short wPage;
};
struct __rtdefpagebus
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wPage;
};
struct __rtdefpagebus_reply
{
  short int status;
};
struct __rtgetpagebus
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetpagebus_reply
{
  short int status;
  unsigned short wPage;
};
struct __rtdefaddress
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wAddress;
};
struct __rtdefaddress_reply
{
  short int status;
};
struct __rtgetaddress
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetaddress_reply
{
  short int status;
  unsigned short wAddress;
};
struct __rtgetw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
  unsigned short wAddr;
};
struct __rtgetw_reply
{
  short int status;
  unsigned short wData;
};
struct __rtputw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
  unsigned short wAddr;
  unsigned short wData;
};
struct __rtputw_reply
{
  short int status;
};
struct __rtgetblk
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
  unsigned short wAddr;
  unsigned short wLen;
};
struct __rtgetblk_reply
{
  short int status;
  char data[1];
};
struct __rtputblk
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
  unsigned short wAddr;
  unsigned short wLen;
  char data[1];
};
struct __rtputblk_reply
{
  short int status;
};
struct __rtsetanswbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBits;
};
struct __rtsetanswbits_reply
{
  short int status;
};
struct __rtclranswbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBits;
};
struct __rtclranswbits_reply
{
  short int status;
};
struct __rtgetanswbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetanswbits_reply
{
  short int status;
  unsigned short wBits;
};
struct __rtgetflags
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wMinFlag;
  unsigned short wMaxFlag;
};
struct __rtgetflags_reply
{
  short int status;
  char data[1];
};
struct __rtputflags
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wMinFlag;
  unsigned short wMaxFlag;
  char data[1];
};
struct __rtputflags_reply
{
  short int status;
};
struct __rtsetflag
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtsetflag_reply
{
  short int status;
};
struct __rtclrflag
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtclrflag_reply
{
  short int status;
};
struct __rtgetflag
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtgetflag_reply
{
  short int status;
  unsigned short wFlag;
};
struct __rtgetstate
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetstate_reply
{
  short int status;
  unsigned short wState;
};
struct __rtbusy
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtbusy_reply
{
  short int status;
  int short fBusy;
};
struct __rtlock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtlock_reply
{
  short int status;
};
struct __rtunlock
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtunlock_reply
{
  short int status;
};
struct __rtgetcmddata
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBusCmd;
};
struct __rtgetcmddata_reply
{
  short int status;
  unsigned short wData;
};
struct __rtputcmddata
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBusCmd;
  unsigned short wData;
};
struct __rtputcmddata_reply
{
  short int status;
};
struct __rtdefmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wMode;
};
struct __rtdefmode_reply
{
  short int status;
};
struct __rtgetmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetmode_reply
{
  short int status;
  unsigned short wMode;
};
struct __tmksetcwbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBits;
};
struct __tmksetcwbits_reply
{
  short int status;
};
struct __tmkclrcwbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBits;
};
struct __tmkclrcwbits_reply
{
  short int status;
};
struct __tmkgetcwbits
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetcwbits_reply
{
  short int status;
  unsigned short wBits;
};
struct __mtgetsw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
};
struct __mtgetsw_reply
{
  short int status;
  unsigned short wData;
};
struct __bc_def_tldw
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wData;
};
struct __bc_def_tldw_reply
{
  short int status;
};
struct __bc_enable_di
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bc_enable_di_reply
{
  short int status;
};
struct __bc_disable_di
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bc_disable_di_reply
{
  short int status;
};
struct __bcdefirqmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wIrqMode;
};
struct __bcdefirqmode_reply
{
  short int status;
};
struct __bcgetirqmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcgetirqmode_reply
{
  short int status;
  unsigned short wIrqMode;
};
struct __rtdefirqmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wIrqMode;
};
struct __rtdefirqmode_reply
{
  short int status;
};
struct __rtgetirqmode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __rtgetirqmode_reply
{
  short int status;
  unsigned short wIrqMode;
};
struct __tmkgetinfo
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetinfo_reply
{
  short int status;
  unsigned short tmkType;
  unsigned short tmkPort1;
  unsigned short tmkPort2;
  unsigned short tmkIrq1;
  unsigned short tmkIrq2;
};
struct __bcdefminbase
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wMinBase;
};
struct __bcdefminbase_reply
{
  short int status;
};
struct __bcgetminbase
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __bcgetminbase_reply
{
  short int status;
  unsigned short wMinBase;
};
struct __tmkproxymode
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wProxyMode;
};
struct __tmkproxymode_reply
{
  short int status;
  unsigned short wProxyMode;
};

#define __mtgetmaxbase __bcgetmaxbase
#define __mtgetmaxbase_reply __bcgetmaxbase_reply
#define __mtgetw __bcgetw
#define __mtgetw_reply __bcgetw_reply
#define __mtputw __bcputw
#define __mtputw_reply __bcputw_reply
#define __mtgetblk __bcgetblk
#define __mtgetblk_reply __bcgetblk_reply
#define __mtputblk __bcputblk
#define __mtputblk_reply __bcputblk_reply
#define __mtstartx __bcstartx
#define __mtstartx_reply __bcstartx_reply
#define __mtdeflink __bcdeflink
#define __mtdeflink_reply __bcdeflink_reply
#define __mtgetlink __bcgetlink
#define __mtgetlink_reply __bcgetlink_reply
#define __mtstop __bcstop
#define __mtstop_reply __bcstop_reply
#define __mtgetstate __bcgetstate
#define __mtgetstate_reply __bcgetstate_reply
#define __mtdefirqmode __bcdefirqmode
#define __mtdefirqmode_reply __bcdefirqmode_reply
#define __mtgetirqmode __bcgetirqmode
#define __mtgetirqmode_reply __bcgetirqmode_reply

struct __tmktimer
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wTimerCtrl;
};
struct __tmktimer_reply
{
  short int status;
  unsigned short wTimerCtrl;
};
struct __tmkgettimer
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgettimer_reply
{
  short int status;
  unsigned long dwTimer;
};
struct __tmkgettimerl
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgettimerl_reply
{
  short int status;
  unsigned short wTimer;
};
struct __bcgetmsgtime
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wBase;
};
struct __bcgetmsgtime_reply
{
  short int status;
  unsigned long dwTime;
};
struct __rtgetmsgtime
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wDir;
  unsigned short wSubAddr;
};
struct __rtgetmsgtime_reply
{
  short int status;
  unsigned long dwTime;
};
struct __tmkgethwver
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgethwver_reply
{
  short int status;
  unsigned short wHWVer;
};
struct __tmkGetVersion
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkGetVersion_reply
{
  short int status;
  unsigned short wVersion;
};
struct __rtenable
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wEnable;
};
struct __rtenable_reply
{
  short int status;
  unsigned short wEnable;
};
struct __mrtgetmaxn
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __mrtgetmaxn_reply
{
  short int status;
  unsigned short wMrtMaxN;
};
//#define SS_MRTCONFIG 0x55 ?
//#define SS_MRTSELECTED 0x56 ?
struct __mrtgetstate
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __mrtgetstate_reply
{
  short int status;
  unsigned short wState;
};
struct __mrtdefbrcsubaddr0
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __mrtdefbcrsubaadr0_reply
{
  short int status;
};
struct __mrtreset
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __mrtreset_reply
{
  short int status;
  unsigned long dwResult;
};
struct __tmkgetpxtime
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetpxtime_reply
{
  short int status;
  unsigned long dwTime;
};
struct __tmkswtimer
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wTimerCtrl;
};
struct __tmkswtimer_reply
{
  short int status;
  unsigned short wTimerCtrl;
};
struct __tmkgetswtimer
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
};
struct __tmkgetswtimer_reply
{
  short int status;
  unsigned long dwSwTimer;
};
struct __tmktimeout
{
  unsigned short type;
  unsigned short subtype;
  short int fd;
  unsigned short wTimeOut;
};
struct __tmktimeout_reply
{
  short int status;
  unsigned short wTimeOut;
};

#define __mtgetmsgtime __bcgetmsgtime
#define __mtgetmsgtime_reply __bcgetmsgtime_reply

int tmk_lock();
int tmk_unlock();
int rtarb_lock();
int rtarb_unlock();
int rtansw_lock();
int rtansw_unlock();
int tmkgetmaxn();
int tmkconfig(int tmkNumber, char *tmkPath);
int tmkdone(int tmkNumber);
int tmkselect(int tmkNumber);
int tmkselected();
void tmkgetinfo(int short *tmkType,
                unsigned short *tmkPort1,
                unsigned short *tmkPort2,
                unsigned short *tmkIrq1,
                unsigned short *tmkIrq2);
int tmkdefmode(unsigned short tmkMode);
int tmkundefmode();
unsigned short tmkgetmode();
int bcreset();
int rtreset();
int mtreset();
int tmkdefproxy(pid_t tmkProxy);
pid_t tmkmakeproxy(pid_t proxyProcessId);
int tmkgetpxd(TTmkProxyData *pProxyData);
unsigned short bcgetmaxbase();
int bcdefbase(unsigned short bcBasePC);
unsigned short bcgetbase();
void bcputw(unsigned short bcAddr, unsigned short bcData);
unsigned short bcgetw(unsigned short bcAddr);
int bcputblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength);
int bcgetblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength);
int bcdefbus(unsigned short bcBus);
unsigned short bcgetbus();
int bcstart(unsigned short bcBaseBus, unsigned short bcCtrlCode);
int bcstartx(unsigned short bcBaseBus, unsigned short bcCtrlCode);
unsigned long bcgetansw(unsigned short bcCtrlCode);
int bcdeflink(unsigned short bcNextBase, unsigned short bcCtrlCode);
unsigned long bcgetlink();
int bcstop();
unsigned long bcgetstate();
unsigned short rtgetmaxpage();
int rtdefpage(unsigned short rtPage);
unsigned short rtgetpage();
int rtdefpagepc(unsigned short rtPagePC);
int rtdefpagebus(unsigned short rtPageBus);
unsigned short rtgetpagepc();
unsigned short rtgetpagebus();
int rtdefaddress(unsigned short rtAddress);
unsigned short rtgetaddress();
void rtdefsubaddr(unsigned short rtDir, unsigned short rtSubAddr);
unsigned short rtgetsubaddr();
void rtputw(unsigned short rtAddr, unsigned short rtData);
unsigned short rtgetw(unsigned short rtAddr);
int rtputblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength);
int rtgetblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength);
int rtsetanswbits(unsigned short rtSetControl);
int rtclranswbits(unsigned short rtClrControl);
unsigned short rtgetanswbits();
void rtgetflags(void *pcBuffer, unsigned short rtDir, unsigned short rtMinFlag, unsigned short rtMaxFlag);
void rtputflags(void *pcBuffer, unsigned short rtDir, unsigned short rtMinFlag, unsigned short rtMaxFlag);
void rtsetflag();
void rtclrflag();
unsigned short rtgetflag(unsigned short rtDir, unsigned short rtSubAddr);
unsigned short rtgetstate();
unsigned short rtbusy();
int rtlock(unsigned short rtDir, unsigned short rtSubAddr);
int rtunlock(unsigned short rtDir, unsigned short rtSubAddr);
unsigned short rtgetcmddata(unsigned short rtBusCommand);
void rtputcmddata(unsigned short rtBusCommand, unsigned short rtData);
void tmksetcwbits(unsigned short tmkSetControl);
void tmkclrcwbits(unsigned short tmkClrControl);
unsigned short tmkgetcwbits();
unsigned short mtgetsw();
int rtdefmode(unsigned short rtMode);
unsigned short rtgetmode();
int bcdefirqmode(unsigned short bcIrqMode);
unsigned short bcgetirqmode();
int rtdefirqmode(unsigned short rtIrqMode);
unsigned short rtgetirqmode();
int bcdefminbase(unsigned short bcMinBase);
unsigned short bcgetminbase();
unsigned short tmkproxymode(unsigned short tmkProxyMode);
unsigned short tmktimer(unsigned short tmkTimerCtrl);
unsigned long tmkgettimer();
unsigned short tmkgettimerl();
unsigned long bcgetmsgtime();
unsigned long rtgetmsgtime();
unsigned short tmkgethwver();
unsigned short tmkGetVersion();
unsigned short rtenable(unsigned short wEnable);
int mrtgetmaxn();
int TmkOpen();
int TmkClose();
int mrtconfig(int mrtNum);
int mrtreset();
unsigned long tmkgetpxtime();
unsigned short tmkswtimer(unsigned short tmkTimerCtrl);
unsigned long tmkgetswtimer();
unsigned short tmktimeout(unsigned short tmkTimeOut);

#define mtgetmaxbase bcgetmaxbase
#define mtdefbase bcdefbase
#define mtgetbase bcgetbase
#define mtgetw bcgetw
#define mtputw bcputw
#define mtgetblk bcgetblk
#define mtputblk bcputblk
#define mtstartx bcstartx
#define mtdeflink bcdeflink
#define mtgetlink bcgetlink
#define mtstop bcstop
#define mtgetstate bcgetstate
#define mtdefirqmode bcdefirqmode
#define mtgetirqmode bcgetirqmode
#define mtgetmsgtime bcgetmsgtime
#define mrtselected tmkselected
#define tmkgetevtime tmkgetpxtime

#endif