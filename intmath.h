/*----------------------------------------------------------------------
| intmath.h
|
| Portable wide-integer and add/subtract-with-carry helpers.
|
| Clang's __builtin_addc / __builtin_subc family and the C23 _BitInt types
| are not available in GCC or MSVC.  The helpers below hide those behind
| plain C arithmetic that every compiler turns back into the expected
| adc/sbb (x86) or adcs/sbcs (ARM64) instruction chains.  Where the Clang
| builtins do exist they are still used, so Clang code generation is
| unchanged.
|
|  Copyright 1995-2026 Mersenne Research, Inc.  All rights reserved.
+---------------------------------------------------------------------*/

#ifndef _INTMATH_H
#define _INTMATH_H

#include "inttypes.h"


#ifdef __has_builtin
#define GW_HAS_BUILTIN(x) __has_builtin(x)
#else
#define GW_HAS_BUILTIN(x) 0
#endif

#if defined(__SIZEOF_INT128__)
#define HAVE_INT128 1
typedef unsigned __int128 uint128;
typedef signed __int128 int128;

#elif defined(__clang__) && !defined(__cplusplus) && \
	defined(__BITINT_MAXWIDTH__) && __BITINT_MAXWIDTH__ >= 128
#define HAVE_INT128 1
typedef unsigned _BitInt(128) uint128;
typedef signed _BitInt(128) int128;
#endif

#if GW_HAS_BUILTIN(__builtin_addc)

static inline uint32_t addc32 (uint32_t a, uint32_t b, uint32_t carry_in, uint32_t *carry_out)
{
	unsigned int cout;
	unsigned int r = __builtin_addc ((unsigned int) a, (unsigned int) b, (unsigned int) carry_in, &cout);
	*carry_out = cout;
	return r;
}

static inline uint64_t addc64 (uint64_t a, uint64_t b, uint64_t carry_in, uint64_t *carry_out)
{
	unsigned long long cout;
	unsigned long long r = __builtin_addcll ((unsigned long long) a, (unsigned long long) b,
						 (unsigned long long) carry_in, &cout);
	*carry_out = cout;
	return r;
}

#else

static inline uint32_t addc32 (uint32_t a, uint32_t b, uint32_t carry_in, uint32_t *carry_out)
{
	uint64_t s = (uint64_t) a + (uint64_t) b + (uint64_t) carry_in;
	*carry_out = (uint32_t) (s >> 32);
	return (uint32_t) s;
}

static inline uint64_t addc64 (uint64_t a, uint64_t b, uint64_t carry_in, uint64_t *carry_out)
{
	uint64_t s = a + b;
	uint64_t c = (s < a);			/* carry out of a + b */
	s += carry_in;
	*carry_out = c | (s < carry_in);	/* plus carry out of the += carry_in */
	return s;
}

#endif

#if GW_HAS_BUILTIN(__builtin_subc)

static inline uint32_t subc32 (uint32_t a, uint32_t b, uint32_t borrow_in, uint32_t *borrow_out)
{
	unsigned int bout;
	unsigned int r = __builtin_subc ((unsigned int) a, (unsigned int) b, (unsigned int) borrow_in, &bout);
	*borrow_out = bout;
	return r;
}

static inline uint64_t subc64 (uint64_t a, uint64_t b, uint64_t borrow_in, uint64_t *borrow_out)
{
	unsigned long long bout;
	unsigned long long r = __builtin_subcll ((unsigned long long) a, (unsigned long long) b,
						 (unsigned long long) borrow_in, &bout);
	*borrow_out = bout;
	return r;
}

#else

static inline uint32_t subc32 (uint32_t a, uint32_t b, uint32_t borrow_in, uint32_t *borrow_out)
{
	uint64_t d = (uint64_t) a - (uint64_t) b - (uint64_t) borrow_in;
	*borrow_out = (uint32_t) (d >> 32) & 1;
	return (uint32_t) d;
}

static inline uint64_t subc64 (uint64_t a, uint64_t b, uint64_t borrow_in, uint64_t *borrow_out)
{
	uint64_t d = a - b;
	uint64_t c = (a < b);			/* borrow out of a - b */
	*borrow_out = c | (d < borrow_in);	/* plus borrow out of the -= borrow_in */
	return d - borrow_in;
}

#endif

#endif
