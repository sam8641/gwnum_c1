#include <stdlib.h>
#include <ctype.h>

#include "../gwnum.h"
#include "../gwcommon.h"
#include "../unravel.h"
#include "../gwtables.h"
#include "../xarch.h"
#include "../xbasics.h"
#include "../xmult.h"
#include "hg.h"
#include "hgonepass.h"
#include <stdio.h>

volatile int test123;
#if 0
int testv00,testv01,testv02,testv03,testv04,testv05,testv06,testv07,testv08,testv09;
int testv10,testv11,testv12,testv13,testv14,testv15,testv16,testv17,testv18,testv19;
int testv20,testv21,testv22,testv23,testv24,testv25,testv26,testv27,testv28,testv29;
int testv30,testv31,testv32,testv33,testv34,testv35,testv36,testv37,testv38,testv39;
#endif

//xonepass contains code that does the following:
// rsi = (uintptr_t)g->DESTARG
// rbx = (uintptr_t)g->DIST_TO_FFTSRCARG

#if 0
// hgonepass.mac
static void xmiddle_123(struct gwasm_data *__restrict g) {
	uintptr_t rax, rbx, rsi, rdi, rbp;
	vec2f64 xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
	rbx = (uintptr_t)g->DIST_TO_FFTSRCARG;
	rdi = (uintptr_t)g->DESTARG;
	rsi = (uintptr_t)g->sincos1;
	if(g->ffttype < 2){
		s2cl_eight_reals_fft_2_final(rsi, 2*64, 64);
		rax = g->count1;
		rdi += XMM_SCD;
		do{
			s2cl_four_complex_fft_final(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}else if(g->ffttype == 2){
		s2cl_eight_reals_with_square_2(rsi, 2*64, 64);
		rax = g->count1;
		do{
			s2cl_four_complex_with_square(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}else{
		rbp = (uintptr_t)g->DIST_TO_MULSRCARG;
		s2cl_eight_reals_with_mult_2(rsi, 2*64, 64);
		rax = g->count1;
		do{
			s2cl_four_complex_with_mult(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}

	rbp = g->DIST_TO_MULSRCARG;
	s2cl_eight_reals_with_mulf_2(rsi, 2*64, 64);
	rax = g->count1;
	rdi += XMM_SCD;
	do{
		s2cl_four_complex_with_mulf(rsi, 2*64, 64);
		rdi += XMM_SCD;
		rax--;
	}while(rax);
	//rsi = (uintptr_t)g->DESTARG;
}
// hgonepass.mac
static void xmiddle_123p(struct gwasm_data *__restrict g) {
	uintptr_t rax, rbx, rsi, rdi, rbp;
	vec2f64 xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
	rbx = (uintptr_t)g->DIST_TO_FFTSRCARG;
	rdi = (uintptr_t)g->DESTARG;
	rsi = (uintptr_t)g->sincos1;
	rax = g->count1;
	if(g->ffttype < 2){
		do{
			s2cl_four_complex_fft_final(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}else if(g->ffttype == 2){
		do{
			s2cl_four_complex_with_square(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}else{
		rbp = (uintptr_t)g->DIST_TO_MULSRCARG;
		do{
			s2cl_four_complex_with_mult(rsi, 2*64, 64);
			rdi += XMM_SCD;
			rax--;
		}while(rax);
	}
	rdi = (uintptr_t)g->sincos1;
	rbp = g->DIST_TO_MULSRCARG;
	rax = g->count1;
	do{
		s2cl_four_complex_with_mulf(rsi, 2*64, 64);
		rdi += XMM_SCD;
		rax--;
	}while(rax);
	//rsi = (uintptr_t)g->DESTARG;
}
// hgonepass.mac
static void xmiddle_4(struct gwasm_data *__restrict g) {
	uintptr_t rax, rbx, rsi, rdi, rbp;
	vec2f64 xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
	rsi = (uintptr_t)g->DESTARG;
	rbx = (uintptr_t)g->DIST_TO_FFTSRCARG;
	rdi = (uintptr_t)g->sincos1;
	rbp = g->DIST_TO_MULSRCARG;
	s2cl_eight_reals_with_mulf_2(rsi, 2*64, 64);
	rax = g->count1;
	rdi += XMM_SCD;
	do{
		s2cl_four_complex_with_mulf(rsi, 2*64, 64);
		rdi += XMM_SCD;
		rax--;
	}while(rax);
	//rsi = (uintptr_t)g->DESTARG;
}
// hgonepass.mac
static void xmiddle_4p(struct gwasm_data *__restrict g) {
	uintptr_t rax, rbx, rsi, rdi, rbp;
	vec2f64 xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7,xmm8,xmm9;
	rsi = (uintptr_t)g->DESTARG;
	rbx = (uintptr_t)g->DIST_TO_FFTSRCARG;
	rdi = (uintptr_t)g->sincos1;
	rbp = g->DIST_TO_MULSRCARG;
	rax = g->count1;
	do{
		s2cl_four_complex_with_mulf(rsi, 2*64, 64);
		rdi += XMM_SCD;
		rax--;
	}while(rax);
	//rsi = (uintptr_t)g->DESTARG;
}

#endif


//#define ne0
//#define ne1 _ac
//#define ne(A)

//#define xonepass(fftname, negacyclic) \
//	void xfft_hg_##fftname##_op##negacyclic##_BLEND \
//	{} \
//	\

// xonepass is found in ghonepass.h2

//             func. macro.
// negacyclic:   _ac    p

#define INITVAR1 \
	uintptr_t rbx,rsi,rdi; \
	vec2f64 xmm0,xmm1,xmm2,xmm3,xmm4,xmm5,xmm6,xmm7; \
	rsi = (uintptr_t)g->DESTARG; \
	rbx = (uintptr_t)g->DIST_TO_FFTSRCARG;

#define N452(A) #A
#define N_TO_STRING(A) N452(A)
#define P1 static char Z1=0; if(Z1 == 0) \
	{Z1=1; puts("hg_blend.c " N_TO_STRING(__LINE__));}

#if 1
void xfft_hg_32_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft32(0);}
void xfft_hg_48_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft48(0);}
void xfft_hg_64_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft64(0);}
void xfft_hg_80_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft80(0);}
void xfft_hg_96_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft96(0);}
void xfft_hg_112_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft112(0);}
void xfft_hg_128_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft128(0);}
void xfft_hg_160_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft160(0);}
void xfft_hg_192_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft192(0);}
void xfft_hg_224_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft224(0);}
void xfft_hg_256_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft256(0);}
void xfft_hg_320_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft320(0);}
void xfft_hg_384_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft384(0);}
void xfft_hg_448_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft448(0);}
void xfft_hg_512_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft512(0);}
void xfft_hg_640_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft640(0);}
void xfft_hg_768_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft768(0);}
void xfft_hg_896_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft896(0);}
void xfft_hg_1024_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1024(0);}
void xfft_hg_1280_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1280(0);}
void xfft_hg_1536_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1536(0);}
void xfft_hg_1792_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1792(0);}
void xfft_hg_2048_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft2048(0);}
void xfft_hg_2560_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft2560(0);}
void xfft_hg_3072_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft3072(0);}
void xfft_hg_3584_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft3584(0);}
void xfft_hg_4096_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft4096(0);}
void xfft_hg_5120_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft5120(0);}
void xfft_hg_6144_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft6144(0);}
//void xfft_hg_7168_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft7168(0);}
void xfft_hg_8192_op_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft8192(0);}
#endif
#if 1
void xfft_hg_32_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft32p(0);}
void xfft_hg_48_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft48p(0);}
void xfft_hg_64_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft64p(0);}
void xfft_hg_96_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft96p(0);}
void xfft_hg_128_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft128p(0);}
void xfft_hg_192_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft192p(0);}
void xfft_hg_256_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft256p(0);}
void xfft_hg_384_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft384p(0);}
void xfft_hg_512_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft512p(0);}
void xfft_hg_768_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft768p(0);}
void xfft_hg_1024_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1024p(0);}
void xfft_hg_1536_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft1536p(0);}
void xfft_hg_2048_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft2048p(0);}
void xfft_hg_3072_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft3072p(0);}
void xfft_hg_4096_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft4096p(0);}
void xfft_hg_6144_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft6144p(0);}
//void xfft_hg_8192_op_ac_BLEND(struct gwasm_data *__restrict g) {INITVAR1; xfft8192p(0);}
#endif




// xfft_hg_32_BLEND

//
	//
//
