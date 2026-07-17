#include "inttypes.h"
#include <stdio.h>

#ifdef _MSC_VER
#include <intrin.h>
#define shldq(A,B,C) __shiftleft128(B,A,C)
#define shrdq(A,B,C) __shiftright128(A,B,C)
#else

#if defined(__i386__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
#include <x86intrin.h>
#endif

typedef unsigned _BitInt(128) uint128;
typedef signed _BitInt(128) int128;
#if 0
static inline uint64_t shldq(uint64_t a, uint64_t b, uint32_t c) {
	uint128 r = b | ((uint128)a << 64);
	return r << (c&63) >> 64;
}
static inline uint64_t shrdq(uint64_t a, uint64_t b, uint32_t c) {
	uint128 r = a | ((uint128)b << 64);
	return r >> (c&63);
}
#else
static inline uint64_t shldq(uint64_t a, uint64_t b, uint32_t c) {
	c &= 63;
	return a<<c | b>>1>>(63^c);
}
static inline uint64_t shrdq(uint64_t a, uint64_t b, uint32_t c) {
	c &= 63;
	return a>>c | b<<1<<(63^c);
}
#endif
static inline uint64_t _mul128(int64_t a, int64_t b, int64_t *h) {
	int128 o = a * (int128)b;
	*h = o >> 64;
	return (uint64_t)o;
}
static inline uint64_t _umul128(uint64_t a, uint64_t b, uint64_t *h) {
	uint128 o = a * (uint128)b;
	*h = o >> 64;
	return (uint64_t)o;
}

static inline int64_t _div128(int64_t high, uint64_t low, int64_t d, int64_t *r) {
#ifdef __x86_64__
	uint64_t q;
	// the "r"(d) can be "rm", but clang is not smart
	__asm__ ("idivq %[v]": "=a" (q), "=d" (*r) : [v] "r" (d), "a" (low), "d" (high) : "cc");
	return q;
#else
	int128 n = ((uint128)(high) << 64) | low;
	*r = n % d;
	return n / d;
#endif
}
static inline uint64_t _udiv128(uint64_t high, uint64_t low, uint64_t d, uint64_t *r) {
#ifdef __x86_64__
	uint64_t q;
	__asm__ ("divq %[v]": "=a" (q), "=d" (*r) : [v] "r" (d), "a" (low), "d" (high) : "cc");
	return q;
#else
	uint128 n = ((uint128)(high) << 64) | low;
	*r = n % d;
	return n / d;
#endif
}

#endif

#if 1
void addhlp (uint32_t *res, uint32_t *carry, uint32_t val) {
	uint32_t c = 0;
	*res = __builtin_addc(*res, val, c, &c);
	*carry = __builtin_addc(*carry, 0, c, &c);
}
void subhlp (uint32_t *res, uint32_t *carry, uint32_t val) {
	uint32_t c = 0;
	*res = __builtin_subc(*res, val, c, &c);
	*carry = __builtin_subc(*carry, 0, c, &c);
}
void muladdhlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2) {
	uint64_t m = val1 * (uint64_t)val2;
	uint32_t c = 0;
	*res = __builtin_addc(*res, (uint32_t)m, c, &c);
	*carryl = __builtin_addc(*carryl, m >> 32, c, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c);
}
void muladd2hlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2) {
	uint64_t m = val1 * (uint64_t)val2;
	uint32_t m1 = (uint32_t)m;
	uint32_t m2 = m >> 32;
	uint32_t c = 0;
	m1 = __builtin_addc(m1, m1, 0, &c);
	m2 = __builtin_addc(m2, m2, c, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c);
	*res = __builtin_addc(*res, m1, 0, &c);
	*carryl = __builtin_addc(*carryl, m2, c, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c);
}
void mulsubhlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2) {
	uint64_t m = val1 * (uint64_t)val2;
	uint32_t c = 0;
	*res = __builtin_subc(*res, (uint32_t)m, c, &c);
	*carryl = __builtin_subc(*carryl, m >> 32, c, &c);
	*carryh = __builtin_subc(*carryh, 0, c, &c);
}
#else
void addhlp (uint32_t *res, uint32_t *carry, uint32_t val) {
	uint64_t a = *res + (((uint64_t) *carry) << 32);
	a += val;
	*res = (uint32_t)a;
	*carry = a >> 32;
	//puts("+");
}
void subhlp (uint32_t *res, uint32_t *carry, uint32_t val) {
	uint64_t a = *res + (((uint64_t) *carry) << 32);
	a -= val;
	*res = (uint32_t)a;
	*carry = a >> 32;
	//puts(" -");
}
void muladdhlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2) {
#if 1
	uint64_t a = val1 * (uint64_t)val2;
	unsigned _BitInt(96) r =
		(((uint64_t) *carryl) << 32) | *res |
		(((unsigned _BitInt(96)) *carryh) << 64);
	r += a;
	*res = (uint32_t)r;
	*carryl = r >> 32;
	*carryh = r >> 64;
#else
	uint64_t a = val1 * (uint64_t)val2;
	uint64_t b = (((uint64_t) *carryl) << 32) + *res;
	unsigned long long c = 0;
	unsigned int c4 = 0;
	a = __builtin_addcll(a, b, 0, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c4);
	*res = (uint32_t)a;
	*carryl = a >> 32;
#endif
	//puts("   *+");
}
void muladd2hlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2){
#if 1
	uint64_t a = val1 * (uint64_t)val2;
	unsigned _BitInt(96) r =
		(((uint64_t) *carryl) << 32) | *res |
		(((unsigned _BitInt(96)) *carryh) << 64);
	r += a;
	r += a;
	*res = (uint32_t)r;
	*carryl = r >> 32;
	*carryh = r >> 64;
#else
	uint64_t a = val1 * (uint64_t)val2;
	uint64_t b = (((uint64_t)*carryl) << 32) + *res;
	unsigned long long c = 0;
	unsigned int c4 = 0;
	a = __builtin_addcll(a, b, 0, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c4);
	a = __builtin_addcll(a, b, 0, &c);
	*carryh = __builtin_addc(*carryh, 0, c, &c4);
	*res = (uint32_t)a;
	*carryl = a >> 32;
#endif
	//puts("      *++");
}
void mulsubhlp (uint32_t *res, uint32_t *carryl, uint32_t *carryh, uint32_t val1, uint32_t val2){
#if 1
	uint64_t a = val1 * (uint64_t)val2;
	unsigned _BitInt(96) r =
		(((uint64_t) *carryl) << 32) | *res |
		(((unsigned _BitInt(96)) *carryh) << 64);
	r -= a;
	*res = (uint32_t)r;
	*carryl = r >> 32;
	*carryh = r >> 64;
#else
	uint64_t a = val1 * (uint64_t)val2;
	uint64_t b = (((uint64_t)*carryl) << 32) + *res;
	unsigned long long c = 0;
	unsigned int c4 = 0;
	a = __builtin_subcll(a, b, 0, &c);
	*carryh = __builtin_subc(*carryh, 0, c, &c4);
	*res = (uint32_t)a;
	*carryl = a >> 32;
#endif
	//puts("         *-");
}
#endif

const double TWOPOW32 = 4294967296.0;		 // 2^32
const double BIGVAL = 9223372036854775808.0;  // 2^63

#if 1
int gcdhlp (uint32_t ulen, uint32_t *udata, uint32_t vlen, uint32_t *vdata, unsigned int *struct_ptr) {
	//puts("         gcdhlp");
#if 1
	uintptr_t rax,rcx,rdx,rbx,rsi,rbp,r8,r9,r10,r12,r13,r14,r15,t;
	rcx = ulen;
	r8 = vlen;

	r14 = udata[rcx-1];	/* U[Ulen-1] */
	r15 = 0;		/* Zero V in case U and V not same len */
	if(rcx != r8)			/* Load top V word if U and V same len */
		goto noload;
	r15 = vdata[rcx-1];	/* V[Ulen-1] */

	if(rcx == 1)			/* Are there more words to shift */
		goto simple;			/* bits from? */

	noload:
	r14 <<= 32;
	r15 <<= 32;
	rax = udata[rcx-2];	/* U[Ulen-2] */
	rbx = vdata[rcx-2];	/* V[Ulen-2] */
	r14 += rax;
	r15 += rbx;

	if(rcx == 2)			/* Are there more words to shift */
		goto simple;			/* bits from? */

	rax = udata[rcx-3];	/* U[Ulen-3] */
	rbx = vdata[rcx-3];	/* V[Ulen-3] */

	rcx = __builtin_clzll(r14);		/* Count bits to shift U */
	/*cl ^= 63;*/			/* Turn bit # into a shift count */

	rax <<= 32;
	rbx <<= 32;
	r14 = shldq(r14, rax, rcx); //shld	r14, rax, cl;		/* Shift U */
	r15 = shldq(r15, rbx, rcx); //shld	r15, rbx, cl;		/* Shift V */

	/* Init extended GCD information */

	r8 = 1;			/* A */
	r9 = 0;			/* B */
	r10 = 0;		/* C */
	r13 = 1;			/* D */
	r12 = 0;		/* ODD */

	/* Do as many operations as we can constrained by a maximum 32-bit result */
	/*	FPU contains U, V, D, B, C, A */
	/* As Knuth suggests: */
	/*	Compute (U-B)/(V+D), the smaller quotient */
	/*	Compute (U+A)/(V-C), the larger quotient, break if not equal */
	/*	Set newB = D, newD = B+Q*D, break if newD won't fit in 32 bits */
	/*	Set newA = C, newC = A+Q*C */
	/*	Set newU = V, newV = U-Q*V */

	rsi = 1;			/* Compute 2^32 */
	rsi <<= 32;
	r14 >>= 1;			/* Lose a bit so we can use signed */
	r15 >>= 1;			/* multiply and divide instructions */

	dloop:
	rax = r14;		/* U */
	rax -= r9;			/* U-B */
	rcx = r15;		/* V */
	rcx += r13;		/* V+D */
	rdx = 0;
	rax = _div128(rdx, rax, rcx, (int64_t*)&rdx);	/* Q = (U-B)/(V+D) */

	rcx = r15;		/* V */
	rcx -= r10;		/* V-C */
	rbp = rax;		/* Copy Q */
	rbp *= rcx;		/* Q*(V-C) */
	rbp += rcx;		/* (Q+1)*(V-C) */
	rbx = (r14+r8);		/* U+A */
	if(rbx >= rbp)		/* Compare U+A to (Q+1)*(V-C) */
		goto lpdone;			/* Break if above or equal */

	rbx = r13;		/* D */
	rbx *= rax;		/* Q*D */
	rbx += r9;			/* B+Q*D (newD) */
	if(rbx >= rsi)		/* Will new D be too large? */
		goto lpdone;			/* Break if newD is 32-bits or more */
	r9 = r13;			/* newB = D */
	r13 = rbx;		/* newD = B+Q*D */

	rcx = r10;		/* C */
	rcx *= rax;		/* Q*C */
	rcx += r8;			/* A+Q*C (newC) */
	r8 = r10;			/* newA = C */
	r10 = rcx;		/* newC = A+Q*C */

	rax *= r15;		/* Q*V */
	r14 -= rax;		/* U-Q*V (newV) */
	t = r14; r14 = r15; r15 = t;	/* newU = V, newV = U-Q*V */

	r12 ^= 1;			/* Flip ODD */

	/*	Compute (U-A)/(V+C), the smaller quotient */
	/*	Compute (U+B)/(V-D), the larger quotient, break if not equal */
	/*	Set newB = D, newD = B+Q*D, break if newD won't fit in 32 bits */
	/*	Set newA = C, newC = A+Q*C */
	/*	Set newU = V, newV = U-Q*V */

	rax = r14;		/* U */
	rax -= r8;			/* U-A */
	rcx = r15;		/* V */
	rcx += r10;		/* V+C */
	rdx = 0;
	rax = _div128(rdx, rax, rcx, (int64_t*)&rdx); /* Q = (U-A)/(V+C) */

	rcx = r15;		/* V */
	rcx -= r13;		/* V-D */
	rbp = rax;		/* Copy Q */
	rbp *= rcx;		/* Q*(V-D) */
	rbp += rcx;		/* (Q+1)*(V-D) */
	rbx = (r14+r9);		/* U+B */
	if(rbx >= rbp)		/* Compare U+B to (Q+1)*(V-D) */
		goto lpdone;			/* Break if above or equal */

	rbx = r13;		/* D */
	rbx *= rax;		/* Q*D */
	rbx += r9;			/* B+Q*D (newD) */
	if(rbx >= rsi)		/* Will new D be too large? */
		goto lpdone;			/* Break if newD is 32-bits or more */
	r9 = r13;			/* newB = D */
	r13 = rbx;		/* newD = B+Q*D */

	rcx = r10;		/* C */
	rcx *= rax;		/* Q*C */
	rcx += r8;			/* A+Q*C (newC) */
	r8 = r10;			/* newA = C */
	r10 = rcx;		/* newC = A+Q*C */

	rax *= r15;		/* Q*V */
	r14 -= rax;		/* U-Q*V (newV) */
	t = r14; r14 = r15; r15 = t;	/* newU = V, newV = U-Q*V */

	r12 ^= 1;			/* Flip ODD */
	goto	dloop;

	/* The single precision case: */

	/* Init extended GCD information */

	simple:	r8 = 1;			/* A */
	r9 = 0;			/* B */
	r10 = 0;		/* C */
	r13 = 1;			/* D */
	r12 = 0;		/* ODD */

	/*	Compute U/V, the quotient */
	/*	Set newB = D, newD = B+Q*D, break if newD won't fit in 32 bits */
	/*	Set newA = C, newC = A+Q*C */
	/*	Set newU = V, newV = U-Q*V */

	rsi = 1;			/* Compute 2^32 */
	rsi <<= 32;
	sloop:
	rax = r14;		/* U */
	rdx = 0;
	rax = rax / r15;			/* Q = U/V */
	rbp = rax;		/* Copy Q */

	rax *= r13;			/* Q*D */
	rax += r9;			/* B+Q*D */
	if(rax >= rsi)		/* Will new D be too large? */
		goto lpdone;		/* Break if D >= 2^32 */
	r9 = r13;			/* newB = D */
	r13 = rax;		/* newD = B+Q*D */

	rax = r10;		/* C */
	rax *= rbp;			/* Q*C */
	rax += r8;			/* A+Q*C (newC) */
	r8 = r10;			/* newA = C */
	r10 = rax;		/* newC = A+Q*C */

	rax = r15;		/* V */
	rax *= rbp;			/* Q*V */
	r14 -= rax;		/* U-Q*V (newV) */
	t = r14; r14 = r15; r15 = t;		/* newU = V, newV = U-Q*V */

	r12 ^= 1;			/* Flip ODD */

	if(r15)		/* Loop if V is not zero */
		goto sloop;

	/* Copy extended GCD info to globals */

	lpdone:
	struct_ptr[0] = r8; /* Save A */
	struct_ptr[1] = r9; /* Save B */
	struct_ptr[2] = r10; /* Save C */
	struct_ptr[3] = r13; /* Save D */
	struct_ptr[4] = r12; /* Save ODD */

#else
	uint64_t a,c,b,si,bp,r8,r9,r10,r12,r13,r14,r15,t;
	int64_t d;

	c = ulen;
	r8 = vlen;

	// (cx,dx,r8,r9,r11)

	r14 = udata[c-1];
	r15 = 0;
	if(c == r8)
	{
		r15 = vdata[c-1];
		if(c == 1) goto simple;
	}
	r14 <<= 32;
	r15 <<= 32;
	a = udata[c-2];
	b = vdata[c-2];
	r14 += a;
	r15 += b;

	if(c == 2) goto simple;

	a = udata[c-3];
	b = vdata[c-3];

	c = __builtin_clzll(r14);  // __bsrd or __builtin_clz
	// c ^= 63;, not needed, unless BSR is used.

	a <<= 32;
	b <<= 32;
	r14 = shldq(r14, a, c);
	r15 = shldq(r15, b, c);

	r8 = 1;
	r9 = 0;
	r10 = 0;
	r13 = 1;
	r12 = 0;

	si = 0x100000000ULL;
	r14  >>= 1;
	r15 >>= 1;

dloop:
	a = r14;
	a -= r9;
	c = r15;
	c += r13;
	d = 0;
	a = _div128(d, a, c, &d);

	c = r15;
	c -= r10;
	bp = a;
	bp *= c;
	bp += c;
	b = r14 + r8;
	if(b >= bp) goto lpdone;

	b = r13;
	b *= a;
	b += r9;
	if(b >= si) goto lpdone;
	r9 = r13;
	r13 = b;

	c = r10;
	c *= a;
	c += r8;
	r8 = r10;
	r10 = c;

	a *= r15;
	r14 -= a;
	t = r14; r14 = r15; r15 = t; // xchg

	r12 ^= 1;



	a = r14;
	a -= r8;
	c = r15;
	c += r10;
	d = 0;
	a = _div128(d, a, c, &d);

	c = r15;
	c -= r13;
	bp = a;
	bp *= c;
	bp += c;
	b = r14 + r9;
	if(b >= bp) goto lpdone;

	b = r13;
	b *= a;
	b += r9;
	if(b >= si) goto lpdone;
	r9 = r13;
	r13 = b;

	c = r10;
	c *= a;
	c += r8;
	r8 = r10;
	r10 = c;

	a *= r15;
	r14 -= a;
	t = r14; r14 = r15; r15 = t; // xchg

	r12 ^= 1;
	goto dloop;

simple:
	r8 = 1;
	r9 = 0;
	r10 = 0;
	r13 = 1;
	r12 = 0;


	si = 0x100000000ULL;
sloop:
	a = r14;
	//d = 0;
	//d = a % r15;  // unused remainder
	a = a / r15;  // unsigned "div" with rdx = 0
	bp = a;
	a = a * r13; //_umul128(a, r13, &d);
	a += r9;
	if(a >= si) goto lpdone;
	r9 = r13;
	r13 = a;

	a = r10;
	a = a * bp; //_umul128(a, bp, &d);
	a += r8;
	r8 = r10;
	r10 = a;

	a = r15;
	a = a * bp; //_umul128(a, bp, &d);
	r14 -= a;
	t = r14; r14 = r15; r15 = t; // xchg

	r12 ^= 1;

	if(r15) goto sloop;

lpdone:
	struct_ptr[0] = (uint32_t)r8;
	struct_ptr[1] = (uint32_t)r9;
	struct_ptr[2] = (uint32_t)r10;
	struct_ptr[3] = (uint32_t)r13;
	struct_ptr[4] = (uint32_t)r12;
#endif
	return r9 != 0 ? 1 : 0;
}
#endif
