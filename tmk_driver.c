
/****************************************************************************/
/*      TMKLL4 v3.07 for QNX4. ELCUS, 1997,2020.                            */
/*      Interface to driver TMK1553B v3.07 for QNX4.                        */
/****************************************************************************/

#ifndef _TMKLL_
#define _TMKLL_

#define _TMK1553B_MRT
#define MAX_TMK_NUMBER (8+31*4-1)

#include "inc/tmk_driver.h"

static int tmkError;

static int __tmkPath;
static int __hTMK[MAX_TMK_NUMBER+1];
static int __tmkMaxNumber=0;
static int __tmkSelectedNumber=0;

static unsigned short __abcBasePC[MAX_TMK_NUMBER+1];
static unsigned short __abcMaxBase[MAX_TMK_NUMBER+1];
static unsigned short __artSubAddr[MAX_TMK_NUMBER+1];
static unsigned short __artDir[MAX_TMK_NUMBER+1];
static unsigned short __artMaxPage[MAX_TMK_NUMBER+1];

static struct _mxfer_entry mx_tmk_s[2], mx_tmk_r[2], mx_bc_s[2], mx_rt_s[2];

union __tmk_msgs_s
{
  unsigned short type;
  struct _tmk_msg_header  hdr;
  struct __tmk_lock       t_l;
  struct __rtarb_lock     ra_l;
  struct __rtansw_lock    raw_l;
  struct __tmkdefmode     tdm;
  struct __tmkundefmode   tudm;
  struct __tmkgetmode     tgm;
  struct __bcreset        br;
  struct __rtreset        rr;
  struct __mtreset        mr;
  struct __tmkdefproxy    tdp;
  struct __tmkmakeproxy   tmp;
  struct __tmkgetpxd      tgpd;
  struct __bcgetmaxbase   bgmb;
  struct __mtgetmaxbase   mgmb;
  struct __bcgetw         bgw;
  struct __mtgetw         mgw;
  struct __bcputw         bpw;
  struct __mtputw         mpw;
  struct __bcgetblk       bgbl;
  struct __mtgetblk       mgbl;
  struct __bcputblk       bpbl;
  struct __mtputblk       mpbl;
  struct __bcdefbus       bdbs;
  struct __bcgetbus       bgbs;
  struct __bcstart        bst;
  struct __bcstartx       bsx;
  struct __mtstartx       msx;
  struct __bcgetansw      bgaw;
  struct __bcdeflink      bdl;
  struct __mtdeflink      mdl;
  struct __bcgetlink      bgl;
  struct __mtgetlink      mgl;
  struct __bcstop         bsp;
  struct __mtstop         msp;
  struct __bcgetstate     bgs;
  struct __mtgetstate     mgs;
  struct __rtgetmaxpage   rgmp;
  struct __rtdefpage      rdp;
  struct __rtgetpage      rgp;
  struct __rtdefpagepc    rdpp;
  struct __rtgetpagepc    rgpp;
  struct __rtdefpagebus   rdpb;
  struct __rtgetpagebus   rgpb;
  struct __rtdefaddress   rda;
  struct __rtgetaddress   rga;
  struct __rtgetw         rgw;
  struct __rtputw         rpw;
  struct __rtgetblk       rgbl;
  struct __rtputblk       rpbl;
  struct __rtsetanswbits  rsab;
  struct __rtclranswbits  rcab;
  struct __rtgetanswbits  rgab;
  struct __rtgetflags     rgfs;
  struct __rtputflags     rpfs;
  struct __rtsetflag      rsf;
  struct __rtclrflag      rcf;
  struct __rtgetflag      rgf;
  struct __rtgetstate     rgs;
  struct __rtbusy         rb;
  struct __rtlock         rl;
  struct __rtunlock       rul;
  struct __rtgetcmddata   rgcd;
  struct __rtputcmddata   rpcd;
  struct __rtdefmode      rdm;
  struct __rtgetmode      rgm;
  struct __tmksetcwbits   tscb;
  struct __tmkclrcwbits   tccb;
  struct __tmkgetcwbits   tgcb;
  struct __mtgetsw        mgsw;
  struct __bc_def_tldw    b_d_t;
  struct __bc_enable_di   b_e_d;
  struct __bc_disable_di  b_d_d;
  struct __bcdefirqmode   bdim;
  struct __bcgetirqmode   bgim;
  struct __rtdefirqmode   rdim;
  struct __rtgetirqmode   rgim;
  struct __mtdefirqmode   mdim;
  struct __mtgetirqmode   mgim;
  struct __tmkgetinfo     tgi;
  struct __bcdefminbase   bdnb;
  struct __bcgetminbase   bgnb;
  struct __tmkproxymode   tpm;
  struct __tmktimer       tt;
  struct __tmkgettimer    tgt;
  struct __tmkgettimerl   tgtl;
  struct __bcgetmsgtime   bgmt;
  struct __mtgetmsgtime   mgmt;
  struct __rtgetmsgtime   rgmt;
  struct __tmkgethwver    tghwv;
  struct __tmkGetVersion        tGV;
  struct __rtenable             re;
  struct __mrtgetmaxn           mrgmn;
//#define SS_MRTCONFIG 0x55 ?
//#define SS_MRTSELECTED 0x56 ?
  struct __mrtgetstate          mrgs;
  struct __mrtdefbrcsubaddr0    mrdbsa0;
  struct __mrtreset             mrr;
  struct __tmkgetpxtime         tgpt;
  struct __tmkswtimer           tswt;
  struct __tmkgetswtimer        tgswt;
  struct __tmktimeout           tto;
};
static union __tmk_msgs_s __tms[MAX_TMK_NUMBER+1], *__ptms;

union __tmk_msgs_r
{
  unsigned short status;
  struct __tmk_lock_reply       t_l_r;
  struct __rtarb_lock_reply     ra_l_r;
  struct __rtansw_lock_reply    raw_l_r;
  struct __tmkdefmode_reply     tdm_r;
  struct __tmkundefmode_reply   tudm_r;
  struct __tmkgetmode_reply     tgm_r;
  struct __bcreset_reply        br_r;
  struct __rtreset_reply        rr_r;
  struct __mtreset_reply        mr_r;
  struct __tmkdefproxy_reply    tdp_r;
  struct __tmkmakeproxy_reply   tmp_r;
  struct __tmkgetpxd_reply      tgpd_r;
  struct __bcgetmaxbase_reply   bgmb_r;
  struct __mtgetmaxbase_reply   mgmb_r;
  struct __bcgetw_reply         bgw_r;
  struct __mtgetw_reply         mgw_r;
  struct __bcputw_reply         bpw_r;
  struct __mtputw_reply         mpw_r;
  struct __bcgetblk_reply       bgbl_r;
  struct __mtgetblk_reply       mgbl_r;
  struct __bcputblk_reply       bpbl_r;
  struct __mtputblk_reply       mpbl_r;
  struct __bcdefbus_reply       bdbs_r;
  struct __bcgetbus_reply       bgbs_r;
  struct __bcstart_reply        bst_r;
  struct __bcstartx_reply       bsx_r;
  struct __mtstartx_reply       msx_r;
  struct __bcgetansw_reply      bgaw_r;
  struct __bcdeflink_reply      bdl_r;
  struct __mtdeflink_reply      mdl_r;
  struct __bcgetlink_reply      bgl_r;
  struct __mtgetlink_reply      mgl_r;
  struct __bcstop_reply         bsp_r;
  struct __mtstop_reply         msp_r;
  struct __bcgetstate_reply     bgs_r;
  struct __mtgetstate_reply     mgs_r;
  struct __rtgetmaxpage_reply   rgmp_r;
  struct __rtdefpage_reply      rdp_r;
  struct __rtgetpage_reply      rgp_r;
  struct __rtdefpagepc_reply    rdpp_r;
  struct __rtgetpagepc_reply    rgpp_r;
  struct __rtdefpagebus_reply   rdpb_r;
  struct __rtgetpagebus_reply   rgpb_r;
  struct __rtdefaddress_reply   rda_r;
  struct __rtgetaddress_reply   rga_r;
  struct __rtgetw_reply         rgw_r;
  struct __rtputw_reply         rpw_r;
  struct __rtgetblk_reply       rgbl_r;
  struct __rtputblk_reply       rpbl_r;
  struct __rtsetanswbits_reply  rsab_r;
  struct __rtclranswbits_reply  rcab_r;
  struct __rtgetanswbits_reply  rgab_r;
  struct __rtgetflags_reply     rgfs_r;
  struct __rtputflags_reply     rpfs_r;
  struct __rtsetflag_reply      rsf_r;
  struct __rtclrflag_reply      rcf_r;
  struct __rtgetflag_reply      rgf_r;
  struct __rtgetstate_reply     rgs_r;
  struct __rtbusy_reply         rb_r;
  struct __rtlock_reply         rl_r;
  struct __rtunlock_reply       rul_r;
  struct __rtgetcmddata_reply   rgcd_r;
  struct __rtputcmddata_reply   rpcd_r;
  struct __rtdefmode_reply      rdm_r;
  struct __rtgetmode_reply      rgm_r;
  struct __tmksetcwbits_reply   tscb_r;
  struct __tmkclrcwbits_reply   tccb_r;
  struct __tmkgetcwbits_reply   tgcb_r;
  struct __mtgetsw_reply        mgsw_r;
  struct __bc_def_tldw_reply    b_d_t_r;
  struct __bc_enable_di_reply   b_e_d_r;
  struct __bc_disable_di_reply  b_d_d_r;
  struct __bcdefirqmode_reply   bdim_r;
  struct __bcgetirqmode_reply   bgim_r;
  struct __rtdefirqmode_reply   rdim_r;
  struct __rtgetirqmode_reply   rgim_r;
  struct __mtdefirqmode_reply   mdim_r;
  struct __mtgetirqmode_reply   mgim_r;
  struct __tmkgetinfo_reply     tgi_r;
  struct __bcdefminbase_reply   bdnb_r;
  struct __bcgetminbase_reply   bgnb_r;
  struct __tmkproxymode_reply   tpm_r;
  struct __tmktimer_reply       tt_r;
  struct __tmkgettimer_reply    tgt_r;
  struct __tmkgettimerl_reply   tgtl_r;
  struct __bcgetmsgtime_reply   bgmt_r;
  struct __mtgetmsgtime_reply   mgmt_r;
  struct __rtgetmsgtime_reply   rgmt_r;
  struct __tmkgethwver_reply    tghwv_r;
  struct __tmkGetVersion_reply  tGV_r;
  struct __rtenable_reply       re_r;
  struct __mrtgetmaxn_reply     mrgmn_r;
//#define SS_MRTCONFIG 0x55 ?
//#define SS_MRTSELECTED 0x56 ?
  struct __mrtgetstate_reply    mrgs_r;
  struct __mrtdefbcrsubaadr0_reply mrdbsa0_r;
  struct __mrtreset_reply       mrr_r;
  struct __tmkgetpxtime_reply   tgpt_r;
  struct __tmkswtimer_reply     tswt_r;
  struct __tmkgetswtimer_reply  tgswt_r;
  struct __tmktimeout_reply     tto_r;
};
static union __tmk_msgs_r __tmr;

union __bc_base_msgs_s
{
  struct _bc_a_msg_header hdr;
  struct __bcgetw         bgw;
  struct __bcputw         bpw;
  struct __bcgetblk       bgbl;
  struct __bcputblk       bpbl;
  struct __bcgetansw      bgaw;
  struct __bcdeflink      bdl;
  struct __bcgetlink      bgl;
  struct __mtgetw         mgw;
  struct __mtputw         mpw;
  struct __mtgetblk       mgbl;
  struct __mtputblk       mpbl;
  struct __mtdeflink      mdl;
  struct __mtgetlink      mgl;
  struct __mtgetsw        mgsw;
  struct __bcgetmsgtime   bgmt;
  struct __mtgetmsgtime   mgmt;
};
static union __bc_base_msgs_s __bbms[MAX_TMK_NUMBER+1], *__pbbms;

union __rt_subaddr_msgs_s
{
  struct _rt_a_msg_header hdr;
  struct __rtgetw         rgw;
  struct __rtputw         rpw;
  struct __rtgetblk       rgbl;
  struct __rtputblk       rpbl;
  struct __rtsetflag      rsf;
  struct __rtclrflag      rcf;
  struct __rtgetflag      rgf;
  struct __rtlock         rl;
  struct __rtunlock       rul;
  struct __rtgetmsgtime   rgmt;
};
static union __rt_subaddr_msgs_s __rsms[MAX_TMK_NUMBER+1], *__prsms;


int tmk_lock()
{
  __ptms->hdr.subtype = SS_TMK_LOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmk_lock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmk_lock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int tmk_unlock()
{
  __ptms->hdr.subtype = SS_TMK_UNLOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmk_unlock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmk_unlock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int rtarb_lock()
{
  __ptms->hdr.subtype = SS_RTARB_LOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtarb_lock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtarb_lock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int rtarb_unlock()
{
  __ptms->hdr.subtype = SS_RTARB_UNLOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtarb_unlock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtarb_unlock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int rtansw_lock()
{
  __ptms->hdr.subtype = SS_RTANSW_LOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtansw_lock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtansw_lock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int rtansw_unlock()
{
  __ptms->hdr.subtype = SS_RTANSW_UNLOCK;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtansw_unlock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtansw_unlock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return __tmr.status;
}
int tmkgetmaxn()
{
  return MAX_TMK_NUMBER;
}
int tmkconfig(int tmkNumber, char *tmkPath)
{
  if (tmkNumber<0 || tmkNumber>MAX_TMK_NUMBER)
  {
    return(tmkError = TMK_BAD_NUMBER);
  }
  __hTMK[tmkNumber] = open(tmkPath,0);
  if (__hTMK[tmkNumber]==-1)
  {
    tmkError = TMK_BAD_TYPE;
    __tmkPath = 0;
  }
  else
  {
    tmkError = EOK;
    __tmkPath = __hTMK[tmkNumber];
    __tmkSelectedNumber = tmkNumber;
    if (__tmkMaxNumber<tmkNumber)
      __tmkMaxNumber=tmkNumber;
    __ptms = &__tms[tmkNumber];
    __ptms->hdr.type = _IO_TMKLL;
    __ptms->hdr.fd = __tmkPath;
    __pbbms = &__bbms[tmkNumber];
    __pbbms->hdr.type = _IO_TMKLL;
    __pbbms->hdr.fd = __tmkPath;
    __pbbms->hdr.wBase = 0;
    __prsms = &__rsms[tmkNumber];
    __prsms->hdr.type = _IO_TMKLL;
    __prsms->hdr.fd = __tmkPath;
    __prsms->hdr.wDir = RT_RECEIVE;
    __prsms->hdr.wSubAddr = 0x10;
    _setmx(&mx_tmk_s[0], __ptms, 0);
    _setmx(&mx_tmk_r[0], &__tmr, 0);
    _setmx(&mx_bc_s[0], __pbbms, 0);
    _setmx(&mx_rt_s[0], __prsms, 0);
    __ptms->hdr.subtype = SS_BCGETMAXBASE;
    mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetmaxbase);
    mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetmaxbase_reply);
    Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
    __abcMaxBase[tmkNumber] = __tmr.bgmb_r.wMaxBase;
    __ptms->hdr.subtype = SS_RTGETMAXPAGE;
    mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetmaxpage);
    mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetmaxpage_reply);
    Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
    __artMaxPage[tmkNumber] = __tmr.rgmp_r.wMaxPage;
  }
  return tmkError;
}
int tmkdone(int tmkNumber)
{
  int i, imax, imin;
  
  if (tmkNumber == ALL_TMKS)
  {
    imin = 0;
    imax = __tmkMaxNumber;
  }
  else if (tmkNumber>=0 && tmkNumber<=MAX_TMK_NUMBER)
  {
    imin = tmkNumber;
    imax = tmkNumber;
  }
  else
  {
    return(tmkError = TMK_BAD_NUMBER);
  }
  for (i=imin; i<=imax; i++)
  {
    if (__hTMK[i])
    {
      if (close(__hTMK[i]) == -1)
        tmkError = errno;
      __hTMK[i] = 0;
    }
  }
  return tmkError;
}
int tmkselect(int tmkNumber)
{
  if (tmkNumber>=0 && tmkNumber<=__tmkMaxNumber && __hTMK[tmkNumber])
  {
    __tmkSelectedNumber=tmkNumber;
    __tmkPath=__hTMK[tmkNumber];
    __ptms = &__tms[tmkNumber];
    __pbbms = &__bbms[tmkNumber];
    __prsms = &__rsms[tmkNumber];
    _setmx(&mx_tmk_s[0], __ptms, 0);
    _setmx(&mx_tmk_r[0], &__tmr, 0);
    _setmx(&mx_bc_s[0], __pbbms, 0);
    _setmx(&mx_rt_s[0], __prsms, 0);
    return(tmkError = EOK);
  }
  return(tmkError = TMK_BAD_NUMBER);
}
int tmkselected()
{
  return(__tmkSelectedNumber);
}
void tmkgetinfo(int short *tmkType,
                unsigned short *tmkPort1,
                unsigned short *tmkPort2,
                unsigned short *tmkIrq1,
                unsigned short *tmkIrq2)
{
  __ptms->hdr.subtype = SS_TMKGETINFO;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgetinfo);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgetinfo_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  if (tmkType)
    *tmkType = __tmr.tgi_r.tmkType;
  if (tmkPort1)
    *tmkPort1 = __tmr.tgi_r.tmkPort1;
  if (tmkPort2)
    *tmkPort2 = __tmr.tgi_r.tmkPort2;
  if (tmkIrq1)
    *tmkIrq1 = __tmr.tgi_r.tmkIrq1;
  if (tmkIrq2)
    *tmkIrq2 = __tmr.tgi_r.tmkIrq2;
}
int tmkdefmode(unsigned short tmkMode)
{
  __ptms->hdr.subtype = SS_TMKDEFMODE;
  __ptms->tdm.wMode = tmkMode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkdefmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkdefmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
int tmkundefmode()
{
  __ptms->hdr.subtype = SS_TMKUNDEFMODE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkundefmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkundefmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short tmkgetmode()
{
  __ptms->hdr.subtype = SS_TMKGETMODE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgetmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgetmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tgm_r.wMode);
}
int bcreset()
{
  __ptms->hdr.subtype = SS_BCRESET;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcreset);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcreset_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
int rtreset()
{
  __ptms->hdr.subtype = SS_RTRESET;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtreset);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtreset_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
int mtreset()
{
  __ptms->hdr.subtype = SS_MTRESET;
  mx_tmk_s[0].mxfer_len = sizeof(struct __mtreset);
  mx_tmk_r[0].mxfer_len = sizeof(struct __mtreset_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
int tmkdefproxy(pid_t tmkProxy)
{
  __ptms->hdr.subtype = SS_TMKDEFPROXY;
  __ptms->tdp.Proxy = tmkProxy;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkdefproxy);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkdefproxy_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
pid_t tmkmakeproxy(pid_t proxyProcessId)
{
  __ptms->hdr.subtype = SS_TMKMAKEPROXY;
  __ptms->tmp.ProcessId = proxyProcessId;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkmakeproxy);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkmakeproxy_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  if ((tmkError = __tmr.status) == EOK)
    return(__tmr.tmp_r.Proxy);
  else
    return -1;
}
int tmkgetpxd(TTmkProxyData *pProxyData)
{
  __ptms->hdr.subtype = SS_TMKGETPXD;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgetpxd);
  mx_tmk_r[0].mxfer_len = sizeof(__tmr.tgpd_r) - sizeof(TTmkProxyData);
  _setmx(&mx_tmk_r[1], pProxyData, sizeof(TTmkProxyData));
  Sendfdmx(__tmkPath, 1, 2, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short bcgetmaxbase()
{
  __ptms->hdr.subtype = SS_BCGETMAXBASE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetmaxbase);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetmaxbase_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  __abcMaxBase[__tmkSelectedNumber] = __tmr.bgmb_r.wMaxBase;
  return(__tmr.bgmb_r.wMaxBase);
}
int bcdefbase(unsigned short bcBasePC)
{
  if (bcBasePC > __abcMaxBase[__tmkSelectedNumber])
    return(tmkError = BC_BAD_BASE);
  __pbbms->hdr.wBase = bcBasePC;
  return(tmkError = 0);
}
unsigned short bcgetbase()
{
  return(__pbbms->hdr.wBase);
}
void bcputw(unsigned short bcAddr, unsigned short bcData)
{
  __pbbms->hdr.subtype = SS_BCPUTW;
  __pbbms->bpw.wAddr = bcAddr;
  __pbbms->bpw.wData = bcData;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcputw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcputw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
}
unsigned short bcgetw(unsigned short bcAddr)
{
  __pbbms->hdr.subtype = SS_BCGETW;
  __pbbms->bgw.wAddr = bcAddr;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcgetw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.bgw_r.wData);
}
int bcputblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength)
{
  __pbbms->hdr.subtype = SS_BCPUTBLK;
  __pbbms->bpbl.wAddr = bcAddr;
  __pbbms->bpbl.wLen = cwLength;
  mx_bc_s[0].mxfer_len = sizeof(__pbbms->bpbl) - sizeof(__pbbms->bpbl.data);
  _setmx(&mx_bc_s[1], pcBuffer, cwLength<<1);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcputblk_reply);
  Sendfdmx(__tmkPath, 2, 1, &mx_bc_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
} 
int bcgetblk(unsigned short bcAddr, void *pcBuffer, unsigned short cwLength)
{
  __pbbms->hdr.subtype = SS_BCGETBLK;
  __pbbms->bgbl.wAddr = bcAddr;
  __pbbms->bgbl.wLen = cwLength;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcgetblk);
  mx_tmk_r[0].mxfer_len = sizeof(__tmr.bgbl_r) - sizeof(__tmr.bgbl_r.data);
  _setmx(&mx_tmk_r[1], pcBuffer, cwLength<<1);
  Sendfdmx(__tmkPath, 1, 2, &mx_bc_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int bcdefbus(unsigned short bcBus)
{
  __ptms->hdr.subtype = SS_BCDEFBUS;
  __ptms->bdbs.wBus = bcBus;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcdefbus);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcdefbus_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short bcgetbus()
{
  __ptms->hdr.subtype = SS_BCGETBUS;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetbus);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetbus_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.bgbs_r.wBus);
}
int bcstart(unsigned short bcBaseBus, unsigned short bcCtrlCode)
{
  __ptms->hdr.subtype = SS_BCSTART;
  __ptms->bst.wBase = bcBaseBus;
  __ptms->bst.wCtrlCode = bcCtrlCode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcstart);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcstart_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
int bcstartx(unsigned short bcBaseBus, unsigned short bcCtrlCode)
{
  __ptms->hdr.subtype = SS_BCSTARTX;
  __ptms->bsx.wBase = bcBaseBus;
  __ptms->bsx.wCtrlCode = bcCtrlCode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcstartx);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcstartx_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned long bcgetansw(unsigned short bcCtrlCode)
{
  __pbbms->hdr.subtype = SS_BCGETANSW;
  __pbbms->bgaw.wCtrlCode = bcCtrlCode;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcgetansw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetansw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.bgaw_r.l.AWs);
}
int bcdeflink(unsigned short bcNextBase, unsigned short bcCtrlCode)
{
  __pbbms->hdr.subtype = SS_BCDEFLINK;
  __pbbms->bdl.wNextBase = bcNextBase;
  __pbbms->bdl.wCtrlCode = bcCtrlCode;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcdeflink);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcdeflink_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned long bcgetlink()
{
  __pbbms->hdr.subtype = SS_BCGETLINK;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcgetlink);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetlink_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.bgl_r.l.Link);
}
int bcstop()
{
  __ptms->hdr.subtype = SS_BCSTOP;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcstop);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcstop_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned long bcgetstate()
{
  __ptms->hdr.subtype = SS_BCGETSTATE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetstate);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetstate_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.bgs_r.l.State);
} 
unsigned short rtgetmaxpage()
{
  __ptms->hdr.subtype = SS_RTGETMAXPAGE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetmaxpage);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetmaxpage_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgmp_r.wMaxPage);
}
int rtdefpage(unsigned short rtPage)
{
  __ptms->hdr.subtype = SS_RTDEFPAGE;
  __ptms->rdp.wPage = rtPage;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefpage);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefpage_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned short rtgetpage()
{
  __ptms->hdr.subtype = SS_RTGETPAGE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetpage);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetpage_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgp_r.wPage);
}
int rtdefpagepc(unsigned short rtPagePC)
{
  __ptms->hdr.subtype = SS_RTDEFPAGEPC;
  __ptms->rdpp.wPage = rtPagePC;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefpagepc);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefpagepc_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int rtdefpagebus(unsigned short rtPageBus)
{
  __ptms->hdr.subtype = SS_RTDEFPAGEBUS;
  __ptms->rdpb.wPage = rtPageBus;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefpagebus);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefpagebus_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned short rtgetpagepc()
{
  __ptms->hdr.subtype = SS_RTGETPAGEPC;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetpagepc);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetpagepc_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgpp_r.wPage);
}
unsigned short rtgetpagebus()
{
  __ptms->hdr.subtype = SS_RTGETPAGEBUS;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetpagebus);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetpagebus_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgpb_r.wPage);
}
int rtdefaddress(unsigned short rtAddress)
{
  __ptms->hdr.subtype = SS_RTDEFADDRESS;
  __ptms->rda.wAddress = rtAddress;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefaddress);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefaddress_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned short rtgetaddress()
{
  __ptms->hdr.subtype = SS_RTGETADDRESS;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetaddress);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetaddress_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rga_r.wAddress);
}
void rtdefsubaddr(unsigned short rtDir, unsigned short rtSubAddr)
{
  __prsms->hdr.wDir = rtDir;
  __prsms->hdr.wSubAddr = rtSubAddr;
}
unsigned short rtgetsubaddr()
{
  return(__prsms->hdr.wSubAddr & 0x1F | __prsms->hdr.wDir & RT_TRANSMIT);
}
void rtputw(unsigned short rtAddr, unsigned short rtData)
{
  __prsms->hdr.subtype = SS_RTPUTW;
  __prsms->rpw.wAddr = rtAddr;
  __prsms->rpw.wData = rtData;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtputw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtputw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
}
unsigned short rtgetw(unsigned short rtAddr)
{
  __prsms->hdr.subtype = SS_RTGETW;
  __prsms->rgw.wAddr = rtAddr;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtgetw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.rgw_r.wData);
}
int rtputblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength)
{
  __prsms->hdr.subtype = SS_RTPUTBLK;
  __prsms->rpbl.wAddr = rtAddr;
  __prsms->rpbl.wLen = cwLength;
  mx_rt_s[0].mxfer_len = sizeof(__prsms->rpbl) - sizeof(__prsms->rpbl.data);
  _setmx(&mx_rt_s[1], pcBuffer, cwLength<<1);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtputblk_reply);
  Sendfdmx(__tmkPath, 2, 1, &mx_rt_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int rtgetblk(unsigned short rtAddr, void *pcBuffer, unsigned short cwLength)
{
  __prsms->hdr.subtype = SS_RTGETBLK;
  __prsms->rgbl.wAddr = rtAddr;
  __prsms->rgbl.wLen = cwLength;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtgetblk);
  mx_tmk_r[0].mxfer_len = sizeof(__tmr.rgbl_r) - sizeof(__tmr.rgbl_r.data);
  _setmx(&mx_tmk_r[1], pcBuffer, cwLength<<1);
  Sendfdmx(__tmkPath, 1, 2, &mx_rt_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int rtsetanswbits(unsigned short rtSetControl)
{
  __ptms->hdr.subtype = SS_RTSETANSWBITS;
  __ptms->rsab.wBits = rtSetControl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtsetanswbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtsetanswbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int rtclranswbits(unsigned short rtClrControl)
{
  __ptms->hdr.subtype = SS_RTCLRANSWBITS;
  __ptms->rcab.wBits = rtClrControl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtclranswbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtclranswbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned short rtgetanswbits()
{
  __ptms->hdr.subtype = SS_RTGETANSWBITS;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetanswbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetanswbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgab_r.wBits);
}
void rtgetflags(void *pcBuffer, unsigned short rtDir, unsigned short rtMinFlag, unsigned short rtMaxFlag)
{
  short nLen;

   if ((nLen = rtMaxFlag&0x1F - rtMinFlag&0x1F + 1) <= 0)
    return;
  __ptms->hdr.subtype = SS_RTGETFLAGS;
  __ptms->rgfs.wDir = rtDir;
  __ptms->rgfs.wMinFlag = rtMinFlag;
  __ptms->rgfs.wMaxFlag = rtMaxFlag;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtgetflags);
  mx_tmk_r[0].mxfer_len = sizeof(__tmr.rgfs_r) - sizeof(__tmr.rgfs_r.data);
  _setmx(&mx_tmk_r[1], pcBuffer, nLen<<1);
  Sendfdmx(__tmkPath, 1, 2, &mx_rt_s, &mx_tmk_r);
  return;
}
void rtputflags(void *pcBuffer, unsigned short rtDir, unsigned short rtMinFlag, unsigned short rtMaxFlag)
{
  short nLen;

   if ((nLen = rtMaxFlag&0x1F - rtMinFlag&0x1F + 1) <= 0)
    return;
  __ptms->hdr.subtype = SS_RTPUTFLAGS;
  __ptms->rpfs.wDir = rtDir;
  __ptms->rpfs.wMinFlag = rtMinFlag;
  __ptms->rpfs.wMaxFlag = rtMaxFlag;
  mx_rt_s[0].mxfer_len = sizeof(__ptms->rpfs) - sizeof(__ptms->rpfs.data);
  _setmx(&mx_rt_s[1], pcBuffer, nLen<<1);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtputflags_reply);
  Sendfdmx(__tmkPath, 2, 1, &mx_rt_s, &mx_tmk_r);
  return;
}
void rtsetflag()
{
  __prsms->hdr.subtype = SS_RTSETFLAG;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtsetflag);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtsetflag_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
}
void rtclrflag()
{
  __prsms->hdr.subtype = SS_RTCLRFLAG;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtclrflag);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtclrflag_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
}
unsigned short rtgetflag(unsigned short rtDir, unsigned short rtSubAddr)
{
  __prsms->hdr.subtype = SS_RTGETFLAG;
  __prsms->hdr.wDir = rtDir;
  __prsms->hdr.wSubAddr = rtSubAddr;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtgetflag);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetflag_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  return(__tmr.rgf_r.wFlag);
}
unsigned short rtgetstate()
{
  __ptms->hdr.subtype = SS_RTGETSTATE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetstate);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetstate_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgs_r.wState);
}
unsigned short rtbusy()
{
  __ptms->hdr.subtype = SS_RTBUSY;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtbusy);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtbusy_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rb_r.fBusy);
}
int rtlock(unsigned short rtDir, unsigned short rtSubAddr)
{
  __prsms->hdr.subtype = SS_RTLOCK;
  __prsms->hdr.wDir = rtDir;
  __prsms->hdr.wSubAddr = rtSubAddr;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtlock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtlock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
int rtunlock(unsigned short rtDir, unsigned short rtSubAddr)
{
  __prsms->hdr.subtype = SS_RTUNLOCK;
  __prsms->hdr.wDir = rtDir;
  __prsms->hdr.wSubAddr = rtSubAddr;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtunlock);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtunlock_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  return(tmkError = __tmr.status);
}
unsigned short rtgetcmddata(unsigned short rtBusCommand)
{
  __ptms->hdr.subtype = SS_RTGETCMDDATA;
  __ptms->rgcd.wBusCmd = rtBusCommand;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetcmddata);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetcmddata_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgcd_r.wData);
}
void rtputcmddata(unsigned short rtBusCommand, unsigned short rtData)
{
  __ptms->hdr.subtype = SS_RTPUTCMDDATA;
  __ptms->rpcd.wBusCmd = rtBusCommand;
  __ptms->rpcd.wData = rtData;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtputcmddata);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtputcmddata_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return;
}
void tmksetcwbits(unsigned short tmkSetControl)
{
  __ptms->hdr.subtype = SS_TMKSETCWBITS;
  __ptms->tscb.wBits = tmkSetControl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmksetcwbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmksetcwbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return;
}
void tmkclrcwbits(unsigned short tmkClrControl)
{
  __ptms->hdr.subtype = SS_TMKCLRCWBITS;
  __ptms->tscb.wBits = tmkClrControl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkclrcwbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkclrcwbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return;
}
unsigned short tmkgetcwbits()
{
  __ptms->hdr.subtype = SS_TMKGETCWBITS;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgetcwbits);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgetcwbits_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tgcb_r.wBits);
}
unsigned short mtgetsw()
{
  __pbbms->hdr.subtype = SS_MTGETSW;
  mx_bc_s[0].mxfer_len = sizeof(struct __mtgetsw);
  mx_tmk_r[0].mxfer_len = sizeof(struct __mtgetsw_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.mgsw_r.wData);
}
int rtdefmode(unsigned short rtMode)
{
  __ptms->hdr.subtype = SS_RTDEFMODE;
  __ptms->rdm.wMode = rtMode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short rtgetmode()
{
  __ptms->hdr.subtype = SS_RTGETMODE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgm_r.wMode);
}
int bcdefirqmode(unsigned short bcIrqMode)
{
  __ptms->hdr.subtype = SS_BCDEFIRQMODE;
  __ptms->bdim.wIrqMode = bcIrqMode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcdefirqmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcdefirqmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short bcgetirqmode()
{
  __ptms->hdr.subtype = SS_BCGETIRQMODE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetirqmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetirqmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.bgim_r.wIrqMode);
}
int rtdefirqmode(unsigned short rtIrqMode)
{
  __ptms->hdr.subtype = SS_RTDEFIRQMODE;
  __ptms->rdim.wIrqMode = rtIrqMode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtdefirqmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtdefirqmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short rtgetirqmode()
{
  __ptms->hdr.subtype = SS_RTGETIRQMODE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtgetirqmode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetirqmode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.rgim_r.wIrqMode);
}
int bcdefminbase(unsigned short bcMinBase)
{
  __ptms->hdr.subtype = SS_BCDEFMINBASE;
  __ptms->bdnb.wMinBase = bcMinBase;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcdefminbase);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcdefminbase_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.status);
}
unsigned short bcgetminbase()
{
  __ptms->hdr.subtype = SS_BCGETMINBASE;
  mx_tmk_s[0].mxfer_len = sizeof(struct __bcgetminbase);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetminbase_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.bgnb_r.wMinBase);
}
unsigned short tmkproxymode(unsigned short tmkProxyMode)
{
  __ptms->hdr.subtype = SS_TMKPROXYMODE;
  __ptms->tpm.wProxyMode = tmkProxyMode;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkproxymode);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkproxymode_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tpm_r.wProxyMode);
}



unsigned short tmktimer(unsigned short tmkTimerCtrl)
{
  __ptms->hdr.subtype = SS_TMKTIMER;
  __ptms->tt.wTimerCtrl = tmkTimerCtrl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmktimer);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmktimer_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tt_r.wTimerCtrl);
}
unsigned long tmkgettimer()
{
  __ptms->hdr.subtype = SS_TMKGETTIMER;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgettimer);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgettimer_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tgt_r.dwTimer);
}
unsigned short tmkgettimerl()
{
  __ptms->hdr.subtype = SS_TMKGETTIMERL;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgettimerl);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgettimerl_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tgtl_r.wTimer);
}
unsigned long bcgetmsgtime()
{
  __pbbms->hdr.subtype = SS_BCGETMSGTIME;
  mx_bc_s[0].mxfer_len = sizeof(struct __bcgetmsgtime);
  mx_tmk_r[0].mxfer_len = sizeof(struct __bcgetmsgtime_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_bc_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.bgmt_r.dwTime);
}
#define mtgetmsgtime bcgetmsgtime
unsigned long rtgetmsgtime()
{
  __prsms->hdr.subtype = SS_RTGETMSGTIME;
  mx_rt_s[0].mxfer_len = sizeof(struct __rtgetmsgtime);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtgetmsgtime_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.rgmt_r.dwTime);
}
unsigned short tmkgethwver()
{
  __ptms->hdr.subtype = SS_TMKGETHWVER;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgethwver);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgethwver_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tghwv_r.wHWVer);
}
unsigned short tmkGetVersion()
{
  __ptms->hdr.subtype = SS_TMKGETVERSION;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkGetVersion);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkGetVersion_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tGV_r.wVersion);
}
unsigned short rtenable(unsigned short wEnable)
{
  __ptms->hdr.subtype = SS_RTENABLE;
  __ptms->re.wEnable = wEnable;
  mx_tmk_s[0].mxfer_len = sizeof(struct __rtenable);
  mx_tmk_r[0].mxfer_len = sizeof(struct __rtenable_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.re_r.wEnable);
}
int mrtgetmaxn()
{
  return -1;
}
#define mrtselected tmkselected
int TmkOpen()
{
  return 0;
}  
int TmkClose()
{
  return 0;
}
int mrtconfig(int mrtNum)
{
  return 0;
}
int mrtreset()
{
  return -1;
}
unsigned long tmkgetpxtime()
{
  __prsms->hdr.subtype = SS_TMKGETPXTIME;
  mx_rt_s[0].mxfer_len = sizeof(struct __tmkgetpxtime);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgetpxtime_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_rt_s, &mx_tmk_r);
  tmkError = __tmr.status;
  return(__tmr.tgpt_r.dwTime);
}
#define tmkgetevtime tmkgetpxtime
unsigned short tmkswtimer(unsigned short tmkTimerCtrl)
{
  __ptms->hdr.subtype = SS_TMKSWTIMER;
  __ptms->tswt.wTimerCtrl = tmkTimerCtrl;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkswtimer);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkswtimer_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tswt_r.wTimerCtrl);
}
unsigned long tmkgetswtimer()
{
  __ptms->hdr.subtype = SS_TMKGETSWTIMER;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmkgetswtimer);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmkgetswtimer_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tgswt_r.dwSwTimer);
}
unsigned short tmktimeout(unsigned short tmkTimeOut)
{
  __ptms->hdr.subtype = SS_TMKTIMEOUT;
  __ptms->tto.wTimeOut = tmkTimeOut;
  mx_tmk_s[0].mxfer_len = sizeof(struct __tmktimeout);
  mx_tmk_r[0].mxfer_len = sizeof(struct __tmktimeout_reply);
  Sendfdmx(__tmkPath, 1, 1, &mx_tmk_s, &mx_tmk_r);
  return(__tmr.tto_r.wTimeOut);
}

#endif
