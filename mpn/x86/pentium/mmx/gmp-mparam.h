/* Intel P55 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001 Free Software Foundation, Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */


#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4


#ifndef UMUL_TIME
#define UMUL_TIME   9 /* cycles */
#endif
#ifndef UDIV_TIME
#define UDIV_TIME   41 /* cycles */
#endif

/* In an isolated test udiv_qrnnd_preinv can measure about 32 cycles, but in
   practice it's not that good due to using up registers.  For instance
   sb_divrem_mn is about the same speed using plain or preinv, so pretend
   preinv is a touch slower than plain.  */
#ifndef UDIV_NORM_PREINV_TIME
#define UDIV_NORM_PREINV_TIME   42 /* cycles */
#endif

/* bsf takes 18-42 cycles, put an average for uniform random numbers */
#ifndef COUNT_TRAILING_ZEROS_TIME
#define COUNT_TRAILING_ZEROS_TIME   20  /* cycles */
#endif


/* 166MHz P55, gcc 2.95.2 */

/* Generated by tuneup.c, 2001-02-03. */

#define KARATSUBA_MUL_THRESHOLD       16
#define TOOM3_MUL_THRESHOLD          105

#define KARATSUBA_SQR_THRESHOLD       20
#define TOOM3_SQR_THRESHOLD          129

#define SB_PREINV_THRESHOLD            0
#define DC_THRESHOLD                  44
#define POWM_THRESHOLD                62

#define GCD_ACCEL_THRESHOLD            3
#define GCDEXT_THRESHOLD              17

#define USE_PREINV_MOD_1               1  /* (native) */
#define DIVREM_2_THRESHOLD             0
#define MODEXACT_1_ODD_THRESHOLD       0

#define FFT_MUL_TABLE  { 464, 992, 1920, 4608, 14336, 40960, 0 }
#define FFT_MODF_MUL_THRESHOLD       480
#define FFT_MUL_THRESHOLD           3328

#define FFT_SQR_TABLE  { 496, 1184, 2176, 5632, 18432, 40960, 0 }
#define FFT_MODF_SQR_THRESHOLD       512
#define FFT_SQR_THRESHOLD           3840
