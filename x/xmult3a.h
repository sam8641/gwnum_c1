#pragma once
#include <stdio.h>

#ifndef ARCH1
#define ARCH1 CORE
#endif



#if 0
#define xnorm_wpn_preload(ttp , zero , echk, const1 , base2 , sse4); \
/*echk(sse4(xmm15 = xptr(g->u.xmm.XMM_ABSVAL))); \
echk(no##sse4(xmm15 = xptr(g->u.xmm.XMM_BIGVAL))); */



#define xnorm_wpn(ttp, zero, echk, const1, base2, sse4) \
ttp(	rcx = (rbx >> 8) & 255);				/* Fudge flags 1,2 */ \
ttp(	rcx &= 0xF0); \
		xmm8 = xptr(rsi+0*16);		/* Load values1				;P4	;Core2 */ \
ttp(	xmm8 *= xptr(rdx+0*XMM_GMD+rcx));	/* Mul by fudged grp two-to-minus-phi	;1-5	;1-4 */ \
		xmm9 = xptr(rsi+1*16);		/* Load values2 */ \
ttp(	xmm9 *= xptr(rdx+1*XMM_GMD+rcx));	/* Mul by fudged grp two-to-minus-phi	;3-7	;2-5 */ \
ttp(	rax = (rbx >> 8) & 255);				/* Big/lit flags 1-4 */ \
no##ttp(base2(rax = 0));			/* --We should clean up base 2 rational FFT so that this isn't
needed */ \
no##const1(echk(error_check_interleaved(sse4, xmm8, xmm10, xmm9, xmm11, xmm6))); \
const1(mul_by_const_interleaved(ttp, base2, echk, sse4, xmm8, xmm12, xmm10, rax*4, xmm9, xmm13, xmm11, rax*4+16, xmm6)); \
ttp(	rbx &= 0x0F);			/* Fudge flags 3,4 */ \
		xmm0 = xptr(rsi+2*16);		/* Load values3 */ \
ttp(	xmm0 *= xptr(rdx+2*XMM_GMD+rbx*8));	/* Mul by fudged grp two-to-minus-phi	;5-9	;3-6 */ \
		xmm1 = xptr(rsi+3*16);		/* Load values4 */ \
ttp(	xmm1 *= xptr(rdx+3*XMM_GMD+rbx*8));	/* Mul by fudged grp two-to-minus-phi	;7-11	;4-7 */ \
no##const1(echk(error_check_interleaved(sse4, xmm0, xmm2, xmm1, xmm3, xmm6))); \
const1(		mul_by_const_interleaved(ttp, base2, echk, sse4, xmm0, xmm4, xmm2, rax*4+32, xmm1, xmm5, xmm3, rax*4+48, xmm6)); \
const1(		xmm8 += xptr(rbp+0*16));		/* x1 = values + carry */ \
no##const1(	xmm8 += xmm12);			/* x1 = values + carry			;6-9	;5-7 */ \
const1(		xmm9 += xptr(rbp+1*16));		/* x2 = values + carry */ \
no##const1(	xmm9 += xmm13);			/* x2 = values + carry			;8-11	;6-8 */ \
\
no##base2(rounding_interleaved(ttp, base2, const1, sse4, xmm8, xmm12, xmm10, rax*4, xmm9, xmm13, xmm11, rax*4+16)); \
\
const1(		xmm0 += xptr(rbp+2*16));		/* x3 = values + carry */ \
no##const1(	xmm0 += xmm4);			/* x3 = values + carry			;10-13	;7-9 */ \
base2(		xmm10 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4));	/* Load maximum * BIGVAL - BIGVAL */ \
base2(no##const1(xmm4 = xmm10));			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(const1(no##echk(xmm15 = xmm10)));			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(		xmm10 += xmm8);			/* y1 = top bits of x			;12-15	;8-10 */ \
const1(		xmm1 += xptr(rbp+3*16));		/* x4 = values + carry */ \
no##const1(	xmm1 += xmm5);			/* x4 = values + carry			;14-17	;9-11 */ \
\
no##base2(rounding_interleaved(ttp, base2, const1, sse4, xmm0, xmm4, xmm2, rax*4+32, xmm1, xmm5, xmm3, rax*4+48)); \
\
base2(		xmm11 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4+16)); /* Load maximum * BIGVAL - BIGVAL */ \
base2(no##const1(xmm5 = xmm11));			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(const1(no##echk(xmm6 = xmm11)));			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(		xmm11 += xmm9);			/* y2 = top bits of x			;16-19	;10-12 */ \
base2(const1(xmm12 += xmm10));			/* Add in upper mul-by-const1 bits */ \
base2(const1(xmm12 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4)));	/* next carry = shifted y1 */ \
base2(no##const1(xmm12 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4)));	/* next carry = shifted y1 */ \
base2(no##const1(xmm12 *= xmm10));			/* next carry = shifted y1		;17-22	;11-15 */ \
base2(		xmm2 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4+32));/* Load maximum * BIGVAL - BIGVAL */ \
base2(		xmm7 = xmm2);			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(		xmm2 += xmm0);			/* y3 = top bits of x			;18-21	;11-13 */ \
base2(		xmm3 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4+48));/* Load maximum * BIGVAL - BIGVAL */ \
base2(		xmm14 = xmm3);			/* Copy maximum * BIGVAL - BIGVAL */ \
base2(		xmm3 += xmm1);			/* y4 = top bits of x			;20-23	;12-14 */ \
base2(const1(xmm13 += xmm11));			/* Add in upper mul-by-const1 bits */ \
base2(const1(xmm13 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+16)));/* next carry = shifted y2 */ \
base2(no##const1(xmm13 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+16)));/* next carry = shifted y2 */ \
base2(no##const1(xmm13 *= xmm11));			/* next carry = shifted y2		;21-26	;13-17 */ \
base2(const1(echk(xmm10 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4))));	/* z1 = y1 - (maximum*BIGVAL-BIGVAL) */ \
base2(const1(no##echk(xmm10 -= xmm15)));			/* z1 = y1 - (maximum*BIGVAL-BIGVAL) */ \
base2(no##const1(xmm10 -= xmm4));			/* z1 = y1 - (maximum*BIGVAL-BIGVAL)	;22-25	;13-15 */ \
base2(const1(	xmm4 += xmm2));			/* Add in upper mul-by-const1 bits */ \
base2(const1(	xmm4 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+32)));/* next carry = shifted y3 */ \
base2(no##const1(xmm4 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+32)));/* next carry = shifted y3 */ \
base2(no##const1(xmm4 *= xmm2));			/* next carry = shifted y3		;23-28	;14-18 */ \
base2(const1(echk(xmm11 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax*4+16))));/* z2 = y2 - (maximum*BIGVAL-BIGVAL) */ \
base2(const1(no##echk(xmm11 -= xmm6)));			/* z2 = y2 - (maximum*BIGVAL-BIGVAL) */ \
base2(no##const1(xmm11 -= xmm5));			/* z2 = y2 - (maximum*BIGVAL-BIGVAL)	;24-27	;14-16 */ \
base2(const1(	xmm5 += xmm3));			/* Add in upper mul-by-const1 bits */ \
base2(const1(	xmm5 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+48)));/* next carry = shifted y4 */ \
base2(no##const1(xmm5 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+48)));/* next carry = shifted y4 */ \
base2(no##const1(xmm5 *= xmm3));			/* next carry = shifted y4		;25-30	;15-19 */ \
const1(		xptr(rbp+0*16) = xmm12);		/* Save carry1 */ \
base2(		xmm2 -= xmm7);			/* z3 = y3 - (maximum*BIGVAL-BIGVAL)	;26-29	;15-17 */ \
const1(		xptr(rbp+1*16) = xmm13);		/* Save carry2 */ \
base2(		xmm3 -= xmm14);			/* z4 = y4 - (maximum*BIGVAL-BIGVAL)	;28-31	;16-18 */ \
base2(		xmm8 -= xmm10);			/* rounded value = x1 - z1		;30-33	;17-19 */ \
const1(		xptr(rbp+2*16) = xmm4);		/* Save carry3 */ \
base2(		xmm9 -= xmm11);			/* rounded value = x2 - z2		;32-35	;18-20 */ \
const1(		xptr(rbp+3*16) = xmm5);		/* Save carry4 */ \
base2(		xmm0 -= xmm2);			/* rounded value = x3 - z3		;34-37	;19-21 */ \
ttp(		xmm8 *= xptr(rdx+0*XMM_GMD+XMM_GMD/2+rcx)); /* value1 *= fudged grp two-to-phi	;35-40	;20-24 */ \
base2(		xmm1 -= xmm3);			/* rounded value = x4 - z4		;36-39	;20-22 */ \
ttp(		xmm9 *= xptr(rdx+1*XMM_GMD+XMM_GMD/2+rcx)); /* value2 *= fudged grp two-to-phi	;37-42	;21-25 */ \
ttp(		xmm0 *= xptr(rdx+2*XMM_GMD+XMM_GMD/2+rbx*8)); /* value3 *= fudged grp two-to-phi;38-41	;22-26 */ \
zero(		xmm0[1] = xmm0[0] = 0); \
ttp(		xmm1 *= xptr(rdx+3*XMM_GMD+XMM_GMD/2+rbx*8)); /* value4 *= fudged grp two-to-phi;40-43	;23-27 */ \
zero(		xmm1[1] = xmm1[0] = 0); \
ttp(		rbx = u16ptr(rdi+2));		/* Load next 4 big vs. little & fudge flags */ \
		xptr(rsi+0*16) = xmm8;		/* Save new value1 */ \
		xptr(rsi+1*16) = xmm9;		/* Save new value2 */ \
		xptr(rsi+2*16) = xmm0;		/* Save new value3 */ \
		xptr(rsi+3*16) = xmm1;		/* Save new value4 */



#define xnorm_wpn_zpad_preload(ttp, echk, const1, base2, sse4, khi, c1, cm1); \

#define nothing34532 \
no##const1(			xmm15 = xptr(g->u.xmm.XMM_K_LO)); \
const1(				xmm15 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_LO)); \
no##const1(			xmm14 = xptr(g->u.xmm.XMM_MINUS_C)); \
const1(				xmm14 = xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
base2(				xmm13 = xptr(g->u.xmm.XMM_BIGBIGVAL)); \
base2(no##echk(no##sse4(			xmm6 = xptr(g->u.xmm.XMM_BIGVAL)))); \
base2(no##echk(sse4(khi(no##const1(	xmm6 = xptr(g->u.xmm.XMM_K_HI)))))); \
base2(no##echk(sse4(khi(const1(		xmm6 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_HI)))))); \
no##base2(no##sse4(					xmm13 = xptr(g->u.xmm.XMM_BIGVAL))); \
no##base2(sse4(echk(				xmm13 = xptr(g->u.xmm.XMM_ABSVAL)))); \
no##base2(no##echk(khi(no##const1(	xmm6 = xptr(g->u.xmm.XMM_K_HI))))); \
no##base2(no##echk(khi(const1(		xmm6 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_HI))))); \

#define xnorm_wpn_zpad(ttp, echk, const1, base2, sse4, khi, c1, cm1); \
ttp(rax = (rbx >> 8) & 255);			/* Big/little flags 1-4 */ \
ttp(rbx &= 0xF0);		/* Fudge flags 1,2 */ \
\
ttp(xmm2 = xptr(rdx+0*XMM_GMD+rbx)); /* Fudged grp two-to-minus-phi */ \
	xmm0 = xptr(rsi);		/* Load values1 */ \
	xmm1 = xptr(rsi+2*16);	/* Load values2 */ \
ttp(xmm0 *= xmm2);		/* Mul by fudged grp two-to-minus-phi */ \
ttp(xmm1 *= xmm2);		/* Mul by fudged grp two-to-minus-phi */ \
\
ttp(xmm9 = xptr(rdx+1*XMM_GMD+rbx)); /* Fudged grp two-to-minus-phi */ \
	xmm7 = xptr(rsi+16);		/* Load high values1 */ \
	xmm8 = xptr(rsi+3*16);	/* Load high values2 */ \
ttp(xmm7 *= xmm9);		/* Mul by fudged grp two-to-minus-phi */ \
ttp(xmm8 *= xmm9);		/* Mul by fudged grp two-to-minus-phi */ \
\
;					/* Split lower word adding in previous high FFT data */ \
	split_lower_zpad_word_interleaved(echk, base2, sse4, xmm0, xmm3, xmm5, rax*4, xmm7, xmm10, xmm12, rax*4+16); \
\
no##const1(	xmm0 = xptr(g->u.xmm.XMM_K_LO)); \
const1(		xmm0 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_LO)); \
			xmm0 *= xmm5; \
no##const1(	xmm7 = xptr(g->u.xmm.XMM_K_LO)); \
const1(		xmm7 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_LO)); \
			xmm7 *= xmm12; \
\
			xmm0 += xmm4;	/* x1 = values + carry */ \
			xmm7 += xmm11;	/* x2 = values + carry */ \
\
khi(no##const1(xmm4 = xptr(g->u.xmm.XMM_K_HI))); \
khi(const1(xmm4 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_HI))); \
khi(xmm11 = xmm4);\
khi(no##base2(xmm4 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4))); /* Non-base2 rounding needs shifted carry */ \
khi(					xmm5 *= xmm4); \
khi(no##base2(xmm11 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax*4+16))); /* Non-base2 rounding needs shifted carry */ \
khi(					xmm12 *= xmm11); \
\
c1(	xmm1 *= xptr(g->u.xmm.XMM_MINUS_C));	/* Do one mul before split rather than two after split */ \
c1(	xmm8 *= xptr(g->u.xmm.XMM_MINUS_C));	/* Do one mul before split rather than two after split */ \
\
	split_upper_zpad_word_interleaved(echk, base2, sse4, xmm1, xmm4, xmm2, rax*4, xmm8, xmm11, xmm9, rax*4+16); \
\
no##const1(no##c1(no##cm1(xmm2 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
no##const1(no##c1(no##cm1(xmm4 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
const1(			xmm2 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
const1(			xmm4 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
no##const1(no##c1(no##cm1(xmm9 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
no##const1(no##c1(no##cm1(xmm11 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
const1(			xmm9 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
const1(			xmm11 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
\
	xmm0 += xmm2;		/* Add upper FFT word to lower FFT word */ \
khi(xmm4 += xmm5);		/* Add upper FFT word to lower FFT word */ \
	xmm7 += xmm9;		/* Add upper FFT word to lower FFT word */ \
khi(xmm11 += xmm12);		/* Add upper FFT word to lower FFT word */ \
\
	rounding_interleaved(ttp, base2, exec, sse4, xmm0, xmm4, xmm2, rax*4, xmm7, xmm11, xmm9, rax*4+16); \
\
ttp(xmm0 *= xptr(rdx+0*XMM_GMD+XMM_GMD/2+rbx)); /* new value1 *= fudged grp two-to-phi */ \
ttp(xmm7 *= xptr(rdx+1*XMM_GMD+XMM_GMD/2+rbx)); /* new value2 *= fudged grp two-to-phi */ \
\
ttp(rbx = u16ptr(rdi+2));	/* Load next big vs. little & fudge flags */ \
\
	xptr(rsi) = xmm0;		/* Save new value1 */ \
	xptr(rsi+1*16) = xmm7;	/* Save new value2 */ \
\
	xmm1 -= xmm1;		/* new high values = zero */ \
	xptr(rsi+2*16) = xmm1;	/* Zero high value1 */ \
	xptr(rsi+3*16) = xmm1;	/* Zero high value2 */ \

#endif

// From: pass1_normalize, in xmult.h; which is from hgpass1.h

#define inorm(lab, ttp, zero, echk, const1, base2, sse4) \
void CONCAT(lab, ARCH1)(struct gwasm_data *__restrict g, uintptr_t rsi) { \
	/*puts("inorm3-1 " #lab","#ttp","#zero","#echk","#const1","#base2","#sse4);*/ \
	/*printf("inorm rsi: %p %p %p\n", (void*)rsi, g->data_addr, g->scratch_area);*/ \
	uintptr_t rdi, rbp; \
	ttp(uintptr_t rdx); \
	ttp(uintptr_t rbx); \
	uintptr_t loopcount1, loopcount2, loopcount3; \
	unsigned int blk8_counter, carry1; \
	vec2f64 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm7; \
	/*vec2f64 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13;*/ \
	base2(const1(no##echk(vec2f64 xmm6))); \
	uintptr_t saved_rsi = rsi; \
	xnorm_wpn_preload(ttp, zero, echk, const1, base2, sse4); \
echk(vec2f64 xmm6 = g->u.xmm.XMM_MAXERR); \
ttp(rdx = (uintptr_t)g->norm_grp_mults); \
	rbp = (uintptr_t)g->carries; \
	rdi = (uintptr_t)g->norm_ptr1; \
	blk8_counter = 0; \
	loopcount3 = g->count3; \
ttp(rbx = u16ptr(rdi)); \
	do{ /*ilp0:*/ \
		loopcount2 = g->count2; \
		do{ /*ilp1:*/ \
			loopcount1 = g->cache_line_multiplier; \
/*64bit*/	/*no##const1(xmm12 = xptr(rbp+0*16));*/ \
/*64bit*/	/*no##const1(xmm13 = xptr(rbp+1*16));*/ \
/*64bit*/	/*no##const1(xmm4 = xptr(rbp+2*16));*/ \
/*64bit*/	/*no##const1(xmm5 = xptr(rbp+3*16));*/ \
			do{ /*ilp2:*/ \
				/*xprefetchw [rsi+64]*/; \
				/*ttp(printf("inorm3: %lu %lu %lu %lu %lu %x reg: %lx %lx \n", loopcount3, loopcount2, loopcount1, (rbx >> 8) & 255, rbx & 255, blk8_counter, rsi, rdi));*/ \
				xnorm_wpn(ttp, zero, echk, const1, base2, sse4); \
				rsi += 64; \
				rdi += 2; \
				loopcount1--; \
			}while(loopcount1); \
			rsi += g->normblkdst; /* Skip gap in blkdst or clmblkdst */ \
/*64bit*/	/*no##const1(xptr(rbp+0*16) = xmm12);*/ \
/*64bit*/	/*no##const1(xptr(rbp+1*16) = xmm13);*/ \
/*64bit*/	/*no##const1(xptr(rbp+2*16) = xmm4);*/ \
/*64bit*/	/*no##const1(xptr(rbp+3*16) = xmm5);*/ \
			rbp += 64; /* Next set of carries */ \
			blk8_counter = __builtin_addc(blk8_counter, 0x80000000u / 4u, 0, &carry1); \
			if(carry1) { \
				/*puts("carry1");*/ \
				rsi += g->normblkdst8; \
			} \
			loopcount2--; \
		}while(loopcount2); \
		ttp(rdx += XMM_GMD*4); \
		loopcount3--; \
	}while(loopcount3); \
echk(g->u.xmm.XMM_MAXERR = xmm6); \
	\
	if(g->this_block == g->last_pass1_block) { \
		rsi = saved_rsi; \
		xnorm_top_carry; \
	} \
}

#define zpnorm(lab, ttp, echk, const1, base2, sse4, khi, c1, cm1) \
void CONCAT(lab, ARCH1)(struct gwasm_data *__restrict g, uintptr_t rsi) { \
	uintptr_t rbp; \
	ttp(uintptr_t rdx); \
	ttp(uintptr_t rbx); \
	ttp(uintptr_t rdi); \
	uintptr_t loopcount1z, loopcount2z, loopcount3z; \
	unsigned int blk8_counterz, carry1; \
	vec2f64 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm7; \
	xnorm_wpn_zpad_preload(ttp, echk, const1, base2, sse4, khi, c1, cm1); \
echk(vec2f64 xmm6 = g->u.xmm.XMM_MAXERR); \
ttp(rdx = (uintptr_t)g->norm_grp_mults); \
	rbp = (uintptr_t)g->carries; \
ttp(rdi = (uintptr_t)g->norm_ptr1); \
	blk8_counterz = 0; \
	loopcount3z = g->count3; \
ttp(rbx = u16ptr(rdi)); \
	do{ /*ilp0:*/ \
		loopcount2z = g->count2; \
		do{ /*ilp1:*/ \
			loopcount1z = g->cache_line_multiplier; \
/*64bit*/	/*xmm4 = xptr(rbp+0*16);*/ \
/*64bit*/	/*xmm11 = xptr(rbp+1*16);*/ \
/*64bit*/	/*xmm3 = xptr(rbp+2*16);*/ \
/*64bit*/	/*xmm10 = xptr(rbp+3*16);*/ \
			do{ /*ilp2:*/ \
				/*ttp(printf("znorm3: %lu %lu %lu %lu %lu\n", loopcount3z, loopcount2z, loopcount1z, (rbx >> 8) & 255, rbx & 255));*/ \
				/*xprefetchw [rsi+64]*/; \
				xnorm_wpn_zpad(ttp, echk, const1, base2, sse4, khi, c1, cm1); \
				rsi += 64; \
				ttp(rdi += 2); \
				loopcount1z--; \
			}while(loopcount1z); \
			rsi += g->normblkdst; \
/*64bit*/	/*xptr(rbp+0*16) = xmm4;*/ \
/*64bit*/	/*xptr(rbp+1*16) = xmm11;*/ \
/*64bit*/	/*xptr(rbp+2*16) = xmm3;*/ \
/*64bit*/	/*xptr(rbp+3*16) = xmm10;*/ \
			rbp += 64; \
			blk8_counterz = __builtin_addc(blk8_counterz, 0x80000000u / 4u, 0, &carry1); \
			if(carry1) { \
				rsi += g->normblkdst8; \
			} \
			loopcount2z--; \
		}while(loopcount2z); \
		ttp(rdx += XMM_GMD*4); \
		loopcount3z--; \
	}while(loopcount3z); \
echk(g->u.xmm.XMM_MAXERR = xmm6); \
}
