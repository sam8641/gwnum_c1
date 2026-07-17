#include <stdlib.h>
#include <ctype.h>

#include "../gwnum.h"
#include "../gwcommon.h"
#include "../unravel.h"
#include "../gwtables.h"
#include "../xarch.h"
#include "../xbasics.h"
#include "../xmult.h"
#include "../gwnum_func.h"

#include "r4.h"
#include "r4dwpnpass1sc.h"

	//
//
//volatile short test12342;

void xpass2_r4_8_levels(struct gwasm_data *__restrict g);
void xpass2_r4_768_levels(struct gwasm_data *__restrict g);
void xpass2_r4_10_levels(struct gwasm_data *__restrict g);
void xpass2_r4_1280_levels(struct gwasm_data *__restrict g);
void xpass2_r4_1536_levels(struct gwasm_data *__restrict g);
void xpass2_r4_11_levels(struct gwasm_data *__restrict g);
void xpass2_r4_2304_levels(struct gwasm_data *__restrict g);
void xpass2_r4_2560_levels(struct gwasm_data *__restrict g);
void xpass2_r4_3072_levels(struct gwasm_data *__restrict g);
void xpass2_r4_3840_levels(struct gwasm_data *__restrict g);
void xpass2_r4_12_levels(struct gwasm_data *__restrict g);
void xpass2_r4_4608_levels(struct gwasm_data *__restrict g);
void xpass2_r4_5120_levels(struct gwasm_data *__restrict g);
void xpass2_r4_6144_levels(struct gwasm_data *__restrict g);
void xpass2_r4_6400_levels(struct gwasm_data *__restrict g);
void xpass2_r4_7680_levels(struct gwasm_data *__restrict g);
void xpass2_r4_13_levels(struct gwasm_data *__restrict g);
void xpass2_r4_9216_levels(struct gwasm_data *__restrict g);
void xpass2_r4_10240_levels(struct gwasm_data *__restrict g);
void xpass2_r4_12288_levels(struct gwasm_data *__restrict g);
void xpass2_r4_12800_levels(struct gwasm_data *__restrict g);
void xpass2_r4_15360_levels(struct gwasm_data *__restrict g);
void xpass2_r4_14_levels(struct gwasm_data *__restrict g);
void xpass2_r4_20480_levels(struct gwasm_data *__restrict g);
void xpass2_r4_25600_levels(struct gwasm_data *__restrict g);

void xgw_carries_wpn(struct gwasm_data *__restrict g);

//r4dwpn_pass1sc128(xfft_r4dwpn_8K_np_8_4_P4, xpass2_r4_8_levels, 8, 4);

//r4dwpn_pass1sc128(xfft_r4dwpn_32K_8_4_P4, xpass2_r4_8_levels, 8, 4);


#if 1
r4dwpn_pass1sc128ac(xfft_r4dwpn_32K_ac_8_4_P4, xpass2_r4_8_levels, 8, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_64K_ac_8_4_P4, xpass2_r4_8_levels, 8, 4);
r4dwpn_pass1sc128ac(xfft_r4dwpn_128K_ac_10_4_P4, xpass2_r4_10_levels, 10, 4);
r4dwpn_pass1sc128ac(xfft_r4dwpn_160K_ac_1280_4_P4, xpass2_r4_1280_levels, 1280, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_256K_ac_10_4_P4, xpass2_r4_10_levels, 10, 4);
r4dwpn_pass1sc384ac(xfft_r4dwpn_288K_ac_768_4_P4, xpass2_r4_768_levels, 768, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_320K_ac_1280_4_P4, xpass2_r4_1280_levels, 1280, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_512K_ac_11_4_P4, xpass2_r4_11_levels, 11, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_576K_ac_2304_4_P4, xpass2_r4_2304_levels, 2304, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_640K_ac_2560_4_P4, xpass2_r4_2560_levels, 2560, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_768K_ac_3072_4_P4, xpass2_r4_3072_levels, 3072, 4);
r4dwpn_pass1sc640ac(xfft_r4dwpn_800K_ac_1280_4_P4, xpass2_r4_1280_levels, 1280, 4);
r4dwpn_pass1sc384ac(xfft_r4dwpn_864K_ac_2304_4_P4, xpass2_r4_2304_levels, 2304, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_960K_ac_3840_4_P4, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1M_ac_12_4_P4, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1152K_ac_4608_4_P4, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1280K_ac_5120_4_P4, xpass2_r4_5120_levels, 5120, 4);
r4dwpn_pass1sc384ac(xfft_r4dwpn_1440K_ac_3840_4_P4, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1536K_ac_6144_4_P4, xpass2_r4_6144_levels, 6144, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1600K_ac_6400_4_P4, xpass2_r4_6400_levels, 6400, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_1728K_ac_2304_4_P4, xpass2_r4_2304_levels, 2304, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_1920K_ac_7680_4_P4, xpass2_r4_7680_levels, 7680, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_2M_ac_13_4_P4, xpass2_r4_13_levels, 13, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_2304K_ac_9216_4_P4, xpass2_r4_9216_levels, 9216, 4);
r4dwpn_pass1sc384ac(xfft_r4dwpn_2400K_ac_6400_4_P4, xpass2_r4_6400_levels, 6400, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_2560K_ac_10240_4_P4, xpass2_r4_10240_levels, 10240, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_2880K_ac_3840_4_P4, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_3M_ac_12_4_P4, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc256ac(xfft_r4dwpn_3200K_ac_12800_4_P4, xpass2_r4_12800_levels, 12800, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_3456K_ac_4608_4_P4, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_3840K_ac_5120_4_P4, xpass2_r4_5120_levels, 5120, 4);
r4dwpn_pass1sc1024ac(xfft_r4dwpn_4M_ac_12_4_P4, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc1024ac(xfft_r4dwpn_4608K_ac_4608_4_P4, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_4800K_ac_6400_4_P4, xpass2_r4_6400_levels, 6400, 4);
r4dwpn_pass1sc1280ac(xfft_r4dwpn_5M_ac_12_4_P4, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc1280ac(xfft_r4dwpn_5760K_ac_4608_4_P4, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc768ac(xfft_r4dwpn_6M_ac_13_4_P4, xpass2_r4_13_levels, 13, 4);
#endif

