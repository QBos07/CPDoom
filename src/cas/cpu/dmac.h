#pragma once

#include "helper.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __has_builtin
#if __has_builtin(__builtin_expect)
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#endif

#ifndef unlikely
#define unlikely(x) (x)
#endif

// Configuration Enums
typedef enum  
{
  DMAC_DMAOR_CMS_NORMAL           = 0x0,
  DMAC_DMAOR_CMS_INTERMITTENT_16  = 0x2,
  DMAC_DMAOR_CMS_INTERMITTENT_64  = 0x3,
  DMAC_DMAOR_CMS_INTERMITTENT_256 = 0x4,
} dmac_dmaor_cms_t;

typedef enum  
{
  DMAC_DMAOR_PR_PRIORITY_0  = 0x0, // CH0 > CH1 > CH2 > CH3 > CH4 > CH5
  DMAC_DMAOR_PR_PRIORITY_1  = 0x1, // CH0 > CH2 > CH3 > CH1 > CH4 > CH5
  DMAC_DMAOR_PR_ROUND_ROBIN = 0x3,
} dmac_dmaor_pr_t;

// CHCR
typedef enum  
{
  DMAC_CHCR_RPT_REPEAT_NORMAL      = 0x0,
  DMAC_CHCR_RPT_REPEAT_SAR_DAR_TCR = 0x1,
  DMAC_CHCR_RPT_REPEAT_DAR_TCR     = 0x2,
  DMAC_CHCR_RPT_REPEAT_SAR_TCR     = 0x3,
  DMAC_CHCR_RPT_RELOAD_SAR_DAR_TCR = 0x5,
  DMAC_CHCR_RPT_RELOAD_DAR_TCR     = 0x6,
  DMAC_CHCR_RPT_RELOAD_SAR_TCR     = 0x7,
} dmac_chcr_rpt_t;

typedef enum  
{
  DMAC_CHCR_AM_READ_CYCLE = 0x0,
  DMAC_CHCR_AM_WRITE_CYCLE = 0x1,
} dmac_chcr_am_t;

typedef enum  
{
  DMAC_CHCR_AL_ACTIVE_LOW = 0x0,
  DMAC_CHCR_AL_ACTIVE_HIGH = 0x1,
} dmac_chcr_al_t;

typedef enum  
{
  DMAC_CHCR_TS_LS_SIZE_1    = 0x0,
  DMAC_CHCR_TS_LS_SIZE_2    = 0x1,
  DMAC_CHCR_TS_LS_SIZE_4    = 0x2,
  DMAC_CHCR_TS_LS_SIZE_16   = 0x3,
  DMAC_CHCR_TS_LS_SIZE_32   = 0x0,
  DMAC_CHCR_TS_LS_SIZE_8    = 0x3,
  DMAC_CHCR_TS_LS_SIZE_8x2  = 0x3,
  DMAC_CHCR_TS_LS_SIZE_16x2 = 0x0,
} dmac_chcr_ts_ls_t;

typedef enum  
{
  DMAC_CHCR_TS_MS_SIZE_1    = 0x0,
  DMAC_CHCR_TS_MS_SIZE_2    = 0x0,
  DMAC_CHCR_TS_MS_SIZE_4    = 0x0,
  DMAC_CHCR_TS_MS_SIZE_16   = 0x0,
  DMAC_CHCR_TS_MS_SIZE_32   = 0x1,
  DMAC_CHCR_TS_MS_SIZE_8    = 0x1,
  DMAC_CHCR_TS_MS_SIZE_8x2  = 0x2,
  DMAC_CHCR_TS_MS_SIZE_16x2 = 0x3,
} dmac_chcr_ts_ms_t;

typedef enum  
{
  DMAC_CHCR_DM_SM_FIXED_SOFT = 0x0, // Address is fixed, but will be incremented in 16/32-byte division  
                                // transfer mode. Check SH7730 User's Manual Figure 12.3.7  
  DMAC_CHCR_DM_SM_INCREMENT  = 0x1,
  DMAC_CHCR_DM_SM_DECREMENT  = 0x2, // Prohibited in 8/16/32-byte transfer mode
  DMAC_CHCR_DM_SM_FIXED_HARD = 0x3, // Address is fixed, even in 16/32-byte division transfer mode. 
} dmac_chcr_dm_sm_t;

typedef enum  
{
  DMAC_CHCR_RS_EXTERNAL = 0x0,  
  DMAC_CHCR_RS_AUTO     = 0x4,
  DMAC_CHCR_RS_DMARS    = 0x8,
} dmac_chcr_rs_t;

typedef enum  
{
  DMAC_CHCR_DLDS_LOW_LEVEL    = 0x0,  
  DMAC_CHCR_DLDS_FALLING_EDGE = 0x1,
  DMAC_CHCR_DLDS_HIGH_LEVEL   = 0x2,
  DMAC_CHCR_DLDS_RISING_EDGE  = 0x3,
} dmac_chcr_dlds_t;

typedef enum  
{
  DMAC_CHCR_TB_CYCLE_STEAL = 0x0,  
  DMAC_CHCR_TB_BURST       = 0x1,
} dmac_chcr_tb_t;

typedef regstruct {
  unsigned                : 1;
  bool              lckn  : 1; // Bus Release Enable in Cycle Steal Mode
  unsigned                : 2;
  dmac_chcr_rpt_t   rpt   : 3; // DMA Settings Renewal Specify
  unsigned                : 1;
  bool              do_   : 1; // DMA Overrun
  unsigned                : 1;
  dmac_chcr_ts_ms_t ts_ms : 2; // DMA Transfer Size Specify (MS 2 bits)
  bool              he    : 1; // Half End Flag
  bool              hie   : 1; // Half End Interrupt Enable
  dmac_chcr_am_t    am    : 1; // Acknowledge Mode
  dmac_chcr_al_t    al    : 1; // Acknowledge Level
  dmac_chcr_dm_sm_t dm    : 2; // Destination Address Mode
  dmac_chcr_dm_sm_t sm    : 2; // Source Address Mode
  dmac_chcr_rs_t    rs    : 4; // Resource Select
  dmac_chcr_dlds_t  dlds  : 2; // DREQ Level and Edge Select
  dmac_chcr_tb_t    tb    : 1; // Transfer Bus Mode
  dmac_chcr_ts_ls_t ts_ls : 2; // DMA Transfer Size Specify (LS 2 bits)
  bool              ie    : 1; // Interrupt Enable
  bool              te    : 1; // Transfer End Flag
  bool              de    : 1; // DMA Enable
} dmac_chcr_t;

typedef regstructx(16)
{
  dmac_dmaor_cms_t cms  : 4; // Cycle Steal Mode
  unsigned            : 2;               
  dmac_dmaor_pr_t  pr   : 2; // Priority Mode
  unsigned            : 5;
  bool           ae   : 1; // Address Error Flag
  bool           nmif : 1; // NMI Flag
  bool           dme  : 1; // DMA Master Enable
} dmac_dmaor_t;

typedef union {
  uint32_t full;
  regstruct {
    uint16_t restore;
    uint16_t counter;
  } split;
} dmac_tcrb_t;

typedef volatile void *dmac_sar_t;
typedef volatile void *dmac_dar_t;
typedef uint32_t dmac_tcr_t;

// Channel 0
HW_REG_T(DMAC_SAR0, 0xFE008020, dmac_sar_t);
HW_REG_T(DMAC_DAR0, 0xFE008024, dmac_dar_t);
HW_REG_T(DMAC_TCR0, 0xFE008028, dmac_tcr_t);
HW_REG_T(DMAC_SARB0, 0xFE008120, dmac_sar_t);
HW_REG_T(DMAC_DARB0, 0xFE008124, dmac_dar_t);
HW_REG32(DMAC_TCRB0, 0xFE008128);
#define AS_STRUCT_TYPE_DMAC_TCRB0 dmac_tcrb_t
HW_REG32(DMAC_CHCR0, 0xFE00802C);
#define AS_STRUCT_TYPE_DMAC_CHCR0 dmac_chcr_t

// Channel 1
HW_REG_T(DMAC_SAR1, 0xFE008030, dmac_sar_t);
HW_REG_T(DMAC_DAR1, 0xFE008034, dmac_dar_t);
HW_REG_T(DMAC_TCR1, 0xFE008038, dmac_tcr_t);
HW_REG_T(DMAC_SARB1, 0xFE008130, dmac_sar_t);
HW_REG_T(DMAC_DARB1, 0xFE008134, dmac_dar_t);
HW_REG32(DMAC_TCRB1, 0xFE008138);
#define AS_STRUCT_TYPE_DMAC_TCRB1 dmac_tcrb_t
HW_REG32(DMAC_CHCR1, 0xFE00803C);
#define AS_STRUCT_TYPE_DMAC_CHCR1 dmac_chcr_t

// Common
HW_REG_T(DMAC_DMAOR, 0xFE008060, uint16_t);
#define AS_STRUCT_TYPE_DMAC_DMAOR dmac_dmaor_t

/**
 * Waits for a DMA operation to complete on a channel.
 *   
 * @param channel The channel to wait for.
 * 
 * @return Returns true on successful operation and false for an address error.
*/
inline bool dma_wait(size_t channel) 
{
  volatile uint32_t *chcr_ptr;
  switch (channel) {
    case 0:
      chcr_ptr = DMAC_CHCR0;
      break;
    case 1:
      chcr_ptr = DMAC_CHCR1;
      break;
  }

  // Check if DMA was never running
  dmac_chcr_t chcr;
  AS_STRUCT_TYPE(DMAC_DMAOR) dmaor;

  AS_STRUCT_GET(chcr_ptr, chcr);
  AS_STRUCT_GET(DMAC_DMAOR, dmaor);

  if (unlikely(!chcr.de || !dmaor.dme)) 
  {
    return true;
  }

  while(true)
  {
    
    AS_STRUCT_GET(chcr_ptr, chcr);
    AS_STRUCT_GET(DMAC_DMAOR, dmaor);

    if (unlikely(dmaor.ae)) 
    {
      // Address error
      dmaor.ae = 0;
      AS_STRUCT_SET(DMAC_DMAOR, dmaor);
      return false;
    }

    if (chcr.te)
    {
      // Success
      return true;
    }
  }
}

#ifdef __cplusplus
}
#endif
