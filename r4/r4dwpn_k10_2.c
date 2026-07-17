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


#if 1
r4dwpn_pass1sc896(xfft_r4dwpn_1120K_1280_4_K10, xpass2_r4_1280_levels, 1280, 4);
r4dwpn_pass1sc384(xfft_r4dwpn_1152K_3072_4_K10, xpass2_r4_3072_levels, 3072, 4);
r4dwpn_pass1sc320(xfft_r4dwpn_1200K_3840_4_K10, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc320(xfft_r4dwpn_1280K_12_4_K10, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc896(xfft_r4dwpn_1344K_1536_4_K10, xpass2_r4_1536_levels, 1536, 4);
r4dwpn_pass1sc384(xfft_r4dwpn_1440K_3840_4_K10, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc384(xfft_r4dwpn_1536K_12_4_K10, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc320(xfft_r4dwpn_1600K_5120_4_K10, xpass2_r4_5120_levels, 5120, 4);
r4dwpn_pass1sc448(xfft_r4dwpn_1680K_3840_4_K10, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc384(xfft_r4dwpn_1728K_4608_4_K10, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc448(xfft_r4dwpn_1792K_12_4_K10, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc640(xfft_r4dwpn_1920K_3072_4_K10, xpass2_r4_3072_levels, 3072, 4);
r4dwpn_pass1sc512(xfft_r4dwpn_2M_12_4_K10, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc448(xfft_r4dwpn_2240K_5120_4_K10, xpass2_r4_5120_levels, 5120, 4);
r4dwpn_pass1sc768(xfft_r4dwpn_2304K_3072_4_K10, xpass2_r4_3072_levels, 3072, 4);
r4dwpn_pass1sc640(xfft_r4dwpn_2400K_3840_4_K10, xpass2_r4_3840_levels, 3840, 4);
r4dwpn_pass1sc640(xfft_r4dwpn_2560K_12_4_K10, xpass2_r4_12_levels, 12, 4);
r4dwpn_pass1sc896(xfft_r4dwpn_2688K_3072_4_K10, xpass2_r4_3072_levels, 3072, 4);
r4dwpn_pass1sc448(xfft_r4dwpn_2800K_6400_4_K10, xpass2_r4_6400_levels, 6400, 4);
r4dwpn_pass1sc640(xfft_r4dwpn_2880K_4608_4_K10, xpass2_r4_4608_levels, 4608, 4);
r4dwpn_pass1sc768(xfft_r4dwpn_3M_12_4_K10, xpass2_r4_12_levels, 12, 4);
#endif
