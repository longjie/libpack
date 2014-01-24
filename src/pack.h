/**
 *	@file pack.h
 *  @defgroup pack
 *  @author Ryosuke Tajima
 *  @license The MIT License
 *
 *  packライブラリの関数宣言
 */
#ifndef __PACK_H__
#define __PACK_H__

#include <stdlib.h>
#include <stdarg.h>

#define INLINE inline

#ifdef __cplusplus
extern "C" {
#endif

int pack_size (char *format, ...);
char* pack_save (char *buffer, char *format, ...);
char* pack_load (char* self, char* format, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PACK_H__ */
