/**
 *  @file   pack.c
 *  @author Ryosuke Tajima
 *  @license The MIT License
 *
 *  データのpack/unpackライブラリ。
 *
 *  書式文字列
 *	c - char
 *	h - short
 *      i - int
 *      l - long
 * 	f - float
 *	d - double
 *
 *	例）
 *  char    ca[4];
 *  float   fa[10];
 *
 *  size = pack_size ("c4 h f#", 10);
 *
 *  saveする場合:
 *  bp = pack_save (bp, "c4 h f#", ca, hv, fa, 10);
 *
 *  loadする場合:
 *  bp = pack_load (bp, "c4 h", ca, &hv);

 *  sizeを確かめる:
 *  if (hv > 10) error ();
 *
 *  bp = pack_load (bp, "f#", fa, hv);
 *
 */
#include "pack.h"

/**
 *  @brief  charをsaveする内部関数
 *  @param  p   save先へのポインタ
 *  @param  v   saveするデータ
 *  @retval saveされたデータの直後へのポインタ
 */
static INLINE char *
pack_save_char (char* p, char v)
{
    *p++ = v;
    return p;
}

/**
 *  @brief  charをloadする内部関数
 *  @param  p   save先へのポインタ
 *  @param  v   saveするデータ
 *  @retval saveされたデータの直後へのポインタ
 */
static INLINE char *
unpack_char (char *p, char *v)
{
    *v = *p++;
    return p;
}

/**
 *  @brief      short型をsaveする内部関数
 *  @param  p   save先へのポインタ
 *  @param  v   saveするデータ
 *  @param  e   1:エンディアン変換する
 *  @retval     saveされたデータの直後へのポインタ
 */
static INLINE char *
pack_save_short (char* p, short v, int e)
{
    char* w = (char *) &v;
    int i, n = sizeof(short);
    if (e) {
	/* エンディアン変換する */
	for (i=0; i<n; i++) {
	    *p++ = w[n-1-i];
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    *p++ = w[i];
	}
    }
    return p;
}

/**
 *  @brief      short型をloadする内部関数
 *  @param  p   load先へのポインタ
 *  @param  v   loadするデータへのポインタ
 *  @param  e   1:エンディアン変換する
 *  @retval     loadされたデータの直後へのポインタ
 */
static INLINE char *
pack_load_short (char *p, short *v, int e)
{
    char* w = (char *) v;
    int i, n = sizeof(short);
    if (e) {
	/* エンディアン変換する */
	for (i=0; i<n; i++) {
	    w[n-1-i] = *p++;
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    w[i] = *p++;
	}
    }
    return p;
}

/**
 *  @brief      int型をsaveする内部関数
 *  @param  p   save先へのポインタ
 *  @param  v   saveするデータ
 *  @param  e   1:エンディアン変換する
 *  @retval     saveされたデータの直後へのポインタ
 */
static INLINE char*
pack_save_int (char *p, int v, int e)
{
    char* w = (char *) &v;
    int i, n = sizeof(int);
    if (e) {
        /* エンディアン変換する */
	for (i=0; i<n; i++) {
	    *p++ = w[n-1-i];
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    *p++ = w[i];
	}
    }
    return p;
}

/**
 *  @brief      intをloadする内部関数
 *  @param  p   loadもと領域へのポインタ
 *  @param  v   データをloadする領域へのポインタ
 *  @param  e   1:エンディアン変換する
 *  @retval     loadされた領域の後へのポインタ
 */
static INLINE char *
pack_load_int (char *p, int *v, int e)
{
    char* w = (char *) v;
    int i, n = sizeof(int);
    if (e) {
        /* エンディアン変換する */
	for (i=0; i<n; i++) {
	    w[n-1-i] = *p++;
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    w[i] = *p++;
	}
    }
    return p;
}

/**
 *  @brief      long型をsaveする内部関数
 *  @param  p   save先へのポインタ
 *  @param  v   saveするデータ
 *  @param  e   1:エンディアン変換する
 *  @retval     saveされたデータの直後へのポインタ
 */
static INLINE char*
pack_save_long (char *p, long v, int e)
{
    char* w = (char *) &v;
    int i, n = sizeof(long);
    if (e) {
        /* エンディアン変換する */
	for (i=0; i<n; i++) {
	    *p++ = w[n-1-i];
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    *p++ = w[i];
	}
    }
    return p;
}

/**
 *  @brief      longをloadする内部関数
 *  @param  p   loadもと領域へのポインタ
 *  @param  v   データをloadする領域へのポインタ
 *  @param  e   1:エンディアン変換する
 *  @retval     loadされた領域の後へのポインタ
 */
static INLINE char *
pack_load_long (char *p, long *v, int e)
{
    char* w = (char *) v;
    int i, n = sizeof(long);
    if (e) {
        /* エンディアン変換する */
	for (i=0; i<n; i++) {
	    w[n-1-i] = *p++;
	}
    }
    else {
        /* エンディアン変換しない */
	for (i=0; i<n; i++) {
	    w[i] = *p++;
	}
    }
    return p;
}


static INLINE char *
pack_save_float (char *p, float v, int e)
{
    char * w = (char *) &v;
    if (e) {
        /* エンディアン変換する */
        *p++ = w[3];
        *p++ = w[2];
        *p++ = w[1];
        *p++ = w[0];
    }
    else {
        /* エンディアン変換しない */
        *p++ = w[0];
        *p++ = w[1];
        *p++ = w[2];
        *p++ = w[3];
    }
    return p;
}

/**
 *  @brief      floatをloadする内部関数
 *  @param  p   load元領域へのポインタ
 *  @param  v   データをloadする領域へのポインタ
 *  @param  e   1:エンディアン変換する
 *  @retval     loadされた領域の後へのポインタ
 */
static INLINE char *
pack_load_float (char *p, float *v, int e)
{
    char* w = (char *) v;
    if (e) {
        w[3] = *p++;
        w[2] = *p++;
        w[1] = *p++;
        w[0] = *p++;
    }
    else {
        w[0] = *p++;
        w[1] = *p++;
        w[2] = *p++;
        w[3] = *p++;
    }
    *v = *((float *) w);
    return p;
}

static INLINE char *
pack_save_double (char *p, double v, int e)
{
    char *w = (char *) &v;
    if (e) {
        *p++ = w[7];
        *p++ = w[6];
        *p++ = w[5];
        *p++ = w[4];
        *p++ = w[3];
        *p++ = w[2];
        *p++ = w[1];
        *p++ = w[0];
    }
    else {
        *p++ = w[0];
        *p++ = w[1];
        *p++ = w[2];
        *p++ = w[3];
        *p++ = w[4];
        *p++ = w[5];
        *p++ = w[6];
        *p++ = w[7];
    }
    return p;
}

static INLINE char *
pack_load_double (char *p, double *v, int e)
{
    char *w = (char *) v;
    if (e) {
        /* エンディアン変換する */
        w[7] = *p++;
        w[6] = *p++;
        w[5] = *p++;
        w[4] = *p++;
        w[3] = *p++;
        w[2] = *p++;
        w[1] = *p++;
        w[0] = *p++;
    }
    else {
        /* エンディアン変換しない */
        w[0] = *p++;
        w[1] = *p++;
        w[2] = *p++;
        w[3] = *p++;
        w[4] = *p++;
        w[5] = *p++;
        w[6] = *p++;
        w[7] = *p++;
    }
    *v = *((double *) w);
    return p;
}

static INLINE char*
pack_save_char_array (char *p, char *v, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_char (p, v[i]);
    }
    return p;
}

static INLINE char *
pack_save_short_array (char *p, short *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_short (p, v[i], e);
    }
    return p;
}

static INLINE char *
pack_array_int (char *p, int *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_int (p, v[i], e);
    }
    return p;
}

static INLINE char *
pack_array_long (char *p, long *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_long (p, v[i], e);
    }
    return p;
}

static INLINE char*
pack_array_float (char *p, float *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_float (p, v[i], e);
    }
    return p;
}

static INLINE char*
pack_array_double (char *p, double *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_save_double (p, v[i], e);
    }
    return p;
}

static INLINE char *
unpack_array_char (char *p, char *v, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        p = unpack_char (p, v++);
    }
    return p;
}

static INLINE char *
unpack_array_short (char *p, short *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_load_short (p, v++, e);
    }
    return p;
}

static INLINE char *
unpack_array_int (char *p, int *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++)
        p = pack_load_int (p, v++, e);
    return p;
}

static INLINE char *
unpack_array_long (char *p, long *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++)
        p = pack_load_long (p, v++, e);
    return p;
}

static INLINE char *
unpack_array_float (char *p, float *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++)
        p = pack_load_float (p, v++, e);
    return p;
}

static INLINE char *
unpack_array_double (char *p, double *v, int n, int e)
{
    int i;
    for (i = 0; i < n; i++) {
        p = pack_load_double (p, v++, e);
    }
    return p;
}

/**
 * @ingroup pack
 * @brief   書式文字列が表すデータ領域のサイズを返す。
 * @param   format  書式文字列
 * @param   ...     saveするデータの配列長の可変引数('#'で与えられる部分)
 * @retval  データ領域のサイズ
 */
int pack_size (char *format, ...)
{
    char *fp, *np;
    int total = 0;
    int size;
    va_list args;

    va_start (args, format);

    fp = format;
    while (*fp != '\0') {
        if (*fp == 'c') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(char);
            continue;
        }
        if (*fp == 'h') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(short);
            continue;
        }
        if (*fp == 'i') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(int);
            continue;
        }
        if (*fp == 'l') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(long);
            continue;
        }
        if (*fp == 'f') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(float);
            continue;
        }
        if (*fp == 'd') {
            fp++;
            if (*fp == '#') {
                fp++;
                size = va_arg (args, int);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np == fp) {
                    size = 1;
                }
                else {
                    fp = np;
                }
            }
            total += size * sizeof(double);
            continue;
        }
        fp++;
    }
    va_end (args);
    return total;
}

/**
 *  @ingroup pack
 *  @brief  書式文字列 formatに従ってbufferにデータをパックする
 *  @param  buffer  データ領域の先頭へのポインタ
 *  @param  format  書式文字列
 *  @param  ...     saveする変数列（可変引数）
 *  @retval buffer内にsaveされたデータの直後へのポインタ
 */
char* pack_save (char *buffer, char *format, ...)
{
    char *fp, *bp, *np;
    int size;
    int endian = 0;
    va_list args;

    va_start (args, format);
    fp = format;
    bp = buffer;

    while (*fp != '\0') {
        if (*fp == '!') {
            /* エンディアン変換を行う */
            fp++;
            endian = 1;
            continue;
        }
        if (*fp == 'c') {
            char* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, char *);
                size = va_arg (args, int);
                bp = pack_save_char_array (bp, data, size);
            }
            else {
                size = strtol (fp, &np, 10);
                if (np != fp) {
                    bp = pack_save_char_array (bp, va_arg (args, char *), size);
                    fp = np;
                }
                else {
                    bp = pack_save_char (bp, va_arg (args, int));
                }
            }
            continue;
        }
        if (*fp == 'h') {
            short* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, short *);
                size = va_arg (args, int);
                bp = pack_save_short_array (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_save_short (bp, va_arg (args, int), endian);
                }
                else {
                    bp = pack_save_short_array (bp, va_arg (args, short *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'i') {
            int* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, int *);
                size = va_arg (args, int);
                bp = pack_array_int (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_save_int (bp, va_arg (args, int), endian);
                }
                else {
                    bp = pack_array_int (bp, va_arg (args, int*), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'l') {
            long* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, long *);
                size = va_arg (args, int);
                bp = pack_array_long (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_save_long (bp, va_arg (args, int), endian);
                }
                else {
                    bp = pack_array_long (bp, va_arg (args, long *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'f') {
            float* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, float *);
                size = va_arg (args, int);
                bp = pack_array_float (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_save_float (bp, va_arg (args, double), endian);
                }
                else {
                    bp = pack_array_float (bp, va_arg (args, float *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'd') {
            double* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, double *);
                size = va_arg (args, int);
                bp = pack_array_double (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_save_double (bp, va_arg (args, double), endian);
                }
                else {
                    bp = pack_array_double (bp, va_arg (args, double *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        fp++;
    }
    va_end (args);
    return bp;
}

/**
 *  @ingroup pack
 *  @brief  書式文字列に従ってbufferから変数へデータをloadする。
 *  @param  buffer  データ領域の先頭へのポインタ
 *  @param  format  書式文字列
 *  @param  ...     loadする変数列（可変引数）
 *  @retval buffer内からloadされた領域の直後へのポインタ
 */
char* pack_load (char *buffer, char *format, ...)
{
    char *fp, *np, *bp;
    int size;
    int endian = 0;
    va_list args;

    va_start (args, format);
    fp = format;
    bp = buffer;
    while (*fp != '\0') {
        if (*fp == '!') {
            /* エンディアン変換を行う */
            fp++;
            endian = 1;
            continue;
        }
        if (*fp == 'c') {
            char* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, char *);
                size = va_arg (args, int);
                bp = unpack_array_char (bp, data, size);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = unpack_char (bp, va_arg (args, char *));
                }
                else {
                    bp = unpack_array_char (bp, va_arg (args, char *), size);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'h') {
            short* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, short *);
                size = va_arg (args, int);
                bp = unpack_array_short (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_load_short (bp, va_arg (args, short *), endian);
                }
                else {
                    bp = unpack_array_short (bp, va_arg (args, short *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'i') {
            int* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, int*);
                size = va_arg (args, int);
                bp = unpack_array_int (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_load_int (bp, va_arg (args, int*), endian);
                }
                else {
                    bp = unpack_array_int (bp, va_arg (args, int*), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'l') {
            long* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, long *);
                size = va_arg (args, int);
                bp = unpack_array_long (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_load_long (bp, va_arg (args, long *), endian);
                }
                else {
                    bp = unpack_array_long (bp, va_arg (args, long *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'f') {
            float* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, float *);
                size = va_arg (args, int);
                bp = unpack_array_float (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_load_float (bp, va_arg (args, float *), endian);
                }
                else {
                    bp = unpack_array_float (bp, va_arg (args, float *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        if (*fp == 'd') {
            double* data;
            fp++;
            if (*fp == '#') {
                fp++;
                data = va_arg (args, double *);
                size = va_arg (args, int);
                bp = unpack_array_double (bp, data, size, endian);
            }
            else {
                size = strtol (fp, &np, 10);
                if (fp == np) {
                    bp = pack_load_double (bp, va_arg (args, double *), endian);
                }
                else {
                    bp = unpack_array_double (bp, va_arg (args, double *), size, endian);
                    fp = np;
                }
            }
            continue;
        }
        fp++;
    }
    va_end (args);
    return bp;
}
