#pragma once
	//
#if 0

#define xfive_reals_fft_preload \
	xmm8 = xptr(g->u.xmm.XMM_P618);		/* (.588/.951) */ \
	xmm9 = xptr(g->u.xmm.XMM_P309);		/* .309 */ \
	xmm10 = xptr(g->u.xmm.XMM_P951);		/* .951 */ \
	xmm11 = xptr(g->u.xmm.XMM_P588);		/* .588 */ \
	xmm12 = xptr(g->u.xmm.XMM_M809);		/* -.809 */ \
	xmm13 = xptr(g->u.xmm.XMM_M262);		/* (-.809/.309) */ \
	xmm14 = xptr(g->u.xmm.XMM_M162);		/* (-.951/.588) */ \
	xmm15 = xptr(g->u.xmm.XMM_M382);		/* (.309/-.809) */ \

#define x5r_fft(r1, r2, r3, r4, r5, t1, t2, t3) \
	t1 = r5;			/* 0-5 Copy R5 */ \
	r5 += r2;			/* 1-4 T1 = R2 + R5 */ \
	t2 = r4;			/* 2-7 Copy R4 */ \
	r4 += r3;			/* 3-5 T2 = R3 + R4 */ \
	t3 = r1;			/* 4-9 newR2 = R1 */ \
	r2 -= t1;			/* 6-9 T3 = R2 - R5 */ \
	t1 = r1;			/* 7-12 newR3 = R1 */ \
	r3 -= t2;			/* 8-11 T4 = R3 - R4 */ \
	t2 = xmm8;		/* 9-14 const1 (.588/.951) */ \
	r1 += r5;			/* 10-13 newR1 = R1 + T1 */ \
	r5 *= xmm9;		/* 11-16 T1 = T1 * .309 */ \
	r2 *= xmm10;		/* 13-18 T3 = T3 * .951 (new I2) */ \
	r1 += r4;			/* 14-17 newR1 = newR1 + T2 */ \
	r3 *= xmm11;		/* 15-20 T4 = T4 * .588 */ \
	t3 += r5;			/* 17-20 newR2 = newR2 + T1 */ \
	r4 *= xmm12;		/* 18-23 T2 = T2 * -.809 */ \
	r5 *= xmm13;		/* 20-25 T1 = T1 * (-.809/.309) */ \
	t2 *= r2;			/* 22-27 T3 = T3 * (.588/.951) */ \
	r2 += r3;			/* 23-26 newI2 = newI2 + T4 */ \
	r3 *= xmm14;		/* 24-29 T4 = T4 * (-.951/.588) */ \
	t3 += r4;			/* 25-28 newR2 = newR2 + T2 */ \
	r4 *= xmm15;		/* 26-31 T2 = T2 * (.309/-.809) */ \
	t1 += r5;			/* 27-30 newR3 = newR3 + T1 */ \
	t2 += r3;			/* 30-33 T3 = T3 + T4 (final I3) */ \
	t1 += r4;			/* 32-35 newR3 = newR3 + T2 */ \

#define xfive_reals_unfft_preload \
	xmm8 = xptr(g->u.xmm.XMM_P309);		/* Load .309 */ \
	xmm9 = xptr(g->u.xmm.XMM_M809);		/* Load -.809 */ \
	xmm10 = xptr(g->u.xmm.XMM_P951);		/* Load 0.951 */ \
	xmm11 = xptr(g->u.xmm.XMM_P588);		/* Load 0.588 */ \

#define x5r_unfft(r1, r2, r3, r4, r5, t1, t2, t3, mem1) \
	t1 = xmm8;		/* Load .309 */ \
	t1 *= r2;			/* 1-6 R2*.309 */ \
	t2 = xmm9;		/* Load -.809 */ \
	t2 *= r2;			/* 3-8 R2*-.809 */ \
	r2 += r4;			/* 4-7 R2+R3 */ \
	t3 = xmm9;		/* Load -.809 */ \
	t3 *= r4;			/* 5-10 R3*-.809 */ \
	r2 += r1;			/* 6-9 R1+R2+R3 (final R1) */ \
	r4 *= xmm8;		/* 7-12 R3*.309 */ \
	t1 += r1;			/* 8-11 R1 + R2*.309 */ \
	mem1 = r2;		/* Save final R1 */ \
	r2 = xmm10;		/* Load 0.951 */ \
	r2 *= r3;	 		/* 9-14 I2*.951 */ \
	t2 += r1;			/* 10-13 R1 + R2*-.809 */ \
	r1 = xmm11;		/* Load 0.588 */ \
	r1 *= r5;			/* 11-16 I3*.588 */ \
	t1 += t3;			/* 12-15 R1 + R2*.309 - R3*.809 */ \
	r3 *= xmm11;		/* 13-18 I2*.588 */ \
	t2 += r4;			/* 14-17 R1 - R2*.809 + R3*.309 */ \
	r5 *= xmm10;		/* 15-20 I3*-.951 */ \
	t3 = t1;			/* 16-21 R1 + R2*.309 - R3*.809 */ \
	r2 += r1;			/* 17-20 I2*.951 + I3*.588 */ \
	r4 = t2;			/* 18-23 R1 - R2*.809 + R3*.309 */ \
	r3 -= r5;			/* 21-24 I2*.588 - I3*.951 */ \
	t1 += r2;			/* 23-26 final R2 */ \
	t3 -= r2;			/* 25-28 final R5 */ \
	t2 += r3;			/* 27-30 final R3 */ \
	r4 -= r3;			/* 29-31 final R4 */ \


#define x4c_fft(r1, r2, r3, r4, r5, r6, r7, r8, mem8, screg, off, pre1, pre2, dst1, dst2) \
	r8 = xptr(screg+off+32+16);	/* cosine/sine */ \
	r8 *= r3;			/* A3 = R3 * cosine/sine	;1-6 */ \
	r8 -= r7;			/* A3 = A3 - I3			;8-11 */ \
	r7 *= xptr(screg+off+32+16);	/* B3 = I3 * cosine/sine	;3-8 */ \
	r7 += r3;			/* B3 = B3 + R3			;10-13 */ \
	r3 = xptr(screg+off+0+16);	/* cosine/sine */ \
	r3 *= r2;			/* A2 = R2 * cosine/sine	;5-10 */ \
	r3 -= r6;			/* A2 = A2 - I2			;12-15 */ \
	r6 *= xptr(screg+off+0+16);	/* B2 = I2 * cosine/sine	;9-14 */ \
	r6 += r2;			/* B2 = B2 + R2			;16-19 */ \
	r2 = xptr(screg+off+64+16);	/* cosine/sine */ \
	r2 *= mem8;		/* B4 = I4 * cosine/sine	;11-16 */ \
	r2 += r4;			/* B4 = B4 + R4			;18-21 */ \
	r4 *= xptr(screg+off+64+16);	/* A4 = R4 * cosine/sine	;7-12 */ \
	r4 -= mem8;		/* A4 = A4 - I4			;14-17 */ \
	r8 *= xptr(screg+off+32);	/* A3 = A3 * sine (new R3)	;13-18 */ \
	 xmm8 = r1; \
	r7 *= xptr(screg+off+32);	/* B3 = B3 * sine (new I3)	;15-20 */ \
	 xmm9 = r5; \
	r3 *= xptr(screg+off+0);	/* A2 = A2 * sine (new R2)	;17-22 */ \
	r4 *= xptr(screg+off+64);	/* A4 = A4 * sine (new R4)	;19-24 */ \
	xprefetchw u64ptr(pre1); \
	 r1 -= r8;			/* R1 = R1 - R3 (new R3)	;20-23 */ \
	r6 *= xptr(screg+off+0);	/* B2 = B2 * sine (new I2)	;21-26 */ \
	 r5 -= r7;			/* I1 = I1 - I3 (new I3)	;22-25 */ \
	r2 *= xptr(screg+off+64);	/* B4 = B4 * sine (new I4)	;23-28 */ \
	xprefetchw u64ptr(pre1+pre2); \
	 r8 += xmm8;		/* R3 = R1 + R3 (new R1)	;24-27 */ \
	 xmm8 = r3; \
	 r3 -= r4;			/* R2 = R2 - R4 (new R4)	;26-29 */ \
	 r7 += xmm9;		/* I3 = I1 + I3 (new I1)	;28-31 */ \
	 xmm9 = r6; \
	 r6 -= r2;			/* I2 = I2 - I4 (new I4)	;30-33 */ \
	xmm10 = r5; \
	r5 -= r3;			/* I3 = I3 - R4 (final I4)	;32-35 */ \
	xmm11 = r1; \
	 r4 += xmm8;		/* R4 = R2 + R4 (new R2)	;34-37 */ \
	 r2 += xmm9;		/* I4 = I2 + I4 (new I2)	;36-39 */ \
	IFNB <dst1>; \
	dst1 = r5; \
	ENDIF; \
	r1 -= r6;			/* R3 = R3 - I4 (final R3)	;38-41 */ \
	xmm8 = r8; \
	r8 -= r4;			/* R1 = R1 - R2 (final R2)	;40-43 */ \
	xmm9 = r7; \
	r7 -= r2;			/* I1 = I1 - I2 (final I2)	;42-45 */ \
	IFNB <dst2>; \
	dst2 = r1; \
	ENDIF; \
	r3 += xmm10;		/* R4 = I3 + R4 (final I3)	;44-47 */ \
	r6 += xmm11;		/* I4 = R3 + I4 (final R4)	;46-49 */ \
	r4 += xmm8;		/* R2 = R1 + R2 (final R1)	;48-51 */ \
	r2 += xmm9;		/* I2 = I1 + I2 (final I1)	;50-53 */ \


#define x4c_fft_mem(R1,R2,R3,R4,R5,R6,R7,R8,screg,off,pre1,pre2,dst1,dst2) \
	xmm0 = R3;		/* R3 */ \
	xmm1 = xptr(screg+off+32+16);	/* cosine/sine */ \
	xmm1 *= xmm0;		/* A3 = R3 * cosine/sine	;1-6 */ \
	xmm2 = R7;		/* I3 */ \
	xmm3 = xptr(screg+off+32+16);	/* cosine/sine */ \
	xmm3 *= xmm2;		/* B3 = I3 * cosine/sine	;3-8 */ \
	xmm4 = R2;		/* R2 */ \
	xmm6 = xptr(screg+off+0+16);	/* cosine/sine */ \
	xmm4 *= xmm6;		/* A2 = R2 * cosine/sine	;5-10 */ \
	xmm5 = R4;		/* R4 */ \
	xmm7 = xptr(screg+off+64+16);	/* cosine/sine */ \
	xmm5 *= xmm7;		/* A4 = R4 * cosine/sine	;7-12 */ \
	xmm1 -= xmm2;		/* A3 = A3 - I3			;8-11 */ \
	xmm2 = R6;		/* I2 */ \
	xmm6 *= xmm2;		/* B2 = I2 * cosine/sine	;9-14 */ \
	xmm3 += xmm0;		/* B3 = B3 + R3			;10-13 */ \
	xmm0 = R8;		/* I4 */ \
	xmm7 *= xmm0;		/* B4 = I4 * cosine/sine	;11-16 */ \
	xmm4 -= xmm2;		/* A2 = A2 - I2			;12-15 */ \
	xmm2 = xptr(screg+off+32);	/* sine */ \
	xmm1 *= xmm2;		/* A3 = A3 * sine (new R3)	;13-18 */ \
	xmm5 -= xmm0;		/* A4 = A4 - I4			;14-17 */ \
	xmm3 *= xmm2;		/* B3 = B3 * sine (new I3)	;15-20 */ \
	xmm6 += R2;		/* B2 = B2 + R2			;16-19 */ \
	xmm0 = xptr(screg+off+0);	/* sine */ \
	xmm4 *= xmm0;		/* A2 = A2 * sine (new R2)	;17-22 */ \
	xprefetchw u64ptr(pre1); \
	xmm7 += R4;		/* B4 = B4 + R4			;18-21 */ \
	xmm5 *= xptr(screg+off+64);	/* A4 = A4 * sine (new R4)	;19-24 */ \
	 xmm2 = R1;		/* R1 */ \
	 xmm2 -= xmm1;		/* R1 = R1 - R3 (new R3)	;20-23 */ \
	xmm6 *= xmm0;		/* B2 = B2 * sine (new I2)	;21-26 */ \
	 xmm0 = R5;		/* I1 */ \
	 xmm0 -= xmm3;		/* I1 = I1 - I3 (new I3)	;22-25 */ \
	xmm7 *= xptr(screg+off+64);	/* B4 = B4 * sine (new I4)	;23-28 */ \
	 xmm1 += R1;		/* R3 = R1 + R3 (new R1)	;24-27 */ \
	xprefetchw u64ptr(pre1+pre2); \
	 xmm8 = xmm4; \
	 xmm4 -= xmm5;		/* R2 = R2 - R4 (new R4)	;26-29 */ \
	 xmm9 = xmm6; \
	 xmm3 += R5;		/* I3 = I1 + I3 (new I1)	;28-31 */ \
	 xmm6 -= xmm7;		/* I2 = I2 - I4 (new I4)	;30-33 */ \
	xmm10 = xmm0; \
	xmm0 -= xmm4;		/* I3 = I3 - R4 (final I4)	;32-35 */ \
	 xmm5 += xmm8;		/* R4 = R2 + R4 (new R2)	;34-37 */ \
	 xmm7 += xmm9;		/* I4 = I2 + I4 (new I2)	;36-39 */ \
	IFNB <dst1>; \
	dst1 = xmm0; \
	ENDIF; \
	xmm8 = xmm2; \
	xmm2 -= xmm6;		/* R3 = R3 - I4 (final R3)	;38-41 */ \
	xmm9 = xmm1; \
	xmm1 -= xmm5;		/* R1 = R1 - R2 (final R2)	;40-43 */ \
	xmm11 = xmm3; \
	xmm3 -= xmm7;		/* I1 = I1 - I2 (final I2)	;42-45 */ \
	IFNB <dst2>; \
	dst2 = xmm2; \
	ENDIF; \
	xmm4 += xmm10;		/* R4 = I3 + R4 (final I3)	;44-47 */ \
	xmm6 += xmm8;		/* I4 = R3 + I4 (final R4)	;46-49 */ \
	xmm5 += xmm9;		/* R2 = R1 + R2 (final R1)	;48-51 */ \
	xmm7 += xmm11;		/* I2 = I1 + I2 (final I1)	;50-53 */ \


#define x8r_fft \
	xmm8 = xmm3; \
	xmm3 -= xmm7;		/* new R8 = R4 - R8 */ \
	xmm7 += xmm8;		/* new R4 = R4 + R8 */ \
	xmm9 = xmm1; \
	xmm1 -= xmm5;		/* new R6 = R2 - R6 */ \
	xmm5 += xmm9;		/* new R2 = R2 + R6 */ \
	 xmm3 *= xptr(g->u.xmm.XMM_SQRTHALF);	/* R8 = R8 * square root */ \
	 xmm1 *= xptr(g->u.xmm.XMM_SQRTHALF);	/* R6 = R6 * square root */ \
	xmm8 = xmm0; \
	xmm0 -= xmm4;		/* new R5 = R1 - R5 */ \
	xmm4 += xmm8;		/* new R1 = R1 + R5 */ \
	 xmm9 = xmm5; \
	 xmm5 -= xmm7;		/* R2 = R2 - R4 (new & final R4) */ \
	xmm10 = xmm2; \
	xmm2 -= xmm6;		/* new R7 = R3 - R7 */ \
	xmm6 += xmm10;		/* new R3 = R3 + R7 */ \
	 xmm8 = xmm1; \
	 xmm1 -= xmm3;		/* R6 = R6 - R8 (Real part) */ \
	 xmm10 = xmm4; \
	 xmm4 -= xmm6;		/* R1 = R1 - R3 (new & final R3) */ \
	 xmm7 += xmm9;		/* R4 = R2 + R4 (new R2) */ \
	xmm3 += xmm8;		/* R8 = R6 + R8 (Imaginary part) */ \
	xmm8 = xmm0; \
	xmm0 -= xmm1;		/* R5 = R5 - R6 (final R7) */ \
	 xmm6 += xmm10;		/* R3 = R1 + R3 (new R1) */ \
	xmm9 = xmm2; \
	xmm2 -= xmm3;		/* R7 = R7 - R8 (final R8) */ \
	xmm10 = xmm6; \
	xmm6 -= xmm7;		/* R1 = R1 - R2 (final R2) */ \
	xmm1 += xmm8;		/* R6 = R5 + R6 (final R5) */ \
	xmm3 += xmm9;		/* R8 = R7 + R8 (final R6) */ \
	xmm7 += xmm10;		/* R2 = R1 + R2 (final R1) */ \



#define xs8r_fft(r0, r1, r2, r3, r4, r5, r6, r7) \
	r5 *= g->u.xmm.XMM_SQRTHALF[0];	/* R6 = R6 * square root of 1/2 */ \
	r7 *= g->u.xmm.XMM_SQRTHALF[0];	/* R8 = R8 * square root of 1/2 */ \
	r0 -= r2;			/* new R3 = R1 - R3 (final R3) */ \
	r2 *= 2; \
	r2 += r0;			/* new R1 = R1 + R3 */ \
	r1 -= r3;			/* new R4 = R2 - R4 (final R4) */ \
	r3 *= 2; \
	r3 += r1;			/* new R2 = R2 + R4 */ \
	r5 -= r7;			/* R6 = R6 - R8 (Real part) */ \
	r7 *= 2;			/* R8 = R8 * 2 */ \
	r7 += r5;			/* R8 = R6 + R8 (Imaginary part) */ \
	r2 -= r3;			/* R1 = R1 - R2 (final R2) */ \
	r3 *= 2;			/* R2 = R2 * 2 */ \
	r3 += r2;			/* R2 = R1 + R2 (final R1) */ \
	r4 -= r5;			/* R5 = R5 - R6 (final R7) */ \
	r5 *= 2; \
	r5 += r4;			/* R6 = R5 + R6 (final R5) */ \
	r6 -= r7;			/* R7 = R7 - R8 (final R8) */ \
	r7 *= 2; \
	r7 += r6;			/* R8 = R7 + R8 (final R6) */ \


#define xs8r_unfft(r1, r2, r3, r4, r5, r6, r7, r8) \
	r1 -= r2;			/* R1 = R1 - R2 (new R2) */ \
	r1 *= 0.5;			/* Mul R1 by HALF */ \
	r2 += r1;			/* R2 = R1 + R2 (new R1) */ \
\
	r5 -= r7;			/* R5 = R5 - R7 (new R6) */ \
	r7 *= 2;			/* R7 = R7 * 2 */ \
	r7 += r5;			/* R7 = R5 + R7 (new R5) */ \
\
	r6 -= r8;			/* R6 = R6 - R8 (new R8) */ \
	r8 *= 2;;			/* R8 = R8 * 2 */ \
	r8 += r6;			/* R8 = R6 + R8 (new R7) */ \
\
	r6 -= r5;			/* R8 = R8 - R6 */ \
	r5 *= 2;			/* R6 = R6 * 2 */ \
	r5 += r6;			/* R6 = R6 + R8 */ \
	r5 *= g->u.xmm.XMM_SQRTHALF[0];	/* R6 = R6 * square root of 1/2 */ \
	r6 *= g->u.xmm.XMM_SQRTHALF[0];	/* R8 = R8 * square root of 1/2 */ \
\
	r2 -= r3;			/* R1 = R1 - R3 (new R3) */ \
	r3 *= 2;			/* R3 = R3 * 2 */ \
	r3 += r2;			/* R3 = R1 + R3 (new R1) */ \
\
	r1 -= r4;			/* R2 = R2 - R4 (new R4) */ \
	r4 *= 2;			/* R4 = R4 * 2 */ \
	r4 += r1;			/* R4 = R2 + R4 (new R2) */ \

#endif

#if 0
#define xs8r_mulf(r1, r2, r3, r4, r5, r6, r7, r8, m1, m2, m3, m4, m5, m6, m7, m8) \
	r1 *= f64ptr(m1+rbp);		/* R11 */ \
	r2 *= f64ptr(m2+rbp);		/* R22 */ \
	f64ptr(rsi-16) = r1;		/* Save product of sum of FFT values */ \
	xs_complex_mult(r3, r4, f64ptr(m3+rbp), f64ptr(m4+rbp), xmm8[0], xmm9[0]); \
	xs_complex_mult(r5, r6, f64ptr(m5+rbp), f64ptr(m6+rbp), xmm8[0], xmm9[0]); \
	xs_complex_mult(r7, r8, f64ptr(m7+rbp), f64ptr(m8+rbp), xmm8[0], xmm9[0]);
#endif

