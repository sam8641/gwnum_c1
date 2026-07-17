#pragma once

/* Copyright 2009-2023 - Mersenne Research, Inc.  All rights reserved */ \
/* Author:  George Woltman */ \
/* Email: woltman@alum.mit.edu */ \
/* */ \
\
/* */ \
/* Macros for a radix-8 step in an FFT.  This is used in a radix-4 FFT */ \
/* with an odd number of levels. */ \
/* */ \
\
\
\
/* */ \
/* ************************************* eight-complex-djbfft variants ****************************************** */ \
/* */ \
\
/* This is a standard eight-complex case with 7 sin/cos twiddle factors applied. */ \
/* DJB allows us to do this using only 4 sin/cos twiddle factors. */
#if 0 // UNUSED

#define r8_x8cl_eight_complex_djbfft(srcreg,srcinc,d1,d2,d4,screg) \
bug	r8_x8c_djbfft(srcreg+0,d1,d2,d4,dstreg+0,e1,e2,screg,0); \
bug	r8_x8c_djbfft(srcreg+32,d1,d2,d4,dstreg+e4,e1,e2,screg,0); \
	srcreg += srcinc; \
\
\

#define r8_g8cl_eight_complex_djbfft(srcreg,srcinc,d1,d2,d4,dstreg,dstinc,e1,e2,e4,screg) \
untested	r8_x8c_djbfft(srcreg+0,d1,d2,d4,dstreg+0,e1,e2,screg,0); \
untested	r8_x8c_djbfft(srcreg+32,d1,d2,d4,dstreg+e4,e1,e2,screg,0); \
	srcreg += srcinc; \
	dstreg += dstinc; \
\
\

#define r8_x8c_djbfft(srcreg,d1,d2,d4,dstreg,e1,e2,screg,scoff) \
	xmm0 = xptr(srcreg);			/* R1 */ \
	xmm2 = xptr(srcreg+d4);		/* R5 */ \
	xmm2 += xmm0;			/* R5 = R1 + R5 (new1 R1) */ \
\
	xmm1 = xptr(srcreg+d2);		/* R3 */ \
	xmm3 = xptr(srcreg+d4+d2);		/* R7 */ \
	xmm3 += xmm1;			/* R7 = R3 + R7 (new1 R3) */ \
\
	xmm4 = xptr(srcreg+16);		/* I1 */ \
	xmm6 = xptr(srcreg+d4+16);		/* I5 */ \
	xmm6 += xmm4;			/* I5 = I1 + I5 (new1 I1) */ \
\
	xmm0 -= xptr(srcreg+d4);		/* R1 = R1 - R5 (new1 R5) */ \
	xmm1 -= xptr(srcreg+d4+d2);		/* R3 = R3 - R7 (new1 R7) */ \
\
	xmm5 = xmm3;			/* Copy R3 */ \
	xmm3 += xmm2;			/* R3 = R1 + R3 (new2 R1) */ \
	xmm2 -= xmm5;			/* R1 = R1 - R3 (new2 R3) */ \
\
	xmm5 = xptr(srcreg+d2+16);		/* I3 */ \
	xmm7 = xptr(srcreg+d4+d2+16);		/* I7 */ \
	xmm7 += xmm5;			/* I7 = I3 + I7 (new1 I3) */ \
\
	xmm4 -= xptr(srcreg+d4+16);		/* I1 = I1 - I5 (new1 I5) */ \
	xmm5 -= xptr(srcreg+d4+d2+16);		/* I3 = I3 - I7 (new1 I7) */ \
\
	xptr(dstreg) = xmm3;			/* Save R1 */ \
\
	xmm3 = xmm7;			/* Copy I3 */ \
	xmm7 += xmm6;			/* I3 = I1 + I3 (new2 I1) */ \
	xmm6 -= xmm3;			/* I1 = I1 - I3 (new2 I3) */ \
\
	xptr(dstreg+16) = xmm7;		/* Save I1 */ \
\
	xmm3 = xmm1;			/* Copy R7 */ \
	xmm1 += xmm4;			/* R7 = I5 + R7 (new2 I5) */ \
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm5;			/* R5 = R5 - I7 (new2 R5) */ \
	xmm4 -= xmm3;			/* I5 = I5 - R7 (new2 I7) */ \
	xmm5 += xmm7;			/* I7 = R5 + I7 (new2 R7) */ \
\
	xptr(dstreg+e1) = xmm2;		/* Save R3 */ \
	xptr(dstreg+e1+16) = xmm6;		/* Save I3 */ \
	xptr(dstreg+e2) = xmm0;		/* Save R5 */ \
	xptr(dstreg+e2+16) = xmm1;		/* Save I5 */ \
	xptr(dstreg+e2+e1) = xmm5;		/* Save R7 */ \
	xptr(dstreg+e2+e1+16) = xmm4;		/* Save I7 */ \
\
	xmm0 = xptr(srcreg+d1);		/* R2 */ \
	xmm2 = xptr(srcreg+d4+d1);		/* R6 */ \
	xmm2 += xmm0;			/* R6 = R2 + R6 (new1 R2) */ \
\
	xmm1 = xptr(srcreg+d2+d1);		/* R4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1);		/* R8 */ \
	xmm3 += xmm1;			/* R8 = R4 + R8 (new1 R4) */ \
\
	xmm4 = xptr(srcreg+d1+16);		/* I2 */ \
	xmm6 = xptr(srcreg+d4+d1+16);		/* I6 */ \
	xmm6 += xmm4;			/* I6 = I2 + I6 (new1 I2) */ \
\
	xmm0 -= xptr(srcreg+d4+d1);		/* R2 = R2 - R6 (new1 R6) */ \
	xmm1 -= xptr(srcreg+d4+d2+d1);		/* R4 = R4 - R8 (new1 R8) */ \
\
	xmm5 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm2;			/* R4 = R2 + R4 (new2 R2) */ \
	xmm2 -= xmm5;			/* R2 = R2 - R4 (new2 R4) */ \
\
	xmm5 = xptr(srcreg+d2+d1+16);		/* I4 */ \
	xmm7 = xptr(srcreg+d4+d2+d1+16);	/* I8 */ \
	xmm7 += xmm5;			/* I8 = I4 + I8 (new1 I4) */ \
\
	xmm4 -= xptr(srcreg+d4+d1+16);		/* I2 = I2 - I6 (new1 I6) */ \
	xmm5 -= xptr(srcreg+d4+d2+d1+16);	/* I4 = I4 - I8 (new1 I8) */ \
\
	xptr(dstreg+e1+32) = xmm2;		/* Save R4 */ \
\
	xmm2 = xmm7;			/* Copy I4 */ \
	xmm7 += xmm6;			/* I4 = I2 + I4 (new2 I2) */ \
	xmm6 -= xmm2;			/* I2 = I2 - I4 (new2 I4) */ \
\
	xptr(dstreg+e1+48) = xmm6;		/* Save I4 */ \
\
	xmm2 = xmm1;			/* Copy R8 */ \
	xmm1 += xmm4;			/* R8 = I6 + R8 (new2 I6) */ \
	xmm6 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm5;			/* R6 = R6 - I8 (new2 R6) */ \
	xmm4 -= xmm2;			/* I6 = I6 - R8 (new2 I8) */ \
	xmm5 += xmm6;			/* I8 = R6 + I8 (new2 R8) */ \
\
	xmm2 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm1;			/* R6 = R6 - I6 */ \
	xmm1 += xmm2;			/* I6 = R6 + I6 */ \
	xmm2 = XMM_SQRTHALF2; \
	xmm0 *= xmm2;			/* R6 = R6 * SQRTHALF (new2 R6) */ \
	xmm1 *= xmm2;			/* I6 = I6 * SQRTHALF (new2 I6) */ \
\
	xmm6 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - I8 */ \
	xmm4 += xmm6;			/* I8 = R8 + I8 */ \
	xmm5 *= xmm2;			/* R8 = R8 * SQRTHALF (new2 R8) */ \
	xmm4 *= xmm2;			/* I8 = I8 * SQRTHALF (new2 I8) */ \
\
/* the last level */ \
\
	xmm2 = xptr(dstreg);			/* R1 */ \
	xmm2 -= xmm3;			/* R1 = R1 - R2 (new3 R2) */ \
	xmm3 += xptr(dstreg);			/* R2 = R1 + R2 (final R1) */ \
	xmm6 = xptr(dstreg+16);		/* I1 */ \
	xmm6 -= xmm7;			/* I1 = I1 - I2 (new3 I2) */ \
	xmm7 += xptr(dstreg+16);		/* I2 = I1 + I2 (final I1) */ \
\
	xptr(dstreg) = xmm3;			/* Save R1 */ \
	xptr(dstreg+16) = xmm7;		/* Save I1 */ \
\
	xmm3 = xptr(screg+scoff+96+16);	/* cosine/sine */ \
	xmm3 *= xmm2;			/* A2 = R2 * cosine/sine */ \
	xmm3 -= xmm6;			/* A2 = A2 - I2 */ \
	xmm6 *= xptr(screg+scoff+96+16);	/* B2 = I2 * cosine/sine */ \
	xmm6 += xmm2;			/* B2 = B2 + R2 */ \
\
	xptr(dstreg+e2+e1+32) = xmm5;		/* Save R8 */ \
\
	xmm3 *= xptr(screg+scoff+96);		/* A2 = A2 * sine (final R2) */ \
	xmm6 *= xptr(screg+scoff+96);		/* B2 = B2 * sine (final I2) */ \
	xptr(dstreg+32) = xmm3;		/* Save R2 */ \
	xptr(dstreg+48) = xmm6;		/* Save I2 */ \
\
	xmm2 = xptr(dstreg+e2);		/* R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new3 R6) */ \
	xmm7 = xptr(dstreg+e2+16);		/* I5 */ \
	xmm7 -= xmm1;			/* I5 = I5 - I6 (new3 I6) */ \
\
	xmm5 = xptr(screg+scoff+64+16);	/* cosine/sine */ \
	xmm3 = xmm2;			/* Copy R6 */ \
	xmm2 *= xmm5;			/* A6 = R6 * cosine/sine */ \
	xmm2 += xmm7;			/* A6 = A6 + I6 */ \
	xmm7 *= xmm5;			/* B6 = I6 * cosine/sine */ \
	xmm7 -= xmm3;			/* B6 = B6 - R6 */ \
\
	xmm3 = xptr(dstreg+e2+e1);		/* R7 */ \
	xmm3 -= xmm4;			/* R7 = R7 - I8 (new3 R7) */ \
\
	xmm6 = xptr(screg+scoff+64); \
	xmm2 *= xmm6;			/* A6 = A6 * sine (final R6) */ \
	xmm7 *= xmm6;			/* B6 = B6 * sine (final I6) */ \
	xptr(dstreg+e2+32) = xmm2;		/* Save R6 */ \
	xptr(dstreg+e2+48) = xmm7;		/* Save I6 */ \
\
	xmm2 = xmm3;			/* Copy R7 */ \
	xmm3 *= xmm5;			/* A7 = R7 * cosine/sine */ \
\
	xmm7 = xptr(dstreg+e2+e1+16);		/* I7 */ \
	xmm7 += xptr(dstreg+e2+e1+32);		/* R8 = I7 + R8 (new3 I7) */ \
\
	xmm3 -= xmm7;			/* A7 = A7 - I7 */ \
	xmm7 *= xmm5;			/* B7 = I7 * cosine/sine */ \
	xmm7 += xmm2;			/* B7 = B7 + R7 */ \
\
	xmm0 += xptr(dstreg+e2);		/* R6 = R5 + R6 (new3 R5) */ \
	xmm1 += xptr(dstreg+e2+16);		/* I6 = I5 + I6 (new3 I5) */ \
	xmm4 += xptr(dstreg+e2+e1+48);		/* I8 = R7 + I8 (new3 R8) */ \
	xmm5 = xptr(dstreg+e2+e1+16);		/* I7 */ \
	xmm5 -= xptr(dstreg+e2+e1+32);		/* I7 = I7 - R8 (new3 I8) */ \
\
	xmm3 *= xmm6;			/* A7 = A7 * sine (final R7) */ \
	xptr(dstreg+e2+e1) = xmm3;		/* Save R7 */ \
\
	xmm2 = xptr(screg+scoff+0+16);	/* cosine/sine */ \
	xmm3 = xmm0;			/* Copy R5 */ \
	xmm0 *= xmm2;			/* A5 = R5 * cosine/sine */ \
	xmm0 -= xmm1;			/* A5 = A5 - I5 */ \
	xmm1 *= xmm2;			/* B5 = I5 * cosine/sine */ \
\
	xmm7 *= xmm6;			/* B7 = B7 * sine (final I7) */ \
\
	xmm6 = xmm4;			/* Copy R8 */ \
	xmm4 *= xmm2;			/* A8 = R8 * cosine/sine */ \
	xmm4 += xmm5;			/* A8 = A8 + I8 */ \
	xmm5 *= xmm2;			/* B8 = I8 * cosine/sine */ \
\
	xmm1 += xmm3;			/* B5 = B5 + R5 */ \
	xmm5 -= xmm6;			/* B8 = B8 - R8 */ \
\
	xmm6 = xptr(dstreg+e1);		/* R3 */ \
	xmm2 = xptr(dstreg+e1+48);		/* I4 */ \
	xmm6 -= xmm2;			/* R3 = R3 - I4 (new3 R3) */ \
	xmm2 += xptr(dstreg+e1);		/* I4 = R3 + I4 (new3 R4) */ \
\
	xptr(dstreg+e2+e1+16) = xmm7;		/* Save I7 */ \
\
	xmm3 = xptr(screg+scoff+0); \
	xmm0 *= xmm3;			/* A5 = A5 * sine (final R5) */ \
	xptr(dstreg+e2) = xmm0;		/* Save R5 */ \
\
	xmm7 = xptr(screg+scoff+32+16);	/* cosine/sine */ \
	xmm0 = xmm6;			/* Copy R3 */ \
	xmm6 *= xmm7;			/* A3 = R3 * cosine/sine */ \
\
	xmm1 *= xmm3;			/* B5 = B5 * sine (final I5) */ \
	xptr(dstreg+e2+16) = xmm1;		/* Save I5 */ \
\
	xmm1 = xmm2;			/* Copy R4 */ \
	xmm2 *= xmm7;			/* A4 = R4 * cosine/sine */ \
\
	xmm4 *= xmm3;			/* A8 = A8 * sine (final R8) */ \
	xptr(dstreg+e2+e1+32) = xmm4;		/* Save R8 */ \
	xmm5 *= xmm3;			/* B8 = B8 * sine (final I8) */ \
\
	xmm4 = xptr(dstreg+e1+16);		/* I3 */ \
	xmm3 = xptr(dstreg+e1+32);		/* R4 */ \
	xmm4 -= xmm3;			/* I3 = I3 - R4 (new3 I4) */ \
	xmm3 += xptr(dstreg+e1+16);		/* R4 = I3 + R4 (new3 I3) */ \
\
	xmm6 -= xmm3;			/* A3 = A3 - I3 */ \
	xmm3 *= xmm7;			/* B3 = I3 * cosine/sine */ \
	xmm3 += xmm0;			/* B3 = B3 + R3 */ \
\
	xmm2 += xmm4;			/* A4 = A4 + I4 */ \
	xmm4 *= xmm7;			/* B4 = I4 * cosine/sine */ \
	xmm4 -= xmm1;			/* B4 = B4 - R4 */ \
\
	xmm7 = xptr(screg+scoff+32); \
	xmm6 *= xmm7;			/* A3 = A3 * sine (final R3) */ \
	xmm3 *= xmm7;			/* B3 = B3 * sine (final I3) */ \
	xmm2 *= xmm7;			/* A4 = A4 * sine (final R4) */ \
	xmm4 *= xmm7;			/* B4 = B4 * sine (final I4) */ \
\
	xptr(dstreg+e2+e1+48) = xmm5;		/* Save I8 */ \
	xptr(dstreg+e1) = xmm6;		/* Save R3 */ \
	xptr(dstreg+e1+16) = xmm3;		/* Save I3 */ \
	xptr(dstreg+e1+32) = xmm2;		/* Save R4 */ \
	xptr(dstreg+e1+48) = xmm4;		/* Save I4 */ \

#endif
\
/* */ \
/* ************************************* eight-complex-with-square and variants ****************************************** */ \
/* */ \
\
/* */ \
/* These macros are used in the last levels of pass 2 in two pass FFTs. */ \
/* */ \
\
/* */ \
/* The last three levels of the forward FFT are performed. */ \
/* No sin/cos multipliers are needed. */ \
/* */ \
\

#define r8_x8cl_eight_complex_fft_final_preload \


// d1 = 64, d2 = 2*64, d4 = 4*64
#if 1
#define r8_x8cl_eight_complex_fft_final(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_part2(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_part2(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_x8cl_eight_complex_fft_final(srcreg,srcinc,d1,d2,d4) \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_x8c_simple_fft_part2(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_part2((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#define r8_x8c_simple_fft_part1(srcreg,d1,d2,d4,dst) \
	xmm0 = xptr(srcreg);			/* R1 */ \
	xmm2 = xptr(srcreg+d4);		/* R5 */ \
	xmm7 = xmm2;			/* Copy R5 */ \
	xmm2 += xmm0;			/* R5 = R1 + R5 (new R1) */ \
	xmm0 -= xmm7;			/* R1 = R1 - R5 (new R5) */ \
\
	xmm1 = xptr(srcreg+d2);		/* R3 */ \
	xmm3 = xptr(srcreg+d4+d2);		/* R7 */ \
	xmm7 = xmm3;			/* Copy R7 */ \
	xmm3 += xmm1;			/* R7 = R3 + R7 (new R3) */ \
	xmm1 -= xmm7;			/* R3 = R3 - R7 (new R7) */ \
\
	xmm4 = xptr(srcreg+16);		/* I1 */ \
	xmm6 = xptr(srcreg+d4+16);		/* I5 */ \
	xmm7 = xmm6;			/* Copy I5 */ \
	xmm6 += xmm4;			/* I5 = I1 + I5 (new I1) */ \
	xmm4 -= xmm7;			/* I1 = I1 - I5 (new I5) */ \
\
	xmm7 = xmm3;			/* Copy R3 */ \
	xmm3 += xmm2;			/* R3 = R1 + R3 (final R1) */ \
	xmm2 -= xmm7;			/* R1 = R1 - R3 (final R3) */ \
\
	xptr2(dst,0) = xmm3;			/* Save R1 */ \
	xptr2(dst,d1) = xmm2;			/* Save R3 */ \
\
	xmm5 = xptr(srcreg+d2+16);		/* I3 */ \
	xmm3 = xptr(srcreg+d4+d2+16);		/* I7 */ \
	xmm7 = xmm3;			/* Copy I7 */ \
	xmm3 += xmm5;			/* I7 = I3 + I7 (new I3) */ \
	xmm5 -= xmm7;			/* I3 = I3 - I7 (new I7) */ \
\
	xmm7 = xmm3;			/* Copy I3 */ \
	xmm3 += xmm6;			/* I3 = I1 + I3 (final I1) */ \
	xmm6 -= xmm7;			/* I1 = I1 - I3 (final I3) */ \
\
	xptr2(dst,32) = xmm3;			/* Save I1 */ \
	xptr2(dst,d1+32) = xmm6;		/* Save I3 */ \
\
	xmm3 = xmm1;			/* Copy R7 */ \
	xmm1 += xmm4;			/* R7 = I5 + R7 (final I5) */ \
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm5;			/* R5 = R5 - I7 (final R5) */ \
	xmm4 -= xmm3;			/* I5 = I5 - R7 (final I7) */ \
	xmm5 += xmm7;			/* I7 = R5 + I7 (final R7) */ \
\
	xptr2(dst,d2+32) = xmm1;		/* Save I5 */ \
	xptr2(dst,d2) = xmm0;			/* Save R5 */ \
	xptr2(dst,d2+d1+32) = xmm4;		/* Save I7 */ \
	xptr2(dst,d2+d1) = xmm5;		/* Save R7 */ \
\
	xmm0 = xptr(srcreg+d1);		/* R2 */ \
	xmm2 = xptr(srcreg+d4+d1);		/* R6 */ \
	xmm7 = xmm2;			/* Copy R6 */ \
	xmm2 += xmm0;			/* R6 = R2 + R6 (new R2) */ \
	xmm0 -= xmm7;			/* R2 = R2 - R6 (new R6) */ \
\
	xmm1 = xptr(srcreg+d2+d1);		/* R4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1);		/* R8 */ \
	xmm7 = xmm3;			/* Copy R8 */ \
	xmm3 += xmm1;			/* R8 = R4 + R8 (new R4) */ \
	xmm1 -= xmm7;			/* R4 = R4 - R8 (new R8) */ \
\
	xmm4 = xptr(srcreg+d1+16);		/* I2 */ \
	xmm6 = xptr(srcreg+d4+d1+16);		/* I6 */ \
	xmm7 = xmm6;			/* Copy I6 */ \
	xmm6 += xmm4;			/* I6 = I2 + I6 (new I2) */ \
	xmm4 -= xmm7;			/* I2 = I2 - I6 (new I6) */ \
\
	xmm7 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm2;			/* R4 = R2 + R4 (final R2) */ \
	xmm2 -= xmm7;			/* R2 = R2 - R4 (final R4) */ \
\
	xptr2(dst,16) = xmm3;			/* Save R2 */ \
	xptr2(dst,d1+16) = xmm2;		/* Save R4 */ \
\
	xmm5 = xptr(srcreg+d2+d1+16);		/* I4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1+16);	/* I8 */ \
	xmm7 = xmm3;			/* Copy I8 */ \
	xmm3 += xmm5;			/* I8 = I4 + I8 (new I4) */ \
	xmm5 -= xmm7;			/* I4 = I4 - I8 (new I8) */ \
\
	xmm7 = xmm3;			/* Copy I4 */ \
	xmm3 += xmm6;			/* I4 = I2 + I4 (final I2) */ \
	xmm6 -= xmm7;			/* I2 = I2 - I4 (final I4) */ \
\
	xptr2(dst,48) = xmm3;			/* Save I2 */ \
	xptr2(dst,d1+48) = xmm6;		/* Save I4 */ \
\
	xmm3 = xmm1;			/* Copy R8 */ \
	xmm1 += xmm4;			/* R8 = I6 + R8 (new I6) */ \
	xmm7 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm5;			/* R6 = R6 - I8 (new R6) */ \
	xmm4 -= xmm3;			/* I6 = I6 - R8 (new I8) */ \
	xmm5 += xmm7;			/* I8 = R6 + I8 (new R8) */ \
\
	xmm7 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm1;			/* R6 = R6 - I6 */ \
	xmm1 += xmm7;			/* I6 = R6 + I6 */ \
	xmm3 = XMM_SQRTHALF2; \
	xmm0 *= xmm3;			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm1 *= xmm3;			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - I8 */ \
	xmm4 += xmm7;			/* I8 = R8 + I8 */ \
	xmm5 *= xmm3;			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm4 *= xmm3;			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	xptr2(dst,d2+16) = xmm0;		/* Save R6 */ \
	xptr2(dst,d2+48) = xmm1;		/* Save I6 */ \
	xptr2(dst,d2+d1+16) = xmm5;		/* Save R8 */ \
	xptr2(dst,d2+d1+48) = xmm4;		/* Save I8 */ \
\
\

#define r8_x8c_simple_fft_part2(src,dstreg,d1,d2) \
	xmm2 = xptr2(src,d2);			/* R5 */ \
	xmm0 = xptr2(src,d2+16); 		/* R6 */ \
	xmm7 = xmm2;			/* Copy R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = xptr2(src,d2+32);		/* I5 */ \
	xmm1 = xptr2(src,d2+48); 		/* I6 */ \
	xmm7 = xmm3;			/* Copy I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xmm4 = xptr2(src,d2+d1);		/* R7 */ \
	xmm5 = xptr2(src,d2+d1+48);		/* I8 */ \
	xmm7 = xmm4;			/* Copy R7 */ \
	xmm4 -= xmm5;			/* R7 = R7 - I8 (new R7) */ \
	xmm5 += xmm7;			/* I8 = R7 + I8 (new R8) */ \
\
	xptr(dstreg+d2+16) = xmm2;		/* Save R6 */ \
	xptr(dstreg+d2) = xmm0;		/* Save R5 */ \
	xptr(dstreg+d2+48) = xmm3;		/* Save I6 */ \
	xptr(dstreg+d2+32) = xmm1;		/* Save I5 */ \
	xptr(dstreg+d2+d1) = xmm4;		/* Save R7 */ \
	xptr(dstreg+d2+d1+16) = xmm5;		/* Save R8 */ \
\
	xmm0 = xptr2(src,d2+d1+32);		/* I7 */ \
	xmm1 = xptr2(src,d2+d1+16);		/* R8 */ \
	xmm7 = xmm0;			/* Copy I7 */ \
	xmm0 -= xmm1;			/* I7 = I7 - R8 (new I8) */ \
	xmm1 += xmm7;			/* R8 = I7 + R8 (new I7) */ \
\
	xmm3 = xptr2(src,0);			/* R1 */ \
	xmm4 = xptr2(src,16);			/* R2 */ \
	xmm7 = xmm3;			/* Copy R1 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5 = xptr2(src,32);			/* I1 */ \
	xmm6 = xptr2(src,48);			/* I2 */ \
	xmm7 = xmm5;			/* Copy I1 */ \
	xmm5 -= xmm6;			/* I1 = I1 - I2 (new I2) */ \
	xmm6 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xptr(dstreg+d2+d1+48) = xmm0;		/* Save I8 */ \
	xptr(dstreg+d2+d1+32) = xmm1;		/* Save I7 */ \
	xptr(dstreg+16) = xmm3;		/* Save R2 */ \
	xptr(dstreg) = xmm4;			/* Save R1 */ \
	xptr(dstreg+48) = xmm5;		/* Save I2 */ \
	xptr(dstreg+32) = xmm6;		/* Save I1 */ \
\
	xmm5 = xptr2(src,d1);			/* R3 */ \
	xmm6 = xptr2(src,d1+48);		/* I4 */ \
	xmm7 = xmm5;			/* Copy R3 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += xmm7;			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = xptr2(src,d1+32);		/* I3 */ \
	xmm4 = xptr2(src,d1+16);		/* R4 */ \
	xmm7 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm4;			/* I3 = I3 - R4 (new I4) */ \
	xmm4 += xmm7;			/* R4 = I3 + R4 (new I3) */ \
\
	xptr(dstreg+d1) = xmm5;		/* Save R3 */ \
	xptr(dstreg+d1+16) = xmm6;		/* Save R4 */ \
	xptr(dstreg+d1+48) = xmm3;		/* Save I4 */ \
	xptr(dstreg+d1+32) = xmm4;		/* Save I3 */ \
\
\
/* */ \
/* The last three levels of the forward FFT are performed, point-wise */ \
/* squaring, and first three levels of the inverse FFT are performed. */ \
/* No sin/cos multipliers are needed. */ \
/* */ \
\

#define r8_x8cl_eight_complex_with_square_preload \
\
\

#if 1
#define r8_x8cl_eight_complex_with_square(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_with_square(XMM_COL_MULTS_1,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_square(XMM_COL_MULTS_2,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_x8cl_eight_complex_with_square(srcreg,srcinc,d1,d2,d4) \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_x8c_simple_fft_with_square(g->u.xmm.XMM_COL_MULTS,d1,d2); \
	r8_x8c_simple_fft_with_square((g->u.xmm.XMM_COL_MULTS+256/8),d1,d2); \
	r8_x8c_simple_unfft(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#define r8_x8c_simple_fft_with_square(src,d1,d2) \
	xmm2 = xptr2(src,d2);			/* R5 */ \
	xmm0 = xptr2(src,d2+16); 		/* R6 */ \
	xmm7 = xmm2;			/* Copy R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = xptr2(src,d2+32);		/* I5 */ \
	xmm1 = xptr2(src,d2+48); 		/* I6 */ \
	xmm7 = xmm3;			/* Copy I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xp_complex_square(xmm2, xmm3, xmm7);	/* Square R6/I6 */ \
	xp_complex_square(xmm0, xmm1, xmm7);	/* Square R5/I5 */ \
\
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm2;			/* R5 = R5 - R6 (new R6) */ \
	xmm2 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7 = xmm1;			/* Copy I5 */ \
	xmm1 -= xmm3;			/* I5 = I5 - I6 (new I6) */ \
	xmm3 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(src,d2+16) = xmm0;		/* Save R6 */ \
	xptr2(src,d2) = xmm2;			/* Save R5 */ \
	xptr2(src,d2+48) = xmm1;		/* Save I6 */ \
	xptr2(src,d2+32) = xmm3;		/* Save I5 */ \
\
	xmm4 = xptr2(src,d2+d1);		/* R7 */ \
	xmm5 = xptr2(src,d2+d1+48);		/* I8 */ \
	xmm7 = xmm4;			/* Copy R7 */ \
	xmm4 -= xmm5;			/* R7 = R7 - I8 (new R7) */ \
	xmm5 += xmm7;			/* I8 = R7 + I8 (new R8) */ \
\
	xmm0 = xptr2(src,d2+d1+32);		/* I7 */ \
	xmm1 = xptr2(src,d2+d1+16);		/* R8 */ \
	xmm7 = xmm0;			/* Copy I7 */ \
	xmm0 -= xmm1;			/* I7 = I7 - R8 (new I8) */ \
	xmm1 += xmm7;			/* R8 = I7 + R8 (new I7) */ \
\
	xp_complex_square(xmm5, xmm0, xmm7);	/* Square R8/I8 */ \
	xp_complex_square(xmm4, xmm1, xmm7);	/* Square R7/I7 */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - R7 (new I8) */ \
	xmm4 += xmm7;			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7 = xmm1;			/* Copy I7 */ \
	xmm1 -= xmm0;			/* I7 = I7 - I8 (new R8) */ \
	xmm0 += xmm7;			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(src,d2+d1+48) = xmm5;		/* Save I8 */ \
	xptr2(src,d2+d1) = xmm4;		/* Save R7 */ \
	xptr2(src,d2+d1+16) = xmm1;		/* Save R8 */ \
	xptr2(src,d2+d1+32) = xmm0;		/* Save I7 */ \
\
	xmm3 = xptr2(src,0);			/* R1 */ \
	xmm4 = xptr2(src,16);			/* R2 */ \
	xmm7 = xmm3;			/* Copy R1 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5 = xptr2(src,32);			/* I1 */ \
	xmm6 = xptr2(src,48);			/* I2 */ \
	xmm7 = xmm5;			/* Copy I1 */ \
	xmm5 -= xmm6;			/* I1 = I1 - I2 (new I2) */ \
	xmm6 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xp_complex_square(xmm3, xmm5, xmm7);	/* Square R2/I2 */ \
	xp_complex_square(xmm4, xmm6, xmm7);	/* Square R1/I1 */ \
\
	xmm7 = xmm4;			/* Copy R1 */ \
	xmm4 -= xmm3;			/* R1 = R1 - R2 (new R2) */ \
	xmm3 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7 = xmm6;			/* Copy I1 */ \
	xmm6 -= xmm5;			/* I1 = I1 - I2 (new I2) */ \
	xmm5 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xptr2(src,16) = xmm4;			/* Save R2 */ \
	xptr2(src,0) = xmm3;			/* Save R1 */ \
	xptr2(src,48) = xmm6;			/* Save I2 */ \
	xptr2(src,32) = xmm5;			/* Save I1 */ \
\
	xmm5 = xptr2(src,d1);			/* R3 */ \
	xmm6 = xptr2(src,d1+48);		/* I4 */ \
	xmm7 = xmm5;			/* Copy R3 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += xmm7;			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = xptr2(src,d1+32);		/* I3 */ \
	xmm4 = xptr2(src,d1+16);		/* R4 */ \
	xmm7 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm4;			/* I3 = I3 - R4 (final I4) */ \
	xmm4 += xmm7;			/* R4 = I3 + R4 (final I3) */ \
\
	xp_complex_square(xmm6, xmm3, xmm7);	/* Square R4/I4 */ \
	xp_complex_square(xmm5, xmm4, xmm7);	/* Square R3/I3 */ \
\
	xmm7 = xmm6;			/* Copy R4 */ \
	xmm6 -= xmm5;			/* R4 = R4 - R3 (new I4) */ \
	xmm5 += xmm7;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7 = xmm4;			/* Copy I3 */ \
	xmm4 -= xmm3;			/* I3 = I3 - I4 (new R4) */ \
	xmm3 += xmm7;			/* I4 = I3 + I4 (new I3) */ \
\
	xptr2(src,d1+48) = xmm6;		/* Save I4 */ \
	xptr2(src,d1) = xmm5;			/* Save R3 */ \
	xptr2(src,d1+16) = xmm4;		/* Save R4 */ \
	xptr2(src,d1+32) = xmm3;		/* Save I3 */ \
\
\

#define r8_x8c_simple_unfft(src,dstreg,d1,d2) \
	xmm5 = xptr2(src,d2+32);		/* I5 */ \
	xmm1 = xptr2(src,d2+d1+32);		/* I7 */ \
	xmm7 = xmm5;			/* Copy I5 */ \
	xmm5 -= xmm1;			/* I5 = I5 - I7 (new R7) */ \
	xmm1 += xmm7;			/* I7 = I5 + I7 (new I5) */ \
\
	xmm4 = xptr2(src,0);			/* R1 */ \
	xmm2 = xptr2(src,d1);			/* R3 */ \
	xmm7 = xmm4;			/* Copy R1 */ \
	xmm4 -= xmm2;			/* R1 = R1 - R3 (new R3) */ \
	xmm2 += xmm7;			/* R3 = R1 + R3 (new R1) */ \
\
	xmm7 = xmm4;			/* Copy R3 */ \
	xmm4 -= xmm5;			/* R3 = R3 - R7 (final R7) */ \
	xmm5 += xmm7;			/* R7 = R3 + R7 (final R3) */ \
\
	xptr(dstreg+d2+16) = xmm4;		/* Save R7 */ \
	xptr(dstreg+d2) = xmm5;		/* Save R3 */ \
\
	xmm6 = xptr2(src,d2);			/* R5 */ \
	xmm0 = xptr2(src,d2+d1);		/* R7 */ \
	xmm7 = xmm6;			/* Copy R5 */ \
	xmm6 += xmm0;			/* R5 = R7 + R5 (new R5) */ \
	xmm0 -= xmm7;			/* R7 = R7 - R5 (new I7) */ \
\
	xmm3 = xptr2(src,32);			/* I1 */ \
	xmm4 = xptr2(src,d1+32);		/* I3 */ \
	xmm7 = xmm3;			/* Copy I1 */ \
	xmm3 -= xmm4;			/* I1 = I1 - I3 (new I3) */ \
	xmm4 += xmm7;			/* I3 = I1 + I3 (new I1) */ \
\
	xmm7 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm0;			/* I3 = I3 - I7 (final I7) */ \
	xmm0 += xmm7;			/* I7 = I3 + I7 (final I3) */ \
\
	xptr(dstreg+d2+48) = xmm3;		/* I7 */ \
	xptr(dstreg+d2+32) = xmm0;		/* I3 */ \
\
	xmm7 = xmm2;			/* Copy R1 */ \
	xmm2 -= xmm6;			/* R1 = R1 - R5 (final R5) */ \
	xmm6 += xmm7;			/* R5 = R1 + R5 (final R1) */ \
\
	xmm7 = xmm4;			/* Copy I1 */ \
	xmm4 -= xmm1;			/* I1 = I1 - I5 (final I5) */ \
	xmm1 += xmm7;			/* I5 = I1 + I5 (final I1) */ \
\
	xptr(dstreg+16) = xmm2;		/* R5 */ \
	xptr(dstreg) = xmm6;			/* R1 */ \
	xptr(dstreg+48) = xmm4;		/* I5 */ \
	xptr(dstreg+32) = xmm1;		/* I1 */ \
\
\
;	/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm4 = xptr2(src,d2+16);		/* R6 */ \
	xmm0 = xptr2(src,d2+48);		/* I6 */ \
	xmm7 = xmm0;			/* Copy I6 */ \
	xmm0 -= xmm4;			/* I6 = I6 - R6 */ \
	xmm4 += xmm7;			/* R6 = R6 + I6 */ \
\
;	/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm2 = xptr2(src,d2+d1+16);		/* R8 */ \
	xmm1 = xptr2(src,d2+d1+48);		/* I8 */ \
	xmm7 = xmm1;			/* Copy I8 */ \
	xmm1 -= xmm2;			/* I8 = I8 - R8 */ \
	xmm2 += xmm7;			/* R8 = R8 + I8 */ \
\
	xmm5 = XMM_SQRTHALF2; \
	xmm0 *= xmm5;			/* I6 = I6 * SQRTHALF (new I6) */ \
	xmm4 *= xmm5;			/* R6 = R6 * SQRTHALF (new R6) */ \
	xmm1 *= xmm5;			/* I8 = I8 * SQRTHALF (new I8) */ \
	xmm2 *= xmm5;			/* R8 = R8 * SQRTHALF (new R8) */ \
\
	xmm6 = xptr2(src,16);			/* R2 */ \
	xmm3 = xptr2(src,d1+16);		/* R4 */ \
	xmm7 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm6;			/* R4 = R2 + R4 (new R2) */ \
	xmm6 -= xmm7;			/* R2 = R2 - R4 (new R4) */ \
\
	xmm7 = xmm2;			/* Copy R8 */ \
	xmm2 -= xmm4;			/* R8 = R8 - R6 (new I8) */ \
	xmm4 += xmm7;			/* R6 = R8 + R6 (new R6) */ \
\
	xmm7 = xmm0;			/* Copy I6 */ \
	xmm0 -= xmm1;			/* I6 = I6 - I8 (new R8) */ \
	xmm1 += xmm7;			/* I8 = I6 + I8 (new I6) */ \
\
	xmm7 = xmm3;			/* Copy R2 */ \
	xmm3 -= xmm4;			/* R2 = R2 - R6 (final R6) */ \
	xmm4 += xmm7;			/* R6 = R2 + R6 (final R2) */ \
\
	xptr(dstreg+d1+16) = xmm3;		/* R6 */ \
	xptr(dstreg+d1) = xmm4;		/* R2 */ \
\
	xmm5 = xptr2(src,48);			/* I2 */ \
	xmm3 = xptr2(src,d1+48);		/* I4 */ \
	xmm7 = xmm3;			/* Copy I4 */ \
	xmm3 += xmm5;			/* I4 = I2 + I4 (new I2) */ \
	xmm5 -= xmm7;			/* I2 = I2 - I4 (new I4) */ \
\
	xmm7 = xmm6;			/* Copy R4 */ \
	xmm6 -= xmm0;			/* R4 = R4 - R8 (final R8) */ \
	xmm0 += xmm7;			/* R8 = R4 + R8 (final R4) */ \
\
	xmm7 = xmm3;			/* Copy I2 */ \
	xmm3 -= xmm1;			/* I2 = I2 - I6 (final I6) */ \
	xmm1 += xmm7;			/* I6 = I2 + I6 (final I2) */ \
\
	xmm7 = xmm5;			/* Copy I4 */ \
	xmm5 -= xmm2;			/* I4 = I4 - I8 (final I8) */ \
	xmm2 += xmm7;			/* I8 = I4 + I8 (final I4) */ \
\
	xptr(dstreg+d2+d1+16) = xmm6;		/* R8 */ \
	xptr(dstreg+d2+d1) = xmm0;		/* R4 */ \
	xptr(dstreg+d1+48) = xmm3;		/* I6 */ \
	xptr(dstreg+d1+32) = xmm1;		/* I2 */ \
	xptr(dstreg+d2+d1+48) = xmm5;		/* I8 */ \
	xptr(dstreg+d2+d1+32) = xmm2;		/* I4 */ \
\
\
/* */ \
/* The last three levels of the forward FFT are performed, point-wise */ \
/* multiplication, and first three levels of the inverse FFT are performed. */ \
/* No sin/cos multipliers are needed. */ \
/* */ \
\

#define r8_x8cl_eight_complex_with_mult_preload \
\
\

#if 0
#define r8_x8cl_eight_complex_with_mult(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_with_mult(XMM_COL_MULTS_1,srcreg+rbp,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_mult(XMM_COL_MULTS_2,srcreg+d4+rbp,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_x8cl_eight_complex_with_mult(srcreg,srcinc,d1,d2,d4) \
	r8_x8c_simple_fft_part1(srcreg+0,d1,d2,d4,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_x8c_simple_fft_with_mult(g->u.xmm.XMM_COL_MULTS,srcreg+rbp,d1,d2); \
	r8_x8c_simple_fft_with_mult((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4+rbp,d1,d2); \
	r8_x8c_simple_unfft(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#define r8_x8c_simple_fft_with_mult(src,altsrc,d1,d2) \
	xmm2 = xptr2(src,d2);			/* R5 */ \
	xmm0 = xptr2(src,d2+16); 		/* R6 */ \
	xmm7 = xmm2;			/* Copy R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = xptr2(src,d2+32);		/* I5 */ \
	xmm1 = xptr2(src,d2+48); 		/* I6 */ \
	xmm7 = xmm3;			/* Copy I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xp_complex_mult(xmm2, xmm3, xptr(altsrc+d2+16), xptr(altsrc+d2+48), xmm6, xmm7); /* Mult R6/I6 */ \
	xp_complex_mult(xmm0, xmm1, xptr(altsrc+d2), xptr(altsrc+d2+32), xmm6, xmm7); /* Mult R5/I5 */ \
\
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm2;			/* R5 = R5 - R6 (new R6) */ \
	xmm2 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7 = xmm1;			/* Copy I5 */ \
	xmm1 -= xmm3;			/* I5 = I5 - I6 (new I6) */ \
	xmm3 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(src,d2+16) = xmm0;		/* Save R6 */ \
	xptr2(src,d2) = xmm2;			/* Save R5 */ \
	xptr2(src,d2+48) = xmm1;		/* Save I6 */ \
	xptr2(src,d2+32) = xmm3;		/* Save I5 */ \
\
	xmm4 = xptr2(src,d2+d1);		/* R7 */ \
	xmm5 = xptr2(src,d2+d1+48);		/* I8 */ \
	xmm7 = xmm4;			/* Copy R7 */ \
	xmm4 -= xmm5;			/* R7 = R7 - I8 (new R7) */ \
	xmm5 += xmm7;			/* I8 = R7 + I8 (new R8) */ \
\
	xmm0 = xptr2(src,d2+d1+32);		/* I7 */ \
	xmm1 = xptr2(src,d2+d1+16);		/* R8 */ \
	xmm7 = xmm0;			/* Copy I7 */ \
	xmm0 -= xmm1;			/* I7 = I7 - R8 (new I8) */ \
	xmm1 += xmm7;			/* R8 = I7 + R8 (new I7) */ \
\
	xp_complex_mult(xmm5, xmm0, xptr(altsrc+d2+d1+16), xptr(altsrc+d2+d1+48), xmm6, xmm7); /* Mult R8/I8 */ \
	xp_complex_mult(xmm4, xmm1, xptr(altsrc+d2+d1), xptr(altsrc+d2+d1+32), xmm6, xmm7); /* Mult R7/I7 */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - R7 (new I8) */ \
	xmm4 += xmm7;			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7 = xmm1;			/* Copy I7 */ \
	xmm1 -= xmm0;			/* I7 = I7 - I8 (new R8) */ \
	xmm0 += xmm7;			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(src,d2+d1+48) = xmm5;		/* Save I8 */ \
	xptr2(src,d2+d1) = xmm4;		/* Save R7 */ \
	xptr2(src,d2+d1+16) = xmm1;		/* Save R8 */ \
	xptr2(src,d2+d1+32) = xmm0;		/* Save I7 */ \
\
	xmm3 = xptr2(src,0);			/* R1 */ \
	xmm4 = xptr2(src,16);			/* R2 */ \
	xmm7 = xmm3;			/* Copy R1 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5 = xptr2(src,32);			/* I1 */ \
	xmm6 = xptr2(src,48);			/* I2 */ \
	xmm7 = xmm5;			/* Copy I1 */ \
	xmm5 -= xmm6;			/* I1 = I1 - I2 (new I2) */ \
	xmm6 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xp_complex_mult(xmm3, xmm5, xptr(altsrc+16), xptr(altsrc+48), xmm0, xmm7); /* Mult R2/I2 */ \
	xp_complex_mult(xmm4, xmm6, xptr(altsrc), xptr(altsrc+32), xmm0, xmm7); /* Mult R1/I1 */ \
\
	xmm7 = xmm4;			/* Copy R1 */ \
	xmm4 -= xmm3;			/* R1 = R1 - R2 (new R2) */ \
	xmm3 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7 = xmm6;			/* Copy I1 */ \
	xmm6 -= xmm5;			/* I1 = I1 - I2 (new I2) */ \
	xmm5 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xptr2(src,16) = xmm4;			/* Save R2 */ \
	xptr2(src,0) = xmm3;			/* Save R1 */ \
	xptr2(src,48) = xmm6;			/* Save I2 */ \
	xptr2(src,32) = xmm5;			/* Save I1 */ \
\
	xmm5 = xptr2(src,d1);			/* R3 */ \
	xmm6 = xptr2(src,d1+48);		/* I4 */ \
	xmm7 = xmm5;			/* Copy R3 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += xmm7;			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = xptr2(src,d1+32);		/* I3 */ \
	xmm4 = xptr2(src,d1+16);		/* R4 */ \
	xmm7 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm4;			/* I3 = I3 - R4 (final I4) */ \
	xmm4 += xmm7;			/* R4 = I3 + R4 (final I3) */ \
\
	xp_complex_mult(xmm6, xmm3, xptr(altsrc+d1+16), xptr(altsrc+d1+48), xmm0, xmm7); /* Mult R4/I4 */ \
	xp_complex_mult(xmm5, xmm4, xptr(altsrc+d1), xptr(altsrc+d1+32), xmm0, xmm7); /* Mult R3/I3 */ \
\
	xmm7 = xmm6;			/* Copy R4 */ \
	xmm6 -= xmm5;			/* R4 = R4 - R3 (new I4) */ \
	xmm5 += xmm7;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7 = xmm4;			/* Copy I3 */ \
	xmm4 -= xmm3;			/* I3 = I3 - I4 (new R4) */ \
	xmm3 += xmm7;			/* I4 = I3 + I4 (new I3) */ \
\
	xptr2(src,d1+48) = xmm6;		/* Save I4 */ \
	xptr2(src,d1) = xmm5;			/* Save R3 */ \
	xptr2(src,d1+16) = xmm4;		/* Save R4 */ \
	xptr2(src,d1+32) = xmm3;		/* Save I3 */ \
\
\
/* */ \
/* Point-wise multiplication and first three levels of the inverse FFT are performed. */ \
/* No sin/cos multipliers are needed. */ \
/* */ \
\

#define r8_x8cl_eight_complex_with_mulf_preload \
\
\

#if 1
#define r8_x8cl_eight_complex_with_mulf(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS[16]; \
	r8_x8c_simple_fft_with_mulf(srcreg,d1,d2,XMM_COL_MULTS); \
	r8_x8c_simple_unfft(XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_mulf(srcreg+d4,d1,d2,XMM_COL_MULTS); \
	r8_x8c_simple_unfft(XMM_COL_MULTS,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_x8cl_eight_complex_with_mulf(srcreg,srcinc,d1,d2,d4) \
	r8_x8c_simple_fft_with_mulf(srcreg,d1,d2,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_with_mulf(srcreg+d4,d1,d2,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_x8c_simple_unfft(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif


#define r8_x8c_simple_fft_with_mulf(srcreg,d1,d2,dst) \
	xmm2 = xptr(srcreg+d2+16+rbx);	/* R6 */ \
	xmm3 = xptr(srcreg+d2+48+rbx);	/* I6 */ \
	xmm0 = xptr(srcreg+d2+rbx);		/* R5 */ \
	xmm1 = xptr(srcreg+d2+32+rbx);	/* I5 */ \
\
	xp_complex_mult(xmm2, xmm3, xptr(srcreg+d2+16+rbp), xptr(srcreg+d2+48+rbp), xmm6, xmm7); /* Mult R6/I6 */ \
	xp_complex_mult(xmm0, xmm1, xptr(srcreg+d2+rbp), xptr(srcreg+d2+32+rbp), xmm6, xmm7); /* Mult R5/I5 */ \
\
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm2;			/* R5 = R5 - R6 (new R6) */ \
	xmm2 += xmm7;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7 = xmm1;			/* Copy I5 */ \
	xmm1 -= xmm3;			/* I5 = I5 - I6 (new I6) */ \
	xmm3 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(dst,d2+16) = xmm0;		/* Save R6 */ \
	xptr2(dst,d2) = xmm2;			/* Save R5 */ \
	xptr2(dst,d2+48) = xmm1;		/* Save I6 */ \
	xptr2(dst,d2+32) = xmm3;		/* Save I5 */ \
\
	xmm5 = xptr(srcreg+d2+d1+16+rbx);	/* R8 */ \
	xmm0 = xptr(srcreg+d2+d1+48+rbx);	/* I8 */ \
	xmm4 = xptr(srcreg+d2+d1+rbx);	/* R7 */ \
	xmm1 = xptr(srcreg+d2+d1+32+rbx);	/* I7 */ \
\
	xp_complex_mult(xmm5, xmm0, xptr(srcreg+d2+d1+16+rbp), xptr(srcreg+d2+d1+48+rbp), xmm6, xmm7); /* Mult R8/I8 */ \
	xp_complex_mult(xmm4, xmm1, xptr(srcreg+d2+d1+rbp), xptr(srcreg+d2+d1+32+rbp), xmm6, xmm7); /* Mult R7/I7 */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - R7 (new I8) */ \
	xmm4 += xmm7;			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7 = xmm1;			/* Copy I7 */ \
	xmm1 -= xmm0;			/* I7 = I7 - I8 (new R8) */ \
	xmm0 += xmm7;			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(dst,d2+d1+48) = xmm5;		/* Save I8 */ \
	xptr2(dst,d2+d1) = xmm4;		/* Save R7 */ \
	xptr2(dst,d2+d1+16) = xmm1;		/* Save R8 */ \
	xptr2(dst,d2+d1+32) = xmm0;		/* Save I7 */ \
\
	xmm3 = xptr(srcreg+16+rbx);		/* R2 */ \
	xmm5 = xptr(srcreg+48+rbx);		/* I2 */ \
	xmm4 = xptr(srcreg+rbx);		/* R1 */ \
	xmm6 = xptr(srcreg+32+rbx);		/* I1 */ \
\
	xp_complex_mult(xmm3, xmm5, xptr(srcreg+16+rbp), xptr(srcreg+48+rbp), xmm0, xmm7); /* Mult R2/I2 */ \
	xp_complex_mult(xmm4, xmm6, xptr(srcreg+rbp), xptr(srcreg+32+rbp), xmm0, xmm7); /* Mult R1/I1 */ \
\
	xmm7 = xmm4;			/* Copy R1 */ \
	xmm4 -= xmm3;			/* R1 = R1 - R2 (new R2) */ \
	xmm3 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7 = xmm6;			/* Copy I1 */ \
	xmm6 -= xmm5;			/* I1 = I1 - I2 (new I2) */ \
	xmm5 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xptr2(dst,16) = xmm4;			/* Save R2 */ \
	xptr2(dst,0) = xmm3;			/* Save R1 */ \
	xptr2(dst,48) = xmm6;			/* Save I2 */ \
	xptr2(dst,32) = xmm5;			/* Save I1 */ \
\
	xmm6 = xptr(srcreg+d1+16+rbx);	/* R4 */ \
	xmm3 = xptr(srcreg+d1+48+rbx);	/* I4 */ \
	xmm5 = xptr(srcreg+d1+rbx);		/* R3 */ \
	xmm4 = xptr(srcreg+d1+32+rbx);	/* I3 */ \
\
	xp_complex_mult(xmm6, xmm3, xptr(srcreg+d1+16+rbp), xptr(srcreg+d1+48+rbp), xmm0, xmm7); /* Mult R4/I4 */ \
	xp_complex_mult(xmm5, xmm4, xptr(srcreg+d1+rbp), xptr(srcreg+d1+32+rbp), xmm0, xmm7); /* Mult R3/I3 */ \
\
	xmm7 = xmm6;			/* Copy R4 */ \
	xmm6 -= xmm5;			/* R4 = R4 - R3 (new I4) */ \
	xmm5 += xmm7;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7 = xmm4;			/* Copy I3 */ \
	xmm4 -= xmm3;			/* I3 = I3 - I4 (new R4) */ \
	xmm3 += xmm7;			/* I4 = I3 + I4 (new I3) */ \
\
	xptr2(dst,d1+48) = xmm6;		/* Save I4 */ \
	xptr2(dst,d1) = xmm5;			/* Save R3 */ \
	xptr2(dst,d1+16) = xmm4;		/* Save R4 */ \
	xptr2(dst,d1+32) = xmm3;		/* Save I3 */ \
\
\
/* */ \
/* ************************************* eight-complex-fft8 variants ****************************************** */ \
/* */ \
/* In the negacyclic split premultiplier case, we apply part of the roots of -1 at the */ \
/* end of the first pass.  Also, in the r4delay case we apply part of the first level */ \
/* twiddles at the end of the first pass.  Thus we have 8 sin/cos multiplies instead */ \
/* of the usual 7. */ \
/* */ \
\
/* Used in the last levels of pass 1.  No swizzling. */
#if 0 // UNUSED

#define r8_g8cl_eight_complex_fft8(srcreg,srcinc,d1,d2,d4,dstreg,dstinc,e1,e2,e4,screg) \
	r8_x8c_fft8(srcreg+0,d1,d2,d4,dstreg+0,e1,e2,screg,0); \
	r8_x8c_fft8(srcreg+32,d1,d2,d4,dstreg+e4,e1,e2,screg,0); \
	srcreg += srcinc; \
	dstreg += dstinc; \
\
\

#define r8_x8c_fft8(srcreg,d1,d2,d4,dstreg,e1,e2,screg,scoff) \
	untested - likely buggy; \
	xmm0 = xptr(srcreg);			/* R1 */ \
	xmm2 = xptr(srcreg+d4);		/* R5 */ \
	xmm2 += xmm0;			/* R5 = R1 + R5 (new R1) */ \
\
	xmm1 = xptr(srcreg+d2);		/* R3 */ \
	xmm3 = xptr(srcreg+d4+d2);		/* R7 */ \
	xmm3 += xmm1;			/* R7 = R3 + R7 (new R3) */ \
\
	xmm4 = xptr(srcreg+16);		/* I1 */ \
	xmm6 = xptr(srcreg+d4+16);		/* I5 */ \
	xmm6 += xmm4;			/* I5 = I1 + I5 (new I1) */ \
\
	xmm0 -= xptr(srcreg+d4);		/* R1 = R1 - R5 (new R5) */ \
	xmm1 -= xptr(srcreg+d4+d2);		/* R3 = R3 - R7 (new R7) */ \
\
	xmm5 = xmm3;			/* Copy R3 */ \
	xmm3 += xmm2;			/* R3 = R1 + R3 (final R1) */ \
	xmm2 -= xmm5;			/* R1 = R1 - R3 (final R3) */ \
\
	xmm5 = xptr(srcreg+d2+16);		/* I3 */ \
	xmm7 = xptr(srcreg+d4+d2+16);		/* I7 */ \
	xmm7 += xmm5;			/* I7 = I3 + I7 (new I3) */ \
\
	xmm4 -= xptr(srcreg+d4+16);		/* I1 = I1 - I5 (new I5) */ \
	xmm5 -= xptr(srcreg+d4+d2+16);		/* I3 = I3 - I7 (new I7) */ \
\
	xptr(dstreg) = xmm3;			/* Save R1 */ \
\
	xmm3 = xmm7;			/* Copy I3 */ \
	xmm7 += xmm6;			/* I3 = I1 + I3 (final I1) */ \
	xmm6 -= xmm3;			/* I1 = I1 - I3 (final I3) */ \
\
	xptr(dstreg+16) = xmm7;		/* Save I1 */ \
\
	xmm3 = xmm1;			/* Copy R7 */ \
	xmm1 += xmm4;			/* R7 = I5 + R7 (final I5) */ \
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm5;			/* R5 = R5 - I7 (final R5) */ \
	xmm4 -= xmm3;			/* I5 = I5 - R7 (final I7) */ \
	xmm5 += xmm7;			/* I7 = R5 + I7 (final R7) */ \
\
	xptr(dstreg+e1) = xmm2;		/* Save R3 */ \
	xptr(dstreg+e1+16) = xmm6;		/* Save I3 */ \
	xptr(dstreg+e2) = xmm0;		/* Save R5 */ \
	xptr(dstreg+e2+16) = xmm1;		/* Save I5 */ \
	xptr(dstreg+e2+e1) = xmm5;		/* Save R7 */ \
	xptr(dstreg+e2+e1+16) = xmm4;		/* Save I7 */ \
\
	xmm0 = xptr(srcreg+d1);		/* R2 */ \
	xmm2 = xptr(srcreg+d4+d1);		/* R6 */ \
	xmm2 += xmm0;			/* R6 = R2 + R6 (new R2) */ \
\
	xmm1 = xptr(srcreg+d2+d1);		/* R4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1);		/* R8 */ \
	xmm3 += xmm1;			/* R8 = R4 + R8 (new R4) */ \
\
	xmm4 = xptr(srcreg+d1+16);		/* I2 */ \
	xmm6 = xptr(srcreg+d4+d1+16);		/* I6 */ \
	xmm6 += xmm4;			/* I6 = I2 + I6 (new I2) */ \
\
	xmm0 -= xptr(srcreg+d4+d1);		/* R2 = R2 - R6 (new R6) */ \
	xmm1 -= xptr(srcreg+d4+d2+d1);		/* R4 = R4 - R8 (new R8) */ \
\
	xmm5 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm2;			/* R4 = R2 + R4 (final R2) */ \
	xmm2 -= xmm5;			/* R2 = R2 - R4 (final R4) */ \
\
	xmm5 = xptr(srcreg+d2+d1+16);		/* I4 */ \
	xmm7 = xptr(srcreg+d4+d2+d1+16);	/* I8 */ \
	xmm7 += xmm5;			/* I8 = I4 + I8 (new I4) */ \
\
	xmm4 -= xptr(srcreg+d4+d1+16);		/* I2 = I2 - I6 (new I6) */ \
	xmm5 -= xptr(srcreg+d4+d2+d1+16);	/* I4 = I4 - I8 (new I8) */ \
\
	xptr(dstreg+32) = xmm3;		/* Save R2 */ \
\
	xmm3 = xmm7;			/* Copy I4 */ \
	xmm7 += xmm6;			/* I4 = I2 + I4 (final I2) */ \
	xmm6 -= xmm3;			/* I2 = I2 - I4 (final I4) */ \
\
	xptr(dstreg+48) = xmm7;		/* Save I2 */ \
\
	xmm3 = xmm1;			/* Copy I6 */ \
	xmm1 += xmm4;			/* R8 = I6 + R8 (new I6) */ \
	xmm7 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm5;			/* R6 = R6 - I8 (new R6) */ \
	xmm4 -= xmm3;			/* I6 = I6 - R8 (new I8) */ \
	xmm5 += xmm7;			/* I8 = R6 + I8 (new R8) */ \
\
	xmm3 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm1;			/* R6 = R6 - I6 */ \
	xmm1 += xmm3;			/* I6 = R6 + I6 */ \
	xmm3 = XMM_SQRTHALF2; \
	xmm0 *= xmm3;			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm1 *= xmm3;			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - I8 */ \
	xmm4 += xmm7;			/* I8 = R8 + I8 */ \
	xmm5 *= xmm3;			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm4 *= xmm3;			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	xptr(dstreg+e1+32) = xmm2;		/* Save R4 */ \
	xptr(dstreg+e1+48) = xmm6;		/* Save I4 */ \
\
/* the last level */ \
\
	xmm2 = xptr(dstreg+e2);		/* R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += xptr(dstreg+e2);		/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = xptr(dstreg+e2+16);		/* I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += xptr(dstreg+e2+16);		/* I6 = I5 + I6 (new I5) */ \
\
	xmm6 = xptr(screg+scoff+160+16);	/* cosine/sine */ \
	xmm6 *= xmm2;			/* A6 = R6 * cosine/sine */ \
	xmm6 -= xmm3;			/* A6 = A6 - I6 */ \
	xmm3 *= xptr(screg+scoff+160+16);	/* B6 = I6 * cosine/sine */ \
	xmm3 += xmm2;			/* B6 = B6 + R6 */ \
\
	xmm2 = xptr(dstreg+e2+e1);		/* R7 */ \
	xmm2 -= xmm4;			/* R7 = R7 - I8 (new R7) */ \
	xmm4 += xptr(dstreg+e2+e1);		/* I8 = R7 + I8 (new R8) */ \
\
	xmm7 = xptr(screg+scoff+32+16);	/* cosine/sine */ \
	xmm7 *= xmm0;			/* A5 = R5 * cosine/sine */ \
	xmm7 -= xmm1;			/* A5 = A5 - I5 */ \
	xmm1 *= xptr(screg+scoff+32+16);	/* B5 = I5 * cosine/sine */ \
	xmm1 += xmm0;			/* B5 = B5 + R5 */ \
\
	xmm0 = xptr(dstreg+e2+e1+16);		/* I7 */ \
	xmm0 -= xmm5;			/* I7 = I7 - R8 (new I8) */ \
	xmm5 += xptr(dstreg+e2+e1+16);		/* R8 = I7 + R8 (new I7) */ \
\
	xmm6 *= xptr(screg+scoff+160);		/* A6 = A6 * sine (final R6) */ \
	xptr(dstreg+e2+32) = xmm6;		/* Save R6 */ \
\
	xmm6 = xptr(screg+scoff+96+16);	/* cosine/sine */ \
	xmm6 *= xmm2;			/* A7 = R7 * cosine/sine */ \
	xmm6 -= xmm5;			/* A7 = A7 - I7 */ \
	xmm5 *= xptr(screg+scoff+96+16);	/* B7 = I7 * cosine/sine */ \
	xmm5 += xmm2;			/* B7 = B7 + R7 */ \
\
	xmm3 *= xptr(screg+scoff+160);		/* B6 = B6 * sine (final I6) */ \
	xptr(dstreg+e2+48) = xmm3;		/* Save I6 */ \
\
	xmm7 *= xptr(screg+scoff+32);		/* A5 = A5 * sine (final R5) */ \
	xmm1 *= xptr(screg+scoff+32);		/* B5 = B5 * sine (final I5) */ \
\
	xptr(dstreg+e2) = xmm7;		/* Save R5 */ \
	xptr(dstreg+e2+16) = xmm1;		/* Save I5 */ \
\
	xmm3 = xptr(screg+scoff+224+16);	/* cosine/sine */ \
	xmm3 *= xmm4;			/* A8 = R8 * cosine/sine */ \
	xmm3 -= xmm0;			/* A8 = A8 - I8 */ \
	xmm0 *= xptr(screg+scoff+224+16);	/* B8 = I8 * cosine/sine */ \
	xmm0 += xmm4;			/* B8 = B8 + R8 */ \
\
	xmm6 *= xptr(screg+scoff+96);		/* A7 = A7 * sine (new R7) */ \
	xmm5 *= xptr(screg+scoff+96);		/* B7 = B7 * sine (new I7) */ \
	xmm3 *= xptr(screg+scoff+224);		/* A8 = A8 * sine (new R8) */ \
	xmm0 *= xptr(screg+scoff+224);		/* B8 = B8 * sine (new I8) */ \
\
	xptr(dstreg+e2+e1) = xmm6;		/* Save R7 */ \
	xptr(dstreg+e2+e1+16) = xmm5;		/* Save I7 */ \
	xptr(dstreg+e2+e1+32) = xmm3;		/* Save R8 */ \
	xptr(dstreg+e2+e1+48) = xmm0;		/* Save I8 */ \
\
	xmm3 = xptr(dstreg);			/* R1 */ \
	xmm4 = xptr(dstreg+32);		/* R2 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += xptr(dstreg);			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7 = xptr(dstreg+16);		/* I1 */ \
	xmm0 = xptr(dstreg+48);		/* I2 */ \
	xmm7 -= xmm0;			/* I1 = I1 - I2 (new I2) */ \
	xmm0 += xptr(dstreg+16);		/* I2 = I1 + I2 (new I1) */ \
\
	xmm1 = xptr(screg+scoff+128+16);	/* cosine/sine */ \
	xmm1 *= xmm3;			/* A2 = R2 * cosine/sine */ \
	xmm1 -= xmm7;			/* A2 = A2 - I2 */ \
	xmm7 *= xptr(screg+scoff+128+16);	/* B2 = I2 * cosine/sine */ \
	xmm7 += xmm3;			/* B2 = B2 + R2 */ \
\
	xmm2 = xptr(screg+scoff+0+16);	/* cosine/sine */ \
	xmm2 *= xmm4;			/* A1 = R1 * cosine/sine */ \
	xmm2 -= xmm0;			/* A1 = A1 - I1 */ \
	xmm0 *= xptr(screg+scoff+0+16);	/* B1 = I1 * cosine/sine */ \
	xmm0 += xmm4;			/* B1 = B1 + R1 */ \
\
	xmm1 *= xptr(screg+scoff+128);		/* A2 = A2 * sine (final R2) */ \
	xmm7 *= xptr(screg+scoff+128);		/* B2 = B2 * sine (final I2) */ \
	xmm2 *= xptr(screg+scoff+0);		/* A1 = A1 * sine (final R1) */ \
	xmm0 *= xptr(screg+scoff+0);		/* B1 = B1 * sine (final I1) */ \
\
	xmm5 = xptr(dstreg+e1);		/* R3 */ \
	xmm6 = xptr(dstreg+e1+48);		/* I4 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += xptr(dstreg+e1);		/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = xptr(dstreg+e1+16);		/* I3 */ \
	xmm4 = xptr(dstreg+e1+32);		/* R4 */ \
	xmm3 -= xmm4;			/* I3 = I3 - R4 (final I4) */ \
	xmm4 += xptr(dstreg+e1+16);		/* R4 = I3 + R4 (final I3) */ \
\
	xptr(dstreg+32) = xmm1;		/* Save R2 */ \
	xptr(dstreg+48) = xmm7;		/* Save I2 */ \
	xptr(dstreg) = xmm2;			/* Save R1 */ \
	xptr(dstreg+16) = xmm0;		/* Save I1 */ \
\
	xmm1 = xptr(screg+scoff+64+16);	/* cosine/sine */ \
	xmm1 *= xmm5;			/* A3 = R3 * cosine/sine */ \
	xmm1 -= xmm4;			/* A3 = A3 - I3 */ \
	xmm4 *= xptr(screg+scoff+64+16);	/* B3 = I3 * cosine/sine */ \
	xmm4 += xmm5;			/* B3 = B3 + R3 */ \
\
	xmm7 = xptr(screg+scoff+192+16);	/* cosine/sine */ \
	xmm7 *= xmm6;			/* A4 = R4 * cosine/sine */ \
	xmm7 -= xmm3;			/* A4 = A4 - I4 */ \
	xmm3 *= xptr(screg+scoff+192+16);	/* B4 = I4 * cosine/sine */ \
	xmm3 += xmm6;			/* B4 = B4 + R4 */ \
\
	xmm1 *= xptr(screg+scoff+64);		/* A3 = A3 * sine (final R3) */ \
	xmm4 *= xptr(screg+scoff+64);		/* B3 = B3 * sine (final I3) */ \
	xmm7 *= xptr(screg+scoff+192);		/* A4 = A4 * sine (final R4) */ \
	xmm3 *= xptr(screg+scoff+192);		/* B4 = B4 * sine (final I4) */ \
\
	xptr(dstreg+e1) = xmm1;		/* Save R3 */ \
	xptr(dstreg+e1+16) = xmm4;		/* Save I3 */ \
	xptr(dstreg+e1+32) = xmm7;		/* Save R4 */ \
	xptr(dstreg+e1+48) = xmm3;		/* Save I4 */ \

#endif
\
/* Used in the last levels of pass 1.  Swizzles. */ \

#define r8_sg8cl_eight_complex_fft8(srcreg,srcinc,d1,d2,d4,dstreg,dstinc,e1,e2,e4,screg) \
	r8_s8c_fft8(srcreg+0,d1,d2,d4,dstreg+0,e1,e2,screg,0); \
	r8_s8c_fft8(srcreg+32,d1,d2,d4,dstreg+e4,e1,e2,screg,0); \
	srcreg += srcinc; \
	dstreg += dstinc; \

#if 1  // x86
#define r8_s8c_fft8(srcreg,d1,d2,d4,dstreg,e1,e2,screg,scoff) { \
	xmm0 = xptr(srcreg);			/* R1 */ \
	xmm2 = xptr(srcreg+d4);		/* R5 */ \
	xmm5 = xmm2;			/* Copy R5 */ \
	xmm2 += xmm0;			/* R5 = R1 + R5 (new R1) */ \
\
	xmm1 = xptr(srcreg+d2);		/* R3 */ \
	xmm3 = xptr(srcreg+d4+d2);		/* R7 */ \
	xmm7 = xmm3;			/* Copy R7 */ \
	xmm3 += xmm1;			/* R7 = R3 + R7 (new R3) */ \
\
	xmm4 = xptr(srcreg+16);		/* I1 */ \
	xmm6 = xptr(srcreg+d4+16);		/* I5 */ \
	xmm6 += xmm4;			/* I5 = I1 + I5 (new I1) */ \
\
	xmm0 -= xmm5;			/* R1 = R1 - R5 (new R5) */ \
	xmm1 -= xmm7;			/* R3 = R3 - R7 (new R7) */ \
\
	xmm5 = xmm3;			/* Copy R3 */ \
	xmm3 += xmm2;			/* R3 = R1 + R3 (final R1) */ \
	xmm2 -= xmm5;			/* R1 = R1 - R3 (final R3) */ \
\
	xmm5 = xptr(srcreg+d2+16);		/* I3 */ \
	xmm7 = xptr(srcreg+d4+d2+16);		/* I7 */ \
	xmm7 += xmm5;			/* I7 = I3 + I7 (new I3) */ \
\
	xmm4 -= xptr(srcreg+d4+16);		/* I1 = I1 - I5 (new I5) */ \
	xmm5 -= xptr(srcreg+d4+d2+16);		/* I3 = I3 - I7 (new I7) */ \
\
	vec2f64 saved_R1 = xmm3;			/* Save R1 */ \
\
	xmm3 = xmm7;			/* Copy I3 */ \
	xmm7 += xmm6;			/* I3 = I1 + I3 (final I1) */ \
	xmm6 -= xmm3;			/* I1 = I1 - I3 (final I3) */ \
\
	vec2f64 saved_I1 = xmm7;		/* Save I1 */ \
\
	xmm3 = xmm1;			/* Copy R7 */ \
	xmm1 += xmm4;			/* R7 = I5 + R7 (final I5) */ \
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm5;			/* R5 = R5 - I7 (final R5) */ \
	xmm4 -= xmm3;			/* I5 = I5 - R7 (final I7) */ \
	xmm5 += xmm7;			/* I7 = R5 + I7 (final R7) */ \
\
	vec2f64 saved_R3 = xmm2;		/* Save R3 */ \
	vec2f64 saved_I3 = xmm6;		/* Save I3 */ \
	vec2f64 saved_R5 = xmm0;		/* Save R5 */ \
	vec2f64 saved_I5 = xmm1;		/* Save I5 */ \
	vec2f64 saved_R7 = xmm5;		/* Save R7 */ \
	vec2f64 saved_I7 = xmm4;		/* Save I7 */ \
\
	xmm0 = xptr(srcreg+d1);		/* R2 */ \
	xmm2 = xptr(srcreg+d4+d1);		/* R6 */ \
	xmm2 += xmm0;			/* R6 = R2 + R6 (new R2) */ \
\
	xmm1 = xptr(srcreg+d2+d1);		/* R4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1);		/* R8 */ \
	xmm3 += xmm1;			/* R8 = R4 + R8 (new R4) */ \
\
	xmm4 = xptr(srcreg+d1+16);		/* I2 */ \
	xmm6 = xptr(srcreg+d4+d1+16);		/* I6 */ \
	xmm6 += xmm4;			/* I6 = I2 + I6 (new I2) */ \
\
	xmm0 -= xptr(srcreg+d4+d1);		/* R2 = R2 - R6 (new R6) */ \
	xmm1 -= xptr(srcreg+d4+d2+d1);		/* R4 = R4 - R8 (new R8) */ \
\
	xmm5 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm2;			/* R4 = R2 + R4 (final R2) */ \
	xmm2 -= xmm5;			/* R2 = R2 - R4 (final R4) */ \
\
	xmm5 = xptr(srcreg+d2+d1+16);		/* I4 */ \
	xmm7 = xptr(srcreg+d4+d2+d1+16);	/* I8 */ \
	xmm7 += xmm5;			/* I8 = I4 + I8 (new I4) */ \
\
	xmm4 -= xptr(srcreg+d4+d1+16);		/* I2 = I2 - I6 (new I6) */ \
	xmm5 -= xptr(srcreg+d4+d2+d1+16);	/* I4 = I4 - I8 (new I8) */ \
\
	vec2f64 saved_R2 = xmm3;		/* Save R2 */ \
\
	xmm3 = xmm7;			/* Copy I4 */ \
	xmm7 += xmm6;			/* I4 = I2 + I4 (final I2) */ \
	xmm6 -= xmm3;			/* I2 = I2 - I4 (final I4) */ \
\
	vec2f64 saved_I2 = xmm7;		/* Save I2 */ \
\
	xmm3 = xmm1;			/* Copy I6 */ \
	xmm1 += xmm4;			/* R8 = I6 + R8 (new I6) */ \
	xmm7 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm5;			/* R6 = R6 - I8 (new R6) */ \
	xmm4 -= xmm3;			/* I6 = I6 - R8 (new I8) */ \
	xmm5 += xmm7;			/* I8 = R6 + I8 (new R8) */ \
\
	xmm3 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm1;			/* R6 = R6 - I6 */ \
	xmm1 += xmm3;			/* I6 = R6 + I6 */ \
	xmm3 = XMM_SQRTHALF2; \
	xmm0 *= xmm3;			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm1 *= xmm3;			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - I8 */ \
	xmm4 += xmm7;			/* I8 = R8 + I8 */ \
	xmm5 *= xmm3;			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm4 *= xmm3;			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	vec2f64 saved_R4 = xmm2;		/* Save R4 */ \
	vec2f64 saved_I4 = xmm6;		/* Save I4 */ \
\
/* the last level */ \
\
	xmm2 = saved_R5;		/* R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += saved_R5;		/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = saved_I5;		/* I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += saved_I5;		/* I6 = I5 + I6 (new I5) */ \
\
	xmm6 = xptr(screg+scoff+160+16);	/* cosine/sine */ \
	xmm6 *= xmm2;			/* A6 = R6 * cosine/sine */ \
	xmm6 -= xmm3;			/* A6 = A6 - I6 */ \
	xmm3 *= xptr(screg+scoff+160+16);	/* B6 = I6 * cosine/sine */ \
	xmm3 += xmm2;			/* B6 = B6 + R6 */ \
\
	xmm2 = saved_R7;		/* R7 */ \
	xmm2 -= xmm4;			/* R7 = R7 - I8 (new R7) */ \
	xmm4 += saved_R7;		/* I8 = R7 + I8 (new R8) */ \
\
	xmm7 = xptr(screg+scoff+32+16);	/* cosine/sine */ \
	xmm7 *= xmm0;			/* A5 = R5 * cosine/sine */ \
	xmm7 -= xmm1;			/* A5 = A5 - I5 */ \
	xmm1 *= xptr(screg+scoff+32+16);	/* B5 = I5 * cosine/sine */ \
	xmm1 += xmm0;			/* B5 = B5 + R5 */ \
\
	xmm0 = saved_I7;		/* I7 */ \
	xmm0 -= xmm5;			/* I7 = I7 - R8 (new I8) */ \
	xmm5 += saved_I7;		/* R8 = I7 + R8 (new I7) */ \
\
	xmm6 *= xptr(screg+scoff+160);		/* A6 = A6 * sine (final R6) */ \
	xmm7 *= xptr(screg+scoff+32);		/* A5 = A5 * sine (final R5) */ \
	shuffle_store(xptr(dstreg+e2), xptr(dstreg+e2+16), xmm7, xmm6);	/* Save R5,R6 */ \
\
	xmm6 = xptr(screg+scoff+96+16);	/* cosine/sine */ \
	xmm6 *= xmm2;			/* A7 = R7 * cosine/sine */ \
	xmm6 -= xmm5;			/* A7 = A7 - I7 */ \
	xmm5 *= xptr(screg+scoff+96+16);	/* B7 = I7 * cosine/sine */ \
	xmm5 += xmm2;			/* B7 = B7 + R7 */ \
\
	xmm3 *= xptr(screg+scoff+160);		/* B6 = B6 * sine (final I6) */ \
	xmm1 *= xptr(screg+scoff+32);		/* B5 = B5 * sine (final I5) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e2+32), xptr(dstreg+e2+48), xmm1, xmm3, xmm7); /* Save I5,I6 */ \
\
	xmm3 = xptr(screg+scoff+224+16);	/* cosine/sine */ \
	xmm3 *= xmm4;			/* A8 = R8 * cosine/sine */ \
	xmm3 -= xmm0;			/* A8 = A8 - I8 */ \
	xmm0 *= xptr(screg+scoff+224+16);	/* B8 = I8 * cosine/sine */ \
	xmm0 += xmm4;			/* B8 = B8 + R8 */ \
\
	xmm6 *= xptr(screg+scoff+96);		/* A7 = A7 * sine (new R7) */ \
	xmm5 *= xptr(screg+scoff+96);		/* B7 = B7 * sine (new I7) */ \
	xmm3 *= xptr(screg+scoff+224);		/* A8 = A8 * sine (new R8) */ \
	xmm0 *= xptr(screg+scoff+224);		/* B8 = B8 * sine (new I8) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e2+e1), xptr(dstreg+e2+e1+16), xmm6, xmm3, xmm4);	/* Save R7,R8 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+e1+32), xptr(dstreg+e2+e1+48), xmm5, xmm0, xmm4);	/* Save I7,I8 */ \
\
	xmm3 = saved_R1;			/* R1 */ \
	xmm4 = saved_R2;		/* R2 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += saved_R1;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7 = saved_I1;		/* I1 */ \
	xmm0 = saved_I2;		/* I2 */ \
	xmm7 -= xmm0;			/* I1 = I1 - I2 (new I2) */ \
	xmm0 += saved_I1;		/* I2 = I1 + I2 (new I1) */ \
\
	xmm1 = xptr(screg+scoff+128+16);	/* cosine/sine */ \
	xmm1 *= xmm3;			/* A2 = R2 * cosine/sine */ \
	xmm1 -= xmm7;			/* A2 = A2 - I2 */ \
	xmm7 *= xptr(screg+scoff+128+16);	/* B2 = I2 * cosine/sine */ \
	xmm7 += xmm3;			/* B2 = B2 + R2 */ \
\
	xmm2 = xptr(screg+scoff+0+16);	/* cosine/sine */ \
	xmm2 *= xmm4;			/* A1 = R1 * cosine/sine */ \
	xmm2 -= xmm0;			/* A1 = A1 - I1 */ \
	xmm0 *= xptr(screg+scoff+0+16);	/* B1 = I1 * cosine/sine */ \
	xmm0 += xmm4;			/* B1 = B1 + R1 */ \
\
	xmm1 *= xptr(screg+scoff+128);		/* A2 = A2 * sine (final R2) */ \
	xmm7 *= xptr(screg+scoff+128);		/* B2 = B2 * sine (final I2) */ \
	xmm2 *= xptr(screg+scoff+0);		/* A1 = A1 * sine (final R1) */ \
	xmm0 *= xptr(screg+scoff+0);		/* B1 = B1 * sine (final I1) */ \
\
	xmm5 = saved_R3;		/* R3 */ \
	xmm6 = saved_I4;		/* I4 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += saved_R3;		/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = saved_I3;		/* I3 */ \
	xmm4 = saved_R4;		/* R4 */ \
	xmm3 -= xmm4;			/* I3 = I3 - R4 (final I4) */ \
	xmm4 += saved_I3;		/* R4 = I3 + R4 (final I3) */ \
\
	shuffle_store(xptr(dstreg), xptr(dstreg+16), xmm2, xmm1);				/* Save R1,R2 */ \
	shuffle_store_with_temp(xptr(dstreg+32), xptr(dstreg+48), xmm0, xmm7, xmm1);	/* Save I1,I2 */ \
\
	xmm1 = xptr(screg+scoff+64+16);	/* cosine/sine */ \
	xmm1 *= xmm5;			/* A3 = R3 * cosine/sine */ \
	xmm1 -= xmm4;			/* A3 = A3 - I3 */ \
	xmm4 *= xptr(screg+scoff+64+16);	/* B3 = I3 * cosine/sine */ \
	xmm4 += xmm5;			/* B3 = B3 + R3 */ \
\
	xmm7 = xptr(screg+scoff+192+16);	/* cosine/sine */ \
	xmm7 *= xmm6;			/* A4 = R4 * cosine/sine */ \
	xmm7 -= xmm3;			/* A4 = A4 - I4 */ \
	xmm3 *= xptr(screg+scoff+192+16);	/* B4 = I4 * cosine/sine */ \
	xmm3 += xmm6;			/* B4 = B4 + R4 */ \
\
	xmm1 *= xptr(screg+scoff+64);		/* A3 = A3 * sine (final R3) */ \
	xmm4 *= xptr(screg+scoff+64);		/* B3 = B3 * sine (final I3) */ \
	xmm7 *= xptr(screg+scoff+192);		/* A4 = A4 * sine (final R4) */ \
	xmm3 *= xptr(screg+scoff+192);		/* B4 = B4 * sine (final I4) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e1), xptr(dstreg+e1+16), xmm1, xmm7, xmm0);		/* Save R3,R4 */ \
	shuffle_store_with_temp(xptr(dstreg+e1+32), xptr(dstreg+e1+48), xmm4, xmm3, xmm0);	/* Save I3,I4 */ \
}

#else // X86_64
#define r8_s8c_fft8(srcreg,d1,d2,d4,dstreg,e1,e2,screg,scoff) { \
	vec2f64 xmm8,xmm9,xmm10,xmm11,xmm12,xmm13,xmm14,xmm15; \
	xmm0 = xptr(srcreg);			/* R1 */ \
	xmm1 = xptr(srcreg+d4);		/* R5 */ \
	xmm2 = xmm0;			/* Copy R1			; 1-3 */ \
	xmm0 += xmm1;			/* R1 = R1 + R5 (new R1)	; 1-3 */ \
\
	xmm3 = xptr(srcreg+d2);		/* R3 */ \
	xmm4 = xptr(srcreg+d4+d2);		/* R7 */ \
	xmm5 = xmm3;			/* Copy R3			; 2-4 */ \
	xmm3 += xmm4;			/* R3 = R3 + R7 (new R3)	; 2-4 */ \
\
	xmm6 = xptr(srcreg+16);		/* I1 */ \
	xmm7 = xptr(srcreg+d4+16);		/* I5 */ \
	xmm8 = xmm6;			/* Copy I1			; 3-5 */ \
	xmm6 += xmm7;			/* I1 = I1 + I5 (new I1)	; 3-5 */ \
\
	xmm9 = xptr(srcreg+d2+16);		/* I3 */ \
	xmm10 = xptr(srcreg+d4+d2+16);	/* I7 */ \
	xmm11 = xmm9;			/* Copy I3			; 4-6 */ \
	xmm9 += xmm10;			/* I3 = I3 + I7 (new I3)	; 4-6 */ \
\
	xmm2 -= xmm1;			/* R5 = R1 - R5 (new R5)	; 5-7 */ \
\
	xmm5 -= xmm4;			/* R7 = R3 - R7 (new R7)	; 6-8 */ \
\
	xmm8 -= xmm7;			/* I5 = I1 - I5 (new I5)	; 7-9 */ \
	xmm1 = xmm0;			/* Copy R1			; 7-9 (4) */ \
\
	xmm11 -= xmm10;			/* I7 = I3 - I7 (new I7)	; 8-10	avail 4,7,10,12+ */ \
	xmm12 = xptr(srcreg+d1);		/* R2				; 8 */ \
\
	xmm0 -= xmm3;			/* R1 = R1 - R3 (final R3)	; 9-11 */ \
	xmm4 = xmm6;			/* Copy I1			; 9-11 (6) avail 7,10,13+ */ \
	xmm13 = xptr(srcreg+d4+d1);		/* R6				; 9 */ \
\
	xmm3 += xmm1;			/* R3 = R1 + R3 (final R1)	; 10-12	avail 7,10,1,14+ */ \
	xmm14 = xptr(srcreg+d2+d1);		/* R4				; 10 */ \
\
	xmm6 -= xmm9;			/* I1 = I1 - I3 (final I3)	; 11-13 */ \
	xmm1 = xmm8;			/* Copy I5			; 11-13 (10) avail 7,10,15 */ \
	xmm15 = xptr(srcreg+d4+d2+d1);	/* R8				; 11 */ \
\
	xmm9 += xmm4;			/* I3 = I1 + I3 (final I1)	; 12-14	avail 7,10,4 */ \
	vec2f64 saved_R3 = xmm0;		/* Save R3			; 12	avail 7,10,4,0 */ \
\
	xmm8 -= xmm5;			/* I5 = I5 - R7 (final I7)	; 13-15 */ \
	xmm4 = xmm2;			/* Copy R5			; 13-15 (8) avail 7,10,0 */ \
\
	xmm5 += xmm1;			/* R7 = I5 + R7 (final I5)	; 14-16	avail 7,10,0,1 */ \
	xmm7 = xptr(srcreg+d1+16);		/* I2				; 14	avail 10,0,1 */ \
	vec2f64 saved_I3 = xmm6;		/* Save I3			; 14	avail 10,0,1,6 */ \
\
	xmm2 -= xmm11;			/* R5 = R5 - I7 (final R5)	; 15-17 */ \
	xmm1 = xmm12;			/* Copy R2			; 15-17	avail 10,0,6 */ \
	xmm10 = xptr(srcreg+d4+d1+16);	/* I6				; 15	avail 0,6 */ \
\
	xmm11 += xmm4;			/* I7 = R5 + I7 (final R7)	; 16-18	avail 0,6,4 */ \
	xmm6 = xptr(srcreg+d2+d1+16);		/* I4				; 16	avail 0,4 */ \
	vec2f64 saved_I7 = xmm8;		/* Save I7			; 16	avail 0,4,8 */ \
\
	xmm12 += xmm13;			/* R2 = R2 + R6 (new R2)	; 17-19 */ \
	xmm4 = xmm14;			/* Copy R4			; 17-19	avail 0,8 */ \
	vec2f64 saved_I5 = xmm5;		/* Save I5			; 17	avail 0,8,5 */ \
\
	xmm1 -= xmm13;			/* R6 = R2 - R6 (new R6)	; 18-20	avail 0,8,5,13 */ \
	xmm0 = XMM_SQRTHALF2;						/* 18	avail 8,5,13 */ \
	vec2f64 saved_R5 = xmm2;		/* Save R5			; 18	avail 8,5,13,2 */ \
\
	xmm14 += xmm15;			/* R4 = R4 + R8 (new R4)	; 19-21 */ \
	xmm2 = xmm7;			/* Copy I2			; 19-21	avail 8,5,13 */ \
	vec2f64 saved_R7 = xmm11;		/* Save R7			; 19	avail 8,5,13,11 */ \
\
	xmm4 -= xmm15;			/* R8 = R4 - R8 (new R8)	; 20-22	avail 8,5,13,11,15 */ \
	xmm8 = xptr(srcreg+d4+d2+d1+16);	/* I8				; 18	avail 5,13,11,15 */ \
\
	xmm7 += xmm10;			/* I2 = I2 + I6 (new I2)	; 21-23 */ \
	xmm5 = xmm6;			/* Copy I4			; 21-23	avail 13,11,15 */ \
	xmm1 *= xmm0;			/* R6 = R6 * SQRTHALF		; 21-25 */ \
\
	xmm2 -= xmm10;			/* I6 = I2 - I6 (new I6)	; 22-24	avail 13,11,15,10 */ \
\
	xmm6 += xmm8;			/* I4 = I4 + I8 (new I4)	; 23-25 */ \
	xmm4 *= xmm0;			/* R8 = R8 * SQRTHALF		; 23-27 */ \
\
	xmm5 -= xmm8;			/* I8 = I4 - I8 (new I8)	; 24-26	avail 13,11,15,10,8 */ \
	xmm8 = xmm12;			/* Copy R2			; 24-26	avail 13,11,15,10 */ \
\
	xmm12 += xmm14;			/* R2 = R2 + R4 (final R2)	; 25-27 */ \
	xmm10 = xmm7;			/* Copy I2			; 25-27	avail 13,11,15 */ \
	xmm2 *= xmm0;			/* I6 = I6 * SQRTHALF		; 25-29 */ \
\
	xmm7 += xmm6;			/* I2 = I2 + I4 (final I2)	; 26-28 */ \
	xmm11 = xptr(screg+scoff+128+16);	/* cosine/sine 2		; 26	avail 13,15 */ \
\
	xmm8 -= xmm14;			/* R4 = R2 - R4 (final R4)	; 27-29	avail 13,15,14 */ \
	xmm5 *= xmm0;			/* I8 = I8 * SQRTHALF		; 27-31	avail 13,15,14,0 */ \
	xmm0 = xmm3;			/* Copy R1			; 27-29	avail 13,15,14 */ \
\
	xmm10 -= xmm6;			/* I4 = I2 - I4 (final I4)	; 28-30	avail 13,15,14,6 */ \
	xmm15 = xptr(screg+scoff+0+16);	/* cosine/sine 1		; 28	avail 13,14,6 */ \
\
	xmm3 -= xmm12;			/* R1 = R1 - R2 (new R2)	; 29-31 */ \
	xmm6 = xmm9;			/* Copy I1			; 29-31	avail 13,14 */ \
\
	xmm12 += xmm0;			/* R2 = R1 + R2 (new R1)	; 30-32	avail 13,14,0 */ \
	xmm0 = xmm4;			/* Copy R8			; 30-32 (28) avail 13,14 */ \
\
	xmm9 -= xmm7;			/* I1 = I1 - I2 (new I2)	; 31-33 */ \
	xmm13 = xmm1;			/* Copy R6			; 31-33 (26) avail 14 */ \
\
	xmm7 += xmm6;			/* I2 = I1 + I2 (new I1)	; 32-34	avail 14,6 */ \
	xmm6 = xmm3;			/* Copy R2			; 32-34	avail 14 */ \
	xmm3 *= xmm11;			/* A2 = R2 * cosine/sine	; 32-36 */ \
\
	xmm4 += xmm2;			/* R8 = I6 + R8 (new I6)	; 33-35 */ \
	xmm14 = xmm12;			/* Copy R1			; 33-35	avail none */ \
	xmm12 *= xmm15;			/* A1 = R1 * cosine/sine	; 33-37 */ \
\
	xmm1 -= xmm5;			/* R6 = R6 - I8 (new R6)	; 34-36 */ \
	xmm11 *= xmm9;			/* B2 = I2 * cosine/sine	; 34-38 */ \
\
	xmm2 -= xmm0;			/* I6 = I6 - R8 (new I8)	; 35-37	avail 0 */ \
	xmm15 *= xmm7;			/* B1 = I1 * cosine/sine	; 35-39 */ \
\
	xmm5 += xmm13;			/* I8 = R6 + I8 (new R8)	; 36-38	avail 0,13 */ \
	xmm0 = xptr(screg+scoff+128);		/* sine 2			; 36	avail 13 */ \
\
	xmm3 -= xmm9;			/* A2 = A2 - I2			; 37-39	avail 13,9 */ \
	xmm9 = saved_R3;		/* Reload R3			; 37	avail 13 */ \
\
	xmm12 -= xmm7;			/* A1 = A1 - I1			; 38-40	avail 13,7 */ \
	xmm13 = xptr(screg+scoff+0);		/* sine 1			; 38	avail 7 */ \
\
	xmm11 += xmm6;			/* B2 = B2 + R2			; 39-41	avail 7,6 */ \
	xmm6 = xmm10;			/* Copy I4			; 39-41	avail 7 */ \
	xmm7 = saved_I3;		/* Reload I3			; 39	avail none */ \
\
	xmm15 += xmm14;			/* B1 = B1 + R1			; 40-42	avail 14 */ \
	xmm3 *= xmm0;			/* A2 = A2 * sine (final R2)	; 40-44 */ \
\
	xmm10 += xmm9;			/* I4 = R3 + I4 (new R4)	; 41-43 */ \
	xmm12 *= xmm13;			/* A1 = A1 * sine (final R1)	; 41-45 */ \
	xmm14 = xmm8;			/* Copy R4			; 41-43	avail none */ \
\
	xmm9 -= xmm6;			/* R3 = R3 - I4 (new R3)	; 42-44	avail 6 */ \
	xmm11 *= xmm0;			/* B2 = B2 * sine (final I2)	; 42-46	avail 6,0 */ \
	xmm0 = xmm1;			/* Copy R6			; 42-44 (37) avail 6 */ \
	xmm6 = xptr(screg+scoff+192+16);	/* cosine/sine 4		; 42	avail none */ \
\
	xmm8 += xmm7;			/* R4 = I3 + R4 (new I3)	; 43-45 */ \
	xmm15 *= xmm13;			/* B1 = B1 * sine (final I1)	; 43-47	avail 13 */ \
	xmm13 = xmm5;			/* Copy R8			; 43-45 (39) avail none */ \
\
	xmm7 -= xmm14;			/* I3 = I3 - R4 (new I4)	; 44-46	avail 14 */ \
	xmm14 = xmm10;			/* Copy R4			; 44-46	avail 3,12 */ \
	xmm10 *= xmm6;			/* A4 = R4 * cosine/sine	; 44-48 */ \
\
	xmm1 -= xmm4;			/* R6 = R6 - I6			; 45-47 */ \
	shuffle_store(xptr(dstreg), xptr(dstreg+16), xmm12, xmm3);			/* Save R1,R2 starting at clock 46 */ \
	xmm3 = xptr(screg+scoff+64+16);	/* cosine/sine 3		; 45	avail 12 */ \
	xmm12 = xmm9;			/* Copy R3			; 45-47	avail none */ \
	xmm9 *= xmm3;			/* A3 = R3 * cosine/sine	; 45-49 */ \
\
	xmm4 += xmm0;			/* I6 = R6 + I6			; 46-48	avail 0 */ \
	xmm3 *= xmm8;			/* B3 = I3 * cosine/sine	; 46-50 */ \
\
	xmm5 -= xmm2;			/* R8 = R8 - I8			; 47-49 */ \
	xmm6 *= xmm7;			/* B4 = I4 * cosine/sine	; 47-51 */ \
\
	xmm2 += xmm13;			/* I8 = R8 + I8			; 48-50	avail 0,13 */ \
\
	xmm10 -= xmm7;			/* A4 = A4 - I4			; 49-51	avail 0,13,7 */ \
	xmm7 = xptr(screg+scoff+192);		/* sine 4			; 49	avail 0,13 */ \
\
	xmm9 -= xmm8;			/* A3 = A3 - I3			; 50-52	avail 0,13,8 */ \
	xmm8 = xptr(screg+scoff+64);		/* sine 3			; 50	avail 0,13 */ \
\
	shuffle_store_with_temp(xptr(dstreg+32), xptr(dstreg+48), xmm15, xmm11, xmm0);	/* Save I1,I2 starting at clock 50 */ \
\
	xmm3 += xmm12;			/* B3 = B3 + R3			; 51-53	avail 0,13,15,11,12 */ \
	xmm0 = xmm1;			/* Copy R6			; 51-53	avail 13,15,11,12 */ \
	xmm13 = saved_R5;		/* Reload R5 */ \
\
	xmm6 += xmm14;			/* B4 = B4 + R4			; 52-54	avail 15,11,12,14 */ \
	xmm10 *= xmm7;			/* A4 = A4 * sine (final R4)	; 52-56 */ \
	xmm15 = saved_I5;		/* Reload I5			; 52	avail 11,12,14 */ \
\
	xmm1 += xmm13;			/* R6 = R5 + R6 (new R5)	; 53-55 */ \
	xmm9 *= xmm8;			/* A3 = A3 * sine (final R3)	; 53-57 */ \
	xmm11 = xmm4;			/* Copy I6			; 53-55	avail 12,14 */ \
	xmm14 = xptr(screg+scoff+32+16);	/* cosine/sine 5		; 53	avail 12 */ \
\
	xmm13 -= xmm0;			/* R5 = R5 - R6 (new R6)	; 54-56	avail 12,0 */ \
	xmm3 *= xmm8;			/* B3 = B3 * sine (final I3)	; 54-58 avail 12,0,8 */ \
	xmm0 = xmm2;			/* Copy I8			; 54-56 (51) avail 12,8 */ \
	xmm12 = saved_R7;		/* Reload R7			; 54	avail 8 */ \
\
	xmm4 += xmm15;			/* I6 = I5 + I6 (new I5)	; 55-57 */ \
	xmm6 *= xmm7;			/* B4 = B4 * sine (final I4)	; 55-59 avail 8,7 */ \
	xmm7 = xmm5;			/* Copy R8			; 57-59 (50) avail 8 */ \
\
	xmm15 -= xmm11;			/* I5 = I5 - I6 (new I6)	; 56-58 avail 8,11 */ \
	xmm8 = xmm1;			/* Copy R5			; 56-58 avail 11 */ \
	xmm1 *= xmm14;			/* A5 = R5 * cosine/sine	; 56-60 */ \
	xmm11 = xptr(screg+scoff+160+16);	/* cosine/sine 6		; 56	avail none */ \
\
	xmm2 += xmm12;			/* I8 = R7 + I8 (new R8)	; 57-59 */ \
	shuffle_store(xptr(dstreg+e1), xptr(dstreg+e1+16), xmm9, xmm10);			/* Save R3,R4 starting at clock 58 */ \
	xmm9 = xmm13;			/* Copy R6			; 57-59	avail 10 */ \
	xmm13 *= xmm11;			/* A6 = R6 * cosine/sine	; 57-61 */ \
\
	xmm12 -= xmm0;			/* R7 = R7 - I8 (new R7)	; 58-60 avail 10,0 */ \
	xmm14 *= xmm4;			/* B5 = I5 * cosine/sine	; 58-62 */ \
	xmm10 = saved_I7;	/* Reload I7			; 58	avail 0 */ \
\
	xmm5 += xmm10;			/* R8 = I7 + R8 (new I7)	; 59-61 */ \
	xmm11 *= xmm15;			/* B6 = I6 * cosine/sine	; 59-63 */ \
	xmm0 = xptr(screg+scoff+224+16);	/* cosine/sine 8		; 59	avail none */ \
\
	xmm10 -= xmm7;			/* I7 = I7 - R8 (new I8)	; 60-62 avail 7 */ \
	xmm7 = xmm2;			/* Copy R8 */ \
	xmm2 *= xmm0;			/* A8 = R8 * cosine/sine	; 60-64	avail none */ \
\
	shuffle_store(xptr(dstreg+e1+32), xptr(dstreg+e1+48), xmm3, xmm6);		/* Save I3,I4 starting at clock 60 */ \
\
	xmm1 -= xmm4;			/* A5 = A5 - I5			; 61-63	avail 3,6,4 */ \
	xmm3 = xptr(screg+scoff+96+16);	/* cosine/sine 7		; 61	avail 6,4 */ \
	xmm6 = xmm12;			/* Copy R7			; 61-63	avail 4 */ \
	xmm12 *= xmm3;			/* A7 = R7 * cosine/sine	; 61-65 */ \
\
	xmm13 -= xmm15;			/* A6 = A6 - I6			; 62-64	avail 4,15 */ \
	xmm3 *= xmm5;			/* B7 = I7 * cosine/sine	; 62-66 */ \
	xmm4 = xptr(screg+scoff+32);		/* sine 5			; 62	avail 15 */ \
\
	xmm14 += xmm8;			/* B5 = B5 + R5			; 63-65	avail 15,8 */ \
	xmm0 *= xmm10;			/* B8 = I8 * cosine/sine	; 63-67 */ \
	xmm15 = xptr(screg+scoff+160);	/* sine 6			; 63	avail 8 */ \
\
	xmm11 += xmm9;			/* B6 = B6 + R6			; 64-66	avail 8,9 */ \
	xmm1 *= xmm4;			/* A5 = A5 * sine (final R5)	; 64-68 */ \
	xmm8 = xptr(screg+scoff+224);		/* sine 8			; 64	avail 9 */ \
\
	xmm2 -= xmm10;			/* A8 = A8 - I8			; 65-67	avail 9,10 */ \
	xmm13 *= xmm15;			/* A6 = A6 * sine (final R6)	; 65-69 */ \
	xmm9 = xptr(screg+scoff+96);		/* sine	7			; 65	avail 10 */ \
\
	xmm12 -= xmm5;			/* A7 = A7 - I7			; 66-68	avail 10,5 */ \
	xmm14 *= xmm4;			/* B5 = B5 * sine (final I5)	; 66-70	avail 10,5,4 */ \
\
	xmm3 += xmm6;			/* B7 = B7 + R7			; 67-69	avail 10,5,4,6 */ \
	xmm11 *= xmm15;			/* B6 = B6 * sine (final I6)	; 67-71	avail 10,5,4,6,15 */ \
\
	xmm0 += xmm7;			/* B8 = B8 + R8			; 68-70	avail 10,5,4,6,15,7 */ \
	xmm2 *= xmm8;			/* A8 = A8 * sine (final R8)	; 68-72 */ \
\
	xmm12 *= xmm9;			/* A7 = A7 * sine (final R7)	; 69-73 */ \
	xmm3 *= xmm9;			/* B7 = B7 * sine (final I7)	; 70-74	avail 10,5,4,6,15,7,9 */ \
	xmm0 *= xmm8;			/* B8 = B8 * sine (final I8)	; 71-75	avail 10,5,4,6,15,7,9,8 */ \
\
	shuffle_store_with_temp(xptr(dstreg+e2), xptr(dstreg+e2+16), xmm1, xmm13, xmm4); /* Save R5,R6 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+32), xptr(dstreg+e2+48), xmm14, xmm11, xmm4); /* Save I5,I6 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+e1), xptr(dstreg+e2+e1+16), xmm12, xmm2, xmm4); /* Save R7,R8 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+e1+32), xptr(dstreg+e2+e1+48), xmm3, xmm0, xmm4); /* Save I7,I8 */ \
}


#endif
\
/* */ \
/* ************************************* eight-complex-unfft8 variants ****************************************** */ \
/* */ \
\
/* */ \
/* Radix-8 inverse FFT building block for negacyclic delayed twiddle multipliers from the first few levels (r4delay). */ \
/* Has 8 premult/sin/cos multipliers. */ \
/* */ \
\
/* Used in the last levels of pass 1.  No swizzling. */
#if 0 // UNUSED

#define r8_g4cl_eight_complex_unfft8(srcreg,srcinc,d1,d2,dstreg,dstinc,e1,e2,screg) \
	xmm7 = xptr(screg+0+16);		/* cosine/sine */ \
	xmm7 *= xptr(srcreg);			/* A1 = R1 * cosine/sine */ \
	xmm3 = xptr(screg+128+16);		/* cosine/sine */ \
	xmm3 *= xptr(srcreg+32);		/* A2 = R2 * cosine/sine */ \
	xmm0 = xptr(screg+64+16);		/* cosine/sine */ \
	xmm0 *= xptr(srcreg+d1);		/* A3 = R3 * cosine/sine */ \
	xmm1 = xptr(screg+192+16);		/* cosine/sine */ \
	xmm1 *= xptr(srcreg+d1+32);		/* A4 = R4 * cosine/sine */ \
\
	xmm2 = xptr(srcreg+16);		/* I1 */ \
	xmm7 += xmm2;			/* A1 = A1 + I1 */ \
	xmm2 *= xptr(screg+0+16);		/* B1 = I1 * cosine/sine */ \
	xmm4 = xptr(srcreg+48);		/* I2 */ \
	xmm3 += xmm4;			/* A2 = A2 + I2 */ \
	xmm4 *= xptr(screg+128+16);		/* B2 = I2 * cosine/sine */ \
	xmm6 = xptr(srcreg+d1+16); \
	xmm0 += xmm6;			/* A3 = A3 + I3 */ \
	xmm6 *= xptr(screg+64+16);		/* B3 = I3 * cosine/sine */ \
\
	xmm7 *= xptr(screg+0);			/* A1 = A1 * sine (new R1) */ \
	xmm3 *= xptr(screg+128);		/* A2 = A2 * sine (new R2) */ \
\
	xmm5 = xmm7;			/* Copy R1 */ \
	xmm7 -= xmm3;			/* R1 = R1 - R2 (new R2) */ \
	xmm3 += xmm5;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5 = xptr(srcreg+d1+48);		/* I4 */ \
	xmm1 += xmm5;	 		/* A4 = A4 + I4 */ \
	xmm5 *= xptr(screg+192+16);		/* B4 = I4 * cosine/sine */ \
\
	xmm2 -= xptr(srcreg);			/* B1 = B1 - R1 */ \
	xmm4 -= xptr(srcreg+32);		/* B2 = B2 - R2 */ \
	xmm6 -= xptr(srcreg+d1);		/* B3 = B3 - R3 */ \
	xmm0 *= xptr(screg+64);		/* A3 = A3 * sine (new R3) */ \
	xmm5 -= xptr(srcreg+d1+32);		/* B4 = B4 - R4 */ \
	xmm1 *= xptr(screg+192);		/* A4 = A4 * sine (new R4) */ \
\
	xptr(dstreg+e1) = xmm7;		/* R2 */ \
\
	xmm2 *= xptr(screg+0);			/* B1 = B1 * sine (new I1) */ \
	xmm4 *= xptr(screg+128);		/* B2 = B2 * sine (new I2) */ \
	xmm6 *= xptr(screg+64);		/* B3 = B3 * sine (new I3) */ \
	xmm5 *= xptr(screg+192);		/* B4 = B4 * sine (new I4) */ \
\
	xmm7 = xmm1;			/* Copy R4 */ \
	xmm1 -= xmm0;			/* R4 = R4 - R3 (new I4) */ \
	xmm0 += xmm7;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7 = xmm2;			/* Copy I1 */ \
	xmm2 -= xmm4;			/* I1 = I1 - I2 (new I2) */ \
	xmm4 += xmm7;			/* I2 = I1 + I2 (new I1) */ \
\
	xmm7 = xmm6;			/* Copy I3 */ \
	xmm6 -= xmm5;			/* I3 = I3 - I4 (new R4) */ \
	xmm5 += xmm7;			/* I4 = I3 + I4 (new I3) */ \
\
	xmm7 = xptr(screg+32+16);		/* cosine/sine */ \
	xmm7 *= xptr(srcreg+d2);		/* A5 = R5 * cosine/sine */ \
	xptr(dstreg) = xmm3;			/* R1 */ \
	xmm3 = xptr(screg+160+16);		/* cosine/sine */ \
	xmm3 *= xptr(srcreg+d2+32);		/* A6 = R6 * cosine/sine */ \
	xptr(dstreg+e2) = xmm0;		/* R3 */ \
	xmm0 = xptr(screg+96+16);		/* cosine/sine */ \
	xmm0 *= xptr(srcreg+d2+d1);		/* A7 = R7 * cosine/sine */ \
	xptr(dstreg+e2+e1+32) = xmm1;		/* I4 */ \
	xmm1 = xptr(screg+224+16);		/* cosine/sine */ \
	xmm1 *= xptr(srcreg+d2+d1+32);		/* A8 = R8 * cosine/sine */ \
\
	xptr(dstreg+e1+32) = xmm2;		/* I2 */ \
	xmm2 = xptr(srcreg+d2+16);		/* I5 */ \
	xmm7 += xmm2;			/* A5 = A5 + I5 */ \
	xptr(dstreg+32) = xmm4;		/* I1 */ \
	xmm4 = xptr(srcreg+d2+48);		/* I6 */ \
	xmm3 += xmm4;			/* A6 = A6 + I6 */ \
	xptr(dstreg+e2+e1) = xmm6;		/* R4 */ \
	xmm6 = xptr(srcreg+d2+d1+16);		/* I7 */ \
	xmm0 += xmm6;			/* A7 = A7 + I7 */ \
\
	xmm7 *= xptr(screg+32);		/* A5 = A5 * sine (new R5) */ \
	xmm3 *= xptr(screg+160);		/* A6 = A6 * sine (new R6) */ \
\
	xptr(dstreg+e2+32) = xmm5;		/* I3 */ \
\
	xmm5 = xmm7;			/* Copy R5 */ \
	xmm7 -= xmm3;			/* R5 = R5 - R6 (new R6) */ \
	xmm3 += xmm5;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm5 = xptr(srcreg+d2+d1+48);		/* I8 */ \
	xmm1 += xmm5;	 		/* A8 = A8 + I8 */ \
\
	xmm2 *= xptr(screg+32+16);		/* B5 = I5 * cosine/sine */ \
	xmm2 -= xptr(srcreg+d2);		/* B5 = B5 - R5 */ \
\
	xmm4 *= xptr(screg+160+16);		/* B6 = I6 * cosine/sine */ \
	xmm4 -= xptr(srcreg+d2+32);		/* B6 = B6 - R6 */ \
\
	xmm6 *= xptr(screg+96+16);		/* B7 = I7 * cosine/sine */ \
	xmm6 -= xptr(srcreg+d2+d1);		/* B7 = B7 - R7 */ \
\
	xmm5 *= xptr(screg+224+16);		/* B8 = I8 * cosine/sine */ \
	xmm5 -= xptr(srcreg+d2+d1+32);		/* B8 = B8 - R8 */ \
\
	xmm2 *= xptr(screg+32);		/* B5 = B5 * sine (new I5) */ \
	xmm4 *= xptr(screg+160);		/* B6 = B6 * sine (new I6) */ \
\
	xmm0 *= xptr(screg+96);		/* A7 = A7 * sine (new R7) */ \
	xmm6 *= xptr(screg+96);		/* B7 = B7 * sine (new I7) */ \
\
	xmm1 *= xptr(screg+224);		/* A8 = A8 * sine (new R8) */ \
	xmm5 *= xptr(screg+224);		/* B8 = B8 * sine (new I8) */ \
\
	srcreg += srcinc; \
\
	xptr(dstreg+e1+16) = xmm7;		/* R6 */ \
\
	xmm7 = xmm2;			/* Copy I5 */ \
	xmm2 -= xmm4;			/* I5 = I5 - I6 (new I6) */ \
	xmm4 += xmm7;			/* I6 = I5 + I6 (new I5) */ \
\
	xmm7 = xmm1;			/* Copy R8 */ \
	xmm1 -= xmm0;			/* R8 = R8 - R7 (new I8) */ \
	xmm0 += xmm7;			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7 = xmm6;			/* Copy I7 */ \
	xmm6 -= xmm5;			/* I7 = I7 - I8 (new R8) */ \
	xmm5 += xmm7;			/* I8 = I7 + I8 (new I7) */ \
\
	xmm7 = xmm0;			/* Copy R7 */ \
	xmm0 -= xmm3;			/* R7 = R7 - R5 (new I7) */ \
	xmm3 += xmm7;			/* R5 = R7 + R5 (new R5) */ \
\
	xmm7 = xmm4;			/* Copy I5 */ \
	xmm4 -= xmm5;			/* I5 = I5 - I7 (new R7) */ \
	xmm5 += xmm7;			/* I7 = I5 + I7 (new I5) */ \
\
	xptr(dstreg+e1+48) = xmm2;		/* I6 */ \
\
	xmm7 = xptr(dstreg);			/* R1 */ \
	xmm2 = xptr(dstreg+e2);		/* R3 */ \
	xmm7 -= xmm2;			/* R1 = R1 - R3 (new R3) */ \
	xmm2 += xptr(dstreg);			/* R3 = R1 + R3 (new R1) */ \
\
	xptr(dstreg+e2+e1+16) = xmm6;		/* R8 */ \
\
	xmm6 = xmm7;			/* Copy R3 */ \
	xmm7 -= xmm4;			/* R3 = R3 - R7 (final R7) */ \
	xmm4 += xmm6;			/* R7 = R3 + R7 (final R3) */ \
\
	xptr(dstreg+e2+e1+48) = xmm1;		/* I8 */ \
\
	xmm6 = xptr(dstreg+32);		/* I1 */ \
	xmm1 = xptr(dstreg+e2+32);		/* I3 */ \
	xmm6 -= xmm1;			/* I1 = I1 - I3 (new I3) */ \
	xmm1 += xptr(dstreg+32);		/* I3 = I1 + I3 (new I1) */ \
\
	xptr(dstreg+e2+16) = xmm7;		/* R7 */ \
\
	xmm7 = xmm6;			/* Copy I3 */ \
	xmm6 -= xmm0;			/* I3 = I3 - I7 (final I7) */ \
	xmm0 += xmm7;			/* I7 = I3 + I7 (final I3) */ \
\
	xmm7 = xmm2;			/* Copy R1 */ \
	xmm2 -= xmm3;			/* R1 = R1 - R5 (final R5) */ \
	xmm3 += xmm7;			/* R5 = R1 + R5 (final R1) */ \
\
	xmm7 = xmm1;			/* Copy I1 */ \
	xmm1 -= xmm5;			/* I1 = I1 - I5 (final I5) */ \
	xmm5 += xmm7;			/* I5 = I1 + I5 (final I1) */ \
\
	xptr(dstreg+e2) = xmm4;		/* R3 */ \
	xptr(dstreg+e2+32) = xmm0;		/* I3 */ \
\
;	/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm4 = xptr(dstreg+e1+16);		/* R6 */ \
	xmm0 = xptr(dstreg+e1+48);		/* I6 */ \
	xmm0 -= xmm4;			/* I6 = I6 - R6 */ \
	xmm4 += xptr(dstreg+e1+48);		/* R6 = R6 + I6 */ \
\
	xptr(dstreg+16) = xmm2;		/* R5 */ \
	xptr(dstreg+48) = xmm1;		/* I5 */ \
\
;	/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm2 = xptr(dstreg+e2+e1+16);		/* R8 */ \
	xmm1 = xptr(dstreg+e2+e1+48);		/* I8 */ \
	xmm1 -= xmm2;			/* I8 = I8 - R8 */ \
	xmm2 += xptr(dstreg+e2+e1+48);		/* R8 = R8 + I8 */ \
\
	xptr(dstreg+32) = xmm5;		/* I1 */ \
	xmm5 = XMM_SQRTHALF2; \
	xmm0 *= xmm5;			/* I6 = I6 * SQRTHALF (new I6) */ \
	xmm4 *= xmm5;			/* R6 = R6 * SQRTHALF (new R6) */ \
	xmm1 *= xmm5;			/* I8 = I8 * SQRTHALF (new I8) */ \
	xmm2 *= xmm5;			/* R8 = R8 * SQRTHALF (new R8) */ \
\
	xptr(dstreg) = xmm3;			/* R1 */ \
\
	xmm3 = xptr(dstreg+e1);		/* R2 */ \
	xmm7 = xptr(dstreg+e2+e1);		/* R4 */ \
	xmm7 += xmm3;			/* R4 = R2 + R4 (new R2) */ \
	xmm3 -= xptr(dstreg+e2+e1);		/* R2 = R2 - R4 (new R4) */ \
\
	xmm5 = xmm2;			/* Copy R8 */ \
	xmm2 -= xmm4;			/* R8 = R8 - R6 (new I8) */ \
	xmm4 += xmm5;			/* R6 = R8 + R6 (new R6) */ \
\
	xmm5 = xmm0;			/* Copy I6 */ \
	xmm0 -= xmm1;			/* I6 = I6 - I8 (new R8) */ \
	xmm1 += xmm5;			/* I8 = I6 + I8 (new I6) */ \
\
	xmm5 = xmm7;			/* Copy R2 */ \
	xmm7 -= xmm4;			/* R2 = R2 - R6 (final R6) */ \
	xmm4 += xmm5;			/* R6 = R2 + R6 (final R2) */ \
\
	xptr(dstreg+e2+48) = xmm6;		/* I7 */ \
	xptr(dstreg+e1+16) = xmm7;		/* R6 */ \
\
	xmm5 = xptr(dstreg+e1+32);		/* I2 */ \
	xmm6 = xptr(dstreg+e2+e1+32);		/* I4 */ \
	xmm6 += xmm5;			/* I4 = I2 + I4 (new I2) */ \
	xmm5 -= xptr(dstreg+e2+e1+32);		/* I2 = I2 - I4 (new I4) */ \
\
	xmm7 = xmm3;			/* Copy I4 */ \
	xmm3 -= xmm0;			/* R4 = R4 - R8 (final R8) */ \
	xmm0 += xmm7;			/* R8 = R4 + R8 (final R4) */ \
\
	xmm7 = xmm6;			/* Copy I2 */ \
	xmm6 -= xmm1;			/* I2 = I2 - I6 (final I6) */ \
	xmm1 += xmm7;			/* I6 = I2 + I6 (final I2) */ \
\
	xmm7 = xmm5;			/* Copy I4 */ \
	xmm5 -= xmm2;			/* I4 = I4 - I8 (final I8) */ \
	xmm2 += xmm7;			/* I8 = I4 + I8 (final I4) */ \
\
	xptr(dstreg+e1) = xmm4;		/* R2 */ \
	xptr(dstreg+e1+32) = xmm1;		/* I2 */ \
	xptr(dstreg+e2+e1) = xmm0;		/* R4 */ \
	xptr(dstreg+e2+e1+32) = xmm2;		/* I4 */ \
	xptr(dstreg+e1+48) = xmm6;		/* I6 */ \
	xptr(dstreg+e2+e1+16) = xmm3;		/* R8 */ \
	xptr(dstreg+e2+e1+48) = xmm5;		/* I8 */ \
	dstreg += dstinc; \

#endif
\
/* Used in the last levels of pass 1.  Swizzles. */ \


#if 0 // x86
#define r8_sg4cl_eight_complex_unfft8(srcreg,srcinc,d1,d2,dstreg,dstinc,e1,e2,screg) { \
	shuffle_load_with_temp(xmm7, xmm3, xptr(srcreg), xptr(srcreg+16), xmm0); /* R1,R2 */ \
	xmm5 = xptr(screg+0+16);		/* cosine/sine */ \
	xmm0 = xmm7;			/* Copy R1 */ \
	xmm7 *= xmm5;			/* A1 = R1 * cosine/sine */ \
	xmm6 = xptr(screg+128+16);		/* cosine/sine */ \
	xmm1 = xmm3;			/* Copy R2 */ \
	xmm3 *= xmm6;			/* A2 = R2 * cosine/sine */ \
\
	shuffle_load(xmm2, xmm4, xptr(srcreg+32), xptr(srcreg+48)); /* I1,I2 */ \
	xmm7 += xmm2;			/* A1 = A1 + I1 */ \
	xmm2 *= xmm5;			/* B1 = I1 * cosine/sine */ \
	xmm3 += xmm4;			/* A2 = A2 + I2 */ \
	xmm4 *= xmm6;			/* B2 = I2 * cosine/sine */ \
	xmm2 -= xmm0;			/* B1 = B1 - R1 */ \
	xmm4 -= xmm1;			/* B2 = B2 - R2 */ \
\
	shuffle_load_with_temp(xmm5, xmm6, xptr(srcreg+d1), xptr(srcreg+d1+16), xmm0); /* R3,R4 */ \
	xmm0 = xptr(screg+64+16);		/* cosine/sine */ \
	xmm0 *= xmm5;			/* A3 = R3 * cosine/sine */ \
\
	xmm7 *= xptr(screg+0);			/* A1 = A1 * sine (new R1) */ \
	xmm3 *= xptr(screg+128);		/* A2 = A2 * sine (new R2) */ \
\
	xmm1 = xmm7;			/* Copy R1 */ \
	xmm7 -= xmm3;			/* R1 = R1 - R2 (new R2) */ \
	xmm3 += xmm1;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm1 = xptr(screg+192+16);		/* cosine/sine */ \
	xmm1 *= xmm6;			/* A4 = R4 * cosine/sine */ \
\
	vec2f64 saved_R2 = xmm7;		/* R2 */ \
	vec2f64 saved_R1 = xmm3;			/* R1 */ \
\
	shuffle_load(xmm3, xmm7, xptr(srcreg+d1+32), xptr(srcreg+d1+48));	/* I3,I4 */ \
	xmm0 += xmm3;			/* A3 = A3 + I3 */ \
	xmm3 *= xptr(screg+64+16);		/* B3 = I3 * cosine/sine */ \
	xmm1 += xmm7;	 		/* A4 = A4 + I4 */ \
	xmm7 *= xptr(screg+192+16);		/* B4 = I4 * cosine/sine */ \
	xmm3 -= xmm5;			/* B3 = B3 - R3 */ \
	xmm7 -= xmm6;			/* B4 = B4 - R4 */ \
\
	xmm2 *= xptr(screg+0);			/* B1 = B1 * sine (new I1) */ \
	xmm4 *= xptr(screg+128);		/* B2 = B2 * sine (new I2) */ \
	xmm5 = xptr(screg+64); \
	xmm0 *= xmm5;			/* A3 = A3 * sine (new R3) */ \
	xmm3 *= xmm5;			/* B3 = B3 * sine (new I3) */ \
	xmm5 = xptr(screg+192); \
	xmm1 *= xmm5;			/* A4 = A4 * sine (new R4) */ \
	xmm7 *= xmm5;			/* B4 = B4 * sine (new I4) */ \
\
	xmm5 = xmm2;			/* Copy I1 */ \
	xmm2 -= xmm4;			/* I1 = I1 - I2 (new I2) */ \
	xmm4 += xmm5;			/* I2 = I1 + I2 (new I1) */ \
\
	xmm5 = xmm1;			/* Copy R4 */ \
	xmm1 -= xmm0;			/* R4 = R4 - R3 (new I4) */ \
	xmm0 += xmm5;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm5 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm7;			/* I3 = I3 - I4 (new R4) */ \
	xmm7 += xmm5;			/* I4 = I3 + I4 (new I3) */ \
\
	vec2f64 saved_R4 = xmm3;		/* R4 */ \
	vec2f64 saved_I3 = xmm7;		/* I3 */ \
	shuffle_load_with_temp(xmm7, xmm3, xptr(srcreg+d2), xptr(srcreg+d2+16), xmm5); /* R5,R6 */ \
	xmm5 = xptr(screg+32+16);		/* cosine/sine */ \
	xmm6 = xmm7;			/* Copy R5 */ \
	xmm7 *= xmm5;			/* A5 = R5 * cosine/sine */ \
	vec2f64 saved_R3 = xmm0;		/* R3 */ \
	xmm0 = xptr(screg+160+16);		/* cosine/sine */ \
	vec2f64 saved_I4 = xmm1;		/* I4 */ \
	xmm1 = xmm3;			/* Copy R6 */ \
	xmm3 *= xmm0;			/* A6 = R6 * cosine/sine */ \
\
	vec2f64 saved_I2 = xmm2;		/* I2 */ \
	vec2f64 saved_I1 = xmm4;		/* I1 */ \
	shuffle_load(xmm2, xmm4, xptr(srcreg+d2+32), xptr(srcreg+d2+48)); /* I5,I6 */ \
	xmm7 += xmm2;			/* A5 = A5 + I5 */ \
	xmm2 *= xmm5;			/* B5 = I5 * cosine/sine */ \
	xmm3 += xmm4;			/* A6 = A6 + I6 */ \
	xmm4 *= xmm0;			/* B6 = I6 * cosine/sine */ \
	xmm2 -= xmm6;			/* B5 = B5 - R5 */ \
	xmm4 -= xmm1;			/* B6 = B6 - R6 */ \
\
	shuffle_load_with_temp(xmm5, xmm6, xptr(srcreg+d2+d1), xptr(srcreg+d2+d1+16), xmm0); /* R7,R8 */ \
	xmm0 = xptr(screg+96+16);		/* cosine/sine */ \
	xmm0 *= xmm5;			/* A7 = R7 * cosine/sine */ \
\
	xmm7 *= xptr(screg+32);		/* A5 = A5 * sine (new R5) */ \
	xmm3 *= xptr(screg+160);		/* A6 = A6 * sine (new R6) */ \
\
	xmm1 = xmm7;			/* Copy R5 */ \
	xmm7 -= xmm3;			/* R5 = R5 - R6 (new R6) */ \
	xmm3 += xmm1;			/* R6 = R5 + R6 (new R5) */ \
\
	xmm1 = xptr(screg+224+16);		/* cosine/sine */ \
	xmm1 *= xmm6;			/* A8 = R8 * cosine/sine */ \
\
	vec2f64 saved_R5 = xmm3;		/* R5 */ \
	vec2f64 saved_R6 = xmm7;		/* R6 */ \
\
	shuffle_load(xmm3, xmm7, xptr(srcreg+d2+d1+32), xptr(srcreg+d2+d1+48)); /* I7,I8 */ \
	xmm0 += xmm3;			/* A7 = A7 + I7 */ \
	xmm3 *= xptr(screg+96+16);		/* B7 = I7 * cosine/sine */ \
	xmm1 += xmm7;	 		/* A8 = A8 + I8 */ \
	xmm7 *= xptr(screg+224+16);		/* B8 = I8 * cosine/sine */ \
	xmm3 -= xmm5;			/* B7 = B7 - R7 */ \
	xmm7 -= xmm6;			/* B8 = B8 - R8 */ \
\
	xmm2 *= xptr(screg+32);		/* B5 = B5 * sine (new I5) */ \
	xmm4 *= xptr(screg+160);		/* B6 = B6 * sine (new I6) */ \
	xmm5 = xptr(screg+96); \
	xmm0 *= xmm5;			/* A7 = A7 * sine (new R7) */ \
	xmm3 *= xmm5;			/* B7 = B7 * sine (new I7) */ \
	xmm5 = xptr(screg+224); \
	xmm1 *= xmm5;			/* A8 = A8 * sine (new R8) */ \
	xmm7 *= xmm5;			/* B8 = B8 * sine (new I8) */ \
\
	srcreg += srcinc; \
\
	xmm5 = xmm2;			/* Copy I5 */ \
	xmm2 -= xmm4;			/* I5 = I5 - I6 (new I6) */ \
	xmm4 += xmm5;			/* I6 = I5 + I6 (new I5) */ \
\
	xmm5 = xmm1;			/* Copy R8 */ \
	xmm1 -= xmm0;			/* R8 = R8 - R7 (new I8) */ \
	xmm0 += xmm5;			/* R7 = R8 + R7 (new R7) */ \
\
	xmm5 = xmm3;			/* Copy I7 */ \
	xmm3 -= xmm7;			/* I7 = I7 - I8 (new R8) */ \
	xmm7 += xmm5;			/* I8 = I7 + I8 (new I7) */ \
\
	xmm6 = saved_R5;		/* R5 */ \
	xmm6 += xmm0;			/* R5 = R7 + R5 (new R5) */ \
	xmm0 -= saved_R5;		/* R7 = R7 - R5 (new I7) */ \
\
	xmm5 = xmm4;			/* Copy I5 */ \
	xmm4 -= xmm7;			/* I5 = I5 - I7 (new R7) */ \
	xmm7 += xmm5;			/* I7 = I5 + I7 (new I5) */ \
\
	vec2f64 saved_I6 = xmm2;		/* I6 */ \
\
	xmm5 = saved_R1;			/* R1 */ \
	xmm2 = saved_R3;		/* R3 */ \
	xmm5 -= xmm2;			/* R1 = R1 - R3 (new R3) */ \
	xmm2 += saved_R1;			/* R3 = R1 + R3 (new R1) */ \
\
	vec2f64 saved_R8 = xmm3;		/* R8 */ \
\
	xmm3 = xmm5;			/* Copy R3 */ \
	xmm5 -= xmm4;			/* R3 = R3 - R7 (final R7) */ \
	xmm4 += xmm3;			/* R7 = R3 + R7 (final R3) */ \
\
	vec2f64 saved_I8 = xmm1;		/* I8 */ \
\
	xmm3 = saved_I1;		/* I1 */ \
	xmm1 = saved_I3;		/* I3 */ \
	xmm3 -= xmm1;			/* I1 = I1 - I3 (new I3) */ \
	xmm1 += saved_I1;		/* I3 = I1 + I3 (new I1) */ \
\
	xptr(dstreg+e2+16) = xmm5;		/* R7 */ \
\
	xmm5 = xmm3;			/* Copy I3 */ \
	xmm3 -= xmm0;			/* I3 = I3 - I7 (final I7) */ \
	xmm0 += xmm5;			/* I7 = I3 + I7 (final I3) */ \
\
	xmm5 = xmm2;			/* Copy R1 */ \
	xmm2 -= xmm6;			/* R1 = R1 - R5 (final R5) */ \
	xmm6 += xmm5;			/* R5 = R1 + R5 (final R1) */ \
\
	xmm5 = xmm1;			/* Copy I1 */ \
	xmm1 -= xmm7;			/* I1 = I1 - I5 (final I5) */ \
	xmm7 += xmm5;			/* I5 = I1 + I5 (final I1) */ \
\
	xptr(dstreg+e2) = xmm4;		/* R3 */ \
	xptr(dstreg+e2+32) = xmm0;		/* I3 */ \
\
;	/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm4 = saved_R6;		/* R6 */ \
	xmm0 = saved_I6;		/* I6 */ \
	xmm0 -= xmm4;			/* I6 = I6 - R6 */ \
	xmm4 += saved_I6;		/* R6 = R6 + I6 */ \
\
	xptr(dstreg+16) = xmm2;		/* R5 */ \
	xptr(dstreg+48) = xmm1;		/* I5 */ \
\
;	/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm2 = saved_R8;		/* R8 */ \
	xmm1 = saved_I8;		/* I8 */ \
	xmm1 -= xmm2;			/* I8 = I8 - R8 */ \
	xmm2 += saved_I8;		/* R8 = R8 + I8 */ \
\
	xptr(dstreg+32) = xmm7;		/* I1 */ \
	xmm5 = XMM_SQRTHALF2; \
	xmm0 *= xmm5;			/* I6 = I6 * SQRTHALF (new I6) */ \
	xmm4 *= xmm5;			/* R6 = R6 * SQRTHALF (new R6) */ \
	xmm1 *= xmm5;			/* I8 = I8 * SQRTHALF (new I8) */ \
	xmm2 *= xmm5;			/* R8 = R8 * SQRTHALF (new R8) */ \
\
	xptr(dstreg) = xmm6;			/* R1 */ \
\
	xmm6 = saved_R2;		/* R2 */ \
	xmm7 = saved_R4;		/* R4 */ \
	xmm7 += xmm6;			/* R4 = R2 + R4 (new R2) */ \
	xmm6 -= saved_R4;		/* R2 = R2 - R4 (new R4) */ \
\
	xmm5 = xmm2;			/* Copy R8 */ \
	xmm2 -= xmm4;			/* R8 = R8 - R6 (new I8) */ \
	xmm4 += xmm5;			/* R6 = R8 + R6 (new R6) */ \
\
	xmm5 = xmm0;			/* Copy I6 */ \
	xmm0 -= xmm1;			/* I6 = I6 - I8 (new R8) */ \
	xmm1 += xmm5;			/* I8 = I6 + I8 (new I6) */ \
\
	xmm5 = xmm7;			/* Copy R2 */ \
	xmm7 -= xmm4;			/* R2 = R2 - R6 (final R6) */ \
	xmm4 += xmm5;			/* R6 = R2 + R6 (final R2) */ \
\
	xptr(dstreg+e2+48) = xmm3;		/* I7 */ \
	xptr(dstreg+e1+16) = xmm7;		/* R6 */ \
\
	xmm5 = saved_I2;		/* I2 */ \
	xmm3 = saved_I4;		/* I4 */ \
	xmm3 += xmm5;			/* I4 = I2 + I4 (new I2) */ \
	xmm5 -= saved_I4;		/* I2 = I2 - I4 (new I4) */ \
\
	xmm7 = xmm6;			/* Copy R4 */ \
	xmm6 -= xmm0;			/* R4 = R4 - R8 (final R8) */ \
	xmm0 += xmm7;			/* R8 = R4 + R8 (final R4) */ \
\
	xmm7 = xmm3;			/* Copy I2 */ \
	xmm3 -= xmm1;			/* I2 = I2 - I6 (final I6) */ \
	xmm1 += xmm7;			/* I6 = I2 + I6 (final I2) */ \
\
	xmm7 = xmm5;			/* Copy I4 */ \
	xmm5 -= xmm2;			/* I4 = I4 - I8 (final I8) */ \
	xmm2 += xmm7;			/* I8 = I4 + I8 (final I4) */ \
\
	xptr(dstreg+e1) = xmm4;		/* R2 */ \
	xptr(dstreg+e1+32) = xmm1;		/* I2 */ \
	xptr(dstreg+e2+e1) = xmm0;		/* R4 */ \
	xptr(dstreg+e2+e1+32) = xmm2;		/* I4 */ \
	xptr(dstreg+e1+48) = xmm3;		/* I6 */ \
	xptr(dstreg+e2+e1+16) = xmm6;		/* R8 */ \
	xptr(dstreg+e2+e1+48) = xmm5;		/* I8 */ \
	dstreg += dstinc; \
}

#else // X86_64
#define r8_sg4cl_eight_complex_unfft8(srcreg,srcinc,d1,d2,dstreg,dstinc,e1,e2,screg) { \
	vec2f64 xmm8,xmm9,xmm10,xmm11,xmm12,xmm13,xmm14,xmm15; \
	shuffle_load_with_temp(xmm1, xmm2, xptr(srcreg), xptr(srcreg+16), xmm0); /* R1,R2 */ \
\
	xmm3 = xptr(screg+0+16);		/* cosine/sine 1		; 1 */ \
	xmm15 = xmm1;			/* Copy R1			; 1-3 */ \
	xmm1 *= xmm3;			/* A1 = R1 * cosine/sine	; 1-5 */ \
\
	xmm4 = xptr(screg+128+16);		/* cosine/sine 2		; 2 */ \
	xmm5 = xmm2;			/* Copy R2			; 2-4 */ \
	xmm2 *= xmm4;			/* A2 = R2 * cosine/sine	; 2-6 */ \
\
	shuffle_load_with_temp(xmm6, xmm7, xptr(srcreg+32), xptr(srcreg+48), xmm0); /* I1,I2 */ \
\
	xmm3 *= xmm6;			/* B1 = I1 * cosine/sine	; 3-7 */ \
	xmm4 *= xmm7;			/* B2 = I2 * cosine/sine	; 4-8 */ \
\
	shuffle_load_with_temp(xmm8, xmm9, xptr(srcreg+d1), xptr(srcreg+d1+16), xmm0); /* R3,R4 */ \
\
	xmm10 = xptr(screg+64+16);		/* cosine/sine 3		; 5 */ \
	xmm11 = xmm8;			/* Copy R3			; 5-7 */ \
	xmm8 *= xmm10;			/* A3 = R3 * cosine/sine	; 5-9 */ \
\
	xmm1 += xmm6;			/* A1 = A1 + I1			; 6-8	avail 0,6,12-14 */ \
	xmm12 = xptr(screg+192+16);		/* cosine/sine 4		; 6	avail 0,6,13,14 */ \
	xmm13 = xmm9;			/* Copy R4			; 6-8	avail 0,6,14 */ \
	xmm9 *= xmm12;			/* A4 = R4 * cosine/sine	; 6-10 */ \
\
	shuffle_load_with_temp(xmm6, xmm14, xptr(srcreg+d1+32), xptr(srcreg+d1+48), xmm0); /* I3,I4 */ \
\
	xmm2 += xmm7;			/* A2 = A2 + I2			; 7-9	avail 0,7 */ \
	xmm10 *= xmm6;			/* B3 = I3 * cosine/sine	; 7-11 */ \
	xmm0 = xptr(screg+0);			/* sine 1			; 7	avail 7 */ \
\
	xmm3 -= xmm15;			/* B1 = B1 - R1			; 8-10	avail 7,15 */ \
	xmm12 *= xmm14;			/* B4 = I4 * cosine/sine	; 8-12 */ \
	xmm7 = xptr(screg+128);		/* sine 2			; 8	avail 15 */ \
\
	xmm4 -= xmm5;			/* B2 = B2 - R2			; 9-11	avail 15,5 */ \
	xmm1 *= xmm0;			/* A1 = A1 * sine (new R1)	; 9-13 */ \
\
	xmm8 += xmm6;			/* A3 = A3 + I3			; 10-12	avail 15,5,6 */ \
	xmm2 *= xmm7;			/* A2 = A2 * sine (new R2)	; 10-14 */ \
	xmm5 = xptr(screg+64);		/* sine 3			; 10	avail 15,6 */ \
\
	xmm9 += xmm14;			/* A4 = A4 + I4			; 11-13	avail 15,6,14 */ \
	xmm3 *= xmm0;			/* B1 = B1 * sine (new I1)	; 11-15	avail 15,6,14,0 */ \
	xmm6 = xptr(screg+192);		/* sine 4			; 11	avail 15,14,0 */ \
\
	xmm10 -= xmm11;			/* B3 = B3 - R3			; 12-14	avail 15,14,0,11 */ \
	xmm4 *= xmm7;			/* B2 = B2 * sine (new I2)	; 12-16	avail 15,14,0,11,7 */ \
\
	xmm12 -= xmm13;			/* B4 = B4 - R4			; 13-15	avail 15,14,0,11,7,13 */ \
	xmm8 *= xmm5;			/* A3 = A3 * sine (new R3)	; 13-17 */ \
\
	xmm0 = xmm1;			/* Copy R1			; 14-16 (14 on a Core i7) avail 15,14,11,7,13 */ \
	xmm9 *= xmm6;			/* A4 = A4 * sine (new R4)	; 14-18 */ \
\
	shuffle_load_with_temp(xmm15, xmm14, xptr(srcreg+d2), xptr(srcreg+d2+16), xmm7); /* R5,R6 */ \
\
	xmm1 -= xmm2;			/* R1 = R1 - R2 (newer R2)	; 15-17 */ \
	xmm10 *= xmm5;			/* B3 = B3 * sine (new I3)	; 15-19	avail 11,7,13,5 */ \
	xmm11 = xptr(screg+32+16);		/* cosine/sine 5		; 15 */ \
\
	xprefetchw(u8ptr(dstreg+dstinc)); \
\
	xmm2 += xmm0;			/* R2 = R1 + R2 (newer R1)	; 17-19 (16-18 on a Core i7) avail 7,13,5,0 */ \
	xmm12 *= xmm6;			/* B4 = B4 * sine (new I4)	; 16-20	avail 7,13,5,0,6 */ \
	xmm0 = xmm3;			/* Copy I1			; 16-18	avail 7,13,5,6 */ \
\
	xmm3 -= xmm4;			/* I1 = I1 - I2 (newer I2)	; 18-20 */ \
	xmm5 = xmm8;			/* Copy R3			; 18-20	avail 7,13,6 */ \
	xmm7 = xptr(screg+160+16);		/* cosine/sine 6		; 18	avail 13,6 */ \
	vec2f64 saved_R2 = xmm1;		/* Save R2			; 18	avail 13,6,1 */ \
\
	xmm4 += xmm0;			/* I2 = I1 + I2 (newer I1)	; 19-21	avail 13,6,1,0 */ \
	xmm6 = xmm15;			/* Copy R5			; 19-21	avail 13,1,0 */ \
	xmm15 *= xmm11;			/* A5 = R5 * cosine/sine	; 19-23 */ \
\
	xmm8 += xmm9;			/* R3 = R4 + R3 (newer R3)	; 20-22 */ \
	xmm13 = xmm14;			/* Copy R6			; 20-22	avail 1,0 */ \
	xmm14 *= xmm7;			/* A6 = R6 * cosine/sine	; 20-24 */ \
	vec2f64 saved_R1 = xmm2;			/* Save R1			; 20	avail 1,0,2 */ \
	shuffle_load_with_temp(xmm1, xmm2, xptr(srcreg+d2+32), xptr(srcreg+d2+48), xmm0);	/* I5,I6 */ \
	xmm0 = xmm10;			/* Copy I3			; 20-22	avail none */ \
\
	xmm9 -= xmm5;			/* R4 = R4 - R3 (newer I4)	; 21-23	avail 5 */ \
	xmm11 *= xmm1;			/* B5 = I5 * cosine/sine	; 21-25 */ \
	vec2f64 saved_I2 = xmm3;		/* Save I2			; 21	avail 5,3 */ \
\
	xmm10 -= xmm12;			/* I3 = I3 - I4 (newer R4)	; 22-24 avail 5,3 */ \
	xmm7 *= xmm2;			/* B6 = I6 * cosine/sine	; 22-26 */ \
	vec2f64 saved_I1 = xmm4;		/* Save I1			; 22	avail 5,3,4 */ \
\
	xmm12 += xmm0;			/* I4 = I3 + I4 (newer I3)	; 23-25	avail 5,3,4,0 */ \
	shuffle_load_with_temp(xmm5, xmm3, xptr(srcreg+d2+d1), xptr(srcreg+d2+d1+16), xmm0); /* R7,R8 */ \
	xmm4 = xptr(screg+96+16);		/* cosine/sine 7		; 23	avail 0 */ \
	xmm0 = xmm5;			/* Copy R7			; 23-25	avail none */ \
	xmm5 *= xmm4;			/* A7 = R7 * cosine/sine	; 23-27 */ \
	vec2f64 saved_R3 = xmm8;		/* Save R3			; 23	avail 8 */ \
\
	xmm15 += xmm1;			/* A5 = A5 + I5			; 24-26	avail 8,1 */ \
	xmm8 = xptr(screg+224+16);		/* cosine/sine 8		; 24	avail 1 */ \
	xmm1 = xmm3;			/* Copy R8			; 24-26	avail none */ \
	xmm3 *= xmm8;			/* A8 = R8 * cosine/sine	; 24-28 */ \
	vec2f64 saved_I4 = xmm9;		/* Save I4			; 24	avail 9 */ \
\
	xprefetchw(u8ptr(dstreg+dstinc+e1)); \
\
	xmm14 += xmm2;			/* A6 = A6 + I6			; 25-27	avail 9,2 */ \
	vec2f64 saved_R4 = xmm10;		/* Save R4			; 25	avail 9,2,10 */ \
	shuffle_load_with_temp(xmm9, xmm10, xptr(srcreg+d2+d1+32), xptr(srcreg+d2+d1+48), xmm2); /* I7,I8 */ \
	xmm4 *= xmm9;			/* B7 = I7 * cosine/sine	; 25-29	avail 2 */ \
\
	xmm11 -= xmm6;			/* B5 = B5 - R5			; 26-28	avail 2,6 */ \
	xmm8 *= xmm10;			/* B8 = I8 * cosine/sine	; 26-30 */ \
	xmm6 = xptr(screg+32);		/* sine 5			; 26	avail 2 */ \
\
	xmm7 -= xmm13;			/* B6 = B6 - R6			; 27-29	avail 2,13 */ \
	xmm15 *= xmm6;			/* A5 = A5 * sine (new R5)	; 27-31 */ \
	xmm2 = xptr(screg+160);		/* sine 6			; 27	avail 13 */ \
\
	xmm5 += xmm9;			/* A7 = A7 + I7			; 28-30	avail 13,9 */ \
	xmm14 *= xmm2;			/* A6 = A6 * sine (new R6)	; 28-32 */ \
	xmm13 = xptr(screg+96);		/* sine 7			; 28	avail 9 */ \
\
	xmm3 += xmm10;			/* A8 = A8 + I8			; 29-31	avail 9,10 */ \
	xmm11 *= xmm6;			/* B5 = B5 * sine (new I5)	; 29-33	avail 9,10,6 */ \
	xmm9 = xptr(screg+224);		/* sine 8			; 29	avail 10,6 */ \
\
	xmm4 -= xmm0;			/* B7 = B7 - R7			; 30-32	avail 10,6,0 */ \
	xmm7 *= xmm2;			/* B6 = B6 * sine (new I6)	; 30-34	avail 10,6,0,2 */ \
	xmm0 = xmm12;			/* Copy I3			; 30-32	avail 10,6,2 */ \
	xmm6 = saved_I1;		/* Reload I1			; 30	avail 10,2 */ \
\
	xmm8 -= xmm1;			/* B8 = B8 - R8			; 31-33	avail 10,2,1 */ \
	xmm5 *= xmm13;			/* A7 = A7 * sine (new R7)	; 31-35 */ \
\
	srcreg += srcinc; \
\
	xmm12 += xmm6;			/* I3 = I1 + I3 (new I1)	; 32-34 */ \
	xmm3 *= xmm9;			/* A8 = A8 * sine (new R8)	; 32-36 */ \
	xmm2 = xmm15;			/* Copy R5			; 32-34	avail 10,1 */ \
\
	xmm6 -= xmm0;			/* I1 = I1 - I3 (new I3)	; 33-35	avail 10,1,0 */ \
	xmm4 *= xmm13;			/* B7 = B7 * sine (new I7)	; 33-37	avail 10,1,0,13 */ \
\
	xmm15 -= xmm14;			/* R5 = R5 - R6 (newer R6)	; 34-36 */ \
	xmm8 *= xmm9;			/* B8 = B8 * sine (new I8)	; 34-38	avail 10,1,0,13,9 */ \
	xmm0 = xmm11;			/* Copy I5			; 34-36	avail 10,1,13,9 */ \
\
	xprefetchw(u8ptr(dstreg+dstinc+e2)); \
\
	xmm14 += xmm2;			/* R6 = R5 + R6 (newer R5)	; 35-37	avail 10,1,13,9,2 */ \
\
	xmm11 -= xmm7;			/* I5 = I5 - I6 (newer I6)	; 36-38 */ \
	xmm13 = xmm5;			/* Copy R7			; 36-38	avail 10,1,9,2 */ \
\
	xmm7 += xmm0;			/* I6 = I5 + I6 (newer I5)	; 37-39	avail 10,1,9,2,0 */ \
	xmm2 = XMM_SQRTHALF2;						/* 37	avail 10,1,9,0 */ \
\
	xmm5 += xmm3;			/* R7 = R8 + R7 (newer R7)	; 38-40 */ \
	xmm0 = xmm4;			/* Copy I7			; 38-40	avail 10,1,9 */ \
\
	xmm3 -= xmm13;			/* R8 = R8 - R7 (newer I8)	; 39-41	avail 10,1,9,13 */ \
\
	xmm4 -= xmm8;			/* I7 = I7 - I8 (newer R8)	; 40-42 */ \
	xmm1 = xmm15;			/* Copy R6			; 40-42 (37) avail 10,9,13 */ \
\
	xmm8 += xmm0;			/* I8 = I7 + I8 (newer I7)	; 41-43	avail 10,9,13,0 */ \
\
	xprefetchw(u8ptr(dstreg+dstinc+e2+e1)); \
\
;						/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm15 += xmm11;			/* R6 = R6 + I6			; 42-44 */ \
	xmm0 = xmm3;			/* Copy I8			; 42-44	avail 10,9,13 */ \
\
	xmm11 -= xmm1;			/* I6 = I6 - R6			; 43-45	avail 10,9,13,1 */ \
	xmm10 = saved_R1;			/* Reload R1			; 43	avail 9,13,1 */ \
\
;						/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm3 -= xmm4;			/* I8 = I8 - R8			; 44-46 */ \
	xmm1 = xmm14;			/* Copy R5			; 44-46 (38) avail 9,13 */ \
	xmm9 = saved_R3;		/* Reload R3			; 44	avail 13 */ \
\
	xmm4 += xmm0;			/* R8 = R8 + I8			; 45-47	avail 13,0 */ \
	xmm15 *= xmm2;			/* R6 = R6 * SQRTHALF (newer R6); 45-49 */ \
\
	xmm14 += xmm5;			/* R5 = R7 + R5 (new R5)	; 46-48 */ \
	xmm11 *= xmm2;			/* I6 = I6 * SQRTHALF (newer I6); 46-50 */ \
	xmm0 = xmm7;			/* Copy I5			; 46-48 (40) avail 13 */ \
\
	xmm5 -= xmm1;			/* R7 = R7 - R5 (new I7)	; 47-49	avail 13,1 */ \
	xmm3 *= xmm2;			/* I8 = I8 * SQRTHALF (newer I8); 47-51 */ \
\
	xmm7 -= xmm8;			/* I5 = I5 - I7 (new R7)	; 48-50 */ \
	xmm4 *= xmm2;			/* R8 = R8 * SQRTHALF (newer R8); 48-52	avail 13,1,2 */ \
	xmm1 = xmm10;			/* Copy R1			; 48-50	avail 13,2 */ \
\
	xmm8 += xmm0;			/* I7 = I5 + I7 (new I5)	; 49-51	avail 13,2,0 */ \
	xmm13 = saved_R2;		/* Reload R2			; 49	avail 2,0 */ \
\
	xmm10 -= xmm9;			/* R1 = R1 - R3 (new R3)	; 50-52 */ \
	xmm2 = xmm6;			/* Copy I3			; 50-52	avail 0 */ \
\
	xmm9 += xmm1;			/* R3 = R1 + R3 (new R1)	; 51-53	avail 0,1 */ \
	xmm0 = saved_R4;		/* Reload R4			; 51	avail 1 */ \
\
	xmm6 -= xmm5;			/* I3 = I3 - I7 (final I7)	; 52-54	avail 1 storable 6 */ \
	xmm1 = xmm12;			/* Copy I1			; 52-54	avail none storable 6 */ \
\
	xmm5 += xmm2;			/* I7 = I3 + I7 (final I3)	; 53-55	avail 2 storable 6,5 */ \
\
	xmm12 -= xmm8;			/* I1 = I1 - I5 (final I5)	; 54-56	avail 2 storable 6,5,12 */ \
	xmm2 = xmm10;			/* Copy R3			; 54-56	avail none storable 6,5,12 */ \
\
	xmm8 += xmm1;			/* I5 = I1 + I5 (final I1)	; 55-57	avail 1 storable 6,5,12,8 */ \
	xptr(dstreg+e2+48) = xmm6;		/* I7				; 55	avail 1,6 storable 5,12,8 */ \
	xmm6 = saved_I2;		/* Reload I2			; 55	avail 1 storable 5,12,8 */ \
\
	xmm10 -= xmm7;			/* R3 = R3 - R7 (final R7)	; 56-58	avail 1 storable 5,12,8,10 */ \
	xmm1 = xmm9;			/* Copy R1			; 56-58	avail none storable 5,12,8,10 */ \
	xptr(dstreg+e2+32) = xmm5;		/* I3				; 56	avail 5 storable 12,8,10 */ \
\
	xmm7 += xmm2;			/* R7 = R3 + R7 (final R3)	; 57-59	avail 5,2 storable 12,8,10,7 */ \
	xmm5 = saved_I4;		/* Reload I4			; 57	avail 2 storable 12,8,10,7 */ \
	xptr(dstreg+48) = xmm12;		/* I5				; 57	avail 2,12 storable 8,10,7 */ \
\
	xmm9 -= xmm14;			/* R1 = R1 - R5 (final R5)	; 58-60	avail 2,12 storable 8,10,7,9 */ \
	xmm2 = xmm13;			/* Copy R2			; 58-60	avail 12 storable 8,10,7,9 */ \
	xptr(dstreg+32) = xmm8;		/* I1				; 58	avail 12,8 storable 10,7,9 */ \
\
	xmm14 += xmm1;			/* R5 = R1 + R5 (final R1)	; 59-61	avail 12,8,1 storable 10,7,9,14 */ \
	xptr(dstreg+e2+16) = xmm10;		/* R7				; 59	avail 12,8,1,10 storable 7,9,14 */ \
\
	xmm13 += xmm0;			/* R4 = R2 + R4 (new R2)	; 60-62 */ \
	xmm1 = xmm4;			/* Copy R8			; 60-62	avail 12,8,10 storable 7,9,14 */ \
	xptr(dstreg+e2) = xmm7;		/* R3				; 60	avail 12,8,10,7 storable 9,14 */ \
\
	xmm2 -= xmm0;			/* R2 = R2 - R4 (new R4)	; 61-63	avail 12,8,10,7,0 storable 9,14 */ \
	xptr(dstreg+16) = xmm9;		/* R5				; 61	avail 12,8,10,7,0,9 storable 14 */ \
\
	xmm4 -= xmm15;			/* R8 = R8 - R6 (new I8)	; 62-64 */ \
	xmm0 = xmm6;			/* Copy I2			; 62-64	avail 12,8,10,7,9 storable 14 */ \
	xptr(dstreg) = xmm14;			/* R1				; 62	avail 12,8,10,7,9,14 */ \
\
	xmm15 += xmm1;			/* R6 = R8 + R6 (new R6)	; 63-65	avail 12,8,10,7,9,14,1 */ \
\
	xmm6 += xmm5;			/* I4 = I2 + I4 (new I2)	; 64-66 */ \
	xmm1 = xmm11;			/* Copy I6			; 64-66	avail 12,8,10,7,9,14 */ \
\
	xmm0 -= xmm5;			/* I2 = I2 - I4 (new I4)	; 65-67	avail 12,8,10,7,9,14,5 */ \
\
	xmm11 -= xmm3;			/* I6 = I6 - I8 (new R8)	; 66-68 */ \
	xmm7 = xmm13;			/* Copy R2			; 66-68	avail 12,8,10,9,14,5 */ \
\
	xmm3 += xmm1;			/* I8 = I6 + I8 (new I6)	; 67-69	avail 12,8,10,9,14,5,1 */ \
\
	xmm13 -= xmm15;			/* R2 = R2 - R6 (final R6)	; 68-70	avail 12,8,10,9,14,5,1 storable 13 */ \
	xmm1 = xmm4;			/* Copy I8			; 68-70	avail 12,8,10,9,14,5 storable 13 */ \
\
	xmm15 += xmm7;			/* R6 = R2 + R6 (final R2)	; 69-71	avail 12,8,10,9,14,5,7 storable 13,15 */ \
\
	xmm4 += xmm0;			/* I8 = I4 + I8 (final I4)	; 70-72	avail 12,8,10,9,14,5,7 storable 13,15,4 */ \
	xmm5 = xmm2;			/* Copy R4			; 70-72	avail 12,8,10,9,14,7 storable 13,15,4 */ \
\
	xmm0 -= xmm1;			/* I4 = I4 - I8 (final I8)	; 71-73	avail 12,8,10,9,14,7,1 storable 13,15,4,0 */ \
	xptr(dstreg+e1+16) = xmm13;		/* R6				; 71	avail 12,8,10,9,14,7,1,13 storable 15,4,0 */ \
\
	xmm2 -= xmm11;			/* R4 = R4 - R8 (final R8)	; 72-74	avail 12,8,10,9,14,7,1,13 storable 15,4,0,2 */ \
	xmm1 = xmm6;			/* Copy I2			; 72-74	avail 12,8,10,9,14,7,13 storable 15,4,0,2 */ \
	xptr(dstreg+e1) = xmm15;		/* R2				; 72	avail 12,8,10,9,14,7,13,15 storable 4,0,2 */ \
\
	xmm11 += xmm5;			/* R8 = R4 + R8 (final R4)	; 73-75	avail 12,8,10,9,14,7,13,15,5 storable 4,0,2,11 */ \
	xptr(dstreg+e2+e1+32) = xmm4;		/* I4				; 73	avail 12,8,10,9,14,7,13,15,5,4 storable 0,2,11 */ \
\
	xmm6 -= xmm3;			/* I2 = I2 - I6 (final I6)	; 74-76	avail 12,8,10,9,14,7,13,15,5,4 storable 0,2,11,6 */ \
	xptr(dstreg+e2+e1+48) = xmm0;		/* I8				; 74	avail 12,8,10,9,14,7,13,15,5,4,0 storable 2,11,6 */ \
\
	xmm3 += xmm1;			/* I6 = I2 + I6 (final I2)	; 75-77	avail 12,8,10,9,14,7,13,15,5,4,0,1 storable 2,11,6,3 */ \
	xptr(dstreg+e2+e1+16) = xmm2;		/* R8				; 75 */ \
\
	xptr(dstreg+e2+e1) = xmm11;		/* R4				; 76 */ \
	xptr(dstreg+e1+48) = xmm6;		/* I6				; 77 */ \
	xptr(dstreg+e1+32) = xmm3;		/* I2				; 78 */ \
	dstreg += dstinc; \
}

#endif
/* */ \
/* ************************************* sixteen-reals-four-complex-fft8 variants ****************************************** */ \
/* */ \
/* Because of the way we store FFT data elements in cache lines during the pass 1 of the forward FFT, a cache line */ \
/* will contain data needing an eight-reals-fft as well as data needing a four-complex-fft. */ \
\
/* */ \
/* Do three-and-7/8 levels of the forward FFT on 16 real data values with 7 sin/cos multipliers. */ \
/* Output is 2 real values needing N+1 more levels and 7 complex values needing N more FFT levels. */ \
/* Also do a forward FFT on 8 complex values. */ \
/* */ \
/* To simplify implementation of the 16 reals case, I first operate on 4 sets of 4 reals doing */ \
/* one-and-1/2 levels.  Each set outputs two real values and one complex value.  The four complex */ \
/* values are multiplied by w^1.  Then I do one eight-reals-FFT which can use the sin/cos multipliers */ \
/* that r8_g8cl_eight_complex_djbfft uses.  Finally, the one four-complex-FFT uses two more */ \
/* sin/cos multipliers. */ \
/* */ \
\
/* Used in last levels of pass 1 (split premultiplier and delay cases).  No swizzling. */
#if 0 // UNUSED

#define r8_g8cl_sixteen_reals_eight_complex_fft8(srcreg,srcinc,d1,d2,d4,dstreg,dstinc,e1,e2,e4,screg1,screg2) \
	not written; \

#endif
\
/* Used in last levels of pass 1 (split premultiplier and delay cases).  Swizzling. */ \
\

#define r8_sg8cl_sixteen_reals_eight_complex_fft8_preload \
	r4_x8r_fft_mem_preload; \
\

#define r8_sg8cl_sixteen_reals_eight_complex_fft8(srcreg,srcinc,d1,d2,d4,dstreg,dstinc,e1,e2,e4,screg1,screg2) { \
	const uintptr_t e3 = e2 + e1; \
\
/* Do first level on the first 8 reals and 2 levels on the last 8 reals. */ \
/* The second level on the last eight reals is the multiply by i. */ \
\
	xmm0 = xptr(srcreg);		/* R1 */ \
	xmm2 = xptr(srcreg+16);	/* R9 */ \
	xmm0 -= xmm2;		/* new R9 = R1 - R9 */ \
	xmm2 += xptr(srcreg);		/* new R1 = R1 + R9 */ \
\
	xmm1 = xptr(srcreg+d4);	/* R5 */ \
	xmm3 = xptr(srcreg+d4+16);	/* R13 */ \
	xmm1 -= xmm3;		/* new I9 = R5 - R13 */ \
	xmm3 += xptr(srcreg+d4);	/* new R5 = R5 + R13 */ \
\
	xmm7 = xptr(screg2+16);	/* cosine/sine */ \
	xmm7 *= xmm0;		/* A9 = R9 * cosine/sine */ \
	xmm7 -= xmm1;		/* A9 = A9 - I9 */ \
	xmm1 *= xptr(screg2+16);	/* B9 = I9 * cosine/sine */ \
	xmm1 += xmm0;		/* B9 = B9 + R9 */ \
\
	xmm7 *= xptr(screg2);		/* A9 = A9 * sine (final R9) */ \
	xmm1 *= xptr(screg2);		/* B9 = B9 * sine (final I9) */ \
\
	xptr(dstreg) = xmm2;		/* Save R1 */ \
	xptr(dstreg+e1) = xmm3;	/* Save R5 */ \
	xptr(dstreg+e2) = xmm7;	/* Save R9 */ \
	xptr(dstreg+e2+e1) = xmm1;	/* Save I9 */ \
\
	xmm4 = xptr(srcreg+d1);	/* R2 */ \
	xmm6 = xptr(srcreg+d1+16);	/* R10 */ \
	xmm4 -= xmm6;		/* new R10 = R2 - R10 */ \
	xmm6 += xptr(srcreg+d1);	/* new R2 = R2 + R10 */ \
\
	xmm5 = xptr(srcreg+d4+d1);	/* R6 */ \
	xmm7 = xptr(srcreg+d4+d1+16);	/* R14 */ \
	xmm5 -= xmm7;		/* new I10 = R6 - R14 */ \
	xmm7 += xptr(srcreg+d4+d1);	/* new R6 = R6 + R14 */ \
\
	xmm2 = xptr(screg2+48);	/* cosine/sine */ \
	xmm2 *= xmm4;		/* A10 = R10 * cosine/sine */ \
	xmm2 -= xmm5;		/* A10 = A10 - I10 */ \
	xmm5 *= xptr(screg2+48);	/* B10 = I10 * cosine/sine */ \
	xmm5 += xmm4;		/* B10 = B10 + R10 */ \
\
	xmm2 *= xptr(screg2+32);	/* A10 = A10 * sine (final R10) */ \
	xmm5 *= xptr(screg2+32);	/* B10 = B10 * sine (final I10) */ \
\
	xptr(dstreg+16) = xmm6;	/* Save R2 */ \
	xptr(dstreg+e1+16) = xmm7;	/* Save R6 */ \
	xptr(dstreg+e2+16) = xmm2;	/* Save R10 */ \
	xptr(dstreg+e2+e1+16) = xmm5;	/* Save I10 */ \
\
	xmm0 = xptr(srcreg+d2);	/* R3 */ \
	xmm2 = xptr(srcreg+d2+16);	/* R11 */ \
	xmm0 -= xmm2;		/* new R11 = R3 - R11 */ \
	xmm2 += xptr(srcreg+d2);	/* new R3 = R3 + R11 */ \
\
	xmm1 = xptr(srcreg+d4+d2);	/* R7 */ \
	xmm3 = xptr(srcreg+d4+d2+16);	/* R15 */ \
	xmm1 -= xmm3;		/* new I11 = R7 - R15 */ \
	xmm3 += xptr(srcreg+d4+d2);	/* new R7 = R7 + R15 */ \
\
	xmm7 = xptr(screg2+80);	/* cosine/sine */ \
	xmm7 *= xmm0;		/* A11 = R11 * cosine/sine */ \
	xmm7 -= xmm1;		/* A11 = A11 - I11 */ \
	xmm1 *= xptr(screg2+80);	/* B11 = I11 * cosine/sine */ \
	xmm1 += xmm0;		/* B11 = B11 + R11 */ \
\
	xmm7 *= xptr(screg2+64);	/* A11 = A11 * sine (final R11) */ \
	xmm1 *= xptr(screg2+64);	/* B11 = B11 * sine (final I11) */ \
\
	xptr(dstreg+32) = xmm2;	/* Save R3 */ \
	xptr(dstreg+e1+32) = xmm3;	/* Save R7 */ \
	xptr(dstreg+e2+32) = xmm7;	/* Save R11 */ \
	xptr(dstreg+e2+e1+32) = xmm1;	/* Save I11 */ \
\
	xmm4 = xptr(srcreg+d2+d1);	/* R4 */ \
	xmm6 = xptr(srcreg+d2+d1+16);	/* R12 */ \
	xmm4 -= xmm6;		/* new R12 = R4 - R12 */ \
	xmm6 += xptr(srcreg+d2+d1);	/* new R4 = R4 + R12 */ \
\
	xmm5 = xptr(srcreg+d4+d2+d1);	/* R8 */ \
	xmm7 = xptr(srcreg+d4+d2+d1+16); /* R16 */ \
	xmm5 -= xmm7;		/* new I12 = R8 - R16 */ \
	xmm7 += xptr(srcreg+d4+d2+d1);	/* new R8 = R8 + R16 */ \
\
	xmm2 = xptr(screg2+112);	/* cosine/sine */ \
	xmm2 *= xmm4;		/* A12 = R12 * cosine/sine */ \
	xmm2 -= xmm5;		/* A12 = A12 - I12 */ \
	xmm5 *= xptr(screg2+112);	/* B12 = I12 * cosine/sine */ \
	xmm5 += xmm4;		/* B12 = B12 + R12 */ \
\
	xmm2 *= xptr(screg2+96);	/* A12 = A12 * sine (final R12) */ \
	xmm5 *= xptr(screg2+96);	/* B12 = B12 * sine (final I12) */ \
\
	xptr(dstreg+48) = xmm6;	/* Save R4 */ \
	xptr(dstreg+e1+48) = xmm7;	/* Save R8 */ \
	xptr(dstreg+e2+48) = xmm2;	/* Save R12 */ \
	xptr(dstreg+e2+e1+48) = xmm5;	/* Save I12 */ \
\
/* Do last two and 3/4 levels on the remaining real data */ \
\
	xprefetch(u8ptr(srcreg+srcinc)); \
	r4_x8r_fft_mem(xptr(dstreg),xptr(dstreg+16),xptr(dstreg+32),xptr(dstreg+48),xptr(dstreg+e1),xptr(dstreg+e1+16),xptr(dstreg+e1+32),xptr(dstreg+e1+48),screg1+32,screg1+64,screg1+160,dstreg+dstinc,e1,xptr(dstreg),xptr(dstreg+32)); \
	xprefetch(u8ptr(srcreg+srcinc+d1)); \
	shuffle_store_partial(xptr(dstreg), xptr(dstreg+16), xmm0, xmm7);				/* Save real value #1,R2 */ \
	shuffle_store_partial(xptr(dstreg+32), xptr(dstreg+48), xmm1, xmm5);			/* Save real value #2,I2 */ \
	shuffle_store_with_temp(xptr(dstreg+e1), xptr(dstreg+e1+16), xmm4, xmm6, xmm7);		/* Save R3,R4 */ \
	shuffle_store_with_temp(xptr(dstreg+e1+32), xptr(dstreg+e1+48), xmm3, xmm2, xmm7);	/* Save I3,I4 */ \
\
/* Do last two levels on the remaining complex data. */ \
/* Use sin/cos values for w^2, w^4, w^6 (we're doing two levels here and the sin/cos data is for three levels) */ \
\
	xprefetch(u8ptr(srcreg+srcinc+d2)); \
	r4_x4c_fft_mem(xptr(dstreg+e2),xptr(dstreg+e2+16),xptr(dstreg+e2+32),xptr(dstreg+e2+48),xptr(dstreg+e3),xptr(dstreg+e3+16),xptr(dstreg+e3+32),xptr(dstreg+e3+48),screg1+64,screg1+128,screg1+192,dstreg+dstinc+e2,e1,xptr(dstreg+e2),xptr(dstreg+e2+32)); \
	xprefetch(u8ptr(srcreg+srcinc+d2+d1)); \
	shuffle_store_partial(xptr(dstreg+e2), xptr(dstreg+e2+16), xmm2, xmm7);			/* Save R1,R2 */ \
	shuffle_store_partial(xptr(dstreg+e2+32), xptr(dstreg+e2+48), xmm5, xmm6);		/* Save I1,I2 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+e1), xptr(dstreg+e2+e1+16), xmm3, xmm0, xmm7);	/* Save R3,R4 */ \
	shuffle_store_with_temp(xptr(dstreg+e2+e1+32), xptr(dstreg+e2+e1+48), xmm1, xmm4, xmm7);	/* Save I3,I4 */ \
\
/* Now do the eight-complex part.   The code below is very similar to r8_s8c_fft8 */ \
/* except that we can eliminate the complex multiply of R1/I1 (because we are */ \
/* processing the first grouping and the sin/cos multiplier is 1). */ \
\
	xmm0 = xptr(srcreg+32);		/* R1 */ \
	xmm2 = xptr(srcreg+d4+32);		/* R5 */ \
	xmm2 += xmm0;			/* R5 = R1 + R5 (new R1) */ \
\
	xmm1 = xptr(srcreg+d2+32);		/* R3 */ \
	xmm3 = xptr(srcreg+d4+d2+32);		/* R7 */ \
	xmm3 += xmm1;			/* R7 = R3 + R7 (new R3) */ \
\
	xmm4 = xptr(srcreg+48);		/* I1 */ \
	xmm6 = xptr(srcreg+d4+48);		/* I5 */ \
	xmm6 += xmm4;			/* I5 = I1 + I5 (new I1) */ \
\
	xmm0 -= xptr(srcreg+d4+32);		/* R1 = R1 - R5 (new R5) */ \
	xmm1 -= xptr(srcreg+d4+d2+32);		/* R3 = R3 - R7 (new R7) */ \
\
	xmm5 = xmm3;			/* Copy R3 */ \
	xmm3 += xmm2;			/* R3 = R1 + R3 (final R1) */ \
	xmm2 -= xmm5;			/* R1 = R1 - R3 (final R3) */ \
\
	xmm5 = xptr(srcreg+d2+48);		/* I3 */ \
	xmm7 = xptr(srcreg+d4+d2+48);		/* I7 */ \
	xmm7 += xmm5;			/* I7 = I3 + I7 (new I3) */ \
\
	xmm4 -= xptr(srcreg+d4+48);		/* I1 = I1 - I5 (new I5) */ \
	xmm5 -= xptr(srcreg+d4+d2+48);		/* I3 = I3 - I7 (new I7) */ \
\
	xptr(dstreg+e4) = xmm3;		/* Save R1 */ \
\
	xmm3 = xmm7;			/* Copy I3 */ \
	xmm7 += xmm6;			/* I3 = I1 + I3 (final I1) */ \
	xmm6 -= xmm3;			/* I1 = I1 - I3 (final I3) */ \
\
	xptr(dstreg+e4+16) = xmm7;		/* Save I1 */ \
\
	xmm3 = xmm1;			/* Copy R7 */ \
	xmm1 += xmm4;			/* R7 = I5 + R7 (final I5) */ \
	xmm7 = xmm0;			/* Copy R5 */ \
	xmm0 -= xmm5;			/* R5 = R5 - I7 (final R5) */ \
	xmm4 -= xmm3;			/* I5 = I5 - R7 (final I7) */ \
	xmm5 += xmm7;			/* I7 = R5 + I7 (final R7) */ \
\
	xptr(dstreg+e4+e1) = xmm2;		/* Save R3 */ \
	xptr(dstreg+e4+e1+16) = xmm6;		/* Save I3 */ \
	xptr(dstreg+e4+e2) = xmm0;		/* Save R5 */ \
	xptr(dstreg+e4+e2+16) = xmm1;		/* Save I5 */ \
	xptr(dstreg+e4+e2+e1) = xmm5;		/* Save R7 */ \
	xptr(dstreg+e4+e2+e1+16) = xmm4;	/* Save I7 */ \
\
	xmm0 = xptr(srcreg+d1+32);		/* R2 */ \
	xmm2 = xptr(srcreg+d4+d1+32);		/* R6 */ \
	xmm2 += xmm0;			/* R6 = R2 + R6 (new R2) */ \
\
	xmm1 = xptr(srcreg+d2+d1+32);		/* R4 */ \
	xmm3 = xptr(srcreg+d4+d2+d1+32);	/* R8 */ \
	xmm3 += xmm1;			/* R8 = R4 + R8 (new R4) */ \
\
	xmm4 = xptr(srcreg+d1+48);		/* I2 */ \
	xmm6 = xptr(srcreg+d4+d1+48);		/* I6 */ \
	xmm6 += xmm4;			/* I6 = I2 + I6 (new I2) */ \
\
	xmm0 -= xptr(srcreg+d4+d1+32);		/* R2 = R2 - R6 (new R6) */ \
	xmm1 -= xptr(srcreg+d4+d2+d1+32);	/* R4 = R4 - R8 (new R8) */ \
\
	xmm5 = xmm3;			/* Copy R4 */ \
	xmm3 += xmm2;			/* R4 = R2 + R4 (final R2) */ \
	xmm2 -= xmm5;			/* R2 = R2 - R4 (final R4) */ \
\
	xmm5 = xptr(srcreg+d2+d1+48);		/* I4 */ \
	xmm7 = xptr(srcreg+d4+d2+d1+48);	/* I8 */ \
	xmm7 += xmm5;			/* I8 = I4 + I8 (new I4) */ \
\
	xmm4 -= xptr(srcreg+d4+d1+48);		/* I2 = I2 - I6 (new I6) */ \
	xmm5 -= xptr(srcreg+d4+d2+d1+48);	/* I4 = I4 - I8 (new I8) */ \
\
	xptr(dstreg+e4+32) = xmm3;		/* Save R2 */ \
\
	xmm3 = xmm7;			/* Copy I4 */ \
	xmm7 += xmm6;			/* I4 = I2 + I4 (final I2) */ \
	xmm6 -= xmm3;			/* I2 = I2 - I4 (final I4) */ \
\
	xptr(dstreg+e4+48) = xmm7;		/* Save I2 */ \
\
	xmm3 = xmm1;			/* Copy I6 */ \
	xmm1 += xmm4;			/* R8 = I6 + R8 (new I6) */ \
	xmm7 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm5;			/* R6 = R6 - I8 (new R6) */ \
	xmm4 -= xmm3;			/* I6 = I6 - R8 (new I8) */ \
	xmm5 += xmm7;			/* I8 = R6 + I8 (new R8) */ \
\
	xmm3 = xmm0;			/* Copy R6 */ \
	xmm0 -= xmm1;			/* R6 = R6 - I6 */ \
	xmm1 += xmm3;			/* I6 = R6 + I6 */ \
	xmm3 = XMM_SQRTHALF2; \
	xmm0 *= xmm3;			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm1 *= xmm3;			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm7 = xmm5;			/* Copy R8 */ \
	xmm5 -= xmm4;			/* R8 = R8 - I8 */ \
	xmm4 += xmm7;			/* I8 = R8 + I8 */ \
	xmm5 *= xmm3;			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm4 *= xmm3;			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	xptr(dstreg+e4+e1+32) = xmm2;		/* Save R4 */ \
	xptr(dstreg+e4+e1+48) = xmm6;		/* Save I4 */ \
	srcreg += srcinc; \
\
/* the last level */ \
\
	xmm2 = xptr(dstreg+e4+e2);		/* R5 */ \
	xmm2 -= xmm0;			/* R5 = R5 - R6 (new R6) */ \
	xmm0 += xptr(dstreg+e4+e2);		/* R6 = R5 + R6 (new R5) */ \
\
	xmm3 = xptr(dstreg+e4+e2+16);		/* I5 */ \
	xmm3 -= xmm1;			/* I5 = I5 - I6 (new I6) */ \
	xmm1 += xptr(dstreg+e4+e2+16);		/* I6 = I5 + I6 (new I5) */ \
\
	xmm6 = xptr(screg1+160+16);		/* cosine/sine */ \
	xmm6 *= xmm2;			/* A6 = R6 * cosine/sine */ \
	xmm6 -= xmm3;			/* A6 = A6 - I6 */ \
	xmm3 *= xptr(screg1+160+16);		/* B6 = I6 * cosine/sine */ \
	xmm3 += xmm2;			/* B6 = B6 + R6 */ \
\
	xmm2 = xptr(dstreg+e4+e2+e1);		/* R7 */ \
	xmm2 -= xmm4;			/* R7 = R7 - I8 (new R7) */ \
	xmm4 += xptr(dstreg+e4+e2+e1);		/* I8 = R7 + I8 (new R8) */ \
\
	xmm7 = xptr(screg1+32+16);		/* cosine/sine */ \
	xmm7 *= xmm0;			/* A5 = R5 * cosine/sine */ \
	xmm7 -= xmm1;			/* A5 = A5 - I5 */ \
	xmm1 *= xptr(screg1+32+16);		/* B5 = I5 * cosine/sine */ \
	xmm1 += xmm0;			/* B5 = B5 + R5 */ \
\
	xmm0 = xptr(dstreg+e4+e2+e1+16);	/* I7 */ \
	xmm0 -= xmm5;			/* I7 = I7 - R8 (new I8) */ \
	xmm5 += xptr(dstreg+e4+e2+e1+16);	/* R8 = I7 + R8 (new I7) */ \
\
	xmm6 *= xptr(screg1+160);		/* A6 = A6 * sine (final R6) */ \
	xmm7 *= xptr(screg1+32);		/* A5 = A5 * sine (final R5) */ \
	shuffle_store(xptr(dstreg+e4+e2), xptr(dstreg+e4+e2+16), xmm7, xmm6); /* Save R5,R6 */ \
\
	xmm6 = xptr(screg1+96+16);		/* cosine/sine */ \
	xmm6 *= xmm2;			/* A7 = R7 * cosine/sine */ \
	xmm6 -= xmm5;			/* A7 = A7 - I7 */ \
	xmm5 *= xptr(screg1+96+16);		/* B7 = I7 * cosine/sine */ \
	xmm5 += xmm2;			/* B7 = B7 + R7 */ \
\
	xmm3 *= xptr(screg1+160);		/* B6 = B6 * sine (final I6) */ \
	xmm1 *= xptr(screg1+32);		/* B5 = B5 * sine (final I5) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e4+e2+32), xptr(dstreg+e4+e2+48), xmm1, xmm3, xmm7); /* Save I5,I6 */ \
\
	xmm3 = xptr(screg1+224+16);		/* cosine/sine */ \
	xmm3 *= xmm4;			/* A8 = R8 * cosine/sine */ \
	xmm3 -= xmm0;			/* A8 = A8 - I8 */ \
	xmm0 *= xptr(screg1+224+16);		/* B8 = I8 * cosine/sine */ \
	xmm0 += xmm4;			/* B8 = B8 + R8 */ \
\
	xmm6 *= xptr(screg1+96);		/* A7 = A7 * sine (new R7) */ \
	xmm5 *= xptr(screg1+96);		/* B7 = B7 * sine (new I7) */ \
	xmm3 *= xptr(screg1+224);		/* A8 = A8 * sine (new R8) */ \
	xmm0 *= xptr(screg1+224);		/* B8 = B8 * sine (new I8) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e4+e2+e1), xptr(dstreg+e4+e2+e1+16), xmm6, xmm3, xmm4); /* Save R7,R8 */ \
	shuffle_store_with_temp(xptr(dstreg+e4+e2+e1+32), xptr(dstreg+e4+e2+e1+48), xmm5, xmm0, xmm4); /* Save I7,I8 */ \
\
	xmm3 = xptr(dstreg+e4);		/* R1 */ \
	xmm4 = xptr(dstreg+e4+32);		/* R2 */ \
	xmm3 -= xmm4;			/* R1 = R1 - R2 (new R2) */ \
	xmm4 += xptr(dstreg+e4);		/* R2 = R1 + R2 (final R1) */ \
\
	xmm7 = xptr(dstreg+e4+16);		/* I1 */ \
	xmm0 = xptr(dstreg+e4+48);		/* I2 */ \
	xmm7 -= xmm0;			/* I1 = I1 - I2 (new I2) */ \
	xmm0 += xptr(dstreg+e4+16);		/* I2 = I1 + I2 (final I1) */ \
\
	xmm1 = xptr(screg1+128+16);		/* cosine/sine */ \
	xmm1 *= xmm3;			/* A2 = R2 * cosine/sine */ \
	xmm1 -= xmm7;			/* A2 = A2 - I2 */ \
	xmm7 *= xptr(screg1+128+16);		/* B2 = I2 * cosine/sine */ \
	xmm7 += xmm3;			/* B2 = B2 + R2 */ \
\
	xmm1 *= xptr(screg1+128);		/* A2 = A2 * sine (final R2) */ \
	xmm7 *= xptr(screg1+128);		/* B2 = B2 * sine (final I2) */ \
\
	xmm5 = xptr(dstreg+e4+e1);		/* R3 */ \
	xmm6 = xptr(dstreg+e4+e1+48);		/* I4 */ \
	xmm5 -= xmm6;			/* R3 = R3 - I4 (new R3) */ \
	xmm6 += xptr(dstreg+e4+e1);		/* I4 = R3 + I4 (new R4) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e4), xptr(dstreg+e4+16), xmm4, xmm1, xmm3); /* Save R1,R2 */ \
\
	xmm3 = xptr(dstreg+e4+e1+16);		/* I3 */ \
	xmm2 = xptr(dstreg+e4+e1+32);		/* R4 */ \
	xmm3 -= xmm2;			/* I3 = I3 - R4 (final I4) */ \
	xmm2 += xptr(dstreg+e4+e1+16);		/* R4 = I3 + R4 (final I3) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e4+32), xptr(dstreg+e4+48), xmm0, xmm7, xmm1); /* Save I1,I2 */ \
\
	xmm1 = xptr(screg1+64+16);		/* cosine/sine */ \
	xmm1 *= xmm5;			/* A3 = R3 * cosine/sine */ \
	xmm1 -= xmm2;			/* A3 = A3 - I3 */ \
	xmm2 *= xptr(screg1+64+16);		/* B3 = I3 * cosine/sine */ \
	xmm2 += xmm5;			/* B3 = B3 + R3 */ \
\
	xmm7 = xptr(screg1+192+16);		/* cosine/sine */ \
	xmm7 *= xmm6;			/* A4 = R4 * cosine/sine */ \
	xmm7 -= xmm3;			/* A4 = A4 - I4 */ \
	xmm3 *= xptr(screg1+192+16);		/* B4 = I4 * cosine/sine */ \
	xmm3 += xmm6;			/* B4 = B4 + R4 */ \
\
	xmm1 *= xptr(screg1+64);		/* A3 = A3 * sine (final R3) */ \
	xmm2 *= xptr(screg1+64);		/* B3 = B3 * sine (final I3) */ \
	xmm7 *= xptr(screg1+192);		/* A4 = A4 * sine (final R4) */ \
	xmm3 *= xptr(screg1+192);		/* B4 = B4 * sine (final I4) */ \
\
	shuffle_store_with_temp(xptr(dstreg+e4+e1), xptr(dstreg+e4+e1+16), xmm1, xmm7, xmm0); /* Save R3,R4 */ \
	shuffle_store_with_temp(xptr(dstreg+e4+e1+32), xptr(dstreg+e4+e1+48), xmm2, xmm3, xmm0); /* Save I3,I4 */ \
	dstreg += dstinc; \
}

/* */ \
/* ************************************* sixteen-reals-unfft8 variants ****************************************** */ \
/* */ \
\
/* Used in last levels of pass 1 (split premultiplier and delay cases).  No swizzling. */
#if 0 // UNUSED

#define r8_g4cl_sixteen_reals_unfft8(srcreg,srcinc,d1,d2,dstreg,dstinc,e1,e2,screg1,screg2) \
	not written; \

#endif
\
/* Used in last levels of pass 1 (split premultiplier and delay cases).  Swizzling. */ \

#define r8_sg4cl_sixteen_reals_unfft8(srcreg,srcinc,d1,d2,dstreg,dstinc,e1,e2,screg1,screg2) { \
\
/* Do 2 3/4 levels of unfft on the first eight values. */ \
\
	r4_s8r_unfft4(xptr(srcreg),xptr(srcreg+32),xptr(srcreg+16),xptr(srcreg+48),xptr(srcreg+d1),xptr(srcreg+d1+32),xptr(srcreg+d1+16),xptr(srcreg+d1+48),screg1+32,screg1+64,screg1+160,dstreg+dstinc,e1,xptr(dstreg+e2+e1),xptr(dstreg+e2+e1+16)); \
	vec2f64 saved_R1 = xmm1;		/* Save R1 */ \
	vec2f64 saved_R5 = xmm0;	/* Save R5 */ \
	vec2f64 saved_R2 = xmm4;	/* Save R2 */ \
	vec2f64 saved_R6 = xmm3;	/* Save R6 */ \
	vec2f64 saved_R3 = xmm7;	/* Save R3 */ \
	vec2f64 saved_R7 = xmm6;	/* Save R7 */ \
/*	xstore	[dstreg+e2+e1+16], xmm2	;; Save R8 */ \
/*	xstore	[dstreg+e2+e1], xmm5	;; Save R4 */ \
\
/* Do 2 levels of unfft on the second eight values.  Similar to r4_sg2cl_four_complex_unfft4 */ \
/* except there are only 3 sin/cos multiplies (by w^2, w^4, w^6). */ \
\
	shuffle_load_with_temp(xmm6, xmm2, xptr(srcreg+d2), xptr(srcreg+d2+16), xmm4); /* R1,R2 */ \
	xmm4 = xmm2;			/* Copy R2 */ \
	xmm2 *= xptr(screg1+128+16);		/* A2 = R2 * cosine/sine */ \
	shuffle_load_with_temp(xmm1, xmm3, xptr(srcreg+d2+32), xptr(srcreg+d2+48), xmm7); /* I1,I2 */ \
	xmm2 += xmm3;			/* A2 = A2 + I2 */ \
	xmm3 *= xptr(screg1+128+16);		/* B2 = I2 * cosine/sine */ \
	xmm3 -= xmm4;			/* B2 = B2 - R2 */ \
	xmm2 *= xptr(screg1+128);		/* A2 = A2 * sine (new R2) */ \
\
	shuffle_load_with_temp(xmm7, xmm0, xptr(srcreg+d2+d1), xptr(srcreg+d2+d1+16), xmm4); /* R3,R4 */ \
	xmm4 = xmm7;			/* Copy R3 */ \
	xmm7 *= xptr(screg1+64+16);		/* A3 = R3 * cosine/sine */ \
	xmm5 = xmm0;			/* Copy R4 */ \
	xmm0 *= xptr(screg1+192+16);		/* A4 = R4 * cosine/sine */ \
\
	vec2f64 saved_R1b = xmm6;		/* Save new R1 temporarily */ \
	vec2f64 saved_R2b = xmm2;		/* Save new R2 temporarily */ \
\
	shuffle_load(xmm6, xmm2, xptr(srcreg+d2+d1+32), xptr(srcreg+d2+d1+48)); /* I3,I4 */ \
\
	xmm7 += xmm6;			/* A3 = A3 + I3 */ \
	xmm6 *= xptr(screg1+64+16);		/* B3 = I3 * cosine/sine */ \
	xmm0 += xmm2;			/* A4 = A4 + I4 */ \
	xmm2 *= xptr(screg1+192+16);		/* B4 = I4 * cosine/sine */ \
	xmm6 -= xmm4;			/* B3 = B3 - R3 */ \
	xmm2 -= xmm5;			/* B4 = B4 - R4 */ \
\
	xmm3 *= xptr(screg1+128);		/* B2 = B2 * sine (new I2) */ \
	xmm7 *= xptr(screg1+64);		/* A3 = A3 * sine (new R3) */ \
	xmm0 *= xptr(screg1+192);		/* A4 = A4 * sine (new R4) */ \
	xmm6 *= xptr(screg1+64);		/* B3 = B3 * sine (new I3) */ \
	xmm2 *= xptr(screg1+192);		/* B4 = B4 * sine (new I4) */ \
\
	xmm4 = xmm1;			/* Copy I1 */ \
	xmm1 -= xmm3;			/* I1 = I1 - I2 (new I2) */ \
	xmm3 += xmm4;			/* I2 = I1 + I2 (new I1) */ \
\
	xprefetchw(u8ptr(dstreg+dstinc+e2)); \
	srcreg += srcinc; \
\
	xmm4 = xmm0;			/* Copy R4 */ \
	xmm0 -= xmm7;			/* R4 = R4 - R3 (new I4) */ \
	xmm7 += xmm4;			/* R3 = R4 + R3 (new R3) */ \
\
	xmm4 = xmm6;			/* Copy I3 */ \
	xmm6 -= xmm2;			/* I3 = I3 - I4 (new R4) */ \
	xmm2 += xmm4;			/* I4 = I3 + I4 (new I3) */ \
\
	xmm4 = xmm1;			/* Copy I2 */ \
	xmm1 -= xmm0;			/* I2 = I2 - I4 (final I4) */ \
	xmm0 += xmm4;			/* I4 = I2 + I4 (final I2) */ \
\
	xmm4 = saved_R1b;		/* Reload new R1 */ \
	xmm5 = saved_R2b;		/* Reload new R2 */ \
	xmm4 -= xmm5;			/* R1 = R1 - R2 (new R2) */ \
	xmm5 += saved_R1b;		/* R2 = R1 + R2 (new R1) */ \
\
	xptr(dstreg+e2+e1+48) = xmm1;		/* Save I4 (new I12) */ \
\
	xmm1 = xmm3;			/* Copy I1 */ \
	xmm3 -= xmm2;			/* I1 = I1 - I3 (final I3) */ \
	xmm2 += xmm1;			/* I3 = I1 + I3 (final I1) */ \
\
	xmm1 = xmm4;			/* Copy R2 */ \
	xmm4 -= xmm6;			/* R2 = R2 - R4 (final R4) */ \
	xmm6 += xmm1;			/* R4 = R2 + R4 (final R2) */ \
\
	xprefetchw(u8ptr(dstreg+dstinc+e2+e1)); \
\
	xmm1 = xmm5;			/* Copy R1 */ \
	xmm5 -= xmm7;			/* R1 = R1 - R3 (final R3) */ \
	xmm7 += xmm1;			/* R3 = R1 + R3 (final R1) */ \
\
/*	xstore	[dstreg+32], xmm7		;; Save R1 (new R9) */ \
/*	xstore	[dstreg+48], xmm2		;; Save I1 (new I9) */ \
/*	xstore	[dstreg+e1+32], xmm6		;; Save R2 (new R10) */ \
/*	xstore	[dstreg+e1+48], xmm0		;; Save I2 (new I10) */ \
/*	xstore	[dstreg+e2+32], xmm5		;; Save R3 (new R11) */ \
/*	xstore	[dstreg+e2+48], xmm3		;; Save I3 (new I11) */ \
	xptr(dstreg+e2+e1+32) = xmm4;		/* Save R4 (new R12) */ \
\
/* Do first level on the first 8 reals and 2 levels on the last 8 reals. */ \
/* The second level on the last eight reals is the multiply by i (the nop level). */ \
\
	xmm1 = xptr(screg2+16);	/* cosine/sine */ \
	xmm4 = xmm7;		/* Copy R9 */ \
	xmm7 *= xmm1;		/* A9 = R9 * cosine/sine */ \
	xmm7 += xmm2;		/* A9 = A9 + I9 */ \
	xmm2 *= xmm1;		/* B9 = I9 * cosine/sine */ \
	xmm2 -= xmm4;		/* B9 = B9 - R9 */ \
	xmm7 *= xptr(screg2);		/* A9 = A9 * sine (new R9) */ \
	xmm2 *= xptr(screg2);		/* B9 = B9 * sine (new R13) */ \
\
	xmm1 = saved_R1;		/* R1 */ \
	xmm1 -= xmm7;		/* new R9 = R1 - R9 */ \
	xmm7 += saved_R1;		/* new R1 = R1 + R9 */ \
	xptr(dstreg) = xmm7;		/* Save R1 */ \
	xptr(dstreg+32) = xmm1;	/* Save R9 */ \
\
	xmm1 = saved_R5;	/* R5 */ \
	xmm1 -= xmm2;		/* new R13 = R5 - R13 */ \
	xmm2 += saved_R5;	/* new R5 = R5 + R13 */ \
	xptr(dstreg+16) = xmm2;	/* Save R5 */ \
	xptr(dstreg+48) = xmm1;	/* Save R13 */ \
\
	xmm1 = xptr(screg2+32+16);	/* cosine/sine */ \
	xmm4 = xmm6;		/* Copy R10 */ \
	xmm6 *= xmm1;		/* A10 = R10 * cosine/sine */ \
	xmm6 += xmm0;		/* A10 = A10 + I10 */ \
	xmm0 *= xmm1;		/* B10 = I10 * cosine/sine */ \
	xmm0 -= xmm4;		/* B10 = B10 - R10 */ \
	xmm6 *= xptr(screg2+32);	/* A10 = A10 * sine (new R10) */ \
	xmm0 *= xptr(screg2+32);	/* B10 = B10 * sine (new R14) */ \
\
	xmm1 = saved_R2;	/* R2 */ \
	xmm1 -= xmm6;		/* new R10 = R2 - R10 */ \
	xmm6 += saved_R2;	/* new R2 = R2 + R10 */ \
	xptr(dstreg+e1) = xmm6;	/* Save R2 */ \
	xptr(dstreg+e1+32) = xmm1;	/* Save R10 */ \
\
	xmm1 = saved_R6;	/* R6 */ \
	xmm1 -= xmm0;		/* new R14 = R6 - R14 */ \
	xmm0 += saved_R6;	/* new R6 = R6 + R14 */ \
	xptr(dstreg+e1+16) = xmm0;	/* Save R6 */ \
	xptr(dstreg+e1+48) = xmm1;	/* Save R14 */ \
\
	xmm1 = xptr(screg2+64+16);	/* cosine/sine */ \
	xmm4 = xmm5;		/* Copy R11 */ \
	xmm5 *= xmm1;		/* A11 = R11 * cosine/sine */ \
	xmm5 += xmm3;		/* A11 = A11 + I11 */ \
	xmm3 *= xmm1;		/* B11 = I11 * cosine/sine */ \
	xmm3 -= xmm4;		/* B11 = B11 - R11 */ \
	xmm5 *= xptr(screg2+64);	/* A11 = A11 * sine (new R11) */ \
	xmm3 *= xptr(screg2+64);	/* B11 = B11 * sine (new R15) */ \
\
	xmm1 = saved_R3;	/* R3 */ \
	xmm1 -= xmm5;		/* new R11 = R3 - R11 */ \
	xmm5 += saved_R3;	/* new R3 = R3 + R11 */ \
	xptr(dstreg+e2) = xmm5;	/* Save R3 */ \
	xptr(dstreg+e2+32) = xmm1;	/* Save R11 */ \
\
	xmm1 = saved_R7;	/* R7 */ \
	xmm1 -= xmm3;		/* new R15 = R7 - R15 */ \
	xmm3 += saved_R7;	/* new R7 = R7 + R15 */ \
	xptr(dstreg+e2+16) = xmm3;	/* Save R7 */ \
	xptr(dstreg+e2+48) = xmm1;	/* Save R15 */ \
\
	xmm1 = xptr(screg2+96+16);	/* cosine/sine */ \
	xmm1 *= xptr(dstreg+e2+e1+32);	/* A12 = R12 * cosine/sine */ \
	xmm4 = xptr(dstreg+e2+e1+48);	/* I12 */ \
	xmm1 += xmm4;		/* A12 = A12 + I12 */ \
	xmm4 *= xptr(screg2+96+16);	/* B12 = I12 * cosine/sine */ \
	xmm4 -= xptr(dstreg+e2+e1+32);	/* B12 = B12 - R12 */ \
	xmm1 *= xptr(screg2+96);	/* A12 = A12 * sine (new R12) */ \
	xmm4 *= xptr(screg2+96);	/* B12 = B12 * sine (new R16) */ \
\
	xmm0 = xptr(dstreg+e2+e1);	/* R4 */ \
	xmm0 -= xmm1;		/* new R12 = R4 - R12 */ \
	xmm1 += xptr(dstreg+e2+e1);	/* new R4 = R4 + R12 */ \
	xptr(dstreg+e2+e1) = xmm1;	/* Save R4 */ \
	xptr(dstreg+e2+e1+32) = xmm0;	/* Save R12 */ \
\
	xmm0 = xptr(dstreg+e2+e1+16);	/* R8 */ \
	xmm0 -= xmm4;		/* new R16 = R8 - R16 */ \
	xmm4 += xptr(dstreg+e2+e1+16);	/* new R8 = R8 + R16 */ \
	xptr(dstreg+e2+e1+16) = xmm4;	/* Save R8 */ \
	xptr(dstreg+e2+e1+48) = xmm0;	/* Save R16 */ \
	dstreg += dstinc; \
}


/* */ \
/* ********************************* half-sixteen-reals-eight-complex-fft-with-square variants *************************************** */ \
/* */ \
\
/* Macro to do a sixteen_reals_fft and three eight_complex_djbfft in the final levels of pass 2. */ \
/* The sixteen-reals macro and one of the eight-complex only use half the XMM  */ \
/* register.  This isn't very efficient, but this macro is called only once. */ \
\

#if 0
#define r8_h8cl_sixteen_reals_eight_complex_fft_final(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_h16r_simple_fft_part1_16r(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_part2_16r(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_h16r_simple_fft_part1_8c(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_part2_8c(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_part2(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#elif 1
#define r8_h8cl_sixteen_reals_eight_complex_fft_final(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_part2(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	r8_h16r_simple_fft_part2(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_h8cl_sixteen_reals_eight_complex_fft_final(srcreg,srcinc,d1,d2,d4) \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_h16r_simple_fft_part2(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_part2((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#if 1
#define r8_h16r_simple_fft_part1(srcreg,d1,d2,d4,dst) { \
	/* */ \
	/* Do the 16-reals part */ \
	/* */ \
\
	/* Odd level 1 */ \
\
	xmm0[0] = f64ptr(srcreg);		/* R1 */ \
	xmm1[0] = f64ptr(srcreg+16);		/* R9 */ \
	xmm7[0] = xmm1[0];			/* Copy R9 */ \
	xmm1[0] += xmm0[0];			/* R9 = R1 + R9 (new R1) */ \
	xmm0[0] -= xmm7[0];			/* R1 = R1 - R9 (new R9) */ \
\
	xmm2[0] = f64ptr(srcreg+d4);		/* R5 */ \
	xmm3[0] = f64ptr(srcreg+d4+16);		/* R13 */ \
	xmm7[0] = xmm3[0];			/* Copy R13 */ \
	xmm3[0] += xmm2[0];			/* R13 = R5 + R13 (new R5) */ \
	xmm2[0] -= xmm7[0];			/* R5 = R5 - R13 (new R13) */ \
\
	xmm4[0] = f64ptr(srcreg+d2);		/* R3 */ \
	xmm5[0] = f64ptr(srcreg+d2+16);		/* R11 */ \
	xmm7[0] = xmm5[0];			/* Copy R11 */ \
	xmm5[0] += xmm4[0];			/* R11 = R3 + R11 (new R3) */ \
	xmm4[0] -= xmm7[0];			/* R3 = R3 - R11 (new R11) */ \
\
	xmm6[0] = f64ptr(srcreg+d4+d2);		/* R7 */ \
	xmm7[0] = f64ptr(srcreg+d4+d2+16);	/* R15 */ \
	xmm7[0] += xmm6[0];			/* R15 = R7 + R15 (new R7) */ \
	xmm6[0] -= f64ptr(srcreg+d4+d2+16);	/* R7 = R7 - R15 (new R15) */ \
\
;	/* Odd level 2 */ \
\
	xmm1[0] -= xmm3[0];			/* R1 = R1 - R5 (newer R5 & final R5) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm1[0];			/* R5 = R1 + R5 (newer R1) */ \
\
	xmm5[0] -= xmm7[0];			/* R3 = R3 - R7 (newer R7 & final I5) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm5[0];			/* R7 = R3 + R7 (newer R3) */ \
\
;						/* R9/R13 morphs into newer R9/I9 */ \
;						/* R11/R15 morphs into newer R11/I11 */ \
\
;	/* Premultipliers for odd level 3 */ \
\
;						/* mul R11/I11 by SQRTHALF + i*SQRTHALF */ \
	xmm4[0] -= xmm6[0];			/* R11 = R11 - I11 */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm4[0];			/* I11 = R11 + I11 */ \
	xmm4[0] *= XMM_SQRTHALF1;		/* R11 = R11 * SQRTHALF */ \
	xmm6[0] *= XMM_SQRTHALF1;		/* I11 = I11 * SQRTHALF */ \
\
;	/* Odd level 3 */ \
\
	xmm3[0] -= xmm7[0];			/* R1 = R1 - R3 (final R3) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm3[0];			/* R3 = R1 + R3 (final R1) */ \
\
;						/* R5/R7 morphs into final R5/I5 */ \
\
	xmm0[0] -= xmm4[0];			/* R9 = R9 - R11 (final R11) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm0[0];			/* R9 = R9 + R11 (final R9) */ \
\
	xmm2[0] -= xmm6[0];			/* I9 = I9 - I11 (final I11) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm2[0];			/* I9 = I9 + I11 (final I9) */ \
\
\
	xmm4[1] = f64ptr(srcreg+8);		/* R1 */ \
	xmm1[1] = f64ptr(srcreg+d4+8);		/* R5 */ \
	xmm3[1] = xmm1[1];			/* Copy R5 */ \
	xmm1[1] += xmm4[1];			/* R5 = R1 + R5 (new R1) */ \
	xmm4[1] -= xmm3[1];			/* R1 = R1 - R5 (new R5) */ \
\
	xmm6[1] = f64ptr(srcreg+d2+8);		/* R3 */ \
	xmm7[1] = f64ptr(srcreg+d4+d2+8);	/* R7 */ \
	xmm3[1] = xmm7[1];			/* Copy R7 */ \
	xmm7[1] += xmm6[1];			/* R7 = R3 + R7 (new R3) */ \
	xmm6[1] -= xmm3[1];			/* R3 = R3 - R7 (new R7) */ \
\
	xmm2[1] = f64ptr(srcreg+16+8);		/* I1 */ \
	xmm5[1] = f64ptr(srcreg+d4+16+8);	/* I5 */ \
	xmm3[1] = xmm5[1];			/* Copy I5 */ \
	xmm5[1] += xmm2[1];			/* I5 = I1 + I5 (new I1) */ \
	xmm2[1] -= xmm3[1];			/* I1 = I1 - I5 (new I5) */ \
\
	xmm3[1] = xmm7[1];			/* Copy R3 */ \
	xmm7[1] += xmm1[1];			/* R3 = R1 + R3 (final R1) */ \
	xmm1[1] -= xmm3[1];			/* R1 = R1 - R3 (final R3) */ \
\
	xptr2(dst,0) = xmm7;			/* Save R1 R1 */ \
	xptr2(dst,d1) = xmm1;			/* Save R5 R3 */ \
\
	xmm0[1] = f64ptr(srcreg+d2+16+8);	/* I3 */ \
	xmm7[1] = f64ptr(srcreg+d4+d2+16+8);	/* I7 */ \
	xmm3[1] = xmm7[1];			/* Copy I7 */ \
	xmm7[1] += xmm0[1];			/* I7 = I3 + I7 (new I3) */ \
	xmm0[1] -= xmm3[1];			/* I3 = I3 - I7 (new I7) */ \
\
	xmm3[1] = xmm7[1];			/* Copy I3 */ \
	xmm3[1] += xmm5[1];			/* I3 = I1 + I3 (final I1) */ \
	xmm5[1] -= xmm7[1];			/* I1 = I1 - I3 (final I3) */ \
\
	xptr2(dst,32) = xmm3;			/* Save R3 I1 */ \
	xptr2(dst,d1+32) = xmm5;		/* Save I5 I3 */ \
\
	xmm7[1] = xmm6[1];			/* Copy R7 */ \
	xmm6[1] += xmm2[1];			/* R7 = I5 + R7 (final I5) */ \
	xmm3[1] = xmm4[1];			/* Copy R5 */ \
	xmm4[1] -= xmm0[1];			/* R5 = R5 - I7 (final R5) */ \
	xmm2[1] -= xmm7[1];			/* I5 = I5 - R7 (final I7) */ \
	xmm0[1] += xmm3[1];			/* I7 = R5 + I7 (final R7) */ \
\
	xptr2(dst,d2) = xmm4;			/* Save R9 R5 */ \
	xptr2(dst,d2+32) = xmm6;		/* Save I9 I5 */ \
	xptr2(dst,d2+d1) = xmm0;		/* Save R11 R7 */ \
	xptr2(dst,d2+d1+32) = xmm2;		/* Save I11 I7 */ \
\
\
;	/* Even level 1 */ \
\
	xmm0[0] = f64ptr(srcreg+d1);		/* R2 */ \
	xmm1[0] = f64ptr(srcreg+d1+16);		/* R10 */ \
	xmm7[0] = xmm1[0];			/* Copy R10 */ \
	xmm1[0] += xmm0[0];			/* R10 = R2 + R10 (new R2) */ \
	xmm0[0] -= xmm7[0];			/* R2 = R2 - R10 (new R10) */ \
\
	xmm2[0] = f64ptr(srcreg+d4+d1);		/* R6 */ \
	xmm3[0] = f64ptr(srcreg+d4+d1+16);	/* R14 */ \
	xmm7[0] = xmm3[0];			/* Copy R14 */ \
	xmm3[0] += xmm2[0];			/* R14 = R6 + R14 (new R6) */ \
	xmm2[0] -= xmm7[0];			/* R6 = R6 - R14 (new R14) */ \
\
	xmm4[0] = f64ptr(srcreg+d2+d1);		/* R4 */ \
	xmm5[0] = f64ptr(srcreg+d2+d1+16);	/* R12 */ \
	xmm7[0] = xmm5[0];			/* Copy R12 */ \
	xmm5[0] += xmm4[0];			/* R12 = R4 + R12 (new R4) */ \
	xmm4[0] -= xmm7[0];			/* R4 = R4 - R12 (new R12) */ \
\
	xmm6[0] = f64ptr(srcreg+d4+d2+d1);	/* R8 */ \
	xmm7[0] = f64ptr(srcreg+d4+d2+d1+16);	/* R16 */ \
	xmm7[0] += xmm6[0];			/* R16 = R8 + R16 (new R8) */ \
	xmm6[0] -= f64ptr(srcreg+d4+d2+d1+16);	/* R8 = R8 - R16 (new R16) */ \
\
;	/* Even level 2 */ \
\
	xmm1[0] -= xmm3[0];			/* R2 = R2 - R6 (newer R6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm1[0];			/* R6 = R2 + R6 (newer R2) */ \
\
	xmm5[0] -= xmm7[0];			/* R4 = R4 - R8 (newer R8) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm5[0];			/* R8 = R4 + R8 (newer R4) */ \
\
;						/* R10/R14 morphs into newer R10/I10 */ \
;						/* R12/R16 morphs into newer R12/I12 */ \
\
;	/* Premultipliers for even level 3 */ \
\
	double tmp16 = xmm1[0]; \
	double tmp48 = xmm3[0]; \
\
;						/* mul R10/I10 by w^1 = .924 + .383i */ \
	xmm1[0] = xmm0[0];			/* Copy R10 */ \
	xmm0[0] *= CONST_P924; \
	xmm3[0] = xmm2[0];			/* Copy I10 */ \
	xmm3[0] *= CONST_P383; \
	xmm0[0] -= xmm3[0];			/* Twiddled R10 */ \
	xmm1[0] *= CONST_P383; \
	xmm2[0] *= CONST_P924; \
	xmm2[0] += xmm1[0];			/* Twiddled I10 */ \
\
;						/* mul R12/I12 by w^3 = .383 + .924i */ \
	xmm1[0] = xmm4[0];			/* Copy R12 */ \
	xmm4[0] *= CONST_P383; \
	xmm3[0] = xmm6[0];			/* Copy I12 */ \
	xmm3[0] *= CONST_P924; \
	xmm4[0] -= xmm3[0];			/* Twiddled R12 */ \
	xmm1[0] *= CONST_P924; \
	xmm6[0] *= CONST_P383; \
	xmm6[0] += xmm1[0];			/* Twiddled I12 */ \
\
	xmm1[0] = tmp16; \
	xmm3[0] = tmp48; \
\
;	/* Even level 3 */ \
\
	xmm3[0] -= xmm7[0];			/* R2 = R2 - R4 (final R4) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm3[0];			/* R4 = R2 + R4 (final R2) */ \
\
;						/* R6/R8 morph into newer R6/I6 */ \
\
	xmm0[0] -= xmm4[0];			/* R10 = R10 - R12 (final R12) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm0[0];			/* R10 = R10 + R12 (final R10) */ \
\
	xmm2[0] -= xmm6[0];			/* I10 = I10 - I12 (final I12) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm2[0];			/* I10 = I10 + I12 (final I10) */ \
\
;	/* Premultipliers for even level 4 */ \
\
;						/* mul R6/I6 by w^2 = .707 + .707i */ \
	xmm1[0] -= xmm5[0];			/* R6 = R6 - I6 */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm1[0];			/* I6 = R6 + I6 */ \
	xmm1[0] *= XMM_SQRTHALF1;		/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm5[0] *= XMM_SQRTHALF1;		/* I6 = I6 * SQRTHALF (final I6) */ \
\
\
	xmm4[1] = f64ptr(srcreg+d1+8);		/* R2 */ \
	xmm1[1] = f64ptr(srcreg+d4+d1+8);	/* R6 */ \
	xmm3[1] = xmm1[1];			/* Copy R6 */ \
	xmm1[1] += xmm4[1];			/* R6 = R2 + R6 (new R2) */ \
	xmm4[1] -= xmm3[1];			/* R2 = R2 - R6 (new R6) */ \
\
	xmm6[1] = f64ptr(srcreg+d2+d1+8);	/* R4 */ \
	xmm7[1] = f64ptr(srcreg+d4+d2+d1+8);	/* R8 */ \
	xmm3[1] = xmm7[1];			/* Copy R8 */ \
	xmm7[1] += xmm6[1];			/* R8 = R4 + R8 (new R4) */ \
	xmm6[1] -= xmm3[1];			/* R4 = R4 - R8 (new R8) */ \
\
	xmm2[1] = f64ptr(srcreg+d1+16+8);	/* I2 */ \
	xmm5[1] = f64ptr(srcreg+d4+d1+16+8);	/* I6 */ \
	xmm3[1] = xmm5[1];			/* Copy I6 */ \
	xmm5[1] += xmm2[1];			/* I6 = I2 + I6 (new I2) */ \
	xmm2[1] -= xmm3[1];			/* I2 = I2 - I6 (new I6) */ \
\
	xmm3[1] = xmm7[1];			/* Copy R4 */ \
	xmm7[1] += xmm1[1];			/* R4 = R2 + R4 (final R2) */ \
	xmm1[1] -= xmm3[1];			/* R2 = R2 - R4 (final R4) */ \
\
	xptr2(dst,16) = xmm7;			/* Save R2 R2 */ \
	xptr2(dst,d1+16) = xmm1;			/* Save R6 R4 */ \
\
	xmm0[1] = f64ptr(srcreg+d2+d1+16+8);	/* I4 */ \
	xmm7[1] = f64ptr(srcreg+d4+d2+d1+16+8);	/* I8 */ \
	xmm3[1] = xmm7[1];			/* Copy I8 */ \
	xmm7[1] += xmm0[1];			/* I8 = I4 + I8 (new I4) */ \
	xmm0[1] -= xmm3[1];			/* I4 = I4 - I8 (new I8) */ \
\
	xmm3[1] = xmm7[1];			/* Copy I4 */ \
	xmm3[1] += xmm5[1];			/* I4 = I2 + I4 (final I2) */ \
	xmm5[1] -= xmm7[1];			/* I2 = I2 - I4 (final I4) */ \
\
	xptr2(dst,48) = xmm3;			/* Save R4 I2 */ \
	xptr2(dst,d1+48) = xmm5;			/* Save I6 I4 */ \
\
	xmm7[1] = xmm6[1];			/* Copy R8 */ \
	xmm6[1] += xmm2[1];			/* R8 = I6 + R8 (new I6) */ \
	xmm3[1] = xmm4[1];			/* Copy R6 */ \
	xmm4[1] -= xmm0[1];			/* R6 = R6 - I8 (new R6) */ \
	xmm2[1] -= xmm7[1];			/* I6 = I6 - R8 (new I8) */ \
	xmm0[1] += xmm3[1];			/* I8 = R6 + I8 (new R8) */ \
\
	xmm3[1] = xmm4[1];			/* Copy R6 */ \
	xmm4[1] -= xmm6[1];			/* R6 = R6 - I6 */ \
	xmm6[1] += xmm3[1];			/* I6 = R6 + I6 */ \
	xmm7[1] = XMM_SQRTHALF1; \
	xmm4[1] *= xmm7[1];			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm6[1] *= xmm7[1];			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm3[1] = xmm0[1];			/* Copy R8 */ \
	xmm0[1] -= xmm2[1];			/* R8 = R8 - I8 */ \
	xmm2[1] += xmm3[1];			/* I8 = R8 + I8 */ \
	xmm0[1] *= xmm7[1];			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm2[1] *= xmm7[1];			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	xptr2(dst,d2+16) = xmm4;		/* Save R10 R6 */ \
	xptr2(dst,d2+48) = xmm6;		/* Save I10 I6 */ \
	xptr2(dst,d2+d1+16) = xmm0;		/* Save R12 R8 */ \
	xptr2(dst,d2+d1+48) = xmm2;		/* Save I12 I8 */ \
}
#else
#define r8_h16r_simple_fft_part1(srcreg,d1,d2,d4,dst) \
	r8_h16r_simple_fft_part1_16r(srcreg,d1,d2,d4,dst) \
	r8_h16r_simple_fft_part1_8c(srcreg,d1,d2,d4,dst)
#endif

#define r8_h16r_simple_fft_part1_16r(srcreg,d1,d2,d4,dst) { \
	/* */ \
	/* Do the 16-reals part */ \
	/* */ \
\
	/* Odd level 1 */ \
\
	xmm0[0] = f64ptr(srcreg);		/* R1 */ \
	xmm1[0] = f64ptr(srcreg+16);		/* R9 */ \
	xmm7[0] = xmm1[0];			/* Copy R9 */ \
	xmm1[0] += xmm0[0];			/* R9 = R1 + R9 (new R1) */ \
	xmm0[0] -= xmm7[0];			/* R1 = R1 - R9 (new R9) */ \
\
	xmm2[0] = f64ptr(srcreg+d4);		/* R5 */ \
	xmm3[0] = f64ptr(srcreg+d4+16);		/* R13 */ \
	xmm7[0] = xmm3[0];			/* Copy R13 */ \
	xmm3[0] += xmm2[0];			/* R13 = R5 + R13 (new R5) */ \
	xmm2[0] -= xmm7[0];			/* R5 = R5 - R13 (new R13) */ \
\
	xmm4[0] = f64ptr(srcreg+d2);		/* R3 */ \
	xmm5[0] = f64ptr(srcreg+d2+16);		/* R11 */ \
	xmm7[0] = xmm5[0];			/* Copy R11 */ \
	xmm5[0] += xmm4[0];			/* R11 = R3 + R11 (new R3) */ \
	xmm4[0] -= xmm7[0];			/* R3 = R3 - R11 (new R11) */ \
\
	xmm6[0] = f64ptr(srcreg+d4+d2);		/* R7 */ \
	xmm7[0] = f64ptr(srcreg+d4+d2+16);	/* R15 */ \
	xmm7[0] += xmm6[0];			/* R15 = R7 + R15 (new R7) */ \
	xmm6[0] -= f64ptr(srcreg+d4+d2+16);	/* R7 = R7 - R15 (new R15) */ \
\
;	/* Odd level 2 */ \
\
	xmm1[0] -= xmm3[0];			/* R1 = R1 - R5 (newer R5 & final R5) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm1[0];			/* R5 = R1 + R5 (newer R1) */ \
\
	xmm5[0] -= xmm7[0];			/* R3 = R3 - R7 (newer R7 & final I5) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm5[0];			/* R7 = R3 + R7 (newer R3) */ \
\
;						/* R9/R13 morphs into newer R9/I9 */ \
;						/* R11/R15 morphs into newer R11/I11 */ \
\
;	/* Premultipliers for odd level 3 */ \
\
;						/* mul R11/I11 by SQRTHALF + i*SQRTHALF */ \
	xmm4[0] -= xmm6[0];			/* R11 = R11 - I11 */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm4[0];			/* I11 = R11 + I11 */ \
	xmm4[0] *= XMM_SQRTHALF1;		/* R11 = R11 * SQRTHALF */ \
	xmm6[0] *= XMM_SQRTHALF1;		/* I11 = I11 * SQRTHALF */ \
\
;	/* Odd level 3 */ \
\
	xmm3[0] -= xmm7[0];			/* R1 = R1 - R3 (final R3) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm3[0];			/* R3 = R1 + R3 (final R1) */ \
\
;						/* R5/R7 morphs into final R5/I5 */ \
\
	xmm0[0] -= xmm4[0];			/* R9 = R9 - R11 (final R11) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm0[0];			/* R9 = R9 + R11 (final R9) */ \
\
	xmm2[0] -= xmm6[0];			/* I9 = I9 - I11 (final I11) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm2[0];			/* I9 = I9 + I11 (final I9) */ \
\
	f64ptr2(dst,0) = xmm7[0];			/* Save R1 */ \
	f64ptr2(dst,32) = xmm3[0];			/* Save R3 */ \
	f64ptr2(dst,d1) = xmm1[0];			/* Save R5 */ \
	f64ptr2(dst,d1+32) = xmm5[0];		/* Save I5 */ \
	f64ptr2(dst,d2) = xmm4[0];			/* Save R9 */ \
	f64ptr2(dst,d2+32) = xmm6[0];		/* Save I9 */ \
	f64ptr2(dst,d2+d1) = xmm0[0];		/* Save R11 */ \
	f64ptr2(dst,d2+d1+32) = xmm2[0];		/* Save I11 */ \
\
\
;	/* Even level 1 */ \
\
	xmm0[0] = f64ptr(srcreg+d1);		/* R2 */ \
	xmm1[0] = f64ptr(srcreg+d1+16);		/* R10 */ \
	xmm7[0] = xmm1[0];			/* Copy R10 */ \
	xmm1[0] += xmm0[0];			/* R10 = R2 + R10 (new R2) */ \
	xmm0[0] -= xmm7[0];			/* R2 = R2 - R10 (new R10) */ \
\
	xmm2[0] = f64ptr(srcreg+d4+d1);		/* R6 */ \
	xmm3[0] = f64ptr(srcreg+d4+d1+16);	/* R14 */ \
	xmm7[0] = xmm3[0];			/* Copy R14 */ \
	xmm3[0] += xmm2[0];			/* R14 = R6 + R14 (new R6) */ \
	xmm2[0] -= xmm7[0];			/* R6 = R6 - R14 (new R14) */ \
\
	xmm4[0] = f64ptr(srcreg+d2+d1);		/* R4 */ \
	xmm5[0] = f64ptr(srcreg+d2+d1+16);	/* R12 */ \
	xmm7[0] = xmm5[0];			/* Copy R12 */ \
	xmm5[0] += xmm4[0];			/* R12 = R4 + R12 (new R4) */ \
	xmm4[0] -= xmm7[0];			/* R4 = R4 - R12 (new R12) */ \
\
	xmm6[0] = f64ptr(srcreg+d4+d2+d1);	/* R8 */ \
	xmm7[0] = f64ptr(srcreg+d4+d2+d1+16);	/* R16 */ \
	xmm7[0] += xmm6[0];			/* R16 = R8 + R16 (new R8) */ \
	xmm6[0] -= f64ptr(srcreg+d4+d2+d1+16);	/* R8 = R8 - R16 (new R16) */ \
\
;	/* Even level 2 */ \
\
	xmm1[0] -= xmm3[0];			/* R2 = R2 - R6 (newer R6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm1[0];			/* R6 = R2 + R6 (newer R2) */ \
\
	xmm5[0] -= xmm7[0];			/* R4 = R4 - R8 (newer R8) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm5[0];			/* R8 = R4 + R8 (newer R4) */ \
\
;						/* R10/R14 morphs into newer R10/I10 */ \
;						/* R12/R16 morphs into newer R12/I12 */ \
\
;	/* Premultipliers for even level 3 */ \
\
	double tmp16 = xmm1[0]; \
	double tmp48 = xmm3[0]; \
\
;						/* mul R10/I10 by w^1 = .924 + .383i */ \
	xmm1[0] = xmm0[0];			/* Copy R10 */ \
	xmm0[0] *= CONST_P924; \
	xmm3[0] = xmm2[0];			/* Copy I10 */ \
	xmm3[0] *= CONST_P383; \
	xmm0[0] -= xmm3[0];			/* Twiddled R10 */ \
	xmm1[0] *= CONST_P383; \
	xmm2[0] *= CONST_P924; \
	xmm2[0] += xmm1[0];			/* Twiddled I10 */ \
\
;						/* mul R12/I12 by w^3 = .383 + .924i */ \
	xmm1[0] = xmm4[0];			/* Copy R12 */ \
	xmm4[0] *= CONST_P383; \
	xmm3[0] = xmm6[0];			/* Copy I12 */ \
	xmm3[0] *= CONST_P924; \
	xmm4[0] -= xmm3[0];			/* Twiddled R12 */ \
	xmm1[0] *= CONST_P924; \
	xmm6[0] *= CONST_P383; \
	xmm6[0] += xmm1[0];			/* Twiddled I12 */ \
\
	xmm1[0] = tmp16; \
	xmm3[0] = tmp48; \
\
;	/* Even level 3 */ \
\
	xmm3[0] -= xmm7[0];			/* R2 = R2 - R4 (final R4) */ \
	xmm7[0] += xmm7[0]; /* multwo */ \
	xmm7[0] += xmm3[0];			/* R4 = R2 + R4 (final R2) */ \
\
;						/* R6/R8 morph into newer R6/I6 */ \
\
	xmm0[0] -= xmm4[0];			/* R10 = R10 - R12 (final R12) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm0[0];			/* R10 = R10 + R12 (final R10) */ \
\
	xmm2[0] -= xmm6[0];			/* I10 = I10 - I12 (final I12) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm2[0];			/* I10 = I10 + I12 (final I10) */ \
\
;	/* Premultipliers for even level 4 */ \
\
;						/* mul R6/I6 by w^2 = .707 + .707i */ \
	xmm1[0] -= xmm5[0];			/* R6 = R6 - I6 */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm1[0];			/* I6 = R6 + I6 */ \
	xmm1[0] *= XMM_SQRTHALF1;		/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm5[0] *= XMM_SQRTHALF1;		/* I6 = I6 * SQRTHALF (final I6) */ \
\
	f64ptr2(dst,16) = xmm7[0];			/* Save R2 */ \
	f64ptr2(dst,48) = xmm3[0];			/* Save R4 */ \
	f64ptr2(dst,d1+16) = xmm1[0];		/* Save R6 */ \
	f64ptr2(dst,d1+48) = xmm5[0];		/* Save I6 */ \
	f64ptr2(dst,d2+16) = xmm4[0];		/* Save R10 */ \
	f64ptr2(dst,d2+48) = xmm6[0];		/* Save I10 */ \
	f64ptr2(dst,d2+d1+16) = xmm0[0];		/* Save R12 */ \
	f64ptr2(dst,d2+d1+48) = xmm2[0];		/* Save I12 */ \
}
#define r8_h16r_simple_fft_part1_8c(srcreg,d1,d2,d4,dst) \
	/* */ \
	/* Do the eight-complex part */ \
	/* */ \
\
	xmm0[0] = f64ptr(srcreg+8);		/* R1 */ \
	xmm2[0] = f64ptr(srcreg+d4+8);		/* R5 */ \
	xmm7[0] = xmm2[0];			/* Copy R5 */ \
	xmm2[0] += xmm0[0];			/* R5 = R1 + R5 (new R1) */ \
	xmm0[0] -= xmm7[0];			/* R1 = R1 - R5 (new R5) */ \
\
	xmm1[0] = f64ptr(srcreg+d2+8);		/* R3 */ \
	xmm3[0] = f64ptr(srcreg+d4+d2+8);	/* R7 */ \
	xmm7[0] = xmm3[0];			/* Copy R7 */ \
	xmm3[0] += xmm1[0];			/* R7 = R3 + R7 (new R3) */ \
	xmm1[0] -= xmm7[0];			/* R3 = R3 - R7 (new R7) */ \
\
	xmm4[0] = f64ptr(srcreg+16+8);		/* I1 */ \
	xmm6[0] = f64ptr(srcreg+d4+16+8);	/* I5 */ \
	xmm7[0] = xmm6[0];			/* Copy I5 */ \
	xmm6[0] += xmm4[0];			/* I5 = I1 + I5 (new I1) */ \
	xmm4[0] -= xmm7[0];			/* I1 = I1 - I5 (new I5) */ \
\
	xmm7[0] = xmm3[0];			/* Copy R3 */ \
	xmm3[0] += xmm2[0];			/* R3 = R1 + R3 (final R1) */ \
	xmm2[0] -= xmm7[0];			/* R1 = R1 - R3 (final R3) */ \
\
	f64ptr2(dst,0+8) = xmm3[0];		/* Save R1 */ \
	f64ptr2(dst,d1+8) = xmm2[0];		/* Save R3 */ \
\
	xmm5[0] = f64ptr(srcreg+d2+16+8);	/* I3 */ \
	xmm3[0] = f64ptr(srcreg+d4+d2+16+8);	/* I7 */ \
	xmm7[0] = xmm3[0];			/* Copy I7 */ \
	xmm3[0] += xmm5[0];			/* I7 = I3 + I7 (new I3) */ \
	xmm5[0] -= xmm7[0];			/* I3 = I3 - I7 (new I7) */ \
\
	xmm7[0] = xmm3[0];			/* Copy I3 */ \
	xmm3[0] += xmm6[0];			/* I3 = I1 + I3 (final I1) */ \
	xmm6[0] -= xmm7[0];			/* I1 = I1 - I3 (final I3) */ \
\
	f64ptr2(dst,32+8) = xmm3[0];		/* Save I1 */ \
	f64ptr2(dst,d1+32+8) = xmm6[0];		/* Save I3 */ \
\
	xmm3[0] = xmm1[0];			/* Copy R7 */ \
	xmm1[0] += xmm4[0];			/* R7 = I5 + R7 (final I5) */ \
	xmm7[0] = xmm0[0];			/* Copy R5 */ \
	xmm0[0] -= xmm5[0];			/* R5 = R5 - I7 (final R5) */ \
	xmm4[0] -= xmm3[0];			/* I5 = I5 - R7 (final I7) */ \
	xmm5[0] += xmm7[0];			/* I7 = R5 + I7 (final R7) */ \
\
	f64ptr2(dst,d2+32+8) = xmm1[0];		/* Save I5 */ \
	f64ptr2(dst,d2+8) = xmm0[0];		/* Save R5 */ \
	f64ptr2(dst,d2+d1+32+8) = xmm4[0];	/* Save I7 */ \
	f64ptr2(dst,d2+d1+8) = xmm5[0];		/* Save R7 */ \
\
	xmm0[0] = f64ptr(srcreg+d1+8);		/* R2 */ \
	xmm2[0] = f64ptr(srcreg+d4+d1+8);	/* R6 */ \
	xmm7[0] = xmm2[0];			/* Copy R6 */ \
	xmm2[0] += xmm0[0];			/* R6 = R2 + R6 (new R2) */ \
	xmm0[0] -= xmm7[0];			/* R2 = R2 - R6 (new R6) */ \
\
	xmm1[0] = f64ptr(srcreg+d2+d1+8);	/* R4 */ \
	xmm3[0] = f64ptr(srcreg+d4+d2+d1+8);	/* R8 */ \
	xmm7[0] = xmm3[0];			/* Copy R8 */ \
	xmm3[0] += xmm1[0];			/* R8 = R4 + R8 (new R4) */ \
	xmm1[0] -= xmm7[0];			/* R4 = R4 - R8 (new R8) */ \
\
	xmm4[0] = f64ptr(srcreg+d1+16+8);	/* I2 */ \
	xmm6[0] = f64ptr(srcreg+d4+d1+16+8);	/* I6 */ \
	xmm7[0] = xmm6[0];			/* Copy I6 */ \
	xmm6[0] += xmm4[0];			/* I6 = I2 + I6 (new I2) */ \
	xmm4[0] -= xmm7[0];			/* I2 = I2 - I6 (new I6) */ \
\
	xmm7[0] = xmm3[0];			/* Copy R4 */ \
	xmm3[0] += xmm2[0];			/* R4 = R2 + R4 (final R2) */ \
	xmm2[0] -= xmm7[0];			/* R2 = R2 - R4 (final R4) */ \
\
	f64ptr2(dst,16+8) = xmm3[0];		/* Save R2 */ \
	f64ptr2(dst,d1+16+8) = xmm2[0];		/* Save R4 */ \
\
	xmm5[0] = f64ptr(srcreg+d2+d1+16+8);	/* I4 */ \
	xmm3[0] = f64ptr(srcreg+d4+d2+d1+16+8);	/* I8 */ \
	xmm7[0] = xmm3[0];			/* Copy I8 */ \
	xmm3[0] += xmm5[0];			/* I8 = I4 + I8 (new I4) */ \
	xmm5[0] -= xmm7[0];			/* I4 = I4 - I8 (new I8) */ \
\
	xmm7[0] = xmm3[0];			/* Copy I4 */ \
	xmm3[0] += xmm6[0];			/* I4 = I2 + I4 (final I2) */ \
	xmm6[0] -= xmm7[0];			/* I2 = I2 - I4 (final I4) */ \
\
	f64ptr2(dst,48+8) = xmm3[0];		/* Save I2 */ \
	f64ptr2(dst,d1+48+8) = xmm6[0];		/* Save I4 */ \
\
	xmm3[0] = xmm1[0];			/* Copy R8 */ \
	xmm1[0] += xmm4[0];			/* R8 = I6 + R8 (new I6) */ \
	xmm7[0] = xmm0[0];			/* Copy R6 */ \
	xmm0[0] -= xmm5[0];			/* R6 = R6 - I8 (new R6) */ \
	xmm4[0] -= xmm3[0];			/* I6 = I6 - R8 (new I8) */ \
	xmm5[0] += xmm7[0];			/* I8 = R6 + I8 (new R8) */ \
\
	xmm7[0] = xmm0[0];			/* Copy R6 */ \
	xmm0[0] -= xmm1[0];			/* R6 = R6 - I6 */ \
	xmm1[0] += xmm7[0];			/* I6 = R6 + I6 */ \
	xmm3[0] = XMM_SQRTHALF1; \
	xmm0[0] *= xmm3[0];			/* R6 = R6 * SQRTHALF (final R6) */ \
	xmm1[0] *= xmm3[0];			/* I6 = I6 * SQRTHALF (final I6) */ \
\
	xmm7[0] = xmm5[0];			/* Copy R8 */ \
	xmm5[0] -= xmm4[0];			/* R8 = R8 - I8 */ \
	xmm4[0] += xmm7[0];			/* I8 = R8 + I8 */ \
	xmm5[0] *= xmm3[0];			/* R8 = R8 * SQRTHALF (final R8) */ \
	xmm4[0] *= xmm3[0];			/* I8 = I8 * SQRTHALF (final I8) */ \
\
	f64ptr2(dst,d2+16+8) = xmm0[0];		/* Save R6 */ \
	f64ptr2(dst,d2+48+8) = xmm1[0];		/* Save I6 */ \
	f64ptr2(dst,d2+d1+16+8) = xmm5[0];	/* Save R8 */ \
	f64ptr2(dst,d2+d1+48+8) = xmm4[0];	/* Save I8 */ \


#if 1
#define r8_h16r_simple_fft_part2(src,dstreg,d1,d2) \
	/* Do the 16-reals part */ \
\
	xmm1 = xptr2(src,0);		/* R1 R1 */ \
	xmm0 = xptr2(src,16); 		/* R2 R2 */ \
	xmm7 = xmm1;			/* Copy R1 */ \
	xmm1 -= xmm0;			/* R1 = R1 - R2 (new R2) */ \
	xmm0 += xmm7;			/* R2 = R1 + R2 (new R1) */ \
\
	xmm2 = xptr2(src,32);			/* I1, R3/R4 morphs into R3/I3 */ \
	xmm3 = xptr2(src,48); 			/* I2 */ \
\
	xmm7[1] = xmm2[1];			/* Copy I1 */ \
	xmm2[1] -= xmm3[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm3[1] += xmm7[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xptr(dstreg) = xmm0;		/* Save R1 R1 */ \
	xmm7[0] = xmm2[0]; xmm7[1] = xmm1[1]; \
	xptr(dstreg+16) = xmm7;		/* Save R3 R2 */ \
	xmm1[1] = xmm3[1]; \
	xptr(dstreg+32) = xmm1;		/* Save R2 I1 */ \
	xmm3[1] = xmm2[1]; \
	xptr(dstreg+48) = xmm3;		/* Save I3 I2 */ \
\
	xmm4 = xptr2(src,d1);			/* R5 R3 */ \
	xmm5[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm5[1] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm1[0] = xmm4[0] - xmm5[0];		/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] = xmm4[0] + xmm5[0];		/* R6 = R5 + R6 (new R5) */ \
	xmm0[1] = xmm4[1] - xmm5[1];		/* R3 = R3 - I4 (new R3) */ \
	xmm1[1] = xmm4[1] + xmm5[1];		/* I4 = R3 + I4 (new R4) */ \
\
	xmm3 = xptr2(src,d1+32);		/* I5 I3 */ \
	xmm2[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm2[1] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm7 = xmm3;				/* Copy I6I3 */ \
	xmm3 -= xmm2;				/* I5I3 = I5I3 - I6R4 (new I6 I4) */ \
	xmm2 += xmm7;				/* I6R4 = I5I3 + I6R4 (new I5 I3) */ \
\
	xptr(dstreg+d1) = xmm0;		/* Save R5 R3 */ \
	xptr(dstreg+d1+16) = xmm1;		/* Save R6 R4 */ \
	xptr(dstreg+d1+32) = xmm2;		/* Save I5 I3 */ \
	xptr(dstreg+d1+48) = xmm3;		/* Save I6 I4 */ \
\
	xmm1 = xptr2(src,d2);		/* R9 R5 */ \
	xmm0 = xptr2(src,d2+16); 	/* R10 R6 */ \
	xmm7 = xmm1;			/* Copy R9 R5 */ \
	xmm1 -= xmm0;			/* R9R5 = R9R5 - R10R6 (new R10R6) */ \
	xmm0 += xmm7;			/* R10R6 = R9R5 + R10R6 (new R9R5) */ \
\
	xmm3 = xptr2(src,d2+32);		/* I9 I5 */ \
	xmm2 = xptr2(src,d2+48); 		/* I10 I6 */ \
	xmm7 = xmm3;			/* Copy I9 I5 */ \
	xmm3 -= xmm2;			/* I9I5 = I9I5 - I10I6 (new I10I6) */ \
	xmm2 += xmm7;			/* I10I6 = I9I5 + I10I6 (new I9I5) */ \
\
	xptr(dstreg+d2) = xmm0;		/* Save R9 R5 */ \
	xptr(dstreg+d2+16) = xmm1;		/* Save R10 R6 */ \
	xptr(dstreg+d2+32) = xmm2;		/* Save I9 I5 */ \
	xptr(dstreg+d2+48) = xmm3;		/* Save I10 I6 */ \
\
	xmm0 = xptr2(src,d2+d1);		/* R11 R7 */ \
	xmm1 = xptr2(src,d2+d1+48); 		/* I12 I8 */ \
	xmm7 = xmm0;			/* Copy I12 R7 */ \
	xmm0 -= xmm1;			/* R11R7 = R11R7 - I12I8 (new R11R7) */ \
	xmm1 += xmm7;			/* R12I8 = R11R7 + I12I8 (new R12R8) */ \
\
	xmm3 = xptr2(src,d2+d1+32);		/* I11 I7 */ \
	xmm2 = xptr2(src,d2+d1+16); 		/* R12 R8 */ \
	xmm7 = xmm3;			/* Copy R12 */ \
	xmm3 -= xmm2;			/* I11I7 = I11I7 - R12R8 (new I12I8) */ \
	xmm2 += xmm7;			/* I12R8 = I11 + R12R8 (new I11I7) */ \
\
	xptr(dstreg+d2+d1) = xmm0;		/* Save R11 R7 */ \
	xptr(dstreg+d2+d1+16) = xmm1;	/* Save R12 R8 */ \
	xptr(dstreg+d2+d1+32) = xmm2;	/* Save I11 I7 */ \
	xptr(dstreg+d2+d1+48) = xmm3;	/* Save I12 I8 */ \

#else
#define r8_h16r_simple_fft_part2(src,dstreg,d1,d2) \
	r8_h16r_simple_fft_part2_16r(src,dstreg,d1,d2) \
	r8_h16r_simple_fft_part2_8c(src,dstreg,d1,d2)
#endif

#define r8_h16r_simple_fft_part2_16r(src,dstreg,d1,d2) \
	/* Do the 16-reals part */ \
\
	xmm1[0] = f64ptr2(src,0);			/* R1 */ \
	xmm0[0] = f64ptr2(src,16); 		/* R2 */ \
	xmm7[0] = xmm1[0];			/* Copy R2 */ \
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm0[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm2[0] = f64ptr2(src,32);			/* R3/R4 morphs into R3/I3 */ \
	xmm3[0] = f64ptr2(src,48); \
\
	f64ptr(dstreg) = xmm0[0];		/* Save R1 */ \
	f64ptr(dstreg+32) = xmm1[0];		/* Save R2 */ \
	f64ptr(dstreg+16) = xmm2[0];		/* Save R3 */ \
	f64ptr(dstreg+48) = xmm3[0];		/* Save I3 */ \
\
	xmm1[0] = f64ptr2(src,d1);			/* R5 */ \
	xmm0[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm7[0] = xmm1[0];			/* Copy R6 */ \
	xmm1[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d1+32);		/* I5 */ \
	xmm2[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I6 */ \
	xmm3[0] -= xmm2[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr(dstreg+d1) = xmm0[0];		/* Save R5 */ \
	f64ptr(dstreg+d1+32) = xmm2[0];		/* Save I5 */ \
	f64ptr(dstreg+d1+16) = xmm1[0];		/* Save R6 */ \
	f64ptr(dstreg+d1+48) = xmm3[0];		/* Save I6 */ \
\
	xmm1[0] = f64ptr2(src,d2);			/* R9 */ \
	xmm0[0] = f64ptr2(src,d2+16); 		/* R10 */ \
	xmm7[0] = xmm1[0];			/* Copy R10 */ \
	xmm1[0] -= xmm0[0];			/* R9 = R9 - R10 (new R10) */ \
	xmm0[0] += xmm7[0];			/* R10 = R9 + R10 (new R9) */ \
\
	xmm3[0] = f64ptr2(src,d2+32);		/* I9 */ \
	xmm2[0] = f64ptr2(src,d2+48); 		/* I10 */ \
	xmm7[0] = xmm3[0];			/* Copy I10 */ \
	xmm3[0] -= xmm2[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm2[0] += xmm7[0];			/* I10 = I9 + I10 (new I9) */ \
\
	f64ptr(dstreg+d2) = xmm0[0];		/* Save R9 */ \
	f64ptr(dstreg+d2+32) = xmm2[0];		/* Save I9 */ \
	f64ptr(dstreg+d2+16) = xmm1[0];		/* Save R10 */ \
	f64ptr(dstreg+d2+48) = xmm3[0];		/* Save I10 */ \
\
	xmm1[0] = f64ptr2(src,d2+d1);		/* R11 */ \
	xmm0[0] = f64ptr2(src,d2+d1+48); 		/* I12 */ \
	xmm7[0] = xmm1[0];			/* Copy I12 */ \
	xmm1[0] -= xmm0[0];			/* R11 = R11 - I12 (new R11) */ \
	xmm0[0] += xmm7[0];			/* R12 = R11 + I12 (new R12) */ \
\
	xmm3[0] = f64ptr2(src,d2+d1+32);		/* I11 */ \
	xmm2[0] = f64ptr2(src,d2+d1+16); 		/* R12 */ \
	xmm7[0] = xmm3[0];			/* Copy R12 */ \
	xmm3[0] -= xmm2[0];			/* I11 = I11 - R12 (new I12) */ \
	xmm2[0] += xmm7[0];			/* I12 = I11 + R12 (new I11) */ \
\
	f64ptr(dstreg+d2+d1) = xmm1[0];		/* Save R11 */ \
	f64ptr(dstreg+d2+d1+32) = xmm2[0];	/* Save I11 */ \
	f64ptr(dstreg+d2+d1+16) = xmm0[0];	/* Save R12 */ \
	f64ptr(dstreg+d2+d1+48) = xmm3[0];	/* Save I12 */ \

#define r8_h16r_simple_fft_part2_8c(src,dstreg,d1,d2) \
	/* Do the eight-complex part */ \
\
	xmm2[0] = f64ptr2(src,d2+8);		/* R5 */ \
	xmm0[0] = f64ptr2(src,d2+16+8); 		/* R6 */ \
	xmm7[0] = xmm2[0];			/* Copy R5 */ \
	xmm2[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d2+32+8);		/* I5 */ \
	xmm1[0] = f64ptr2(src,d2+48+8);		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I5 */ \
	xmm3[0] -= xmm1[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm1[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xmm4[0] = f64ptr2(src,d2+d1+8);		/* R7 */ \
	xmm5[0] = f64ptr2(src,d2+d1+48+8);	/* I8 */ \
	xmm7[0] = xmm4[0];			/* Copy R7 */ \
	xmm4[0] -= xmm5[0];			/* R7 = R7 - I8 (new R7) */ \
	xmm5[0] += xmm7[0];			/* I8 = R7 + I8 (new R8) */ \
\
	f64ptr(dstreg+d2+16+8) = xmm2[0];	/* Save R6 */ \
	f64ptr(dstreg+d2+8) = xmm0[0];		/* Save R5 */ \
	f64ptr(dstreg+d2+48+8) = xmm3[0];	/* Save I6 */ \
	f64ptr(dstreg+d2+32+8) = xmm1[0];	/* Save I5 */ \
	f64ptr(dstreg+d2+d1+8) = xmm4[0];	/* Save R7 */ \
	f64ptr(dstreg+d2+d1+16+8) = xmm5[0];	/* Save R8 */ \
\
	xmm0[0] = f64ptr2(src,d2+d1+32+8);	/* I7 */ \
	xmm1[0] = f64ptr2(src,d2+d1+16+8);	/* R8 */ \
	xmm7[0] = xmm0[0];			/* Copy I7 */ \
	xmm0[0] -= xmm1[0];			/* I7 = I7 - R8 (new I8) */ \
	xmm1[0] += xmm7[0];			/* R8 = I7 + R8 (new I7) */ \
\
	xmm3[0] = f64ptr2(src,0+8);		/* R1 */ \
	xmm4[0] = f64ptr2(src,16+8);		/* R2 */ \
	xmm7[0] = xmm3[0];			/* Copy R1 */ \
	xmm3[0] -= xmm4[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm4[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5[0] = f64ptr2(src,32+8);		/* I1 */ \
	xmm6[0] = f64ptr2(src,48+8);		/* I2 */ \
	xmm7[0] = xmm5[0];			/* Copy I1 */ \
	xmm5[0] -= xmm6[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm6[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	f64ptr(dstreg+d2+d1+48+8) = xmm0[0];	/* Save I8 */ \
	f64ptr(dstreg+d2+d1+32+8) = xmm1[0];	/* Save I7 */ \
	f64ptr(dstreg+16+8) = xmm3[0];		/* Save R2 */ \
	f64ptr(dstreg+8) = xmm4[0];		/* Save R1 */ \
	f64ptr(dstreg+48+8) = xmm5[0];		/* Save I2 */ \
	f64ptr(dstreg+32+8) = xmm6[0];		/* Save I1 */ \
\
	xmm5[0] = f64ptr2(src,d1+8);		/* R3 */ \
	xmm6[0] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm7[0] = xmm5[0];			/* Copy R3 */ \
	xmm5[0] -= xmm6[0];			/* R3 = R3 - I4 (new R3) */ \
	xmm6[0] += xmm7[0];			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3[0] = f64ptr2(src,d1+32+8);		/* I3 */ \
	xmm4[0] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm7[0] = xmm3[0];			/* Copy I3 */ \
	xmm3[0] -= xmm4[0];			/* I3 = I3 - R4 (new I4) */ \
	xmm4[0] += xmm7[0];			/* R4 = I3 + R4 (new I3) */ \
\
	f64ptr(dstreg+d1+8) = xmm5[0];		/* Save R3 */ \
	f64ptr(dstreg+d1+16+8) = xmm6[0];	/* Save R4 */ \
	f64ptr(dstreg+d1+48+8) = xmm3[0];	/* Save I4 */ \
	f64ptr(dstreg+d1+32+8) = xmm4[0];	/* Save I3 */ \
\
\
\

#if 0
#define r8_h8cl_sixteen_reals_eight_complex_with_square(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	xmult7(srcreg, srcreg); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_h16r_simple_fft_part1_16r(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_with_square_16r(XMM_COL_MULTS_1,d1,d2,srcreg); \
	r8_h16r_simple_unfft_16r(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_h16r_simple_fft_part1_8c(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_with_square_8c(XMM_COL_MULTS_1,d1,d2,srcreg); \
	r8_h16r_simple_unfft_8c(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_square(XMM_COL_MULTS_2,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#elif 1
#define r8_h8cl_sixteen_reals_eight_complex_with_square(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	xmult7(srcreg, srcreg); \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_with_square(XMM_COL_MULTS_2,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	r8_h16r_simple_fft_with_square(XMM_COL_MULTS_1,d1,d2,srcreg); \
	r8_h16r_simple_unfft(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_h8cl_sixteen_reals_eight_complex_with_square(srcreg,srcinc,d1,d2,d4) \
	xmult7(srcreg, srcreg); \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS)); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_h16r_simple_fft_with_square((g->u.xmm.XMM_COL_MULTS),d1,d2,srcreg); \
	r8_x8c_simple_fft_with_square((g->u.xmm.XMM_COL_MULTS+256/8),d1,d2); \
	r8_h16r_simple_unfft((g->u.xmm.XMM_COL_MULTS),srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#if 1
#define r8_h16r_simple_fft_with_square(src,d1,d2,origsrc) \
;	/* Do the 16-reals part */ \
\
	xmm0 = xptr2(src,0);		/* R1 R1 */ \
	xmm1 = xptr2(src,16); 		/* R2 R2 */ \
\
	xmm7 = xmm0;			/* Copy R1 */ \
	xmm0 -= xmm1;			/* R1R1 = R1R1 - R2R2 (new R2R2) */ \
	xmm1 += xmm7;			/* R2R2 = R1R1 + R2R2 (new R1R1) */ \
\
	xmm1[0] *= xmm1[0];			/* Square R1 */ \
	xmm0[0] *= xmm0[0];			/* Square R2 */ \
	f64ptr(origsrc-16) = xmm1[0];		/* Save square of sum of FFT values */ \
\
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm1[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm0[0] += xmm1[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xmm2 = xptr2(src,32);		/* ? I1 */ /* R3/R4 morphs into R3/I3 */ \
	xmm3 = xptr2(src,48); 		/* ? I2 */ \
\
	xmm7[1] = xmm2[1];			/* Copy I1 */ \
	xmm2[1] -= xmm3[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm3[1] += xmm7[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xs_complex_square(xmm0[1], xmm2[1], xmm7[1]);	/* Square R2/I2 */ \
	xmm6[0] = xmm2[0]; xmm6[1] = xmm1[1]; \
	xp_complex_square(xmm6, xmm3, xmm7);	/* Square R3/I3, Square R1/I1 */ \
	xmm2[0] = xmm6[0]; xmm1[1] = xmm6[1]; \
\
						/* R3/I3 morphs into R3/R4 */ \
\
	xmm7[1] = xmm1[1];			/* Copy R1 */ \
	xmm1[1] -= xmm0[1];			/* R1 = R1 - R2 (new R2) */ \
	xmm0[1] += xmm7[1];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[1] = xmm3[1];			/* Copy I1 */ \
	xmm3[1] -= xmm2[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm2[1] += xmm7[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xptr2(src,0) = xmm0;			/* Save R1 R1 */ \
	xptr2(src,16) = xmm1;			/* Save R2 R2 */ \
	xptr2(src,32) = xmm2;			/* Save R3 I1 */ \
	xptr2(src,48) = xmm3;			/* Save R4 I2 */ \
\
	xmm0 = xptr2(src,d1);			/* R5 R3 */ \
	xmm1[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm1[1] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm7 = xmm0;			/* Copy R6 R3 */ \
	xmm0 -= xmm1;			/* R5R3 = R5R3 - R6I4 (new R6R3) */ \
	xmm1 += xmm7;			/* R6I4 = R5R3 + R6I4 (new R5R4) */ \
\
	xmm2[0] = f64ptr2(src,d1+32);		/* I5 */ \
	xmm3[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm2[1] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm3[1] = f64ptr2(src,d1+32+8);		/* I3 */ \
	xmm7 = xmm2;			/* Copy I5 I3 */ \
	xmm2[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[1] += xmm3[1];			/* R4 = I3 + R4 (final I3) */ \
	xmm3[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
	xmm3[1] -= xmm7[1];			/* I3 = I3 - R4 (final I4) */ \
	\
	xp_complex_square(xmm1, xmm3, xmm7);	/* Square R5/I5 R4/I4 */ \
	xp_complex_square(xmm0, xmm2, xmm7);	/* Square R6/I6 R3/I3 */ \
\
	xmm1[0] -= xmm0[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm3[0] -= xmm2[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* I6 = I5 + I6 (new I5) */ \
\
\
	xmm6[1] = xmm1[1];			/* Copy R4 */ \
	xmm1[1] -= xmm0[1];			/* R4 = R4 - R3 (new I4) */ \
	xmm0[1] += xmm6[1];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7[1] = xmm2[1];			/* Copy I3 */ \
	xmm2[1] -= xmm3[1];			/* I3 = I3 - I4 (new R4) */ \
	xmm7[1] += xmm3[1];			/* I4 = I3 + I4 (new I3) */ \
\
	xmm7[0] = xmm2[0]; \
	xmm2[0] = xmm1[0]; \
	xmm1[0] = xmm3[0]; \
	xptr2(src,d1) = xmm0;			/* Save R5 */ \
	xptr2(src,d1+16) = xmm2;		/* Save R6 */ \
	xptr2(src,d1+32) = xmm7;		/* Save I5 */ \
	xptr2(src,d1+48) = xmm1;		/* Save I6 */ \
\
	xmm0 = xptr2(src,d2);			/* R9 R5 */ \
	xmm1 = xptr2(src,d2+16); 		/* R10 R6 */ \
	xmm7 = xmm0;			/* Copy R9 R5 */ \
	xmm0 -= xmm1;			/* R9R5 = R9R5 - R10R6 (new R10R6) */ \
	xmm1 += xmm7;			/* R10R6 = R9R5 + R10R6 (new R9R5) */ \
\
	xmm2 = xptr2(src,d2+32);		/* I9 I5 */ \
	xmm3 = xptr2(src,d2+48); 		/* I10 I6 */ \
	xmm7 = xmm2;			/* Copy I9 I5 */ \
	xmm2 -= xmm3;			/* I9I5 = I9I5 - I10I6 (new I10I6) */ \
	xmm3 += xmm7;			/* I10I6 = I9I5 + I10I6 (new I9I5) */ \
\
	xp_complex_square(xmm1, xmm3, xmm7);	/* Square R9/I9 Square R5/I5 */ \
	xp_complex_square(xmm0, xmm2, xmm7);	/* Square R10/I10 Square R6/I6 */ \
\
	xmm1[0] -= xmm0[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm3[0] -= xmm2[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* I10 = I9 + I10 (new I9) */ \
\
\
	xmm7[1] = xmm1[1];			/* Copy R5 */ \
	xmm1[1] -= xmm0[1];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[1] += xmm7[1];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[1] = xmm3[1];			/* Copy I5 */ \
	xmm3[1] -= xmm2[1];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[1] += xmm7[1];			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(src,d2) = xmm0;		/* Save R9 R5 */ \
	xptr2(src,d2+16) = xmm1;		/* Save R10 R6 */ \
	xptr2(src,d2+32) = xmm2;		/* Save I9 I5 */ \
	xptr2(src,d2+48) = xmm3;		/* Save I10 I6 */ \
\
	xmm0 = xptr2(src,d2+d1);		/* R11 R7 */ \
	xmm3 = xptr2(src,d2+d1+48); 		/* I12 I8 */ \
	xmm7 = xmm0;			/* Copy I11 R7 */ \
	xmm0 -= xmm3;			/* R11R7 = R11R7 - I12I8 (new R11R7) */ \
	xmm3 += xmm7;			/* R12I8 = R11R7 + I12I8 (new R12R8) */ \
\
	xmm2 = xptr2(src,d2+d1+32);	/* I11 I7 */ \
	xmm1 = xptr2(src,d2+d1+16); /* R12 I8 */ \
	xmm7 = xmm2;			/* Copy I11 I7 */ \
	xmm2 -= xmm1;			/* I11I7 = I11I7 - R12I8 (new I12I8) */ \
	xmm1 += xmm7;			/* I12I8 = I11I7 + R12I8 (new I11I7) */ \
\
	xp_complex_square(xmm0, xmm1, xmm7);	/* Square R11/I11 Square R7/I7 */ \
	xp_complex_square(xmm3, xmm2, xmm7);	/* Square R12/I12 Square R8/I8 */ \
\
	xmm3[0] -= xmm0[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm3[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm1[0] -= xmm2[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm1[0];			/* I12 = I11 + I12 (new I11) */ \
\
	xmm7[1] = xmm3[1];			/* Copy R8 */ \
	xmm3[1] -= xmm0[1];			/* R8 = R8 - R7 (new I8) */ \
	xmm0[1] += xmm7[1];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[1] = xmm1[1];			/* Copy I7 */ \
	xmm1[1] -= xmm2[1];			/* I7 = I7 - I8 (new R8) */ \
	xmm2[1] += xmm7[1];			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(src,d2+d1) = xmm0;		/* Save R11 R7 */ \
	xptr2(src,d2+d1+16) = xmm1;		/* Save R12 R8 */ \
	xptr2(src,d2+d1+32) = xmm2;		/* Save I11 I7 */ \
	xptr2(src,d2+d1+48) = xmm3;		/* Save I12 I8 */ \

#else
#define r8_h16r_simple_fft_with_square(src,d1,d2,origsrc) \
	r8_h16r_simple_fft_with_square_16r(src,d1,d2,origsrc) \
	r8_h16r_simple_fft_with_square_8c(src,d1,d2,origsrc)
#endif

#define r8_h16r_simple_fft_with_square_16r(src,d1,d2,origsrc) \
;	/* Do the 16-reals part */ \
\
	xmm1[0] = f64ptr2(src,0);			/* R1 */ \
	xmm0[0] = f64ptr2(src,16); 		/* R2 */ \
	xmm7[0] = xmm1[0];			/* Copy R2 */ \
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm0[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm0[0] *= xmm0[0];			/* Square R1 */ \
	xmm1[0] *= xmm1[0];			/* Square R2 */ \
	f64ptr(origsrc-16) = xmm0[0];		/* Save square of sum of FFT values */ \
\
	xmm0[0] -= xmm1[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm0[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm1[0] += xmm0[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xmm2[0] = f64ptr2(src,32);			/* R3/R4 morphs into R3/I3 */ \
	xmm3[0] = f64ptr2(src,48); \
\
	xs_complex_square(xmm2[0], xmm3[0], xmm7[0]);	/* Square R3/I3 */ \
\
;						/* R3/I3 morphs into R3/R4 */ \
\
	f64ptr2(src,0) = xmm1[0];			/* Save R1 */ \
	f64ptr2(src,32) = xmm2[0];			/* Save R3 */ \
	f64ptr2(src,16) = xmm0[0];			/* Save R2 */ \
	f64ptr2(src,48) = xmm3[0];			/* Save R4 */ \
\
	xmm1[0] = f64ptr2(src,d1);			/* R5 */ \
	xmm0[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm7[0] = xmm1[0];			/* Copy R6 */ \
	xmm1[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d1+32);		/* I5 */ \
	xmm2[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I6 */ \
	xmm3[0] -= xmm2[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xs_complex_square(xmm0[0], xmm2[0], xmm7[0]);	/* Square R5/I5 */ \
	xs_complex_square(xmm1[0], xmm3[0], xmm7[0]);	/* Square R6/I6 */ \
\
	xmm0[0] -= xmm1[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm2[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(src,d1) = xmm1[0];			/* Save R5 */ \
	f64ptr2(src,d1+32) = xmm3[0];		/* Save I5 */ \
	f64ptr2(src,d1+16) = xmm0[0];		/* Save R6 */ \
	f64ptr2(src,d1+48) = xmm2[0];		/* Save I6 */ \
\
	xmm1[0] = f64ptr2(src,d2);			/* R9 */ \
	xmm0[0] = f64ptr2(src,d2+16); 		/* R10 */ \
	xmm7[0] = xmm1[0];			/* Copy R10 */ \
	xmm1[0] -= xmm0[0];			/* R9 = R9 - R10 (new R10) */ \
	xmm0[0] += xmm7[0];			/* R10 = R9 + R10 (new R9) */ \
\
	xmm3[0] = f64ptr2(src,d2+32);		/* I9 */ \
	xmm2[0] = f64ptr2(src,d2+48); 		/* I10 */ \
	xmm7[0] = xmm3[0];			/* Copy I10 */ \
	xmm3[0] -= xmm2[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm2[0] += xmm7[0];			/* I10 = I9 + I10 (new I9) */ \
\
	xs_complex_square(xmm0[0], xmm2[0], xmm7[0]);	/* Square R9/I9 */ \
	xs_complex_square(xmm1[0], xmm3[0], xmm7[0]);	/* Square R10/I10 */ \
\
	xmm0[0] -= xmm1[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm2[0] -= xmm3[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I10 = I9 + I10 (new I9) */ \
\
	f64ptr2(src,d2) = xmm1[0];			/* Save R9 */ \
	f64ptr2(src,d2+32) = xmm3[0];		/* Save I9 */ \
	f64ptr2(src,d2+16) = xmm0[0];		/* Save R10 */ \
	f64ptr2(src,d2+48) = xmm2[0];		/* Save I10 */ \
\
	xmm1[0] = f64ptr2(src,d2+d1);		/* R11 */ \
	xmm0[0] = f64ptr2(src,d2+d1+48); 		/* I12 */ \
	xmm7[0] = xmm1[0];			/* Copy I12 */ \
	xmm1[0] -= xmm0[0];			/* R11 = R11 - I12 (new R11) */ \
	xmm0[0] += xmm7[0];			/* R12 = R11 + I12 (new R12) */ \
\
	xmm3[0] = f64ptr2(src,d2+d1+32);		/* I11 */ \
	xmm2[0] = f64ptr2(src,d2+d1+16); 		/* R12 */ \
	xmm7[0] = xmm3[0];			/* Copy R12 */ \
	xmm3[0] -= xmm2[0];			/* I11 = I11 - R12 (new I12) */ \
	xmm2[0] += xmm7[0];			/* I12 = I11 + R12 (new I11) */ \
\
	xs_complex_square(xmm1[0], xmm2[0], xmm7[0]);	/* Square R11/I11 */ \
	xs_complex_square(xmm0[0], xmm3[0], xmm7[0]);	/* Square R12/I12 */ \
\
	xmm0[0] -= xmm1[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm2[0] -= xmm3[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I12 = I11 + I12 (new I11) */ \
\
	f64ptr2(src,d2+d1) = xmm1[0];		/* Save R11 */ \
	f64ptr2(src,d2+d1+32) = xmm3[0];		/* Save I11 */ \
	f64ptr2(src,d2+d1+16) = xmm2[0];		/* Save R12 */ \
	f64ptr2(src,d2+d1+48) = xmm0[0];		/* Save I12 */ \

#define r8_h16r_simple_fft_with_square_8c(src,d1,d2,origsrc) \
;	/* Do the eight-complex part */ \
\
	xmm2[0] = f64ptr2(src,d2+8);		/* R5 */ \
	xmm0[0] = f64ptr2(src,d2+16+8); 		/* R6 */ \
	xmm7[0] = xmm2[0];			/* Copy R5 */ \
	xmm2[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d2+32+8);		/* I5 */ \
	xmm1[0] = f64ptr2(src,d2+48+8); 		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I5 */ \
	xmm3[0] -= xmm1[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm1[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xs_complex_square(xmm2[0], xmm3[0], xmm7[0]);	/* Square R6/I6 */ \
	xs_complex_square(xmm0[0], xmm1[0], xmm7[0]);	/* Square R5/I5 */ \
\
	xmm7[0] = xmm0[0];			/* Copy R5 */ \
	xmm0[0] -= xmm2[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm2[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I5 */ \
	xmm1[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(src,d2+16+8) = xmm0[0];		/* Save R6 */ \
	f64ptr2(src,d2+8) = xmm2[0];		/* Save R5 */ \
	f64ptr2(src,d2+48+8) = xmm1[0];		/* Save I6 */ \
	f64ptr2(src,d2+32+8) = xmm3[0];		/* Save I5 */ \
\
	xmm4[0] = f64ptr2(src,d2+d1+8);		/* R7 */ \
	xmm5[0] = f64ptr2(src,d2+d1+48+8);	/* I8 */ \
	xmm7[0] = xmm4[0];			/* Copy R7 */ \
	xmm4[0] -= xmm5[0];			/* R7 = R7 - I8 (new R7) */ \
	xmm5[0] += xmm7[0];			/* I8 = R7 + I8 (new R8) */ \
\
	xmm0[0] = f64ptr2(src,d2+d1+32+8);	/* I7 */ \
	xmm1[0] = f64ptr2(src,d2+d1+16+8);	/* R8 */ \
	xmm7[0] = xmm0[0];			/* Copy I7 */ \
	xmm0[0] -= xmm1[0];			/* I7 = I7 - R8 (new I8) */ \
	xmm1[0] += xmm7[0];			/* R8 = I7 + R8 (new I7) */ \
\
	xs_complex_square(xmm5[0], xmm0[0], xmm7[0]);	/* Square R8/I8 */ \
	xs_complex_square(xmm4[0], xmm1[0], xmm7[0]);	/* Square R7/I7 */ \
\
	xmm7[0] = xmm5[0];			/* Copy R8 */ \
	xmm5[0] -= xmm4[0];			/* R8 = R8 - R7 (new I8) */ \
	xmm4[0] += xmm7[0];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I7 */ \
	xmm1[0] -= xmm0[0];			/* I7 = I7 - I8 (new R8) */ \
	xmm0[0] += xmm7[0];			/* I8 = I7 + I8 (new I7) */ \
\
	f64ptr2(src,d2+d1+48+8) = xmm5[0];	/* Save I8 */ \
	f64ptr2(src,d2+d1+8) = xmm4[0];		/* Save R7 */ \
	f64ptr2(src,d2+d1+16+8) = xmm1[0];	/* Save R8 */ \
	f64ptr2(src,d2+d1+32+8) = xmm0[0];	/* Save I7 */ \
\
	xmm3[0] = f64ptr2(src,0+8);		/* R1 */ \
	xmm4[0] = f64ptr2(src,16+8);		/* R2 */ \
	xmm7[0] = xmm3[0];			/* Copy R1 */ \
	xmm3[0] -= xmm4[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm4[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5[0] = f64ptr2(src,32+8);		/* I1 */ \
	xmm6[0] = f64ptr2(src,48+8);		/* I2 */ \
	xmm7[0] = xmm5[0];			/* Copy I1 */ \
	xmm5[0] -= xmm6[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm6[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	xs_complex_square(xmm3[0], xmm5[0], xmm7[0]);	/* Square R2/I2 */ \
	xs_complex_square(xmm4[0], xmm6[0], xmm7[0]);	/* Square R1/I1 */ \
\
	xmm7[0] = xmm4[0];			/* Copy R1 */ \
	xmm4[0] -= xmm3[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm3[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[0] = xmm6[0];			/* Copy I1 */ \
	xmm6[0] -= xmm5[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm5[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	f64ptr2(src,16+8) = xmm4[0];		/* Save R2 */ \
	f64ptr2(src,0+8) = xmm3[0];		/* Save R1 */ \
	f64ptr2(src,48+8) = xmm6[0];		/* Save I2 */ \
	f64ptr2(src,32+8) = xmm5[0];		/* Save I1 */ \
\
	xmm5[0] = f64ptr2(src,d1+8);		/* R3 */ \
	xmm6[0] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm7[0] = xmm5[0];			/* Copy R3 */ \
	xmm5[0] -= xmm6[0];			/* R3 = R3 - I4 (new R3) */ \
	xmm6[0] += xmm7[0];			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3[0] = f64ptr2(src,d1+32+8);		/* I3 */ \
	xmm4[0] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm7[0] = xmm3[0];			/* Copy I3 */ \
	xmm3[0] -= xmm4[0];			/* I3 = I3 - R4 (final I4) */ \
	xmm4[0] += xmm7[0];			/* R4 = I3 + R4 (final I3) */ \
\
	xs_complex_square(xmm6[0], xmm3[0], xmm7[0]);	/* Square R4/I4 */ \
	xs_complex_square(xmm5[0], xmm4[0], xmm7[0]);	/* Square R3/I3 */ \
\
	xmm7[0] = xmm6[0];			/* Copy R4 */ \
	xmm6[0] -= xmm5[0];			/* R4 = R4 - R3 (new I4) */ \
	xmm5[0] += xmm7[0];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7[0] = xmm4[0];			/* Copy I3 */ \
	xmm4[0] -= xmm3[0];			/* I3 = I3 - I4 (new R4) */ \
	xmm3[0] += xmm7[0];			/* I4 = I3 + I4 (new I3) */ \
\
	f64ptr2(src,d1+48+8) = xmm6[0];		/* Save I4 */ \
	f64ptr2(src,d1+8) = xmm5[0];		/* Save R3 */ \
	f64ptr2(src,d1+16+8) = xmm4[0];		/* Save R4 */ \
	f64ptr2(src,d1+32+8) = xmm3[0];		/* Save I3 */ \
\
\

#if 1
#define r8_h16r_simple_unfft(src,dstreg,d1,d2) { \
\
	vec2f64 m0,m1,m2,m3,m4,m5,m6,m7; \
	m0 = xptr2(src,0); 			/* R1 R1 */ \
	m1 = xptr2(src,32); 		/* R3 I1 */ \
	m2 = xptr2(src,d1); 		/* R5 R3 */ \
	m3 = xptr2(src,d1+32); 		/* I5 I3 */ \
	m4 = xptr2(src,d2);			/* R9 R5 */ \
	m5 = xptr2(src,d2+32); 		/* I9 I5 */ \
	m6 = xptr2(src,d2+d1); 		/* R11 R7 */ \
	m7 = xptr2(src,d2+d1+32); 		/* I11 I7 */ \
\
	xmm7[0] = m0[0]; 		/* R1 */ \
	xmm3[0] = m1[0]; 		/* R3 */ \
	xmm1[0] = m2[0]; 		/* R5 */ \
	xmm5[0] = m3[0]; 		/* I5 */ \
	xmm4[0] = m4[0];		/* R9 */ \
	xmm6[0] = m5[0]; 		/* I9 */ \
	xmm0[0] = m6[0]; 		/* R11 */ \
	xmm2[0] = m7[0]; 		/* I11 */ \
\
	xmm7[0] -= xmm3[0];			/* R1 = R1 - R3 (new R3) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm7[0];			/* R3 = R1 + R3 (new R1) */ \
\
;						/* R5/I5 morphs into new R5/R7 */ \
\
	xmm4[0] -= xmm0[0];			/* R9 = R9 - R11 (new R11) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm4[0];			/* R9 = R9 + R11 (new R9) */ \
\
	xmm6[0] -= xmm2[0];			/* I9 = I9 - I11 (new I11) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm6[0];			/* I9 = I9 + I11 (new I9) */ \
\
;	/* Premultipliers for odd level 3 */ \
\
;						/* mul R11/I11 by SQRTHALF - i*SQRTHALF */ \
	xmm6[0] -= xmm4[0];			/* I11 = I11 - R11 */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm6[0];			/* R11 = I11 + R11 */ \
	xmm6[0] *= XMM_SQRTHALF1;		/* I11 = I11 * SQRTHALF */ \
	xmm4[0] *= XMM_SQRTHALF1;		/* R11 = R11 * SQRTHALF */ \
\
;	/* Odd level 2 */ \
\
	xmm3[0] -= xmm1[0];			/* R1 = R1 - R5 (newer R5) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm3[0];			/* R5 = R1 + R5 (newer R1) */ \
\
	xmm7[0] -= xmm5[0];			/* R3 = R3 - R7 (newer R7) */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm7[0];			/* R7 = R3 + R7 (newer R3) */ \
\
;						/* R9/I9 morphs into newer R9/R13 */ \
;						/* R11/I11 morphs into newer R11/R15 */ \
\
;	/* Odd level 1 */ \
\
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R9 (new R9) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R9 = R1 + R9 (new R1) */ \
\
	xmm3[0] -= xmm2[0];			/* R5 = R5 - R13 (new R13) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* R13 = R5 + R13 (new R5) */ \
\
	xmm5[0] -= xmm4[0];			/* R3 = R3 - R11 (new R11) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm5[0];			/* R11 = R3 + R11 (new R3) */ \
\
	xmm7[0] -= xmm6[0];			/* R7 = R7 - R15 (new R15) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm7[0];			/* R15 = R7 + R15 (new R7) */ \
\
	xmm6[1] = m0[1];		/* R1 */ \
	xmm2[1] = m2[1];		/* R3 */ \
	xmm0[1] = m4[1];		/* R5 */ \
	xmm4[1] = m5[1];		/* I5 */ \
	xmm5[1] = m6[1];		/* R7 */ \
	xmm1[1] = m7[1];		/* I7 */ \
\
	xmm3[1] = xmm4[1];			/* Copy I5 */ \
	xmm4[1] -= xmm1[1];			/* I5 = I5 - I7 (new R7) */ \
	xmm1[1] += xmm3[1];			/* I7 = I5 + I7 (new I5) */ \
\
	xmm3[1] = xmm6[1];			/* Copy R1 */ \
	xmm6[1] -= xmm2[1];			/* R1 = R1 - R3 (new R3) */ \
	xmm2[1] += xmm3[1];			/* R3 = R1 + R3 (new R1) */ \
\
	xmm3[1] = xmm6[1];			/* Copy R3 */ \
	xmm6[1] -= xmm4[1];			/* R3 = R3 - R7 (final R7) */ \
	xmm4[1] += xmm3[1];			/* R7 = R3 + R7 (final R3) */ \
\
	xptr(dstreg+d2) = xmm4;		/* Save R3 R3 */ \
	xptr(dstreg+d2+16) = xmm6;		/* Save R7 R7 */ \
\
	xmm3[1] = xmm0[1];			/* Copy R5 */ \
	xmm0[1] += xmm5[1];			/* R5 = R7 + R5 (new R5) */ \
	xmm5[1] -= xmm3[1];			/* R7 = R7 - R5 (new I7) */ \
\
	xmm7[1] = m1[1];		/* I1 */ \
	xmm6[1] = m3[1];		/* I3 */ \
	xmm3[1] = xmm7[1];			/* Copy I1 */ \
	xmm7[1] -= xmm6[1];			/* I1 = I1 - I3 (new I3) */ \
	xmm6[1] += xmm3[1];			/* I3 = I1 + I3 (new I1) */ \
\
	xmm3[1] = xmm7[1];			/* Copy I3 */ \
	xmm7[1] -= xmm5[1];			/* I3 = I3 - I7 (final I7) */ \
	xmm5[1] += xmm3[1];			/* I7 = I3 + I7 (final I3) */ \
\
	xmm3[1] = xmm2[1];			/* Copy R1 */ \
	xmm2[1] -= xmm0[1];			/* R1 = R1 - R5 (final R5) */ \
	xmm0[1] += xmm3[1];			/* R5 = R1 + R5 (final R1) */ \
\
	xmm3[1] = xmm6[1];			/* Copy I1 */ \
	xmm6[1] -= xmm1[1];			/* I1 = I1 - I5 (final I5) */ \
	xmm1[1] += xmm3[1];			/* I5 = I1 + I5 (final I1) */ \
\
	xptr(dstreg) = xmm0;		/* R1 R1 */ \
	xptr(dstreg+16) = xmm2;		/* R5 R5 */ \
	xptr(dstreg+32) = xmm1;		/* R9 I1 */ \
	xmm3[1] = xmm6[1]; \
	xptr(dstreg+48) = xmm3;		/* R13 I5 */ \
	xptr(dstreg+d2+32) = xmm5;		/* R11 I7 */ \
	xptr(dstreg+d2+48) = xmm7;		/* R15 I3 */ \
\
	\
	m0 = xptr2(src,16);			/* R2 R2 */ \
	m1 = xptr2(src,48);			/* R4 I2 */ \
	m2 = xptr2(src,d1+16);		/* R6 R4 */ \
	m3 = xptr2(src,d1+48);		/* I6 I4 */ \
	m4 = xptr2(src,d2+16);		/* R10 R6 */ \
	m5 = xptr2(src,d2+48);		/* I10 I6 */ \
	m6 = xptr2(src,d2+d1+16);		/* R12 R8 */ \
	m7 = xptr2(src,d2+d1+48);		/* I12 I8 */ \
	/* Premultipliers for even level 4 */ \
\
				/* mul R6/I6 by w^2 = .707 - .707i */ \
	xmm1[0] = m2[0]; 		/* R6 */ \
	xmm5[0] = m3[0]; 		/* I6 */ \
	xmm5[0] -= xmm1[0];			/* I6 = I6 - R6 */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm5[0];			/* R6 = I6 + R6 */ \
	xmm5[0] *= XMM_SQRTHALF1;		/* I6 = I6 * SQRTHALF */ \
	xmm1[0] *= XMM_SQRTHALF1;		/* R6 = R6 * SQRTHALF */ \
\
;	/* Even level 3 */ \
\
	xmm7[0] = m0[0];		/* R2 */ \
	xmm3[0] = m1[0]; 		/* R4 */ \
	xmm4[0] = m4[0]; 		/* R10 */ \
	xmm6[0] = m5[0]; 		/* I10 */ \
	xmm0[0] = m6[0]; 		/* R12 */ \
	xmm2[0] = m7[0]; 		/* I12 */ \
\
	xmm7[0] -= xmm3[0];			/* R2 = R2 - R4 (new R4) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm7[0];			/* R4 = R2 + R4 (new R2) */ \
\
;						/* R6/I6 morph into new R6/R8 */ \
\
	xmm4[0] -= xmm0[0];			/* R10 = R10 - R12 (new R12) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm4[0];			/* R10 = R10 + R12 (new R10) */ \
\
	xmm6[0] -= xmm2[0];			/* I10 = I10 - I12 (new I12) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm6[0];			/* I10 = I10 + I12 (new I10) */ \
\
;	/* Premultipliers for even level 3 */ \
\
	double tmp0 = xmm1[0]; \
	double tmp1 = xmm3[0]; \
\
;						/* mul R10/I10 by w^1 = .924 - .383i */ \
	xmm1[0] = xmm0[0];			/* Copy R10 */ \
	xmm0[0] *= CONST_P924; \
	xmm3[0] = xmm2[0];			/* Copy I10 */ \
	xmm3[0] *= CONST_P383; \
	xmm0[0] += xmm3[0];			/* Twiddled R10 */ \
	xmm1[0] *= CONST_P383; \
	xmm2[0] *= CONST_P924; \
	xmm2[0] -= xmm1[0];			/* Twiddled I10 */ \
\
;						/* mul R12/I12 by w^3 = .383 - .924i */ \
	xmm1[0] = xmm4[0];			/* Copy R12 */ \
	xmm4[0] *= CONST_P383; \
	xmm3[0] = xmm6[0];			/* Copy I12 */ \
	xmm3[0] *= CONST_P924; \
	xmm4[0] += xmm3[0];			/* Twiddled R12 */ \
	xmm1[0] *= CONST_P924; \
	xmm6[0] *= CONST_P383; \
	xmm6[0] -= xmm1[0];			/* Twiddled I12 */ \
\
	xmm1[0] = tmp0; \
	xmm3[0] = tmp1; \
\
;	/* Even level 2 */ \
\
	xmm3[0] -= xmm1[0];			/* R2 = R2 - R6 (newer R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm3[0];			/* R6 = R2 + R6 (newer R2) */ \
\
	xmm7[0] -= xmm5[0];			/* R4 = R4 - R8 (newer R8) */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm7[0];			/* R8 = R4 + R8 (newer R4) */ \
\
;						/* R10/I10 morphs into newer R10/R14 */ \
;						/* R12/I12 morphs into newer R12/R16 */ \
\
;	/* Even level 1 */ \
\
	xmm1[0] -= xmm0[0];			/* R2 = R2 - R10 (new R10) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R10 = R2 + R10 (new R2) */ \
\
	xmm3[0] -= xmm2[0];			/* R6 = R6 - R14 (new R14) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* R14 = R6 + R14 (new R6) */ \
\
	xmm5[0] -= xmm4[0];			/* R4 = R4 - R12 (new R12) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm5[0];			/* R12 = R4 + R12 (new R4) */ \
\
	xmm7[0] -= xmm6[0];			/* R8 = R8 - R16 (new R16) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm7[0];			/* R16 = R8 + R16 (new R8) */ \
\
\
;	/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm0[1] = m4[1];		/* R6 */ \
	xmm4[1] = m5[1];		/* I6 */ \
	xmm5[1] = m6[1];		/* R8 */ \
	xmm1[1] = m7[1];		/* I8 */ \
	xmm6[1] = m0[1];		/* R2 */ \
	xmm2[1] = m2[1];		/* R4 */ \
\
	xmm3[1] = xmm4[1];			/* Copy I6 */ \
	xmm4[1] -= xmm0[1];			/* I6 = I6 - R6 */ \
	xmm0[1] += xmm3[1];			/* R6 = R6 + I6 */ \
\
;	/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm3[1] = xmm1[1];			/* Copy I8 */ \
	xmm1[1] -= xmm5[1];			/* I8 = I8 - R8 */ \
	xmm5[1] += xmm3[1];			/* R8 = R8 + I8 */ \
\
	xmm7[1] = XMM_SQRTHALF1; \
	xmm4[1] *= xmm7[1];			/* I6 = I6 * SQRTHALF (new I6) */ \
	xmm0[1] *= xmm7[1];			/* R6 = R6 * SQRTHALF (new R6) */ \
	xmm1[1] *= xmm7[1];			/* I8 = I8 * SQRTHALF (new I8) */ \
	xmm5[1] *= xmm7[1];			/* R8 = R8 * SQRTHALF (new R8) */ \
\
	xmm3[1] = xmm2[1];			/* Copy R4 */ \
	xmm2[1] += xmm6[1];			/* R4 = R2 + R4 (new R2) */ \
	xmm6[1] -= xmm3[1];			/* R2 = R2 - R4 (new R4) */ \
\
	xmm3[1] = xmm5[1];			/* Copy R8 */ \
	xmm5[1] -= xmm0[1];			/* R8 = R8 - R6 (new I8) */ \
	xmm0[1] += xmm3[1];			/* R6 = R8 + R6 (new R6) */ \
\
	xmm3[1] = xmm4[1];			/* Copy I6 */ \
	xmm4[1] -= xmm1[1];			/* I6 = I6 - I8 (new R8) */ \
	xmm1[1] += xmm3[1];			/* I8 = I6 + I8 (new I6) */ \
\
	xmm3[1] = xmm2[1];			/* Copy R2 */ \
	xmm2[1] -= xmm0[1];			/* R2 = R2 - R6 (final R6) */ \
	xmm0[1] += xmm3[1];			/* R6 = R2 + R6 (final R2) */ \
\
	xptr(dstreg+d1) = xmm0;		/* R2 R2 */ \
	xptr(dstreg+d1+16) = xmm2;		/* R6 R6 */ \
\
	xmm7[1] = m1[1];		/* I2 */ \
	xmm2[1] = m3[1];		/* I4 */ \
	xmm3[1] = xmm2[1];			/* Copy I4 */ \
	xmm2[1] += xmm7[1];			/* I4 = I2 + I4 (new I2) */ \
	xmm7[1] -= xmm3[1];			/* I2 = I2 - I4 (new I4) */ \
\
	xmm3[1] = xmm6[1];			/* Copy R4 */ \
	xmm6[1] -= xmm4[1];			/* R4 = R4 - R8 (final R8) */ \
	xmm4[1] += xmm3[1];			/* R8 = R4 + R8 (final R4) */ \
\
	xmm3[1] = xmm2[1];			/* Copy I2 */ \
	xmm2[1] -= xmm1[1];			/* I2 = I2 - I6 (final I6) */ \
	xmm1[1] += xmm3[1];			/* I6 = I2 + I6 (final I2) */ \
\
	xmm3[1] = xmm7[1];			/* Copy I4 */ \
	xmm7[1] -= xmm5[1];			/* I4 = I4 - I8 (final I8) */ \
	xmm5[1] += xmm3[1];			/* I8 = I4 + I8 (final I4) */ \
\
	xptr(dstreg+d1+32) = xmm1;		/* R10 I2 */ \
	xmm3[1] = xmm2[1]; \
	xptr(dstreg+d1+48) = xmm3;		/* R14 I6 */ \
	xptr(dstreg+d2+d1) = xmm4;		/* R4 R4 */ \
	xptr(dstreg+d2+d1+16) = xmm6;	/* R8 R8 */ \
	xptr(dstreg+d2+d1+32) = xmm5;	/* R12 I4 */ \
	xptr(dstreg+d2+d1+48) = xmm7;	/* R16 I8 */ \
}
#else
#define r8_h16r_simple_unfft(src,dstreg,d1,d2) \
	r8_h16r_simple_unfft_16r(src,dstreg,d1,d2) \
	r8_h16r_simple_unfft_8c(src,dstreg,d1,d2)
#endif

#define r8_h16r_simple_unfft_16r(src,dstreg,d1,d2) { \
	/* Do the 16-reals part */ \
\
	/* Premultipliers for even level 4 */ \
\
						/* mul R6/I6 by w^2 = .707 - .707i */ \
	xmm1[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm5[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm5[0] -= xmm1[0];			/* I6 = I6 - R6 */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm5[0];			/* R6 = I6 + R6 */ \
	xmm5[0] *= XMM_SQRTHALF1;		/* I6 = I6 * SQRTHALF */ \
	xmm1[0] *= XMM_SQRTHALF1;		/* R6 = R6 * SQRTHALF */ \
\
;	/* Even level 3 */ \
\
	xmm7[0] = f64ptr2(src,16);			/* R2 */ \
	xmm3[0] = f64ptr2(src,48); 		/* R4 */ \
	xmm4[0] = f64ptr2(src,d2+16); 		/* R10 */ \
	xmm6[0] = f64ptr2(src,d2+48); 		/* I10 */ \
	xmm0[0] = f64ptr2(src,d2+d1+16); 		/* R12 */ \
	xmm2[0] = f64ptr2(src,d2+d1+48); 		/* I12 */ \
\
	xmm7[0] -= xmm3[0];			/* R2 = R2 - R4 (new R4) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm7[0];			/* R4 = R2 + R4 (new R2) */ \
\
;						/* R6/I6 morph into new R6/R8 */ \
\
	xmm4[0] -= xmm0[0];			/* R10 = R10 - R12 (new R12) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm4[0];			/* R10 = R10 + R12 (new R10) */ \
\
	xmm6[0] -= xmm2[0];			/* I10 = I10 - I12 (new I12) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm6[0];			/* I10 = I10 + I12 (new I10) */ \
\
;	/* Premultipliers for even level 3 */ \
\
	double tmp0 = xmm1[0]; \
	double tmp1 = xmm3[0]; \
\
;						/* mul R10/I10 by w^1 = .924 - .383i */ \
	xmm1[0] = xmm0[0];			/* Copy R10 */ \
	xmm0[0] *= CONST_P924; \
	xmm3[0] = xmm2[0];			/* Copy I10 */ \
	xmm3[0] *= CONST_P383; \
	xmm0[0] += xmm3[0];			/* Twiddled R10 */ \
	xmm1[0] *= CONST_P383; \
	xmm2[0] *= CONST_P924; \
	xmm2[0] -= xmm1[0];			/* Twiddled I10 */ \
\
;						/* mul R12/I12 by w^3 = .383 - .924i */ \
	xmm1[0] = xmm4[0];			/* Copy R12 */ \
	xmm4[0] *= CONST_P383; \
	xmm3[0] = xmm6[0];			/* Copy I12 */ \
	xmm3[0] *= CONST_P924; \
	xmm4[0] += xmm3[0];			/* Twiddled R12 */ \
	xmm1[0] *= CONST_P924; \
	xmm6[0] *= CONST_P383; \
	xmm6[0] -= xmm1[0];			/* Twiddled I12 */ \
\
	xmm1[0] = tmp0; \
	xmm3[0] = tmp1; \
\
;	/* Even level 2 */ \
\
	xmm3[0] -= xmm1[0];			/* R2 = R2 - R6 (newer R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm3[0];			/* R6 = R2 + R6 (newer R2) */ \
\
	xmm7[0] -= xmm5[0];			/* R4 = R4 - R8 (newer R8) */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm7[0];			/* R8 = R4 + R8 (newer R4) */ \
\
;						/* R10/I10 morphs into newer R10/R14 */ \
;						/* R12/I12 morphs into newer R12/R16 */ \
\
;	/* Even level 1 */ \
\
	xmm1[0] -= xmm0[0];			/* R2 = R2 - R10 (new R10) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R10 = R2 + R10 (new R2) */ \
\
	xmm3[0] -= xmm2[0];			/* R6 = R6 - R14 (new R14) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* R14 = R6 + R14 (new R6) */ \
\
	xmm5[0] -= xmm4[0];			/* R4 = R4 - R12 (new R12) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm5[0];			/* R12 = R4 + R12 (new R4) */ \
\
	xmm7[0] -= xmm6[0];			/* R8 = R8 - R16 (new R16) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm7[0];			/* R16 = R8 + R16 (new R8) */ \
\
	f64ptr(dstreg+d1+32) = xmm1[0];		/* R10 */ \
	f64ptr(dstreg+d1) = xmm0[0];		/* R2 */ \
	f64ptr(dstreg+d1+48) = xmm3[0];		/* R14 */ \
	f64ptr(dstreg+d1+16) = xmm2[0];		/* R6 */ \
	f64ptr(dstreg+d2+d1+32) = xmm5[0];	/* R12 */ \
	f64ptr(dstreg+d2+d1) = xmm4[0];		/* R4 */ \
	f64ptr(dstreg+d2+d1+48) = xmm7[0];	/* R16 */ \
	f64ptr(dstreg+d2+d1+16) = xmm6[0];	/* R8 */ \
\
;	/* Odd level 3 */ \
\
	xmm7[0] = f64ptr2(src,0); 			/* R1 */ \
	xmm3[0] = f64ptr2(src,32); 		/* R3 */ \
	xmm1[0] = f64ptr2(src,d1); 		/* R5 */ \
	xmm5[0] = f64ptr2(src,d1+32); 		/* I5 */ \
	xmm4[0] = f64ptr2(src,d2);			/* R9 */ \
	xmm6[0] = f64ptr2(src,d2+32); 		/* I9 */ \
	xmm0[0] = f64ptr2(src,d2+d1); 		/* R11 */ \
	xmm2[0] = f64ptr2(src,d2+d1+32); 		/* I11 */ \
\
	xmm7[0] -= xmm3[0];			/* R1 = R1 - R3 (new R3) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm7[0];			/* R3 = R1 + R3 (new R1) */ \
\
;						/* R5/I5 morphs into new R5/R7 */ \
\
	xmm4[0] -= xmm0[0];			/* R9 = R9 - R11 (new R11) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm4[0];			/* R9 = R9 + R11 (new R9) */ \
\
	xmm6[0] -= xmm2[0];			/* I9 = I9 - I11 (new I11) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm6[0];			/* I9 = I9 + I11 (new I9) */ \
\
;	/* Premultipliers for odd level 3 */ \
\
;						/* mul R11/I11 by SQRTHALF - i*SQRTHALF */ \
	xmm6[0] -= xmm4[0];			/* I11 = I11 - R11 */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm6[0];			/* R11 = I11 + R11 */ \
	xmm6[0] *= XMM_SQRTHALF1;		/* I11 = I11 * SQRTHALF */ \
	xmm4[0] *= XMM_SQRTHALF1;		/* R11 = R11 * SQRTHALF */ \
\
;	/* Odd level 2 */ \
\
	xmm3[0] -= xmm1[0];			/* R1 = R1 - R5 (newer R5) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm3[0];			/* R5 = R1 + R5 (newer R1) */ \
\
	xmm7[0] -= xmm5[0];			/* R3 = R3 - R7 (newer R7) */ \
	xmm5[0] += xmm5[0]; /* multwo */ \
	xmm5[0] += xmm7[0];			/* R7 = R3 + R7 (newer R3) */ \
\
;						/* R9/I9 morphs into newer R9/R13 */ \
;						/* R11/I11 morphs into newer R11/R15 */ \
\
;	/* Odd level 1 */ \
\
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R9 (new R9) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R9 = R1 + R9 (new R1) */ \
\
	xmm3[0] -= xmm2[0];			/* R5 = R5 - R13 (new R13) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* R13 = R5 + R13 (new R5) */ \
\
	xmm5[0] -= xmm4[0];			/* R3 = R3 - R11 (new R11) */ \
	xmm4[0] += xmm4[0]; /* multwo */ \
	xmm4[0] += xmm5[0];			/* R11 = R3 + R11 (new R3) */ \
\
	xmm7[0] -= xmm6[0];			/* R7 = R7 - R15 (new R15) */ \
	xmm6[0] += xmm6[0]; /* multwo */ \
	xmm6[0] += xmm7[0];			/* R15 = R7 + R15 (new R7) */ \
\
	f64ptr(dstreg+32) = xmm1[0];		/* R9 */ \
	f64ptr(dstreg) = xmm0[0];		/* R1 */ \
	f64ptr(dstreg+48) = xmm3[0];		/* R13 */ \
	f64ptr(dstreg+16) = xmm2[0];		/* R5 */ \
	f64ptr(dstreg+d2+32) = xmm5[0];		/* R11 */ \
	f64ptr(dstreg+d2) = xmm4[0];		/* R3 */ \
	f64ptr(dstreg+d2+48) = xmm7[0];		/* R15 */ \
	f64ptr(dstreg+d2+16) = xmm6[0];		/* R7 */ \
}
#define r8_h16r_simple_unfft_8c(src,dstreg,d1,d2) \
	/* Do the eight-complex part */ \
\
	xmm5[0] = f64ptr2(src,d2+32+8);		/* I5 */ \
	xmm1[0] = f64ptr2(src,d2+d1+32+8);	/* I7 */ \
	xmm7[0] = xmm5[0];			/* Copy I5 */ \
	xmm5[0] -= xmm1[0];			/* I5 = I5 - I7 (new R7) */ \
	xmm1[0] += xmm7[0];			/* I7 = I5 + I7 (new I5) */ \
\
	xmm4[0] = f64ptr2(src,0+8);		/* R1 */ \
	xmm2[0] = f64ptr2(src,d1+8);		/* R3 */ \
	xmm7[0] = xmm4[0];			/* Copy R1 */ \
	xmm4[0] -= xmm2[0];			/* R1 = R1 - R3 (new R3) */ \
	xmm2[0] += xmm7[0];			/* R3 = R1 + R3 (new R1) */ \
\
	xmm7[0] = xmm4[0];			/* Copy R3 */ \
	xmm4[0] -= xmm5[0];			/* R3 = R3 - R7 (final R7) */ \
	xmm5[0] += xmm7[0];			/* R7 = R3 + R7 (final R3) */ \
\
	f64ptr(dstreg+d2+16+8) = xmm4[0];	/* Save R7 */ \
	f64ptr(dstreg+d2+8) = xmm5[0];		/* Save R3 */ \
\
	xmm6[0] = f64ptr2(src,d2+8);		/* R5 */ \
	xmm0[0] = f64ptr2(src,d2+d1+8);		/* R7 */ \
	xmm7[0] = xmm6[0];			/* Copy R5 */ \
	xmm6[0] += xmm0[0];			/* R5 = R7 + R5 (new R5) */ \
	xmm0[0] -= xmm7[0];			/* R7 = R7 - R5 (new I7) */ \
\
	xmm3[0] = f64ptr2(src,32+8);		/* I1 */ \
	xmm4[0] = f64ptr2(src,d1+32+8);		/* I3 */ \
	xmm7[0] = xmm3[0];			/* Copy I1 */ \
	xmm3[0] -= xmm4[0];			/* I1 = I1 - I3 (new I3) */ \
	xmm4[0] += xmm7[0];			/* I3 = I1 + I3 (new I1) */ \
\
	xmm7[0] = xmm3[0];			/* Copy I3 */ \
	xmm3[0] -= xmm0[0];			/* I3 = I3 - I7 (final I7) */ \
	xmm0[0] += xmm7[0];			/* I7 = I3 + I7 (final I3) */ \
\
	f64ptr(dstreg+d2+48+8) = xmm3[0];	/* I7 */ \
	f64ptr(dstreg+d2+32+8) = xmm0[0];	/* I3 */ \
\
	xmm7[0] = xmm2[0];			/* Copy R1 */ \
	xmm2[0] -= xmm6[0];			/* R1 = R1 - R5 (final R5) */ \
	xmm6[0] += xmm7[0];			/* R5 = R1 + R5 (final R1) */ \
\
	xmm7[0] = xmm4[0];			/* Copy I1 */ \
	xmm4[0] -= xmm1[0];			/* I1 = I1 - I5 (final I5) */ \
	xmm1[0] += xmm7[0];			/* I5 = I1 + I5 (final I1) */ \
\
	f64ptr(dstreg+16+8) = xmm2[0];		/* R5 */ \
	f64ptr(dstreg+8) = xmm6[0];		/* R1 */ \
	f64ptr(dstreg+48+8) = xmm4[0];		/* I5 */ \
	f64ptr(dstreg+32+8) = xmm1[0];		/* I1 */ \
\
\
;	/* multiply R6/I6 by SQRTHALF - i*SQRTHALF */ \
	xmm4[0] = f64ptr2(src,d2+16+8);		/* R6 */ \
	xmm0[0] = f64ptr2(src,d2+48+8);		/* I6 */ \
	xmm7[0] = xmm0[0];			/* Copy I6 */ \
	xmm0[0] -= xmm4[0];			/* I6 = I6 - R6 */ \
	xmm4[0] += xmm7[0];			/* R6 = R6 + I6 */ \
\
;	/* multiply R8/I8 by SQRTHALF - i*SQRTHALF */ \
	xmm2[0] = f64ptr2(src,d2+d1+16+8);	/* R8 */ \
	xmm1[0] = f64ptr2(src,d2+d1+48+8);	/* I8 */ \
	xmm7[0] = xmm1[0];			/* Copy I8 */ \
	xmm1[0] -= xmm2[0];			/* I8 = I8 - R8 */ \
	xmm2[0] += xmm7[0];			/* R8 = R8 + I8 */ \
\
	xmm5[0] = XMM_SQRTHALF1; \
	xmm0[0] *= xmm5[0];			/* I6 = I6 * SQRTHALF (new I6) */ \
	xmm4[0] *= xmm5[0];			/* R6 = R6 * SQRTHALF (new R6) */ \
	xmm1[0] *= xmm5[0];			/* I8 = I8 * SQRTHALF (new I8) */ \
	xmm2[0] *= xmm5[0];			/* R8 = R8 * SQRTHALF (new R8) */ \
\
	xmm6[0] = f64ptr2(src,16+8);		/* R2 */ \
	xmm3[0] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm7[0] = xmm3[0];			/* Copy R4 */ \
	xmm3[0] += xmm6[0];			/* R4 = R2 + R4 (new R2) */ \
	xmm6[0] -= xmm7[0];			/* R2 = R2 - R4 (new R4) */ \
\
	xmm7[0] = xmm2[0];			/* Copy R8 */ \
	xmm2[0] -= xmm4[0];			/* R8 = R8 - R6 (new I8) */ \
	xmm4[0] += xmm7[0];			/* R6 = R8 + R6 (new R6) */ \
\
	xmm7[0] = xmm0[0];			/* Copy I6 */ \
	xmm0[0] -= xmm1[0];			/* I6 = I6 - I8 (new R8) */ \
	xmm1[0] += xmm7[0];			/* I8 = I6 + I8 (new I6) */ \
\
	xmm7[0] = xmm3[0];			/* Copy R2 */ \
	xmm3[0] -= xmm4[0];			/* R2 = R2 - R6 (final R6) */ \
	xmm4[0] += xmm7[0];			/* R6 = R2 + R6 (final R2) */ \
\
	f64ptr(dstreg+d1+16+8) = xmm3[0];	/* R6 */ \
	f64ptr(dstreg+d1+8) = xmm4[0];		/* R2 */ \
\
	xmm5[0] = f64ptr2(src,48+8);		/* I2 */ \
	xmm3[0] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm7[0] = xmm3[0];			/* Copy I4 */ \
	xmm3[0] += xmm5[0];			/* I4 = I2 + I4 (new I2) */ \
	xmm5[0] -= xmm7[0];			/* I2 = I2 - I4 (new I4) */ \
\
	xmm7[0] = xmm6[0];			/* Copy R4 */ \
	xmm6[0] -= xmm0[0];			/* R4 = R4 - R8 (final R8) */ \
	xmm0[0] += xmm7[0];			/* R8 = R4 + R8 (final R4) */ \
\
	xmm7[0] = xmm3[0];			/* Copy I2 */ \
	xmm3[0] -= xmm1[0];			/* I2 = I2 - I6 (final I6) */ \
	xmm1[0] += xmm7[0];			/* I6 = I2 + I6 (final I2) */ \
\
	xmm7[0] = xmm5[0];			/* Copy I4 */ \
	xmm5[0] -= xmm2[0];			/* I4 = I4 - I8 (final I8) */ \
	xmm2[0] += xmm7[0];			/* I8 = I4 + I8 (final I4) */ \
\
	f64ptr(dstreg+d2+d1+16+8) = xmm6[0];	/* R8 */ \
	f64ptr(dstreg+d2+d1+8) = xmm0[0];	/* R4 */ \
	f64ptr(dstreg+d1+48+8) = xmm3[0];	/* I6 */ \
	f64ptr(dstreg+d1+32+8) = xmm1[0];	/* I2 */ \
	f64ptr(dstreg+d2+d1+48+8) = xmm5[0];	/* I8 */ \
	f64ptr(dstreg+d2+d1+32+8) = xmm2[0];	/* I4 */ \
\
\
\

#if 0
#define r8_h8cl_sixteen_reals_eight_complex_with_mult(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	xmult7(srcreg, srcreg+rbp); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_h16r_simple_fft_part1_16r(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_with_mult_16r(XMM_COL_MULTS_1,srcreg+rbp,d1,d2,srcreg); \
	r8_h16r_simple_unfft_16r(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_h16r_simple_fft_part1_8c(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_h16r_simple_fft_with_mult_8c(XMM_COL_MULTS_1,srcreg+rbp,d1,d2,srcreg); \
	r8_h16r_simple_unfft_8c(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_mult(XMM_COL_MULTS_2,srcreg+d4+rbp,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#elif 1
#define r8_h8cl_sixteen_reals_eight_complex_with_mult(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS_1[16]; \
	vec2f64 XMM_COL_MULTS_2[16]; \
	xmult7(srcreg, srcreg+rbp); \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,XMM_COL_MULTS_1); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,XMM_COL_MULTS_2); \
	r8_x8c_simple_fft_with_mult(XMM_COL_MULTS_2,srcreg+d4+rbp,d1,d2); \
	r8_x8c_simple_unfft(XMM_COL_MULTS_2,srcreg+d4,d1,d2); \
	r8_h16r_simple_fft_with_mult(XMM_COL_MULTS_1,srcreg+rbp,d1,d2,srcreg); \
	r8_h16r_simple_unfft(XMM_COL_MULTS_1,srcreg+0,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_h8cl_sixteen_reals_eight_complex_with_mult(srcreg,srcinc,d1,d2,d4) \
	xmult7(srcreg, srcreg+rbp); \
	r8_h16r_simple_fft_part1(srcreg+0,d1,d2,d4,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_part1(srcreg+32,d1,d2,d4,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_h16r_simple_fft_with_mult(g->u.xmm.XMM_COL_MULTS,srcreg+rbp,d1,d2,srcreg); \
	r8_x8c_simple_fft_with_mult((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4+rbp,d1,d2); \
	r8_h16r_simple_unfft(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#if 1
#define r8_h16r_simple_fft_with_mult(src,altsrc,d1,d2,origsrc) \
\
	xmm0 = xptr2(src,0);		/* R1 R1 */ \
	xmm1 = xptr2(src,16); 		/* R2 R2 */ \
	xmm7 = xmm0;			/* Copy R1 R1 */ \
	xmm0 -= xmm1;			/* R1R1 = R1R1 - R2R2 (new R2R2) */ \
	xmm1 += xmm7;			/* R2R2 = R1R1 + R2R2 (new R1R1) */ \
\
	xmm1[0] *= f64ptr(altsrc);		/* R1 * R1-from-mem */ \
	xmm0[0] *= f64ptr(altsrc+32);		/* R2 * R2-from-mem */ \
	f64ptr(origsrc-16) = xmm1[0];		/* Save product of sum of FFT values */ \
\
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm1[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm0[0] += xmm1[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xmm2 = xptr2(src,32);		/* R3 I1 ; R3/R4 morphs into R3/I3 */ \
	xmm3 = xptr2(src,48);		/* R4 I2 */ \
\
	xmm7[1] = xmm2[1];			/* Copy I1 */ \
	xmm2[1] -= xmm3[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm3[1] += xmm7[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xmm4[0] = xmm2[0]; xmm4[1] = xmm0[1]; \
	xmm2[0] = xmm3[0]; \
	xp_complex_mult(xmm4, xmm2, xptr(altsrc+16), xptr(altsrc+48), xmm6, xmm7); /* Mult R3/I3 R2/I2 */ \
	xmm3[0] = xmm2[0]; \
	xmm2[0] = xmm4[0]; xmm0[1] = xmm4[1]; \
	\
	xs_complex_mult(xmm1[1], xmm3[1], f64ptr(altsrc+8), f64ptr(altsrc+32+8), xmm6[1], xmm7[1]); /* Mult R1/I1 */ \
\
						/* R3/I3 morphs into R3/R4 */ \
\
	xmm7[1] = xmm1[1];			/* Copy R1 */ \
	xmm1[1] -= xmm0[1];			/* R1 = R1 - R2 (new R2) */ \
	xmm0[1] += xmm7[1];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[1] = xmm3[1];			/* Copy I1 */ \
	xmm3[1] -= xmm2[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm2[1] += xmm7[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xptr2(src,0) = xmm0;			/* Save R1 R1 */ \
	xptr2(src,16) = xmm1;			/* Save R2 R2 */ \
	xptr2(src,32) = xmm2;			/* Save R3 I1 */ \
	xptr2(src,48) = xmm3;			/* Save R4 I2 */ \
\
\
	xmm0 = xptr2(src,d1   );		/* R5 R3 */ \
	xmm1 = xptr2(src,d1+16); 		/* R6 R4 */ \
	xmm2 = xptr2(src,d1+32);		/* I5 I3 */ \
	xmm3 = xptr2(src,d1+48); 		/* I6 I4 */ \
\
	xmm4[0] = xmm1[0]; xmm4[1] = xmm0[1]; \
	xmm5[0] = xmm3[0]; xmm5[1] = xmm1[1]; \
	xmm3[0] = xmm0[0]; \
\
	xmm7[0] = xmm3[0];			/* Copy R6 */ \
	xmm3[0] -= xmm4[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm4[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
	xmm7[1] = xmm4[1];			/* Copy R3 */ \
	xmm4[1] -= xmm3[1];			/* R3 = R3 - I4 (new R3) */ \
	xmm3[1] += xmm7[1];			/* I4 = R3 + I4 (new R4) */ \
\
	xmm7 = xmm2;			/* Copy I5 I3 */ \
	xmm2 -= xmm5;			/* I5I3 = I5I3 - I6R4 (new I6I4) */ \
	xmm5 += xmm7;			/* I6R4 = I5I3 + I6R4 (new I5I3) */ \
\
	xp_complex_mult(xmm4, xmm5, xptr(altsrc+d1), xptr(altsrc+d1+32), xmm6, xmm7); /* Mult R5/I5 R3/I3 */ \
	xp_complex_mult(xmm3, xmm2, xptr(altsrc+d1+16), xptr(altsrc+d1+48), xmm6, xmm7); /* Mult R6/I6 R4/I4 */ \
\
	xmm0[0] = xmm3[0]; \
	xmm1[0] = xmm4[0]; xmm0[1] = xmm4[1]; \
	xmm3[0] = xmm5[0]; xmm1[1] = xmm5[1]; \
\
	xmm1[0] -= xmm0[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm3[0] -= xmm2[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xmm7[1] = xmm3[1];			/* Copy R4 */ \
	xmm3[1] -= xmm0[1];			/* R4 = R4 - R3 (new I4) */ \
	xmm0[1] += xmm7[1];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7[1] = xmm1[1];			/* Copy I3 */ \
	xmm1[1] -= xmm2[1];			/* I3 = I3 - I4 (new R4) */ \
	xmm2[1] += xmm7[1];			/* I4 = I3 + I4 (new I3) */ \
\
	xptr2(src,d1   ) = xmm0;		/* Save R5 R3 */ \
	xptr2(src,d1+16) = xmm1;		/* Save R6 R4 */ \
	xptr2(src,d1+32) = xmm2;		/* Save I5 I3 */ \
	xptr2(src,d1+48) = xmm3;		/* Save I6 I4 */ \
\
	xmm0 = xptr2(src,d2);			/* R9 R5 */ \
	xmm1 = xptr2(src,d2+16); 		/* R10 R6 */ \
	xmm7 = xmm0;			/* Copy R9 R5 */ \
	xmm0 -= xmm1;			/* R9R5 = R9R5 - R10R6 (new R10R6) */ \
	xmm1 += xmm7;			/* R10R6 = R9R5 + R10R6 (new R9R5) */ \
\
	xmm2 = xptr2(src,d2+32);		/* I9 I5 */ \
	xmm3 = xptr2(src,d2+48); 		/* I10 I6 */ \
	xmm7 = xmm2;			/* Copy I9 I5 */ \
	xmm2 -= xmm3;			/* I9I5 = I9I5 - I10I6 (new I10I6) */ \
	xmm3 += xmm7;			/* I10I6 = I9I5 + I10I6 (new I9I5) */ \
\
	xp_complex_mult(xmm1, xmm3, xptr(altsrc+d2), xptr(altsrc+d2+32), xmm6, xmm7); /* Mult R9/I9 R5/I5 */ \
	xp_complex_mult(xmm0, xmm2, xptr(altsrc+d2+16), xptr(altsrc+d2+48), xmm6, xmm7); /* Mult R10/I10 R6/I6 */ \
\
	xmm1[0] -= xmm0[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm3[0] -= xmm2[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm3[0];			/* I10 = I9 + I10 (new I9) */ \
\
	xmm7[1] = xmm1[1];			/* Copy R5 */ \
	xmm1[1] -= xmm0[1];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[1] += xmm7[1];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[1] = xmm3[1];			/* Copy I5 */ \
	xmm3[1] -= xmm2[1];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[1] += xmm7[1];			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(src,d2   ) = xmm0;		/* Save R9 */ \
	xptr2(src,d2+16) = xmm1;		/* Save R10 */ \
	xptr2(src,d2+32) = xmm2;		/* Save I9 */ \
	xptr2(src,d2+48) = xmm3;		/* Save I10 */ \
\
	xmm0 = xptr2(src,d2+d1);		/* R11 R7 */ \
	xmm3 = xptr2(src,d2+d1+48); 		/* I12 I8 */ \
	xmm7 = xmm0;			/* Copy I11 R7 */ \
	xmm0 -= xmm3;			/* R11R7 = R11R7 - I12I8 (new R11R7) */ \
	xmm3 += xmm7;			/* R12I8 = R11R7 + I12I8 (new R12I8) */ \
\
	xmm2 = xptr2(src,d2+d1+32);		/* I11 I7 */ \
	xmm1 = xptr2(src,d2+d1+16); 		/* R12 R8 */ \
	xmm7 = xmm2;			/* Copy I11 I7 */ \
	xmm2 -= xmm1;			/* I11I7 = I11I7 - R12R8 (new I12R8) */ \
	xmm1 += xmm7;			/* R12R8 = I11I7 + R12R8 (new I11I7) */ \
\
	xp_complex_mult(xmm0, xmm1, xptr(altsrc+d2+d1), xptr(altsrc+d2+d1+32), xmm6, xmm7); /* Mult R11/I11 R7/I7 */ \
	xp_complex_mult(xmm3, xmm2, xptr(altsrc+d2+d1+16), xptr(altsrc+d2+d1+48), xmm6, xmm7); /* Mult R12/I12 R8/I8 */ \
\
	xmm3[0] -= xmm0[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm3[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm1[0] -= xmm2[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm2[0] += xmm2[0]; /* multwo */ \
	xmm2[0] += xmm1[0];			/* I12 = I11 + I12 (new I11) */ \
\
	xmm7[1] = xmm3[1];			/* Copy R8 */ \
	xmm3[1] -= xmm0[1];			/* R8 = R8 - R7 (new I8) */ \
	xmm0[1] += xmm7[1];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[1] = xmm1[1];			/* Copy I7 */ \
	xmm1[1] -= xmm2[1];			/* I7 = I7 - I8 (new R8) */ \
	xmm2[1] += xmm7[1];			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(src,d2+d1) = xmm0;		/* Save R11 R7 */ \
	xptr2(src,d2+d1+16) = xmm1;		/* Save R12 R8 */ \
	xptr2(src,d2+d1+32) = xmm2;		/* Save I11 I7 */ \
	xptr2(src,d2+d1+48) = xmm3;		/* Save I12 I8 */ \

#else
#define r8_h16r_simple_fft_with_mult(src,altsrc,d1,d2,origsrc) \
	r8_h16r_simple_fft_with_mult_16r(src,altsrc,d1,d2,origsrc) \
	r8_h16r_simple_fft_with_mult_8c(src,altsrc,d1,d2,origsrc)
#endif

#define r8_h16r_simple_fft_with_mult_16r(src,altsrc,d1,d2,origsrc) \
;	/* Do the 16-reals part */ \
\
	xmm1[0] = f64ptr2(src,0);			/* R1 */ \
	xmm0[0] = f64ptr2(src,16); 		/* R2 */ \
	xmm7[0] = xmm1[0];			/* Copy R2 */ \
	xmm1[0] -= xmm0[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm0[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm0[0] *= f64ptr(altsrc);		/* R1 * R1-from-mem */ \
	xmm1[0] *= f64ptr(altsrc+32);		/* R2 * R2-from-mem */ \
	f64ptr(origsrc-16) = xmm0[0];		/* Save product of sum of FFT values */ \
\
	xmm0[0] -= xmm1[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm0[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm1[0] += xmm0[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xmm2[0] = f64ptr2(src,32);			/* R3/R4 morphs into R3/I3 */ \
	xmm3[0] = f64ptr2(src,48); \
\
	xs_complex_mult(xmm2[0], xmm3[0], f64ptr(altsrc+16), f64ptr(altsrc+48), xmm6[0], xmm7[0]); /* Mult R3/I3 */ \
\
;						/* R3/I3 morphs into R3/R4 */ \
\
	f64ptr2(src,0) = xmm1[0];			/* Save R1 */ \
	f64ptr2(src,32) = xmm2[0];			/* Save R3 */ \
	f64ptr2(src,16) = xmm0[0];			/* Save R2 */ \
	f64ptr2(src,48) = xmm3[0];			/* Save R4 */ \
\
	xmm1[0] = f64ptr2(src,d1);			/* R5 */ \
	xmm0[0] = f64ptr2(src,d1+16); 		/* R6 */ \
	xmm7[0] = xmm1[0];			/* Copy R6 */ \
	xmm1[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d1+32);		/* I5 */ \
	xmm2[0] = f64ptr2(src,d1+48); 		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I6 */ \
	xmm3[0] -= xmm2[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm2[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xs_complex_mult(xmm0[0], xmm2[0], f64ptr(altsrc+d1), f64ptr(altsrc+d1+32), xmm6[0], xmm7[0]); /* Mult R5/I5 */ \
	xs_complex_mult(xmm1[0], xmm3[0], f64ptr(altsrc+d1+16), f64ptr(altsrc+d1+48), xmm6[0], xmm7[0]); /* Mult R6/I6 */ \
\
	xmm0[0] -= xmm1[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm2[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(src,d1) = xmm1[0];			/* Save R5 */ \
	f64ptr2(src,d1+32) = xmm3[0];		/* Save I5 */ \
	f64ptr2(src,d1+16) = xmm0[0];		/* Save R6 */ \
	f64ptr2(src,d1+48) = xmm2[0];		/* Save I6 */ \
\
	xmm1[0] = f64ptr2(src,d2);			/* R9 */ \
	xmm0[0] = f64ptr2(src,d2+16); 		/* R10 */ \
	xmm7[0] = xmm1[0];			/* Copy R10 */ \
	xmm1[0] -= xmm0[0];			/* R9 = R9 - R10 (new R10) */ \
	xmm0[0] += xmm7[0];			/* R10 = R9 + R10 (new R9) */ \
\
	xmm3[0] = f64ptr2(src,d2+32);		/* I9 */ \
	xmm2[0] = f64ptr2(src,d2+48); 		/* I10 */ \
	xmm7[0] = xmm3[0];			/* Copy I10 */ \
	xmm3[0] -= xmm2[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm2[0] += xmm7[0];			/* I10 = I9 + I10 (new I9) */ \
\
	xs_complex_mult(xmm0[0], xmm2[0], f64ptr(altsrc+d2), f64ptr(altsrc+d2+32), xmm6[0], xmm7[0]); /* Mult R9/I9 */ \
	xs_complex_mult(xmm1[0], xmm3[0], f64ptr(altsrc+d2+16), f64ptr(altsrc+d2+48), xmm6[0], xmm7[0]); /* Mult R10/I10 */ \
\
	xmm0[0] -= xmm1[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm2[0] -= xmm3[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I10 = I9 + I10 (new I9) */ \
\
	f64ptr2(src,d2) = xmm1[0];			/* Save R9 */ \
	f64ptr2(src,d2+32) = xmm3[0];		/* Save I9 */ \
	f64ptr2(src,d2+16) = xmm0[0];		/* Save R10 */ \
	f64ptr2(src,d2+48) = xmm2[0];		/* Save I10 */ \
\
	xmm1[0] = f64ptr2(src,d2+d1);		/* R11 */ \
	xmm0[0] = f64ptr2(src,d2+d1+48); 		/* I12 */ \
	xmm7[0] = xmm1[0];			/* Copy I12 */ \
	xmm1[0] -= xmm0[0];			/* R11 = R11 - I12 (new R11) */ \
	xmm0[0] += xmm7[0];			/* R12 = R11 + I12 (new R12) */ \
\
	xmm3[0] = f64ptr2(src,d2+d1+32);		/* I11 */ \
	xmm2[0] = f64ptr2(src,d2+d1+16); 		/* R12 */ \
	xmm7[0] = xmm3[0];			/* Copy R12 */ \
	xmm3[0] -= xmm2[0];			/* I11 = I11 - R12 (new I12) */ \
	xmm2[0] += xmm7[0];			/* I12 = I11 + R12 (new I11) */ \
\
	xs_complex_mult(xmm1[0], xmm2[0], f64ptr(altsrc+d2+d1), f64ptr(altsrc+d2+d1+32), xmm6[0], xmm7[0]); /* Mult R11/I11 */ \
	xs_complex_mult(xmm0[0], xmm3[0], f64ptr(altsrc+d2+d1+16), f64ptr(altsrc+d2+d1+48), xmm6[0], xmm7[0]); /* Mult R12/I12 */ \
\
	xmm0[0] -= xmm1[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm2[0] -= xmm3[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I12 = I11 + I12 (new I11) */ \
\
	f64ptr2(src,d2+d1) = xmm1[0];		/* Save R11 */ \
	f64ptr2(src,d2+d1+32) = xmm3[0];		/* Save I11 */ \
	f64ptr2(src,d2+d1+16) = xmm2[0];		/* Save R12 */ \
	f64ptr2(src,d2+d1+48) = xmm0[0];		/* Save I12 */ \

#define r8_h16r_simple_fft_with_mult_8c(src,altsrc,d1,d2,origsrc) \
;	/* Do the eight-complex part */ \
\
	xmm2[0] = f64ptr2(src,d2+8);		/* R5 */ \
	xmm0[0] = f64ptr2(src,d2+16+8); 		/* R6 */ \
	xmm7[0] = xmm2[0];			/* Copy R5 */ \
	xmm2[0] -= xmm0[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm0[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm3[0] = f64ptr2(src,d2+32+8);		/* I5 */ \
	xmm1[0] = f64ptr2(src,d2+48+8); 		/* I6 */ \
	xmm7[0] = xmm3[0];			/* Copy I5 */ \
	xmm3[0] -= xmm1[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm1[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xs_complex_mult(xmm2[0], xmm3[0], f64ptr(altsrc+d2+16+8), f64ptr(altsrc+d2+48+8), xmm6[0], xmm7[0]); /* Mult R6/I6 */ \
	xs_complex_mult(xmm0[0], xmm1[0], f64ptr(altsrc+d2+8), f64ptr(altsrc+d2+32+8), xmm6[0], xmm7[0]); /* Mult R5/I5 */ \
\
	xmm7[0] = xmm0[0];			/* Copy R5 */ \
	xmm0[0] -= xmm2[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm2[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I5 */ \
	xmm1[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(src,d2+16+8) = xmm0[0];		/* Save R6 */ \
	f64ptr2(src,d2+8) = xmm2[0];		/* Save R5 */ \
	f64ptr2(src,d2+48+8) = xmm1[0];		/* Save I6 */ \
	f64ptr2(src,d2+32+8) = xmm3[0];		/* Save I5 */ \
\
	xmm4[0] = f64ptr2(src,d2+d1+8);		/* R7 */ \
	xmm5[0] = f64ptr2(src,d2+d1+48+8);	/* I8 */ \
	xmm7[0] = xmm4[0];			/* Copy R7 */ \
	xmm4[0] -= xmm5[0];			/* R7 = R7 - I8 (new R7) */ \
	xmm5[0] += xmm7[0];			/* I8 = R7 + I8 (new R8) */ \
\
	xmm0[0] = f64ptr2(src,d2+d1+32+8);	/* I7 */ \
	xmm1[0] = f64ptr2(src,d2+d1+16+8);	/* R8 */ \
	xmm7[0] = xmm0[0];			/* Copy I7 */ \
	xmm0[0] -= xmm1[0];			/* I7 = I7 - R8 (new I8) */ \
	xmm1[0] += xmm7[0];			/* R8 = I7 + R8 (new I7) */ \
\
	xs_complex_mult(xmm5[0], xmm0[0], f64ptr(altsrc+d2+d1+16+8), f64ptr(altsrc+d2+d1+48+8), xmm6[0], xmm7[0]); /* Mult R8/I8 */ \
	xs_complex_mult(xmm4[0], xmm1[0], f64ptr(altsrc+d2+d1+8), f64ptr(altsrc+d2+d1+32+8), xmm6[0], xmm7[0]); /* Mult R7/I7 */ \
\
	xmm7[0] = xmm5[0];			/* Copy R8 */ \
	xmm5[0] -= xmm4[0];			/* R8 = R8 - R7 (new I8) */ \
	xmm4[0] += xmm7[0];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I7 */ \
	xmm1[0] -= xmm0[0];			/* I7 = I7 - I8 (new R8) */ \
	xmm0[0] += xmm7[0];			/* I8 = I7 + I8 (new I7) */ \
\
	f64ptr2(src,d2+d1+48+8) = xmm5[0];	/* Save I8 */ \
	f64ptr2(src,d2+d1+8) = xmm4[0];		/* Save R7 */ \
	f64ptr2(src,d2+d1+16+8) = xmm1[0];	/* Save R8 */ \
	f64ptr2(src,d2+d1+32+8) = xmm0[0];	/* Save I7 */ \
\
	xmm3[0] = f64ptr2(src,0+8);		/* R1 */ \
	xmm4[0] = f64ptr2(src,16+8);		/* R2 */ \
	xmm7[0] = xmm3[0];			/* Copy R1 */ \
	xmm3[0] -= xmm4[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm4[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm5[0] = f64ptr2(src,32+8);		/* I1 */ \
	xmm6[0] = f64ptr2(src,48+8);		/* I2 */ \
	xmm7[0] = xmm5[0];			/* Copy I1 */ \
	xmm5[0] -= xmm6[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm6[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	xs_complex_mult(xmm3[0], xmm5[0], f64ptr(altsrc+16+8), f64ptr(altsrc+48+8), xmm0[0], xmm7[0]); /* Mult R2/I2 */ \
	xs_complex_mult(xmm4[0], xmm6[0], f64ptr(altsrc+8), f64ptr(altsrc+32+8), xmm0[0], xmm7[0]); /* Mult R1/I1 */ \
\
	xmm7[0] = xmm4[0];			/* Copy R1 */ \
	xmm4[0] -= xmm3[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm3[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[0] = xmm6[0];			/* Copy I1 */ \
	xmm6[0] -= xmm5[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm5[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	f64ptr2(src,16+8) = xmm4[0];		/* Save R2 */ \
	f64ptr2(src,0+8) = xmm3[0];		/* Save R1 */ \
	f64ptr2(src,48+8) = xmm6[0];		/* Save I2 */ \
	f64ptr2(src,32+8) = xmm5[0];		/* Save I1 */ \
\
	xmm5[0] = f64ptr2(src,d1+8);		/* R3 */ \
	xmm6[0] = f64ptr2(src,d1+48+8);		/* I4 */ \
	xmm7[0] = xmm5[0];			/* Copy R3 */ \
	xmm5[0] -= xmm6[0];			/* R3 = R3 - I4 (new R3) */ \
	xmm6[0] += xmm7[0];			/* I4 = R3 + I4 (new R4) */ \
\
	xmm3[0] = f64ptr2(src,d1+32+8);		/* I3 */ \
	xmm4[0] = f64ptr2(src,d1+16+8);		/* R4 */ \
	xmm7[0] = xmm3[0];			/* Copy I3 */ \
	xmm3[0] -= xmm4[0];			/* I3 = I3 - R4 (final I4) */ \
	xmm4[0] += xmm7[0];			/* R4 = I3 + R4 (final I3) */ \
\
	xs_complex_mult(xmm6[0], xmm3[0], f64ptr(altsrc+d1+16+8), f64ptr(altsrc+d1+48+8), xmm0[0], xmm7[0]); /* Mult R4/I4 */ \
	xs_complex_mult(xmm5[0], xmm4[0], f64ptr(altsrc+d1+8), f64ptr(altsrc+d1+32+8), xmm0[0], xmm7[0]); /* Mult R3/I3 */ \
\
	xmm7[0] = xmm6[0];			/* Copy R4 */ \
	xmm6[0] -= xmm5[0];			/* R4 = R4 - R3 (new I4) */ \
	xmm5[0] += xmm7[0];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7[0] = xmm4[0];			/* Copy I3 */ \
	xmm4[0] -= xmm3[0];			/* I3 = I3 - I4 (new R4) */ \
	xmm3[0] += xmm7[0];			/* I4 = I3 + I4 (new I3) */ \
\
	f64ptr2(src,d1+48+8) = xmm6[0];		/* Save I4 */ \
	f64ptr2(src,d1+8) = xmm5[0];		/* Save R3 */ \
	f64ptr2(src,d1+16+8) = xmm4[0];		/* Save R4 */ \
	f64ptr2(src,d1+32+8) = xmm3[0];		/* Save I3 */ \
\
\
\

#if 0
#define r8_h8cl_sixteen_reals_eight_complex_with_mulf(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS[16]; \
	xmult7(srcreg+rbx, srcreg+rbp); \
	r8_x8c_simple_fft_with_mulf(srcreg+d4,d1,d2,XMM_COL_MULTS); \
	r8_x8c_simple_unfft(XMM_COL_MULTS,srcreg+d4,d1,d2); \
	r8_h16r_simple_fft_with_mulf_16r(srcreg,d1,d2,XMM_COL_MULTS); \
	r8_h16r_simple_unfft_16r(XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_h16r_simple_fft_with_mulf_8c(srcreg,d1,d2,XMM_COL_MULTS); \
	r8_h16r_simple_unfft_8c(XMM_COL_MULTS,srcreg+0,d1,d2); \
	srcreg += srcinc; \
}
#elif 1
#define r8_h8cl_sixteen_reals_eight_complex_with_mulf(srcreg,srcinc,d1,d2,d4) { \
	vec2f64 XMM_COL_MULTS[16]; \
	xmult7(srcreg+rbx, srcreg+rbp); \
	r8_h16r_simple_fft_with_mulf(srcreg,d1,d2,XMM_COL_MULTS); \
	r8_h16r_simple_unfft(XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_fft_with_mulf(srcreg+d4,d1,d2,XMM_COL_MULTS); \
	r8_x8c_simple_unfft(XMM_COL_MULTS,srcreg+d4,d1,d2); \
	srcreg += srcinc; \
}
#else
#define r8_h8cl_sixteen_reals_eight_complex_with_mulf(srcreg,srcinc,d1,d2,d4) \
	xmult7(srcreg+rbx, srcreg+rbp); \
	r8_h16r_simple_fft_with_mulf(srcreg,d1,d2,g->u.xmm.XMM_COL_MULTS); \
	r8_x8c_simple_fft_with_mulf(srcreg+d4,d1,d2,(g->u.xmm.XMM_COL_MULTS+256/8)); \
	r8_h16r_simple_unfft(g->u.xmm.XMM_COL_MULTS,srcreg+0,d1,d2); \
	r8_x8c_simple_unfft((g->u.xmm.XMM_COL_MULTS+256/8),srcreg+d4,d1,d2); \
	srcreg += srcinc; \

#endif

#if 1
#define r8_h16r_simple_fft_with_mulf(srcreg,d1,d2,dst) \
	xmm0 = xptr(srcreg+rbx);	/* R1 R1 */ \
	xmm1 = xptr(srcreg+16+rbx);	/*  ? R2 */ \
	xmm2 = xptr(srcreg+32+rbx);	/* R2 I1 */ \
	xmm3 = xptr(srcreg+48+rbx);	/*  ? I2 */ \
\
	xmm4 = xptr(srcreg+rbp); \
	xmm5 = xptr(srcreg+rbp+32); \
\
	xmm0[0] *= xmm4[0];		/* R1 * R1-from-mem */ \
	xmm2[0] *= xmm5[0];	/* R2 * R2-from-mem */ \
	f64ptr(srcreg-16) = xmm0[0];		/* Save product of sum of FFT values */ \
\
	xmm0[0] -= xmm2[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm0[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm2[0] += xmm0[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xs_complex_mult(xmm0[1], xmm2[1], xmm4[1], xmm5[1], xmm6[1], xmm7[1]); /* Mult R1/I1 */ \
	xp_complex_mult(xmm1, xmm3, xptr(srcreg+16+rbp), xptr(srcreg+48+rbp), xmm6, xmm7); /* Mult R3/I3 Mult R2/I2 */ \
\
						/* R3/I3 morphs into R3/R4 */ \
\
	xmm6[1] = xmm0[1];			/* Copy R1 */ \
	xmm0[1] -= xmm1[1];			/* R1 = R1 - R2 (new R2) */ \
	xmm6[1] += xmm1[1];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[1] = xmm2[1];			/* Copy I1 */ \
	xmm2[1] -= xmm3[1];			/* I1 = I1 - I2 (new I2) */ \
	xmm7[1] += xmm3[1];			/* I2 = I1 + I2 (new I1) */ \
\
	xmm6[0] = xmm2[0]; \
	xmm7[0] = xmm1[0]; \
	xmm2[0] = xmm3[0]; \
	xptr2(dst,0) = xmm6;			/* Save R1 R1 */ \
	xptr2(dst,16) = xmm0;			/* Save R2 R2 */ \
	xptr2(dst,32) = xmm7;			/* Save R3 I1 */ \
	xptr2(dst,48) = xmm2;			/* Save R4 I2 */ \
\
	xmm0 = xptr(srcreg+d1+rbx);	/* R5 R3 */ \
	xmm1 = xptr(srcreg+d1+16+rbx);	/* R6 R4 */ \
	xmm2 = xptr(srcreg+d1+32+rbx);	/* I5 I3 */ \
	xmm3 = xptr(srcreg+d1+48+rbx);	/* I6 I4 */ \
\
	xp_complex_mult(xmm0, xmm2, xptr(srcreg+d1+rbp), xptr(srcreg+d1+32+rbp), xmm6, xmm7); /* Mult R5/I5 Mult R3/I3 */ \
	xp_complex_mult(xmm1, xmm3, xptr(srcreg+d1+16+rbp), xptr(srcreg+d1+48+rbp), xmm6, xmm7); /* Mult R6/I6 Mult R4/I4 */ \
\
	xmm0[0] -= xmm1[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm2[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I6 = I5 + I6 (new I5) */ \
\
	xmm6[1] = xmm1[1];			/* Copy R4 */ \
	xmm1[1] -= xmm0[1];			/* R4 = R4 - R3 (new I4) */ \
	xmm6[1] += xmm0[1];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm0[1] = xmm2[1];			/* Copy I3 */ \
	xmm0[1] -= xmm3[1];			/* I3 = I3 - I4 (new R4) */ \
	xmm3[1] += xmm2[1];			/* I4 = I3 + I4 (new I3) */ \
\
	xmm6[0] = xmm1[0]; \
	xmm1[0] = xmm2[0]; \
	xptr2(dst,d1) = xmm6;		/* Save R5 R3 */ \
	xptr2(dst,d1+16) = xmm0;		/* Save R6 R4 */ \
	xptr2(dst,d1+32) = xmm3;		/* Save I5 I3 */ \
	xptr2(dst,d1+48) = xmm1;		/* Save I6 I4 */ \
\
	xmm0 = xptr(srcreg+d2+rbx);	/* R9 R5 */ \
	xmm1 = xptr(srcreg+d2+16+rbx);	/* R10 R6 */ \
	xmm2 = xptr(srcreg+d2+32+rbx);	/* I9 I5 */ \
	xmm3 = xptr(srcreg+d2+48+rbx);	/* I10 I6 */ \
\
	xs_complex_mult(xmm0, xmm2, xptr(srcreg+d2+rbp), xptr(srcreg+d2+32+rbp), xmm6, xmm7); /* Mult R9/I9 Mult R5/I5 */ \
	xs_complex_mult(xmm1, xmm3, xptr(srcreg+d2+16+rbp), xptr(srcreg+d2+48+rbp), xmm6, xmm7); /* Mult R10/I10 Mult R6/I6 */ \
\
	xmm0[0] -= xmm1[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm2[0] -= xmm3[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I10 = I9 + I10 (new I9) */ \
\
	xmm7[1] = xmm0[1];			/* Copy R5 */ \
	xmm0[1] -= xmm1[1];			/* R5 = R5 - R6 (new R6) */ \
	xmm1[1] += xmm7[1];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[1] = xmm2[1];			/* Copy I5 */ \
	xmm2[1] -= xmm3[1];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[1] += xmm7[1];			/* I6 = I5 + I6 (new I5) */ \
\
	xptr2(dst,d2   ) = xmm1;		/* Save R9 R5 */ \
	xptr2(dst,d2+16) = xmm0;		/* Save R10 R6 */ \
	xptr2(dst,d2+32) = xmm3;		/* Save I9 I5 */ \
	xptr2(dst,d2+48) = xmm2;		/* Save I10 I6 */ \
\
	xmm0 = xptr(srcreg+d2+d1+rbx);	/* R11 R7 */ \
	xmm1 = xptr(srcreg+d2+d1+16+rbx); 	/* R12 R8 */ \
	xmm2 = xptr(srcreg+d2+d1+32+rbx);	/* I11 I7 */ \
	xmm3 = xptr(srcreg+d2+d1+48+rbx); 	/* I12 I8 */ \
\
	xp_complex_mult(xmm0, xmm2, xptr(srcreg+d2+d1+rbp), xptr(srcreg+d2+d1+32+rbp), xmm6, xmm7); /* Mult R11/I11 Mult R7/I7 */ \
	xp_complex_mult(xmm1, xmm3, xptr(srcreg+d2+d1+16+rbp), xptr(srcreg+d2+d1+48+rbp), xmm6, xmm7); /* Mult R12/I12 Mult R8/I8 */ \
\
	xmm1[0] -= xmm0[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm0[0] += xmm0[0]; /* multwo */ \
	xmm0[0] += xmm1[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm2[0] -= xmm3[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I12 = I11 + I12 (new I11) */ \
\
	xmm7[1] = xmm1[1];			/* Copy R8 */ \
	xmm1[1] -= xmm0[1];			/* R8 = R8 - R7 (new I8) */ \
	xmm0[1] += xmm7[1];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[1] = xmm2[1];			/* Copy I7 */ \
	xmm2[1] -= xmm3[1];			/* I7 = I7 - I8 (new R8) */ \
	xmm3[1] += xmm7[1];			/* I8 = I7 + I8 (new I7) */ \
\
	xptr2(dst,d2+d1   ) = xmm0;		/* Save R11 R7 */ \
	xptr2(dst,d2+d1+16) = xmm2;		/* Save R12 R8 */ \
	xptr2(dst,d2+d1+32) = xmm3;		/* Save I11 I7 */ \
	xptr2(dst,d2+d1+48) = xmm1;		/* Save I12 I8 */ \

#else
#define r8_h16r_simple_fft_with_mulf(srcreg,d1,d2,dst) \
	r8_h16r_simple_fft_with_mulf_16r(srcreg,d1,d2,dst) \
	r8_h16r_simple_fft_with_mulf_8c(srcreg,d1,d2,dst)
#endif
#define r8_h16r_simple_fft_with_mulf_16r(srcreg,d1,d2,dst) \
;	/* Do the 16-reals part */ \
\
	xmm0[0] = f64ptr(srcreg+rbx);		/* R1 */ \
	xmm1[0] = f64ptr(srcreg+32+rbx);	/* R2 */ \
\
	xmm0[0] *= f64ptr(srcreg+rbp);		/* R1 * R1-from-mem */ \
	xmm1[0] *= f64ptr(srcreg+32+rbp);	/* R2 * R2-from-mem */ \
	f64ptr(srcreg-16) = xmm0[0];		/* Save product of sum of FFT values */ \
\
	xmm0[0] -= xmm1[0];			/* R1 = R1 - R2 (final R2) */ \
	xmm0[0] *= 0.5;				/* Mul R2 by HALF */ \
	xmm1[0] += xmm0[0];			/* R2 = R1 + R2 (final R1) */ \
\
	xmm2[0] = f64ptr(srcreg+16+rbx);	/* R3/R4 morphs into R3/I3 */ \
	xmm3[0] = f64ptr(srcreg+48+rbx); \
\
	xs_complex_mult(xmm2[0], xmm3[0], f64ptr(srcreg+16+rbp), f64ptr(srcreg+48+rbp), xmm6[0], xmm7[0]); /* Mult R3/I3 */ \
\
;						/* R3/I3 morphs into R3/R4 */ \
\
	f64ptr2(dst,0) = xmm1[0];			/* Save R1 */ \
	f64ptr2(dst,32) = xmm2[0];			/* Save R3 */ \
	f64ptr2(dst,16) = xmm0[0];			/* Save R2 */ \
	f64ptr2(dst,48) = xmm3[0];			/* Save R4 */ \
\
	xmm0[0] = f64ptr(srcreg+d1+rbx);	/* R5 */ \
	xmm2[0] = f64ptr(srcreg+d1+32+rbx);	/* I5 */ \
	xmm1[0] = f64ptr(srcreg+d1+16+rbx);	/* R6 */ \
	xmm3[0] = f64ptr(srcreg+d1+48+rbx);	/* I6 */ \
\
	xs_complex_mult(xmm0[0], xmm2[0], f64ptr(srcreg+d1+rbp), f64ptr(srcreg+d1+32+rbp), xmm6[0], xmm7[0]); /* Mult R5/I5 */ \
	xs_complex_mult(xmm1[0], xmm3[0], f64ptr(srcreg+d1+16+rbp), f64ptr(srcreg+d1+48+rbp), xmm6[0], xmm7[0]); /* Mult R6/I6 */ \
\
	xmm0[0] -= xmm1[0];			/* R6 = R5 - R6 (new R6) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R5 = R5 + R6 (new R5) */ \
\
	xmm2[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(dst,d1) = xmm1[0];			/* Save R5 */ \
	f64ptr2(dst,d1+32) = xmm3[0];		/* Save I5 */ \
	f64ptr2(dst,d1+16) = xmm0[0];		/* Save R6 */ \
	f64ptr2(dst,d1+48) = xmm2[0];		/* Save I6 */ \
\
	xmm0[0] = f64ptr(srcreg+d2+rbx);	/* R9 */ \
	xmm2[0] = f64ptr(srcreg+d2+32+rbx);	/* I9 */ \
	xmm1[0] = f64ptr(srcreg+d2+16+rbx);	/* R10 */ \
	xmm3[0] = f64ptr(srcreg+d2+48+rbx);	/* I10 */ \
\
	xs_complex_mult(xmm0[0], xmm2[0], f64ptr(srcreg+d2+rbp), f64ptr(srcreg+d2+32+rbp), xmm6[0], xmm7[0]); /* Mult R9/I9 */ \
	xs_complex_mult(xmm1[0], xmm3[0], f64ptr(srcreg+d2+16+rbp), f64ptr(srcreg+d2+48+rbp), xmm6[0], xmm7[0]); /* Mult R10/I10 */ \
\
	xmm0[0] -= xmm1[0];			/* R10 = R9 - R10 (new R10) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R9 = R9 + R10 (new R9) */ \
\
	xmm2[0] -= xmm3[0];			/* I9 = I9 - I10 (new I10) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I10 = I9 + I10 (new I9) */ \
\
	f64ptr2(dst,d2) = xmm1[0];			/* Save R9 */ \
	f64ptr2(dst,d2+32) = xmm3[0];		/* Save I9 */ \
	f64ptr2(dst,d2+16) = xmm0[0];		/* Save R10 */ \
	f64ptr2(dst,d2+48) = xmm2[0];		/* Save I10 */ \
\
	xmm1[0] = f64ptr(srcreg+d2+d1+rbx);	/* R11 */ \
	xmm2[0] = f64ptr(srcreg+d2+d1+32+rbx);	/* I11 */ \
	xmm0[0] = f64ptr(srcreg+d2+d1+16+rbx); 	/* R12 */ \
	xmm3[0] = f64ptr(srcreg+d2+d1+48+rbx); 	/* I12 */ \
\
	xs_complex_mult(xmm1[0], xmm2[0], f64ptr(srcreg+d2+d1+rbp), f64ptr(srcreg+d2+d1+32+rbp), xmm6[0], xmm7[0]); /* Mult R11/I11 */ \
	xs_complex_mult(xmm0[0], xmm3[0], f64ptr(srcreg+d2+d1+16+rbp), f64ptr(srcreg+d2+d1+48+rbp), xmm6[0], xmm7[0]); /* Mult R12/I12 */ \
\
	xmm0[0] -= xmm1[0];			/* R12 = R12 - R11 (new I12) */ \
	xmm1[0] += xmm1[0]; /* multwo */ \
	xmm1[0] += xmm0[0];			/* R11 = R12 + R11 (new R11) */ \
\
	xmm2[0] -= xmm3[0];			/* I11 = I11 - I12 (new R12) */ \
	xmm3[0] += xmm3[0]; /* multwo */ \
	xmm3[0] += xmm2[0];			/* I12 = I11 + I12 (new I11) */ \
\
	f64ptr2(dst,d2+d1) = xmm1[0];		/* Save R11 */ \
	f64ptr2(dst,d2+d1+32) = xmm3[0];		/* Save I11 */ \
	f64ptr2(dst,d2+d1+16) = xmm2[0];		/* Save R12 */ \
	f64ptr2(dst,d2+d1+48) = xmm0[0];		/* Save I12 */ \

#define r8_h16r_simple_fft_with_mulf_8c(srcreg,d1,d2,dst) \
	/* Do the eight-complex part */ \
\
	xmm2[0] = f64ptr(srcreg+d2+16+rbx+8);	/* R6 */ \
	xmm3[0] = f64ptr(srcreg+d2+48+rbx+8);	/* I6 */ \
	xmm0[0] = f64ptr(srcreg+d2+rbx+8);	/* R5 */ \
	xmm1[0] = f64ptr(srcreg+d2+32+rbx+8);	/* I5 */ \
\
	xs_complex_mult(xmm2[0], xmm3[0], f64ptr(srcreg+d2+16+rbp+8), f64ptr(srcreg+d2+48+rbp+8), xmm6[0], xmm7[0]); /* Mult R6/I6 */ \
	xs_complex_mult(xmm0[0], xmm1[0], f64ptr(srcreg+d2+rbp+8), f64ptr(srcreg+d2+32+rbp+8), xmm6[0], xmm7[0]); /* Mult R5/I5 */ \
\
	xmm7[0] = xmm0[0];			/* Copy R5 */ \
	xmm0[0] -= xmm2[0];			/* R5 = R5 - R6 (new R6) */ \
	xmm2[0] += xmm7[0];			/* R6 = R5 + R6 (new R5) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I5 */ \
	xmm1[0] -= xmm3[0];			/* I5 = I5 - I6 (new I6) */ \
	xmm3[0] += xmm7[0];			/* I6 = I5 + I6 (new I5) */ \
\
	f64ptr2(dst,d2+16+8) = xmm0[0];		/* Save R6 */ \
	f64ptr2(dst,d2+8) = xmm2[0];		/* Save R5 */ \
	f64ptr2(dst,d2+48+8) = xmm1[0];		/* Save I6 */ \
	f64ptr2(dst,d2+32+8) = xmm3[0];		/* Save I5 */ \
\
	xmm5[0] = f64ptr(srcreg+d2+d1+16+rbx+8); /* R8 */ \
	xmm0[0] = f64ptr(srcreg+d2+d1+48+rbx+8); /* I8 */ \
	xmm4[0] = f64ptr(srcreg+d2+d1+rbx+8);	/* R7 */ \
	xmm1[0] = f64ptr(srcreg+d2+d1+32+rbx+8); /* I7 */ \
\
	xs_complex_mult(xmm5[0], xmm0[0], f64ptr(srcreg+d2+d1+16+rbp+8), f64ptr(srcreg+d2+d1+48+rbp+8), xmm6[0], xmm7[0]); /* Mult R8/I8 */ \
	xs_complex_mult(xmm4[0], xmm1[0], f64ptr(srcreg+d2+d1+rbp+8), f64ptr(srcreg+d2+d1+32+rbp+8), xmm6[0], xmm7[0]); /* Mult R7/I7 */ \
\
	xmm7[0] = xmm5[0];			/* Copy R8 */ \
	xmm5[0] -= xmm4[0];			/* R8 = R8 - R7 (new I8) */ \
	xmm4[0] += xmm7[0];			/* R7 = R8 + R7 (new R7) */ \
\
	xmm7[0] = xmm1[0];			/* Copy I7 */ \
	xmm1[0] -= xmm0[0];			/* I7 = I7 - I8 (new R8) */ \
	xmm0[0] += xmm7[0];			/* I8 = I7 + I8 (new I7) */ \
\
	f64ptr2(dst,d2+d1+48+8) = xmm5[0];	/* Save I8 */ \
	f64ptr2(dst,d2+d1+8) = xmm4[0];		/* Save R7 */ \
	f64ptr2(dst,d2+d1+16+8) = xmm1[0];	/* Save R8 */ \
	f64ptr2(dst,d2+d1+32+8) = xmm0[0];	/* Save I7 */ \
\
	xmm3[0] = f64ptr(srcreg+16+rbx+8);	/* R2 */ \
	xmm5[0] = f64ptr(srcreg+48+rbx+8);	/* I2 */ \
	xmm4[0] = f64ptr(srcreg+rbx+8);	/* R1 */ \
	xmm6[0] = f64ptr(srcreg+32+rbx+8);	/* I1 */ \
\
	xs_complex_mult(xmm3[0], xmm5[0], f64ptr(srcreg+16+rbp+8), f64ptr(srcreg+48+rbp+8), xmm0[0], xmm7[0]); /* Mult R2/I2 */ \
	xs_complex_mult(xmm4[0], xmm6[0], f64ptr(srcreg+rbp+8), f64ptr(srcreg+32+rbp+8), xmm0[0], xmm7[0]); /* Mult R1/I1 */ \
\
	xmm7[0] = xmm4[0];			/* Copy R1 */ \
	xmm4[0] -= xmm3[0];			/* R1 = R1 - R2 (new R2) */ \
	xmm3[0] += xmm7[0];			/* R2 = R1 + R2 (new R1) */ \
\
	xmm7[0] = xmm6[0];			/* Copy I1 */ \
	xmm6[0] -= xmm5[0];			/* I1 = I1 - I2 (new I2) */ \
	xmm5[0] += xmm7[0];			/* I2 = I1 + I2 (new I1) */ \
\
	f64ptr2(dst,16+8) = xmm4[0];		/* Save R2 */ \
	f64ptr2(dst,0+8) = xmm3[0];		/* Save R1 */ \
	f64ptr2(dst,48+8) = xmm6[0];		/* Save I2 */ \
	f64ptr2(dst,32+8) = xmm5[0];		/* Save I1 */ \
\
	xmm6[0] = f64ptr(srcreg+d1+16+rbx+8);	/* R4 */ \
	xmm3[0] = f64ptr(srcreg+d1+48+rbx+8);	/* I4 */ \
	xmm5[0] = f64ptr(srcreg+d1+rbx+8);	/* R3 */ \
	xmm4[0] = f64ptr(srcreg+d1+32+rbx+8);	/* I3 */ \
\
	xs_complex_mult(xmm6[0], xmm3[0], f64ptr(srcreg+d1+16+rbp+8), f64ptr(srcreg+d1+48+rbp+8), xmm0[0], xmm7[0]); /* Mult R4/I4 */ \
	xs_complex_mult(xmm5[0], xmm4[0], f64ptr(srcreg+d1+rbp+8), f64ptr(srcreg+d1+32+rbp+8), xmm0[0], xmm7[0]); /* Mult R3/I3 */ \
\
	xmm7[0] = xmm6[0];			/* Copy R4 */ \
	xmm6[0] -= xmm5[0];			/* R4 = R4 - R3 (new I4) */ \
	xmm5[0] += xmm7[0];			/* R3 = R4 + R3 (new R3) */ \
\
	xmm7[0] = xmm4[0];			/* Copy I3 */ \
	xmm4[0] -= xmm3[0];			/* I3 = I3 - I4 (new R4) */ \
	xmm3[0] += xmm7[0];			/* I4 = I3 + I4 (new I3) */ \
\
	f64ptr2(dst,d1+48+8) = xmm6[0];		/* Save I4 */ \
	f64ptr2(dst,d1+8) = xmm5[0];		/* Save R3 */ \
	f64ptr2(dst,d1+16+8) = xmm4[0];		/* Save R4 */ \
	f64ptr2(dst,d1+32+8) = xmm3[0];		/* Save I3 */ \
\
