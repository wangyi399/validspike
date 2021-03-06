/* --------------------------------------------------- */
/* Automatically generated by mwrap                    */
/* --------------------------------------------------- */

/* Code generated by mwrap */
/*
  Copyright statement for mwrap:

  mwrap -- MEX file generation for MATLAB and Octave
  Copyright (c) 2007-2008 David Bindel

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  You may distribute a work that contains part or all of the source code
  generated by mwrap under the terms of your choice.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <mex.h>
#include <stdio.h>
#include <string.h>


#ifndef ulong
#  define ulong unsigned long
#endif
#ifndef uint
#  define uint  unsigned int
#endif
#ifndef uchar
#  define uchar unsigned char
#endif


/*
 * Support for 32-bit and 64-bit MEX files
 */
#ifndef mwSize
#  define mwSize int
#endif
#ifndef mwIndex
#  define mwIndex int
#endif
#ifndef mwSignedIndex
#  define mwSignedIndex int
#endif


/*
 * Records for call profile.
 */
int* mexprofrecord_= NULL;


/*
 * Support routines for copying data into and out of the MEX stubs
 */

void* mxWrapGetP(const mxArray* a, const char* fmt, const char** e)
{
    void* p = 0;
    mxArray* ap;
    if (mxGetClassID(a) == mxDOUBLE_CLASS && 
        mxGetM(a)*mxGetN(a) == 1 && *mxGetPr(a) == 0)
        return p;
    if (mxIsChar(a)) {
        char pbuf[128];
        mxGetString(a, pbuf, sizeof(pbuf));
        sscanf(pbuf, fmt, &p);
    } 
#ifdef R2008OO
    else if (ap = mxGetProperty(a, 0, "mwptr")) {
        return mxWrapGetP(ap, fmt, e);
    }
#endif
    if (p == 0)
        *e = "Invalid pointer";
    return p;
}

mxArray* mxWrapCreateP(void* p, const char* fmt)
{
    if (p == 0) {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetPr(z) = 0;
        return z;
    } else {
        char pbuf[128];
        sprintf(pbuf, fmt, p);
        return mxCreateString(pbuf);
    }
}

mxArray* mxWrapStrncpy(const char* s)
{
    if (s) {
        return mxCreateString(s);
    } else {
        mxArray* z = mxCreateDoubleMatrix(1,1, mxREAL);
        *mxGetPr(z) = 0;
        return z;
    }
}

double mxWrapGetScalar(const mxArray* a, const char** e)
{
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS || mxGetM(a)*mxGetN(a) != 1) {
        *e = "Invalid scalar argument";
        return 0;
    }
    return *mxGetPr(a);
}

char* mxWrapGetString(const mxArray* a, const char** e)
{
    char* s;
    mwSize slen;
    if (!a || (!mxIsChar(a) && mxGetM(a)*mxGetN(a) > 0)) {
        *e = "Invalid string argument";
        return NULL;
    }
    slen = mxGetM(a)*mxGetN(a) + 1;
    s = (char*) mxMalloc(slen);
    if (mxGetM(a)*mxGetN(a) == 0)
        *s = 0;
    else
        mxGetString(a, s, slen);
    return s;
}


#define mxWrapGetArrayDef(func, T) \
T* func(const mxArray* a, const char** e)     \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* q; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    q = mxGetPr(a); \
    for (i = 0; i < arraylen; ++i) \
        *p++ = (T) (*q++); \
    return array; \
}


#define mxWrapCopyDef(func, T) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* p = mxGetPr(a); \
    for (i = 0; i < n; ++i) \
        *p++ = *q++; \
}


#define mxWrapReturnDef(func, T) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    double* p; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxREAL); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxREAL); \
        p = mxGetPr(a); \
        for (i = 0; i < m*n; ++i) \
            *p++ = *q++; \
        return a; \
    } \
}


#define mxWrapGetScalarZDef(func, T, ZT, setz) \
void func(T* z, const mxArray* a) \
{ \
    double* pr = mxGetPr(a); \
    double* pi = mxGetPi(a); \
    setz(z, (ZT) *pr, (pi ? (ZT) *pi : (ZT) 0)); \
}


#define mxWrapGetArrayZDef(func, T, ZT, setz) \
T* func(const mxArray* a, const char** e) \
{ \
    T* array; \
    mwSize arraylen; \
    mwIndex i; \
    T* p; \
    double* qr; \
    double* qi; \
    if (!a || mxGetClassID(a) != mxDOUBLE_CLASS) { \
        *e = "Invalid array argument"; \
        return 0; \
    } \
    arraylen = mxGetM(a)*mxGetN(a); \
    array = (T*) mxMalloc(mxGetM(a)*mxGetN(a) * sizeof(T)); \
    p = array; \
    qr = mxGetPr(a); \
    qi = mxGetPi(a); \
    for (i = 0; i < arraylen; ++i) { \
        ZT val_qr = *qr++; \
        ZT val_qi = (qi ? (ZT) *qi++ : (ZT) 0); \
        setz(p, val_qr, val_qi); \
        ++p; \
    } \
    return array; \
}


#define mxWrapCopyZDef(func, T, real, imag) \
void func(mxArray* a, const T* q, mwSize n) \
{ \
    mwIndex i; \
    double* pr = mxGetPr(a); \
    double* pi = mxGetPi(a); \
    for (i = 0; i < n; ++i) { \
        *pr++ = real(*q); \
        *pi++ = imag(*q); \
        ++q; \
    } \
}


#define mxWrapReturnZDef(func, T, real, imag) \
mxArray* func(const T* q, mwSize m, mwSize n) \
{ \
    mwIndex i; \
    double* pr; \
    double* pi; \
    if (!q) { \
        return mxCreateDoubleMatrix(0,0, mxCOMPLEX); \
    } else { \
        mxArray* a = mxCreateDoubleMatrix(m,n, mxCOMPLEX); \
        pr = mxGetPr(a); \
        pi = mxGetPi(a); \
        for (i = 0; i < m*n; ++i) { \
            *pr++ = real(*q); \
            *pi++ = imag(*q); \
            ++q; \
        } \
        return a; \
    } \
}

/* Array copier definitions */
mxWrapGetArrayDef(mxWrapGetArray_bool, bool)
mxWrapCopyDef    (mxWrapCopy_bool,     bool)
mxWrapReturnDef  (mxWrapReturn_bool,   bool)
mxWrapGetArrayDef(mxWrapGetArray_char, char)
mxWrapCopyDef    (mxWrapCopy_char,     char)
mxWrapReturnDef  (mxWrapReturn_char,   char)
mxWrapGetArrayDef(mxWrapGetArray_double, double)
mxWrapCopyDef    (mxWrapCopy_double,     double)
mxWrapReturnDef  (mxWrapReturn_double,   double)
mxWrapGetArrayDef(mxWrapGetArray_float, float)
mxWrapCopyDef    (mxWrapCopy_float,     float)
mxWrapReturnDef  (mxWrapReturn_float,   float)
mxWrapGetArrayDef(mxWrapGetArray_int, int)
mxWrapCopyDef    (mxWrapCopy_int,     int)
mxWrapReturnDef  (mxWrapReturn_int,   int)
mxWrapGetArrayDef(mxWrapGetArray_long, long)
mxWrapCopyDef    (mxWrapCopy_long,     long)
mxWrapReturnDef  (mxWrapReturn_long,   long)
mxWrapGetArrayDef(mxWrapGetArray_mwIndex, mwIndex)
mxWrapCopyDef    (mxWrapCopy_mwIndex,     mwIndex)
mxWrapReturnDef  (mxWrapReturn_mwIndex,   mwIndex)
mxWrapGetArrayDef(mxWrapGetArray_mwSignedIndex, mwSignedIndex)
mxWrapCopyDef    (mxWrapCopy_mwSignedIndex,     mwSignedIndex)
mxWrapReturnDef  (mxWrapReturn_mwSignedIndex,   mwSignedIndex)
mxWrapGetArrayDef(mxWrapGetArray_mwSize, mwSize)
mxWrapCopyDef    (mxWrapCopy_mwSize,     mwSize)
mxWrapReturnDef  (mxWrapReturn_mwSize,   mwSize)
mxWrapGetArrayDef(mxWrapGetArray_size_t, size_t)
mxWrapCopyDef    (mxWrapCopy_size_t,     size_t)
mxWrapReturnDef  (mxWrapReturn_size_t,   size_t)
mxWrapGetArrayDef(mxWrapGetArray_uchar, uchar)
mxWrapCopyDef    (mxWrapCopy_uchar,     uchar)
mxWrapReturnDef  (mxWrapReturn_uchar,   uchar)
mxWrapGetArrayDef(mxWrapGetArray_uint, uint)
mxWrapCopyDef    (mxWrapCopy_uint,     uint)
mxWrapReturnDef  (mxWrapReturn_uint,   uint)
mxWrapGetArrayDef(mxWrapGetArray_ulong, ulong)
mxWrapCopyDef    (mxWrapCopy_ulong,     ulong)
mxWrapReturnDef  (mxWrapReturn_ulong,   ulong)

/* ---- spikefit.mw: 45 ----
 * spikemod(double[] W, int M, int T, int K, int fac, int Ns, int[] l, double[] t, double[] a, int Nt, output double[M, Nt] F, int subF, inout int[2] iran);
 */
const char* stubids1_ = "spikemod(i double[], i int, i int, i int, i int, i int, i int[], i double[], i double[], i int, o double[xx], i int, io int[x])";

void mexStub1(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    double*     in0_ =0; /* W          */
    int         in1_;    /* M          */
    int         in2_;    /* T          */
    int         in3_;    /* K          */
    int         in4_;    /* fac        */
    int         in5_;    /* Ns         */
    int*        in6_ =0; /* l          */
    double*     in7_ =0; /* t          */
    double*     in8_ =0; /* a          */
    int         in9_;    /* Nt         */
    int         in10_;    /* subF       */
    int*        in11_ =0; /* iran       */
    double*     out0_=0; /* F          */
    mwSize      dim12_;   /* M          */
    mwSize      dim13_;   /* Nt         */
    mwSize      dim14_;   /* 2          */

    dim12_ = (mwSize) mxWrapGetScalar(prhs[12], &mw_err_txt_);
    dim13_ = (mwSize) mxWrapGetScalar(prhs[13], &mw_err_txt_);
    dim14_ = (mwSize) mxWrapGetScalar(prhs[14], &mw_err_txt_);

    if (mxGetM(prhs[11])*mxGetN(prhs[11]) != dim14_) {
        mw_err_txt_ = "Bad argument size: iran";        goto mw_err_label;
    }

    if (mxGetM(prhs[0])*mxGetN(prhs[0]) != 0) {
        in0_ = mxGetPr(prhs[0]);
    } else
        in0_ = NULL;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in3_ = (int) mxWrapGetScalar(prhs[3], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in4_ = (int) mxWrapGetScalar(prhs[4], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in5_ = (int) mxWrapGetScalar(prhs[5], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[6])*mxGetN(prhs[6]) != 0) {
        in6_ = mxWrapGetArray_int(prhs[6], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in6_ = NULL;
    if (mxGetM(prhs[7])*mxGetN(prhs[7]) != 0) {
        in7_ = mxGetPr(prhs[7]);
    } else
        in7_ = NULL;
    if (mxGetM(prhs[8])*mxGetN(prhs[8]) != 0) {
        in8_ = mxGetPr(prhs[8]);
    } else
        in8_ = NULL;
    in9_ = (int) mxWrapGetScalar(prhs[9], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in10_ = (int) mxWrapGetScalar(prhs[10], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[11])*mxGetN(prhs[11]) != 0) {
        in11_ = mxWrapGetArray_int(prhs[11], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in11_ = NULL;
    out0_ = (double*) mxMalloc(dim12_*dim13_*sizeof(double));
    if (mexprofrecord_)
        mexprofrecord_[1]++;
    spikemod(in0_, in1_, in2_, in3_, in4_, in5_, in6_, in7_, in8_, in9_, out0_, in10_, in11_);
    plhs[0] = mxCreateDoubleMatrix(dim12_, dim13_, mxREAL);
    mxWrapCopy_double(plhs[0], out0_, dim12_*dim13_);
    plhs[1] = mxCreateDoubleMatrix(dim14_, 1, mxREAL);
    mxWrapCopy_int(plhs[1], in11_, dim14_);

mw_err_label:
    if (in6_)  mxFree(in6_);
    if (out0_) mxFree(out0_);
    if (in11_)  mxFree(in11_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ---- spikefit.mw: 93 ----
 * fitonesp(double[] W, int M, int T, int K, int fac, output int[1] lb, output double[1] tb, output double[1] ab, int Nt, double[] Y, double eta, double tpad, output double[M, Nt] Fb, output double[1] Jbest, double[] nlps, int locflag, inout double[] srt);
 */
const char* stubids2_ = "fitonesp(i double[], i int, i int, i int, i int, o int[x], o double[x], o double[x], i int, i double[], i double, i double, o double[xx], o double[x], i double[], i int, io double[])";

void mexStub2(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    double*     in0_ =0; /* W          */
    int         in1_;    /* M          */
    int         in2_;    /* T          */
    int         in3_;    /* K          */
    int         in4_;    /* fac        */
    int         in5_;    /* Nt         */
    double*     in6_ =0; /* Y          */
    double      in7_;    /* eta        */
    double      in8_;    /* tpad       */
    double*     in9_ =0; /* nlps       */
    int         in10_;    /* locflag    */
    double*     in11_ =0; /* srt        */
    int*        out0_=0; /* lb         */
    double*     out1_=0; /* tb         */
    double*     out2_=0; /* ab         */
    double*     out3_=0; /* Fb         */
    double*     out4_=0; /* Jbest      */
    mwSize      dim12_;   /* 1          */
    mwSize      dim13_;   /* 1          */
    mwSize      dim14_;   /* 1          */
    mwSize      dim15_;   /* M          */
    mwSize      dim16_;   /* Nt         */
    mwSize      dim17_;   /* 1          */

    dim12_ = (mwSize) mxWrapGetScalar(prhs[12], &mw_err_txt_);
    dim13_ = (mwSize) mxWrapGetScalar(prhs[13], &mw_err_txt_);
    dim14_ = (mwSize) mxWrapGetScalar(prhs[14], &mw_err_txt_);
    dim15_ = (mwSize) mxWrapGetScalar(prhs[15], &mw_err_txt_);
    dim16_ = (mwSize) mxWrapGetScalar(prhs[16], &mw_err_txt_);
    dim17_ = (mwSize) mxWrapGetScalar(prhs[17], &mw_err_txt_);

    if (mxGetM(prhs[0])*mxGetN(prhs[0]) != 0) {
        in0_ = mxGetPr(prhs[0]);
    } else
        in0_ = NULL;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in3_ = (int) mxWrapGetScalar(prhs[3], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in4_ = (int) mxWrapGetScalar(prhs[4], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in5_ = (int) mxWrapGetScalar(prhs[5], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[6])*mxGetN(prhs[6]) != 0) {
        in6_ = mxGetPr(prhs[6]);
    } else
        in6_ = NULL;
    in7_ = (double) mxWrapGetScalar(prhs[7], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in8_ = (double) mxWrapGetScalar(prhs[8], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[9])*mxGetN(prhs[9]) != 0) {
        in9_ = mxGetPr(prhs[9]);
    } else
        in9_ = NULL;
    in10_ = (int) mxWrapGetScalar(prhs[10], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[11])*mxGetN(prhs[11]) != 0) {
        in11_ = mxWrapGetArray_double(prhs[11], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in11_ = NULL;
    out0_ = (int*) mxMalloc(dim12_*sizeof(int));
    out1_ = (double*) mxMalloc(dim13_*sizeof(double));
    out2_ = (double*) mxMalloc(dim14_*sizeof(double));
    out3_ = (double*) mxMalloc(dim15_*dim16_*sizeof(double));
    out4_ = (double*) mxMalloc(dim17_*sizeof(double));
    if (mexprofrecord_)
        mexprofrecord_[2]++;
    fitonesp(in0_, in1_, in2_, in3_, in4_, out0_, out1_, out2_, in5_, in6_, in7_, in8_, out3_, out4_, in9_, in10_, in11_);
    plhs[0] = mxCreateDoubleMatrix(dim12_, 1, mxREAL);
    mxWrapCopy_int(plhs[0], out0_, dim12_);
    plhs[1] = mxCreateDoubleMatrix(dim13_, 1, mxREAL);
    mxWrapCopy_double(plhs[1], out1_, dim13_);
    plhs[2] = mxCreateDoubleMatrix(dim14_, 1, mxREAL);
    mxWrapCopy_double(plhs[2], out2_, dim14_);
    plhs[3] = mxCreateDoubleMatrix(dim15_, dim16_, mxREAL);
    mxWrapCopy_double(plhs[3], out3_, dim15_*dim16_);
    plhs[4] = mxCreateDoubleMatrix(dim17_, 1, mxREAL);
    mxWrapCopy_double(plhs[4], out4_, dim17_);
    plhs[5] = mxCreateDoubleMatrix(mxGetM(prhs[11]), mxGetN(prhs[11]), mxREAL);
    mxWrapCopy_double(plhs[5], in11_, mxGetM(prhs[11])*mxGetN(prhs[11]));

mw_err_label:
    if (out0_) mxFree(out0_);
    if (out1_) mxFree(out1_);
    if (out2_) mxFree(out2_);
    if (out3_) mxFree(out3_);
    if (out4_) mxFree(out4_);
    if (in11_)  mxFree(in11_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ---- spikefit.mw: 168 ----
 * multifitgreedy(double[] W, int M, int T, int K, int fac, output int[1, Nc] Ns, output int[maxNs, Nc] l, output double[maxNs, Nc] t, output double[maxNs, Nc] a, int[] Tc, int Nc, double[] Y, double eta, double tpad, int maxNs, int 1, output double[nrJ, Nc] Jhist, output double[M, Ttot] R, double[] nlps, int locflag);
 */
const char* stubids3_ = "multifitgreedy(i double[], i int, i int, i int, i int, o int[xx], o int[xx], o double[xx], o double[xx], i int[], i int, i double[], i double, i double, i int, i int, o double[xx], o double[xx], i double[], i int)";

void mexStub3(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    double*     in0_ =0; /* W          */
    int         in1_;    /* M          */
    int         in2_;    /* T          */
    int         in3_;    /* K          */
    int         in4_;    /* fac        */
    int*        in5_ =0; /* Tc         */
    int         in6_;    /* Nc         */
    double*     in7_ =0; /* Y          */
    double      in8_;    /* eta        */
    double      in9_;    /* tpad       */
    int         in10_;    /* maxNs      */
    int         in11_;    /* 1          */
    double*     in12_ =0; /* nlps       */
    int         in13_;    /* locflag    */
    int*        out0_=0; /* Ns         */
    int*        out1_=0; /* l          */
    double*     out2_=0; /* t          */
    double*     out3_=0; /* a          */
    double*     out4_=0; /* Jhist      */
    double*     out5_=0; /* R          */
    mwSize      dim14_;   /* 1          */
    mwSize      dim15_;   /* Nc         */
    mwSize      dim16_;   /* maxNs      */
    mwSize      dim17_;   /* Nc         */
    mwSize      dim18_;   /* maxNs      */
    mwSize      dim19_;   /* Nc         */
    mwSize      dim20_;   /* maxNs      */
    mwSize      dim21_;   /* Nc         */
    mwSize      dim22_;   /* nrJ        */
    mwSize      dim23_;   /* Nc         */
    mwSize      dim24_;   /* M          */
    mwSize      dim25_;   /* Ttot       */

    dim14_ = (mwSize) mxWrapGetScalar(prhs[14], &mw_err_txt_);
    dim15_ = (mwSize) mxWrapGetScalar(prhs[15], &mw_err_txt_);
    dim16_ = (mwSize) mxWrapGetScalar(prhs[16], &mw_err_txt_);
    dim17_ = (mwSize) mxWrapGetScalar(prhs[17], &mw_err_txt_);
    dim18_ = (mwSize) mxWrapGetScalar(prhs[18], &mw_err_txt_);
    dim19_ = (mwSize) mxWrapGetScalar(prhs[19], &mw_err_txt_);
    dim20_ = (mwSize) mxWrapGetScalar(prhs[20], &mw_err_txt_);
    dim21_ = (mwSize) mxWrapGetScalar(prhs[21], &mw_err_txt_);
    dim22_ = (mwSize) mxWrapGetScalar(prhs[22], &mw_err_txt_);
    dim23_ = (mwSize) mxWrapGetScalar(prhs[23], &mw_err_txt_);
    dim24_ = (mwSize) mxWrapGetScalar(prhs[24], &mw_err_txt_);
    dim25_ = (mwSize) mxWrapGetScalar(prhs[25], &mw_err_txt_);

    if (mxGetM(prhs[0])*mxGetN(prhs[0]) != 0) {
        in0_ = mxGetPr(prhs[0]);
    } else
        in0_ = NULL;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in3_ = (int) mxWrapGetScalar(prhs[3], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in4_ = (int) mxWrapGetScalar(prhs[4], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[5])*mxGetN(prhs[5]) != 0) {
        in5_ = mxWrapGetArray_int(prhs[5], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in5_ = NULL;
    in6_ = (int) mxWrapGetScalar(prhs[6], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[7])*mxGetN(prhs[7]) != 0) {
        in7_ = mxGetPr(prhs[7]);
    } else
        in7_ = NULL;
    in8_ = (double) mxWrapGetScalar(prhs[8], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in9_ = (double) mxWrapGetScalar(prhs[9], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in10_ = (int) mxWrapGetScalar(prhs[10], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in11_ = (int) mxWrapGetScalar(prhs[11], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[12])*mxGetN(prhs[12]) != 0) {
        in12_ = mxGetPr(prhs[12]);
    } else
        in12_ = NULL;
    in13_ = (int) mxWrapGetScalar(prhs[13], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    out0_ = (int*) mxMalloc(dim14_*dim15_*sizeof(int));
    out1_ = (int*) mxMalloc(dim16_*dim17_*sizeof(int));
    out2_ = (double*) mxMalloc(dim18_*dim19_*sizeof(double));
    out3_ = (double*) mxMalloc(dim20_*dim21_*sizeof(double));
    out4_ = (double*) mxMalloc(dim22_*dim23_*sizeof(double));
    out5_ = (double*) mxMalloc(dim24_*dim25_*sizeof(double));
    if (mexprofrecord_)
        mexprofrecord_[3]++;
    multifitgreedy(in0_, in1_, in2_, in3_, in4_, out0_, out1_, out2_, out3_, in5_, in6_, in7_, in8_, in9_, in10_, in11_, out4_, out5_, in12_, in13_);
    plhs[0] = mxCreateDoubleMatrix(dim14_, dim15_, mxREAL);
    mxWrapCopy_int(plhs[0], out0_, dim14_*dim15_);
    plhs[1] = mxCreateDoubleMatrix(dim16_, dim17_, mxREAL);
    mxWrapCopy_int(plhs[1], out1_, dim16_*dim17_);
    plhs[2] = mxCreateDoubleMatrix(dim18_, dim19_, mxREAL);
    mxWrapCopy_double(plhs[2], out2_, dim18_*dim19_);
    plhs[3] = mxCreateDoubleMatrix(dim20_, dim21_, mxREAL);
    mxWrapCopy_double(plhs[3], out3_, dim20_*dim21_);
    plhs[4] = mxCreateDoubleMatrix(dim22_, dim23_, mxREAL);
    mxWrapCopy_double(plhs[4], out4_, dim22_*dim23_);
    plhs[5] = mxCreateDoubleMatrix(dim24_, dim25_, mxREAL);
    mxWrapCopy_double(plhs[5], out5_, dim24_*dim25_);

mw_err_label:
    if (out0_) mxFree(out0_);
    if (out1_) mxFree(out1_);
    if (out2_) mxFree(out2_);
    if (out3_) mxFree(out3_);
    if (in5_)  mxFree(in5_);
    if (out4_) mxFree(out4_);
    if (out5_) mxFree(out5_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ---- spikefit.mw: 171 ----
 * multifitgreedy(double[] W, int M, int T, int K, int fac, output int[1, Nc] Ns, output int[maxNs, Nc] l, output double[maxNs, Nc] t, output double[maxNs, Nc] a, int[] Tc, int Nc, double[] Y, double eta, double tpad, int maxNs, int 0, output double[nrJ, Nc] Jhist, inout double[] R, double[] nlps, int locflag);
 */
const char* stubids4_ = "multifitgreedy(i double[], i int, i int, i int, i int, o int[xx], o int[xx], o double[xx], o double[xx], i int[], i int, i double[], i double, i double, i int, i int, o double[xx], io double[], i double[], i int)";

void mexStub4(int nlhs, mxArray* plhs[],
              int nrhs, const mxArray* prhs[])
{
    const char* mw_err_txt_ = 0;
    double*     in0_ =0; /* W          */
    int         in1_;    /* M          */
    int         in2_;    /* T          */
    int         in3_;    /* K          */
    int         in4_;    /* fac        */
    int*        in5_ =0; /* Tc         */
    int         in6_;    /* Nc         */
    double*     in7_ =0; /* Y          */
    double      in8_;    /* eta        */
    double      in9_;    /* tpad       */
    int         in10_;    /* maxNs      */
    int         in11_;    /* 0          */
    double*     in12_ =0; /* R          */
    double*     in13_ =0; /* nlps       */
    int         in14_;    /* locflag    */
    int*        out0_=0; /* Ns         */
    int*        out1_=0; /* l          */
    double*     out2_=0; /* t          */
    double*     out3_=0; /* a          */
    double*     out4_=0; /* Jhist      */
    mwSize      dim15_;   /* 1          */
    mwSize      dim16_;   /* Nc         */
    mwSize      dim17_;   /* maxNs      */
    mwSize      dim18_;   /* Nc         */
    mwSize      dim19_;   /* maxNs      */
    mwSize      dim20_;   /* Nc         */
    mwSize      dim21_;   /* maxNs      */
    mwSize      dim22_;   /* Nc         */
    mwSize      dim23_;   /* nrJ        */
    mwSize      dim24_;   /* Nc         */

    dim15_ = (mwSize) mxWrapGetScalar(prhs[15], &mw_err_txt_);
    dim16_ = (mwSize) mxWrapGetScalar(prhs[16], &mw_err_txt_);
    dim17_ = (mwSize) mxWrapGetScalar(prhs[17], &mw_err_txt_);
    dim18_ = (mwSize) mxWrapGetScalar(prhs[18], &mw_err_txt_);
    dim19_ = (mwSize) mxWrapGetScalar(prhs[19], &mw_err_txt_);
    dim20_ = (mwSize) mxWrapGetScalar(prhs[20], &mw_err_txt_);
    dim21_ = (mwSize) mxWrapGetScalar(prhs[21], &mw_err_txt_);
    dim22_ = (mwSize) mxWrapGetScalar(prhs[22], &mw_err_txt_);
    dim23_ = (mwSize) mxWrapGetScalar(prhs[23], &mw_err_txt_);
    dim24_ = (mwSize) mxWrapGetScalar(prhs[24], &mw_err_txt_);

    if (mxGetM(prhs[0])*mxGetN(prhs[0]) != 0) {
        in0_ = mxGetPr(prhs[0]);
    } else
        in0_ = NULL;
    in1_ = (int) mxWrapGetScalar(prhs[1], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in2_ = (int) mxWrapGetScalar(prhs[2], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in3_ = (int) mxWrapGetScalar(prhs[3], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in4_ = (int) mxWrapGetScalar(prhs[4], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[5])*mxGetN(prhs[5]) != 0) {
        in5_ = mxWrapGetArray_int(prhs[5], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in5_ = NULL;
    in6_ = (int) mxWrapGetScalar(prhs[6], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[7])*mxGetN(prhs[7]) != 0) {
        in7_ = mxGetPr(prhs[7]);
    } else
        in7_ = NULL;
    in8_ = (double) mxWrapGetScalar(prhs[8], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in9_ = (double) mxWrapGetScalar(prhs[9], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in10_ = (int) mxWrapGetScalar(prhs[10], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    in11_ = (int) mxWrapGetScalar(prhs[11], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    if (mxGetM(prhs[12])*mxGetN(prhs[12]) != 0) {
        in12_ = mxWrapGetArray_double(prhs[12], &mw_err_txt_);
        if (mw_err_txt_)
            goto mw_err_label;
    } else
        in12_ = NULL;
    if (mxGetM(prhs[13])*mxGetN(prhs[13]) != 0) {
        in13_ = mxGetPr(prhs[13]);
    } else
        in13_ = NULL;
    in14_ = (int) mxWrapGetScalar(prhs[14], &mw_err_txt_);
    if (mw_err_txt_)
        goto mw_err_label;
    out0_ = (int*) mxMalloc(dim15_*dim16_*sizeof(int));
    out1_ = (int*) mxMalloc(dim17_*dim18_*sizeof(int));
    out2_ = (double*) mxMalloc(dim19_*dim20_*sizeof(double));
    out3_ = (double*) mxMalloc(dim21_*dim22_*sizeof(double));
    out4_ = (double*) mxMalloc(dim23_*dim24_*sizeof(double));
    if (mexprofrecord_)
        mexprofrecord_[4]++;
    multifitgreedy(in0_, in1_, in2_, in3_, in4_, out0_, out1_, out2_, out3_, in5_, in6_, in7_, in8_, in9_, in10_, in11_, out4_, in12_, in13_, in14_);
    plhs[0] = mxCreateDoubleMatrix(dim15_, dim16_, mxREAL);
    mxWrapCopy_int(plhs[0], out0_, dim15_*dim16_);
    plhs[1] = mxCreateDoubleMatrix(dim17_, dim18_, mxREAL);
    mxWrapCopy_int(plhs[1], out1_, dim17_*dim18_);
    plhs[2] = mxCreateDoubleMatrix(dim19_, dim20_, mxREAL);
    mxWrapCopy_double(plhs[2], out2_, dim19_*dim20_);
    plhs[3] = mxCreateDoubleMatrix(dim21_, dim22_, mxREAL);
    mxWrapCopy_double(plhs[3], out3_, dim21_*dim22_);
    plhs[4] = mxCreateDoubleMatrix(dim23_, dim24_, mxREAL);
    mxWrapCopy_double(plhs[4], out4_, dim23_*dim24_);
    plhs[5] = mxCreateDoubleMatrix(mxGetM(prhs[12]), mxGetN(prhs[12]), mxREAL);
    mxWrapCopy_double(plhs[5], in12_, mxGetM(prhs[12])*mxGetN(prhs[12]));

mw_err_label:
    if (out0_) mxFree(out0_);
    if (out1_) mxFree(out1_);
    if (out2_) mxFree(out2_);
    if (out3_) mxFree(out3_);
    if (in5_)  mxFree(in5_);
    if (out4_) mxFree(out4_);
    if (in12_)  mxFree(in12_);
    if (mw_err_txt_)
        mexErrMsgTxt(mw_err_txt_);
}

/* ----
 */
void mexFunction(int nlhs, mxArray* plhs[],
                 int nrhs, const mxArray* prhs[])
{
    char id[512];
    if (nrhs == 0) {
        mexPrintf("Mex function installed\n");
        return;
    }

    if (mxGetString(prhs[0], id, sizeof(id)) != 0)
        mexErrMsgTxt("Identifier should be a string");
    else if (strcmp(id, stubids1_) == 0)
        mexStub1(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, stubids2_) == 0)
        mexStub2(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, stubids3_) == 0)
        mexStub3(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, stubids4_) == 0)
        mexStub4(nlhs,plhs, nrhs-1,prhs+1);
    else if (strcmp(id, "*profile on*") == 0) {
        if (!mexprofrecord_) {
            mexprofrecord_ = (int*) malloc(5 * sizeof(int));
            mexLock();
        }
        memset(mexprofrecord_, 0, 5 * sizeof(int));
    } else if (strcmp(id, "*profile off*") == 0) {
        if (mexprofrecord_) {
            free(mexprofrecord_);
            mexUnlock();
        }
        mexprofrecord_ = NULL;
    } else if (strcmp(id, "*profile report*") == 0) {
        if (!mexprofrecord_)
            mexPrintf("Profiler inactive\n");
        mexPrintf("%d calls to spikefit.mw:45\n", mexprofrecord_[1]);
        mexPrintf("%d calls to spikefit.mw:93\n", mexprofrecord_[2]);
        mexPrintf("%d calls to spikefit.mw:168\n", mexprofrecord_[3]);
        mexPrintf("%d calls to spikefit.mw:171\n", mexprofrecord_[4]);
    } else if (strcmp(id, "*profile log*") == 0) {
        FILE* logfp;
        if (nrhs != 2 || mxGetString(prhs[1], id, sizeof(id)) != 0)
            mexErrMsgTxt("Must have two string arguments");
        logfp = fopen(id, "w+");
        if (!logfp)
            mexErrMsgTxt("Cannot open log for output");
        if (!mexprofrecord_)
            fprintf(logfp, "Profiler inactive\n");
        fprintf(logfp, "%d calls to spikefit.mw:45\n", mexprofrecord_[1]);
        fprintf(logfp, "%d calls to spikefit.mw:93\n", mexprofrecord_[2]);
        fprintf(logfp, "%d calls to spikefit.mw:168\n", mexprofrecord_[3]);
        fprintf(logfp, "%d calls to spikefit.mw:171\n", mexprofrecord_[4]);
        fclose(logfp);
    } else
        mexErrMsgTxt("Unknown identifier");
}

