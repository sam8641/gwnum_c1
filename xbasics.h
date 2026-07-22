#pragma once





// TODO: use __builtin_prefetch(a,is_write, level);
// level 0: stream, 1: L3 cache, 2: L2 cache, 3: L1 cache

#define xtouch(A)
#define xtouch_init(A)
#define xprefetch(A)
#define xxprefetch(A)
#define xprefetchw(A)
#define L2prefetch128(A)


#define xs_complex_square xp_complex_square
#if 0
#define xs_complex_mult xp_complex_mult
#define xp_complex_mult(real1, imag1, real2, imag2, tmp1, tmp2) \
	tmp1 = real1*real2-imag1*imag2; \
	tmp2 = real1*imag2+real2*imag1; \
	real1 = tmp1; \
	imag1 = tmp2;
#else
#define xs_complex_mult(real1, imag1, real2m, imag2m, tmp1, tmp2) { \
	double real2 = real2m, imag2 = imag2m; \
	tmp1 = real1; \
	real1 *= real2;		/* real1 * real2 */ \
	tmp2 = imag1 * imag2; /* imag1 * imag2 */ \
	tmp1 *= imag2; /* real1 * imag2 */ \
	imag1 *= real2;		/* real2 * imag1 */ \
	real1 -= tmp2;		/* real1*real2-imag1*imag2 (new real) */ \
	imag1 += tmp1;		/* real1*imag2+real2*imag1 (new imag) */ \
}
#define xp_complex_mult(real1, imag1, real2m, imag2m, tmp1, tmp2) { \
	vec2f64 real2 = real2m, imag2 = imag2m; \
	tmp1 = real1; \
	real1 *= real2;		/* real1 * real2 */ \
	tmp2 = imag1 * imag2; /* imag1 * imag2 */ \
	tmp1 *= imag2; /* real1 * imag2 */ \
	imag1 *= real2;		/* real2 * imag1 */ \
	real1 -= tmp2;		/* real1*real2-imag1*imag2 (new real) */ \
	imag1 += tmp1;		/* real1*imag2+real2*imag1 (new imag) */ \
}
#endif
#if 0
#define xp_complex_square(real, imag, tmp) \
	tmp = imag * real; \
	real = real*real - imag*imag; \
	imag = tmp + tmp;
#else
#define xp_complex_square(real, imag, tmp) \
	tmp = imag * imag; \
	imag *= real; \
	real *= real; \
	real -= tmp;		/* real^2 - imag^2 (new real) */ \
	imag += imag;		/* imag * real * 2 (new imag) */
#endif

#if 1 // Mostly parallel SIMD, must be 16 byte aligned.
#define xmult7(src1, src2) \
if(g->ZERO_PADDED_FFT != 0) {	/* Is this a zero-padded FFT? */ \
	vec2f64 s2,s4,s6; \
	vec2f64 t1,t2,t3,t4,t5,t6; \
	double t7; \
	vec2f64 v0,v1,v2; \
	t2 = xptr(src2-80); \
	t4 = xptr(src2-64); \
	t6 = xptr(src2-48); \
	t1[0] = f64ptr(src2-88); t1[1] = t2[0]; \
	t3[0] = t2[1]; t3[1] = t4[0]; \
	t5[0] = t4[1]; t5[1] = t6[0]; \
	t7 = t6[1]; \
	s4 = xptr(src1-64); \
	s6 = xptr(src1-48); \
	s2 = xptr(src1-80); \
	/* s1 = f64ptr(src1-88); */ \
	\
	v0 = t4 * s4[0]; \
	v0 += t3 * s4[1]; \
	v0 += t2 * s6[0]; \
	v0 += t1 * s6[1]; \
	v0 += t5 * s2[1]; \
	v0 += t6 * s2[0]; \
	v0[0] += t7 * f64ptr(src1-88); \
	*(vec2f64*)&(g->ZPAD0_6[0]) = v0; \
	\
	v1 = t6 * s4[0]; \
	v1 += t5 * s4[1]; \
	v1 += t4 * s6[0]; \
	v1 += t3 * s6[1]; \
	v1[0] += s2[1] * t7; \
	*(vec2f64*)&(g->ZPAD0_6[2]) = v1; \
	\
	v2 = t6 * s6[0]; \
	v2[0] += t7 * s4[1]; \
	v2 += t5 * s6[1]; \
	*(vec2f64*)&(g->ZPAD0_6[4]) = v2; \
	g->ZPAD0_6[6] = t7 * s6[1]; \
}
#else
#define xmult7(src1, src2) \
if(g->ZERO_PADDED_FFT != 0) {	/* Is this a zero-padded FFT? */ \
	double f0,f1,f2,f3; \
	f0 = f64ptr(src1-64);	/* Result0 = word0 * word0 */ \
	f0 *= f64ptr(src2-64); \
	f1 = f64ptr(src1-56);	/*	   + word1 * word-1 */ \
	f1 *= f64ptr(src2-72); \
	f0 += f1; \
	f2 = f64ptr(src1-48);	/*	   + word2 * word-2 */ \
	f2 *= f64ptr(src2-80); \
	f0 += f2; \
	f3 = f64ptr(src1-40);	/*	   + word3 * word-3 */ \
	f3 *= f64ptr(src2-88); \
	f0 += f3; \
	f1 = f64ptr(src1-72);	/*	   + word-1 * word1 */ \
	f1 *= f64ptr(src2-56); \
	f0 += f1; \
	f2 = f64ptr(src1-80);	/*	   + word-2 * word2 */ \
	f2 *= f64ptr(src2-48); \
	f0 += f2; \
	f3 = f64ptr(src1-88);	/*	   + word-3 * word3 */ \
	f3 *= f64ptr(src2-40); \
	f0 += f3; \
	g->ZPAD0_6[0] = f0; \
	\
	f0 = f64ptr(src1-64);	/* Result1 = word0 * word1 */ \
	f0 *= f64ptr(src2-56); \
	f1 = f64ptr(src1-56);	/*	   + word1 * word0 */ \
	f1 *= f64ptr(src2-64); \
	f0 += f1; \
	f2 = f64ptr(src1-48);	/*	   + word2 * word-1 */ \
	f2 *= f64ptr(src2-72); \
	f0 += f2; \
	f3 = f64ptr(src1-40);	/*	   + word3 * word-2 */ \
	f3 *= f64ptr(src2-80); \
	f0 += f3; \
	f2 = f64ptr(src1-72);	/*	   + word-1 * word2 */ \
	f2 *= f64ptr(src2-48); \
	f0 += f2; \
	f3 = f64ptr(src1-80);	/*	   + word-2 * word3 */ \
	f3 *= f64ptr(src2-40); \
	f0 += f3; \
	g->ZPAD0_6[1] = f0; \
	\
	f0 = f64ptr(src1-64);	/* Result2 = word0 * word2 */ \
	f0 *= f64ptr(src2-48); \
	f1 = f64ptr(src1-56);	/*	   + word1 * word1 */ \
	f1 *= f64ptr(src2-56); \
	f0 += f1; \
	f2 = f64ptr(src1-48);	/*	   + word2 * word0 */ \
	f2 *= f64ptr(src2-64); \
	f0 += f2; \
	f3 = f64ptr(src1-40);	/*	   + word3 * word-1 */ \
	f3 *= f64ptr(src2-72); \
	f0 += f3; \
	f3 = f64ptr(src1-72);	/*	   + word-1 * word3 */ \
	f3 *= f64ptr(src2-40); \
	f0 += f3; \
	g->ZPAD0_6[2] = f0; \
	\
	f0 = f64ptr(src1-64);	/* Result3 = word0 * word3 */ \
	f0 *= f64ptr(src2-40); \
	f1 = f64ptr(src1-56);	/*	   + word1 * word2 */ \
	f1 *= f64ptr(src2-48); \
	f0 += f1; \
	f2 = f64ptr(src1-48);	/*	   + word2 * word1 */ \
	f2 *= f64ptr(src2-56); \
	f0 += f2; \
	f3 = f64ptr(src1-40);	/*	   + word3 * word0 */ \
	f3 *= f64ptr(src2-64); \
	f0 += f3; \
	g->ZPAD0_6[3] = f0; \
	\
	f0 = f64ptr(src1-56);	/* Result4 = word1 * word3 */ \
	f0 *= f64ptr(src2-40); \
	f1 = f64ptr(src1-48);	/*	   + word2 * word2 */ \
	f1 *= f64ptr(src2-48); \
	f0 += f1; \
	f2 = f64ptr(src1-40);	/*	   + word3 * word1 */ \
	f2 *= f64ptr(src2-56); \
	f0 += f2; \
	g->ZPAD0_6[4] = f0; \
	\
	f0 = f64ptr(src1-48);	/* Result5 = word2 * word3 */ \
	f0 *= f64ptr(src2-40); \
	f1 = f64ptr(src1-40);	/*	   + word3 * word2 */ \
	f1 *= f64ptr(src2-48); \
	f0 += f1; \
	g->ZPAD0_6[5] = f0; \
	\
	f0 = f64ptr(src1-40);	/* Result6 = word3 * word3 */ \
	f0 *= f64ptr(src2-40); \
	g->ZPAD0_6[6] = f0; \
}
#endif

// xs4c_mulf only used in hg.h, s2cl_eight_reals_with_mult_2
#if 0
#define xs4c_mulf(r1,r2,r3,r4,r5,r6,r7,r8,m1,m2,m3,m4,m5,m6,m7,m8) { \
	vec2f64 tmp8, tmp9; \
	vec2f64 r13 = {r1, r3}; \
	vec2f64 r24 = {r2, r4}; \
	vec2f64 r57 = {r5, r7}; \
	vec2f64 r68 = {r6, r8}; \
	vec2f64 m13 = {f64ptr(m1+rbp), f64ptr(m3+rbp)}; \
	vec2f64 m24 = {f64ptr(m2+rbp), f64ptr(m4+rbp)}; \
	xp_complex_mult(r13, r24, m13, m24, tmp8, tmp9); \
	vec2f64 m57 = {f64ptr(m5+rbp), f64ptr(m7+rbp)}; \
	vec2f64 m68 = {f64ptr(m6+rbp), f64ptr(m8+rbp)}; \
	xp_complex_mult(r57, r68, m57, m68, tmp8, tmp9); \
	r1 = r13[0]; r3 = r13[1]; \
	r2 = r24[0]; r4 = r24[1]; \
	r5 = r57[0]; r7 = r57[1]; \
	r6 = r68[0]; r8 = r68[1]; \
}
#else
#define xs4c_mulf(r1,r2,r3,r4,r5,r6,r7,r8,m1,m2,m3,m4,m5,m6,m7,m8) { \
	double tmp8, tmp9; \
	xs_complex_mult(r1, r2, f64ptr(m1+rbp), f64ptr(m2+rbp), tmp8, tmp9); \
	xs_complex_mult(r3, r4, f64ptr(m3+rbp), f64ptr(m4+rbp), tmp8, tmp9); \
	xs_complex_mult(r5, r6, f64ptr(m5+rbp), f64ptr(m6+rbp), tmp8, tmp9); \
	xs_complex_mult(r7, r8, f64ptr(m7+rbp), f64ptr(m8+rbp), tmp8, tmp9); \
}
#endif
#define xp4c_mulf(r1,r2,r3,r4,r5,r6,r7,r8,m1,m2,m3,m4,m5,m6,m7,m8) { \
	vec2f64 tmp8, tmp9; \
	xp_complex_mult(r1, r2, xptr(m1+rbp), xptr(m2+rbp), tmp8, tmp9); \
	xp_complex_mult(r3, r4, xptr(m3+rbp), xptr(m4+rbp), tmp8, tmp9); \
	xp_complex_mult(r5, r6, xptr(m5+rbp), xptr(m6+rbp), tmp8, tmp9); \
	xp_complex_mult(r7, r8, xptr(m7+rbp), xptr(m8+rbp), tmp8, tmp9); \
}



