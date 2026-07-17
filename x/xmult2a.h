#pragma once

// double define to allow it's inputs to expand correctly.
#define CONCAT2(A, B) A##B
#define CONCAT(A, B) CONCAT2(A, B)

#ifndef ARCH1
#define ARCH1 CORE
#endif

#if 0
#if 1
#define xnorm_2d_setup_ttpexec {	/* Precompute FUDGE * col multipliers */ \
	/*double ftmp;*/ \
	vec2f64 t; \
	rbp = rdi + 256;		/* Create pointer for more one-byte offsets below */ \
	xmm0 = xptr(rbx);		/* Load col two-to-minus-phi */ \
	vec2f64 bb0; bb0 = xmm0 * xptr2(g->u.xmm.XMM_TTMP_FUDGE,24*8); \
	xmm1 = xptr(rbx+16);		/* Load col two-to-phi */ \
	vec2f64 bb1; bb1 = xmm1 * xptr2(g->u.xmm.XMM_TTP_FUDGE,24*8); \
	xptr(rdi-128       ) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128    +16) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128    +32) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128    +48) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	t[0] = bb0[0]; t[1] = xmm0[0]; \
	xptr(rdi-128+64    ) = t;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64 +16) = t;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64 +32) = t;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64 +48) = t;	/* Save ttmp * 1.0,B */ \
	t[0] = xmm0[0]; t[1] = bb0[0]; \
	xptr(rdi-128+128   ) = t;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+16) = t;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+32) = t;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+48) = t;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+192   ) = bb0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+16) = bb0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+32) = bb0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+48) = bb0;	/* Save ttmp * B,B */ \
	xptr(rbp-128       ) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128    +16) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128    +32) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128    +48) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	t[0] = bb1[0]; t[1] = xmm1[0]; \
	xptr(rbp-128+64    ) = t;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64 +16) = t;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64 +32) = t;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64 +48) = t;	/* Save ttp * 1.0,1/B */ \
	t[0] = xmm1[0]; t[1] = bb1[0]; \
	xptr(rbp-128+128   ) = t;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+16) = t;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+32) = t;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+48) = t;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+192   ) = bb1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+16) = bb1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+32) = bb1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+48) = bb1;	/* Save ttp * 1/B,1/B */ \
}
#else
#define xnorm_2d_setup_ttpexec {	/* Precompute FUDGE * col multipliers */ \
	/*double ftmp;*/ \
	rbp = rdi + 256;		/* Create pointer for more one-byte offsets below */ \
	xmm0 = xptr(rbx);		/* Load col two-to-minus-phi */ \
	xmm1 = xptr(rbx+16);		/* Load col two-to-phi */ \
	xptr(rdi-128      ) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128   +16) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128   +32) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rdi-128   +48) = xmm0;	/* Save ttmp * 1.0,1.0 */ \
	xptr(rbp-128      ) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128   +16) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128   +32) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xptr(rbp-128   +48) = xmm1;	/* Save ttp * 1.0,1.0 */ \
	xmm0[0] *= f64ptr2(g->u.xmm.XMM_TTMP_FUDGE,64);/* Compute ttmp * 1.0,B */ \
	xmm1[0] *= f64ptr2(g->u.xmm.XMM_TTP_FUDGE,64);/* Compute ttp * 1.0,1/B */ \
	xptr(rdi-128+64   ) = xmm0;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64+16) = xmm0;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64+32) = xmm0;	/* Save ttmp * 1.0,B */ \
	xptr(rdi-128+64+48) = xmm0;	/* Save ttmp * 1.0,B */ \
	/*ftmp = xmm0[0]; xmm0[0] = xmm0[1]; xmm0[1] = ftmp;*/	/* swizzle */ \
	xptr(rbp-128+64   ) = xmm1;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64+16) = xmm1;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64+32) = xmm1;	/* Save ttp * 1.0,1/B */ \
	xptr(rbp-128+64+48) = xmm1;	/* Save ttp * 1.0,1/B */ \
	xmm0 = __builtin_shufflevector(xmm0, xmm0, 1,0); \
	xmm1 = __builtin_shufflevector(xmm1, xmm1, 1,0); \
	/*ftmp = xmm1[0]; xmm1[0] = xmm1[1]; xmm1[1] = ftmp;*/	/* swizzle */ \
	xptr(rdi-128+128   ) = xmm0;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+16) = xmm0;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+32) = xmm0;	/* Save ttmp * B,1.0 */ \
	xptr(rdi-128+128+48) = xmm0;	/* Save ttmp * B,1.0 */ \
	xptr(rbp-128+128   ) = xmm1;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+16) = xmm1;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+32) = xmm1;	/* Save ttp * 1/B,1.0 */ \
	xptr(rbp-128+128+48) = xmm1;	/* Save ttp * 1/B,1.0 */ \
	xmm0[0] *= f64ptr2(g->u.xmm.XMM_TTMP_FUDGE,64); \
	xmm1[0] *= f64ptr2(g->u.xmm.XMM_TTP_FUDGE,64); \
	xptr(rdi-128+192   ) = xmm0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+16) = xmm0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+32) = xmm0;	/* Save ttmp * B,B */ \
	xptr(rdi-128+192+48) = xmm0;	/* Save ttmp * B,B */ \
	xptr(rbp-128+192   ) = xmm1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+16) = xmm1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+32) = xmm1;	/* Save ttp * 1/B,1/B */ \
	xptr(rbp-128+192+48) = xmm1;	/* Save ttp * 1/B,1/B */ \
}
#endif

#define xnorm_2d_setup_ttpnoexec		/* Precompute FUDGE * col multipliers */ \
	xmm0 = xptr(rbx);		/* Load col two-to-minus-phi */ \
	xptr(rdi-128) = xmm0;		/* Save ttmp * 1.0,1.0 */ \
	xmm1 = xptr(rbx+16);		/* Load col two-to-phi */ \
	xptr(rdi+256-128) = xmm1;	/* Save ttp * 1.0,1.0 */
#define xnorm_2d_setup(ttp) xnorm_2d_setup_ttp##ttp

#define xnorm_2d(ttp, zero, echk, const1, base2, sse4) \
ttp(xmm10 = xptr(rdx+0*32));	/* grp two-to-minus-phi			;P4	;Core2 */ \
ttp(xmm10 *= xptr(rbx+rax));	/* Mul by col two-to-minus-phi		;1-6	;1-5 */ \
no##ttp(xmm10 = xptr(rbx));		/* two-to-minus-phi */ \
	xmm8 = xptr(rsi+0*16);	/* Load values1 */ \
	xmm7 += xmm8;		/* sumout += values1			;2-5	;1-3 */ \
ttp(xmm11 = xptr(rdx+1*32));	/* grp two-to-minus-phi */ \
ttp(xmm11 *= xptr(rbx+rcx));	/* Mul by col two-to-minus-phi		;3-8	;2-6 */ \
no##ttp(xmm11 = xptr(rbx));		/* two-to-minus-phi */ \
ttp(xmm2 = xptr(rdx+2*32));	/* grp two-to-minus-phi */ \
ttp(xmm2 *= xptr(rbx+r8));		/* Mul by col two-to-minus-phi		;5-10	;3-7 */ \
no##ttp(xmm2 = xptr(rbx));		/* two-to-minus-phi */ \
	xmm9 = xptr(rsi+1*16);	/* Load values2 */ \
	xmm7 += xmm9;		/* sumout += values2			;6-9	;4-6 */ \
ttp(xmm3 = xptr(rdx+3*32));	/* grp two-to-minus-phi */ \
ttp(xmm3 *= xptr(rbx+r9));		/* Mul by col two-to-minus-phi		;7-12	;4-8 */ \
no##ttp(xmm3 = xptr(rbx));		/* two-to-minus-phi */ \
	xmm8 *= xmm10;		/* Mul by fudged col two-to-minus-phi	;9-14	;6-10 */ \
	xmm1 = xptr(rsi+3*16);	/* Load values4 */ \
	xmm7 += xmm1;		/* sumout += values4			;10-13	;7-9 */ \
	xmm9 *= xmm11;		/* Mul by fudged col two-to-minus-phi	;11-16	;7-11 */ \
no##const1(echk(error_check_interleaved(sse4, xmm8, xmm12, xmm9, xmm13, xmm6))); \
const1(mul_by_const_interleaved(ttp, base2, echk, sse4, xmm8, xmm12, xmm10, rax, xmm9, xmm13, xmm11, rcx, xmm6)); \
	xmm0 = xptr(rsi+2*16);	/* Load values3 */ \
	xmm7 += xmm0;		/* sumout += values3			;14-17	;10-12 */ \
	xmm0 *= xmm2;		/* Mul by fudged col two-to-minus-phi	;13-18	;8-12 */ \
	xmm1 *= xmm3;		/* Mul by fudged col two-to-minus-phi	;15-20	;9-13 */ \
no##const1(echk(error_check_interleaved(sse4, xmm0, xmm4, xmm1, xmm5, xmm6))); \
const1(mul_by_const_interleaved(ttp, base2, echk, sse4, xmm0, xmm4, xmm2, r8, xmm1, xmm5, xmm3, r9, xmm6)); \
	xmm8 += xptr(rbp+0*16);	/* x1 = values + carry			;16-19	;11-13 */ \
	xmm9 += xptr(rbp+1*16);	/* x2 = values + carry			;18-21	;12-14 */ \
\
no##base2(rounding_interleaved(ttp, base2, const1, sse4, xmm8, xmm12, xmm10, rax, xmm9, xmm13, xmm11, rcx)); \
\
ttp(xmm14 = xptr(rbx+256+rax));	/* col two-to-phi */ \
ttp(xmm14 *= xptr(rdx+0*32+16));	/* two-to-phi = col * grp		;19-24	;12-16 */ \
	xmm0 += xptr(rbp+2*16);	/* x3 = values + carry			;20-23	;13-15 */ \
ttp(xmm15 = xptr(rbx+256+rcx));	/* col two-to-phi */ \
ttp(xmm15 *= xptr(rdx+1*32+16));	/* two-to-phi = col * grp		;21-26	;13-17 */ \
base2(xmm10 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax));/* Load maximum * BIGVAL - BIGVAL */ \
base2(xmm10 += xmm8);		/* y1 = top bits of x			;22-25	;14-16 */ \
	xmm1 += xptr(rbp+3*16);	/* x4 = values + carry			;24-27	;15-17 */ \
\
no##base2(rounding_interleaved(ttp, base2, const1, sse4, xmm0, xmm4, xmm2, r8, xmm1, xmm5, xmm3, r9)); \
\
base2(xmm11 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rcx));/* Load maximum * BIGVAL - BIGVAL */ \
base2(xmm11 += xmm9);		/* y2 = top bits of x			;26-29	;16-18 */ \
base2( const1( xmm12 += xmm10));		/* Add in upper mul-by-const1 bits */ \
base2( const1( xmm12 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax)));/* next carry = shifted y1 */ \
base2( no##const1( xmm12 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax)));/* next carry = shifted y1 */ \
base2( no##const1( xmm12 *= xmm10));	/* next carry = shifted y1		;27-32	;17-21 */ \
base2(xmm2 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,r8));/* Load maximum * BIGVAL - BIGVAL */ \
base2(xmm2 += xmm0);		/* y3 = top bits of x			;28-31	;17-19 */ \
base2(xmm3 = xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,r9));/* Load maximum * BIGVAL - BIGVAL */ \
base2(xmm3 += xmm1);		/* y4 = top bits of x			;30-33	;18-20 */ \
base2( const1( xmm13 += xmm11));		/* Add in upper mul-by-const1 bits */ \
base2( const1( xmm13 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rcx)));/* next carry = shifted y2 */ \
base2( no##const1( xmm13 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rcx)));/* next carry = shifted y2 */ \
base2( no##const1( xmm13 *= xmm11));	/* next carry = shifted y2		;31-36	;19-23 */ \
base2(xmm10 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rax));/* z1 = y1 - (maximum*BIGVAL-BIGVAL) ;32-35	;19-22 */ \
ttp(rax = u8ptr(rdi+4));	/* Load next big vs. little flags */ \
base2( const1( xmm4 += xmm2));		/* Add in upper mul-by-const1 bits */ \
base2( const1( xmm4 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,r8)));/* next carry = shifted y3 */ \
base2( no##const1( xmm4 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,r8)));/* next carry = shifted y3 */ \
base2( no##const1( xmm4 *= xmm2));		/* next carry = shifted y3		;33-38	;20-24 */ \
base2(xmm11 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,rcx));/* z2 = y2 - (maximum*BIGVAL-BIGVAL) ;34-37	;20-22 */ \
ttp(rcx = u8ptr(rdi+5));	/* Load next big vs. little flags */ \
base2( const1( xmm5 += xmm3));		/* Add in upper mul-by-const1 bits */ \
base2( const1( xmm5 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,r9)));/* next carry = shifted y4 */ \
base2( no##const1( xmm5 = xptr2(g->u.xmm.XMM_LIMIT_INVERSE,r9)));/* next carry = shifted y4 */ \
base2( no##const1( xmm5 *= xmm3));		/* next carry = shifted y4		;35-40	;21-25 */ \
	xptr(rbp+0*16) = xmm12;	/* Save carry1 */ \
base2(xmm2 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,r8));/* z3 = y3 - (maximum*BIGVAL-BIGVAL)	;36-39	;21-23 */ \
ttp(xmm12 = xptr(rbx+256+r8));	/* col two-to-phi */ \
ttp(xmm12 *= xptr(rdx+2*32+16));	/* two-to-phi = col * grp		;37-42	;22-26 */ \
ttp(r8 = u8ptr(rdi+6));	/* Load next big vs. little flags */ \
	xptr(rbp+1*16) = xmm13;	/* Save carry2 */ \
base2(xmm3 -= xptr2(g->u.xmm.XMM_LIMIT_BIGMAX,r9));/* z4 = y4 - (maximum*BIGVAL-BIGVAL)	;38-41	;22-24 */ \
ttp(xmm13 = xptr(rbx+256+r9));	/* col two-to-phi */ \
ttp(xmm13 *= xptr(rdx+3*32+16));	/* two-to-phi = col * grp		;39-43	;23-27 */ \
ttp(r9 = u8ptr(rdi+7));	/* Load next big vs. little flags */ \
base2(xmm8 -= xmm10);		/* rounded value = x1 - z1		;40-43	;23-25 */ \
	xptr(rbp+2*16) = xmm4;	/* Save carry3 */ \
base2(xmm9 -= xmm11);		/* rounded value = x2 - z2		;42-45	;24-26 */ \
	xptr(rbp+3*16) = xmm5;	/* Save carry4 */ \
base2(xmm0 -= xmm2);		/* rounded value = x3 - z3		;44-47	;25-27 */ \
ttp(xmm8 *= xmm14);		/* value1 = rounded value * two-to-phi	;45-50	;26-30 */ \
base2(xmm1 -= xmm3);		/* rounded value = x4 - z4		;46-49	;26-28 */ \
ttp(xmm9 *= xmm15);		/* value2 = rounded value * two-to-phi	;47-52	;27-31 */ \
ttp(xmm0 *= xmm12);		/* value3 = rounded value * two-to-phi	;49-54	;28-32 */ \
zero(xmm0[1] = xmm0[0] = 0); \
ttp(xmm1 *= xmm13);		/* value4 = rounded value * two-to-phi	;51-56	;29-33 */ \
zero(xmm1[1] = xmm1[0] = 0); \
	xptr(rsi+0*16) = xmm8;	/* Save new value1 */ \
	xptr(rsi+1*16) = xmm9;	/* Save new value2 */ \
	xptr(rsi+2*16) = xmm0;	/* Save new value3 */ \
	xptr(rsi+3*16) = xmm1;	/* Save new value4 */ \


#define xnorm_2d_zpad(ttp, echk, const1, base2, sse4, khi, c1, cm1) \
	xmm2 = xptr(rbx+rax);	/* col two-to-minus-phi */ \
ttp(xmm2 *= xptr(rdx+0*32));	/* Mul by grp two-to-minus-phi */ \
	xmm0 = xptr(rsi);		/* Load values1 */ \
	xmm7 += xmm0;		/* sumout += values1 */ \
	xmm1 = xptr(rsi+2*16);	/* Load values2 */ \
	xmm7 += xmm1;		/* sumout += values2 */ \
	xmm0 *= xmm2;		/* Mul by fudged col two-to-minus-phi */ \
	xmm1 *= xmm2;		/* Mul by fudged col two-to-minus-phi */ \
\
	split_lower_zpad_word(echk, base2, sse4, xmm0, xmm3, xmm5, rax); \
\
no##const1(	xmm0 = xptr(g->u.xmm.XMM_K_LO)); \
const1(		xmm0 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_LO)); \
		xmm0 *= xmm5; \
\
		xmm0 += xmm4;	/* x1 = values + carry */ \
\
khi( no##const1(	xmm4 = xptr(g->u.xmm.XMM_K_HI))); \
khi( const1(	xmm4 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_HI))); \
khi( no##base2(xmm4 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rax))); /* Non-base2 rounding needs shifted carry */ \
khi(		xmm5 *= xmm4); \
;  \
c1(		xmm1 *= xptr(g->u.xmm.XMM_MINUS_C));	/* Do one mul before split rather than two after split */ \
\
	split_upper_zpad_word(echk, base2, sse4, xmm1, xmm4, xmm2, rax); \
\
no##const1( no##c1( no##cm1(	xmm2 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
no##const1( no##c1( no##cm1(	xmm4 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
const1(			xmm2 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
const1(			xmm4 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
\
	xmm0 += xmm2;		/* Add upper FFT word to lower FFT word */ \
khi(	xmm4 += xmm5);		/* Add upper FFT word to lower FFT word */ \
\
ttp(rcx = u8ptr(rdi+1));	/* Load next big vs. little flags */ \
	xmm10 = xptr(rbx+rcx);	/* col two-to-minus-phi */ \
ttp(xmm10 *= xptr(rdx+1*32));	/* Mul by grp two-to-minus-phi */ \
	xmm8 = xptr(rsi+16);		/* Load high values1 */ \
	xmm7 += xmm8;		/* sumout += values1 */ \
	xmm9 = xptr(rsi+3*16);	/* Load high values2 */ \
	xmm7 += xmm9;		/* sumout += values2 */ \
	xmm8 *= xmm10;		/* Mul by fudged col two-to-minus-phi */ \
	xmm9 *= xmm10;		/* Mul by fudged col two-to-minus-phi */ \
\
	split_lower_zpad_word(echk, base2, sse4, xmm8, xmm11, xmm13, rcx); \
\
no##const1(	xmm8 = xptr(g->u.xmm.XMM_K_LO)); \
const1(		xmm8 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_LO)); \
		xmm8 *= xmm13; \
\
		xmm8 += xmm12;	/* x2 = values + carry */ \
\
khi( no##const1(	xmm12 = xptr(g->u.xmm.XMM_K_HI))); \
khi( const1(	xmm12 = xptr(g->u.xmm.XMM_K_TIMES_MULCONST_HI))); \
khi( no##base2(xmm12 *= xptr2(g->u.xmm.XMM_LIMIT_INVERSE,rcx))); /* Non-base2 rounding needs shifted carry */ \
khi(		xmm13 *= xmm12); \
\
c1(		xmm9 *= xptr(g->u.xmm.XMM_MINUS_C));	/* Do one mul before split rather than two after split */ \
\
	split_upper_zpad_word(echk, base2, sse4, xmm9, xmm12, xmm10, rcx); \
\
no##const1( no##c1( no##cm1(	xmm10 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
no##const1( no##c1( no##cm1(	xmm12 *= xptr(g->u.xmm.XMM_MINUS_C)))); \
const1(			xmm10 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
const1(			xmm12 *= xptr(g->u.xmm.XMM_MINUS_C_TIMES_MULCONST)); \
\
	xmm8 += xmm10;		/* Add upper FFT word to lower FFT word */ \
khi(	xmm12 += xmm13);		/* Add upper FFT word to lower FFT word */ \
\
	rounding_interleaved(ttp, base2, exec, sse4, xmm0, xmm4, xmm2, rax, xmm8, xmm12, xmm10, rcx); \
\
ttp(xmm5 = xptr(rbx+256+rax));	/* col two-to-phi */ \
ttp(xmm5 *= xptr(rdx+0*32+16));	/* new value1 = val * grp two-to-phi */ \
ttp(xmm0 *= xmm5);		/* new value1 *= fudged col two-to-phi */ \
	xptr(rsi) = xmm0;		/* Save new value1 */ \
\
ttp(xmm13 = xptr(rbx+256+rcx));	/* col two-to-phi */ \
ttp(xmm13 *= xptr(rdx+1*32+16));	/* new value2 = val * grp two-to-phi */ \
ttp(rax = u8ptr(rdi+4));	/* Load next big vs. little flags */ \
ttp(xmm8 *= xmm13);		/* new value2 *= fudged col two-to-phi */ \
	xptr(rsi+1*16) = xmm8;	/* Save new value2 */ \
\
	xmm1 -= xmm1;		/* new high values = zero */ \
	xptr(rsi+2*16) = xmm1;	/* Zero high value1 */ \
	xptr(rsi+3*16) = xmm1;	/* Zero high value2 */ \

#endif


#define A_OR_Bnonoexecnoexec(C) C
#define A_OR_Bnonoexecexec(C) C
#define A_OR_Bnoexecnoexec(C)
#define A_OR_Bnoexecexec(C) C
#define A_OR_Bexecnoexec(C) C
#define A_OR_Bexecexec(C) C
#define A_OR_B(A, B, C) A_OR_B##A##B(C)

#define inorm(lab, ttp, zero, echk, const1, base2, sse4) \
void CONCAT(lab, ARCH1)(struct gwasm_data *__restrict g, uintptr_t rsi) { \
	uintptr_t rax, rbx, rdi, rbp; \
A_OR_B##base2##ttp(uintptr_t rcx); \
A_OR_B##base2##ttp(uintptr_t r8); \
A_OR_B##base2##ttp(uintptr_t r9); \
ttp(uintptr_t rdx); \
uintptr_t loopcount1, loopcount2; \
	unsigned int loopcount3, carry1; \
	vec2f64 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7; \
	vec2f64 xmm8, xmm9, xmm10, xmm11, xmm12, xmm13; \
ttp(vec2f64 xmm14); \
ttp(vec2f64 xmm15); \
	uintptr_t saved_rsi = rsi; \
	xmm7 = g->u.xmm.XMM_SUMOUT; \
	xmm6 = g->u.xmm.XMM_MAXERR; \
	rbx = (uintptr_t) g->norm_ptr2;  \
ttp(rax = g->cache_line_multiplier); \
	rdi = ((uintptr_t)g->u.xmm.XMM_COL_MULTS) + 128; /* LEA */ \
ttp(setlp:) \
	xnorm_2d_setup(ttp); \
ttp(rdi += 512); \
ttp(rbx += 32); \
ttp(rax -= 1); \
ttp(if(rax) goto setlp); \
	\
ttp(rdx = (uintptr_t)g->norm_grp_mults); \
	rbp = (uintptr_t)g->carries; \
	rdi = (uintptr_t)g->norm_ptr1; \
	rax = g->addcount1; \
	loopcount2 = rax; \
	loopcount3 = 0; \
ttp(rax = u8ptr(rdi+0)); \
ttp(rcx = u8ptr(rdi+1)); \
ttp(r8 = u8ptr(rdi+2)); /*64b*/ \
ttp(r9 = u8ptr(rdi+3)); /*64b*/ \
no##ttp(base2(rax = 0)); \
no##ttp(base2(rcx = 0)); \
no##ttp(base2(r8 = 0)); /*64b*/ \
no##ttp(base2(r9 = 0)); /*64b*/ \
	do{ \
		rbx = g->cache_line_multiplier; \
		loopcount1 = rbx; \
		rbx = ((uintptr_t)g->u.xmm.XMM_COL_MULTS); /* LEA */ \
		/* L2prefetch128 [rdx+128] */ \
		do{ /*ilp1:*/ \
			/* xprefetchw [rsi+64] */ \
			xnorm_2d(ttp, zero, echk, const1, base2, sse4); \
			rsi += 64; \
		ttp(rbx += 512); \
		ttp(rdi += 4); \
			loopcount1--; \
		}while(loopcount1); \
		rsi += g->normblkdst; \
		rbp += 64; \
	ttp(rdx += 128); \
		loopcount2--; \
		if(loopcount2 == 0) break; \
		loopcount3 = __builtin_addc(loopcount3, 0x80000000u / 4u, 0, &carry1); \
		if(carry1) \
			rsi += g->normblkdst8; /* Add 128 every 8 clmblkdsts */ \
	}while(1); \
	g->u.xmm.XMM_SUMOUT = xmm7; \
	g->u.xmm.XMM_MAXERR = xmm6; \
	\
	if(g->this_block == g->last_pass1_block) { \
		rsi = saved_rsi; \
		xnorm_top_carry; \
	} \
}

#define zpnorm(lab, ttp, echk, const1, base2, sse4, khi, c1, cm1) \
void CONCAT(lab, ARCH1)(struct gwasm_data *__restrict g, uintptr_t rsi) { \
	uintptr_t rax, rcx, rbx, rdi, rbp; \
ttp(uintptr_t rdx); \
	uintptr_t loopcount1z, loopcount2z; \
	unsigned int loopcount3z, carry1; \
	vec2f64 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm7, \
		xmm8, xmm9, xmm10, xmm11, xmm12, xmm13; \
	\
	xmm7 = g->u.xmm.XMM_SUMOUT; \
echk(vec2f64 xmm6 = g->u.xmm.XMM_MAXERR); \
	rbx = (uintptr_t) g->norm_ptr2; \
ttp(rax = g->cache_line_multiplier); \
	rdi = ((uintptr_t)g->u.xmm.XMM_COL_MULTS) + 128; /* LEA */ \
ttp(setlp:) \
	xnorm_2d_setup(ttp); \
ttp(rdi += 512); \
ttp(rbx += 32); \
ttp(rax -= 1); \
ttp(if(rax) goto setlp); \
	\
ttp(rdx = (uintptr_t)g->norm_grp_mults); \
	rbp = (uintptr_t)g->carries; \
	rdi = (uintptr_t)g->norm_ptr1; \
	rax = g->addcount1; \
	loopcount2z = rax; \
	loopcount3z = 0; \
ttp(rax = u8ptr(rdi+0)); \
no##ttp(rax = 0); \
no##ttp(rcx = 0); \
	do{ /*ilp0:*/ \
		rbx = g->cache_line_multiplier; \
		loopcount1z = rbx; \
		rbx = ((uintptr_t)g->u.xmm.XMM_COL_MULTS); /* LEA */ \
		xnorm_2d_zpad_pre_loop; /* 64bit: Preload carries */ \
/* L2prefetch128 [rdx+128] */ \
		do{ /*ilp1:*/ \
			/* xprefetchw [rsi+64] */ \
			xnorm_2d_zpad(ttp, echk, const1, base2, sse4, khi, c1, cm1); \
			rsi += 64; \
			ttp(rbx += 512); \
			ttp(rdi += 4); \
			loopcount1z--; \
		}while(loopcount1z); \
		rsi += g->normblkdst; \
		xnorm_2d_zpad_post_loop; /* 64bit: Store carries */ \
		rbp += 64; \
		ttp(rdx += 128); \
		loopcount2z--; \
		if(loopcount2z == 0) \
			break; \
		loopcount3z = __builtin_addc(loopcount3z, 0x80000000u / 4u, 0, &carry1); \
		if(carry1) \
			rsi += g->normblkdst8; /* Add 128 every 8 clmblkdsts */ \
	}while(1); \
	g->u.xmm.XMM_SUMOUT = xmm7; \
echk(g->u.xmm.XMM_MAXERR = xmm6); \
}
