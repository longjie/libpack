#include <gtest/gtest.h>
#include "pack.h"

/* save/load用のバッファ */
char buff[1024];

/* tailポインタ*/
char *tail;

void clear_buff (void)
{
    memset (buff, 0, sizeof(buff));
}

/* char単独変数のsave/load */
TEST(pack, save_char_single) {
    char a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    clear_buff();
    /* char単独変数のsave */
    tail = pack_save (buff, (char*)"cc ccc ccccc", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10], tail);
    /* char単独変数のload */
    tail = pack_load (buff, (char*)"c cc cc ccccc", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7], &b[8], &b[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* char配列変数のsave/load */
TEST(pack, save_char_array) {
    char a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    clear_buff();
    /*char配列変数のsave */
    tail = pack_save (buff, (char*)"c10", a);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10], tail);
    /*char配列変数のload */
    tail = pack_load (buff, (char*)"c10", b);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* short単独変数のsave/load */
TEST(pack, test_short_single) {
    short a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    /* エンディアン変換なし */
    clear_buff();
    /* short単独変数のsave */
    tail = pack_save (buff, (char*)"hh hhh hhhhh", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(short)], tail);
    /* short単独変数のload */
    tail = pack_load (buff, (char*)"h hh hh hhhhh", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7], &b[8], &b[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(short)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    clear_buff();
    /* short単独変数のsave */
    tail = pack_save (buff, (char*)"!hh hhh hhhhh", a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(short)], tail);
    /* short単独変数のload */
    tail = pack_load (buff, (char*)"!h hh hh hhhhh", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7], &b[8], &b[9]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(short)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* short配列変数のsave/load */
TEST(pack, save_short_array) {
    short a0[10] = {1,2,3,4,5,6,7,8,9,10}, a1[10] = {1,2,3,4,5,6,7,8,9,10}, a2[10] = {1,2,3,4,5,6,7,8,9,10};
    short b0[10] = {}, b1[10] = {}, b2[10] = {};

    /* エンディアン変換なし */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"h10 h10h10", a0, a1, a2);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[30*sizeof(short)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"h10h10 h10", b0, b1, b2);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[30*sizeof(short)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a0[i], b0[i]);
	EXPECT_EQ(a1[i], b1[i]);
	EXPECT_EQ(a2[i], b2[i]);
    }
    /* エンディアン変換あり */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"!h10 h10h10", a0, a1, a2);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[30*sizeof(short)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"!h10h10 h10", b0, b1, b2);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[30*sizeof(short)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a0[i], b0[i]);
	EXPECT_EQ(a1[i], b1[i]);
	EXPECT_EQ(a2[i], b2[i]);
    }
}

/* int変数のsave/load */
TEST(pack, test_int) {
    int a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    /* エンディアン変換なし */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"i i i i2 i2 i3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(int)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"i i i i2 i2 i3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(int)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"!i i i i2 i2 i3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(int)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"!i i i i2 i2 i3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(int)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* long変数のsave/load */
TEST(pack, test_long) {
    long a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    /* エンディアン変換なし */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"l l l l2 l2 l3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(long)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"l l l l2 l2 l3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(long)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"!l l l l2 l2 l3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(long)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"!l l l l2 l2 l3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(long)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* float変数のsave/load */
TEST(pack, test_float) {
    float a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    /* エンディアン変換なし */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"f f f f2 f2 f3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(float)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"f f f f2 f2 f3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(float)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    clear_buff();
     /* short単独変数のsave */
    tail = pack_save (buff, (char*)"!f f f f2 f2 f3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(float)], tail);
     /* short単独変数のload */
    tail = pack_load (buff, (char*)"!f f f f2 f2 f3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(float)], tail);
    /* 値のテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

/* double変数のsave/load */
TEST(pack, test_double) {
    double a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    clear_buff();
    /* save(エンディアン変換なし) */
    tail = pack_save (buff, (char*)"d d d d2 d2 d3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(double)], tail);
    /* load(エンディアン変換なし) */
    tail = pack_load (buff, (char*)"d d d d2 d2 d3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(double)], tail);
    /* positiveテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    clear_buff();
     /* save(エンディアン変換あり) */
    tail = pack_save (buff, (char*)"!d d d d2 d2 d3", a[0], a[1], a[2], &a[3], &a[5], &a[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(double)], tail);
     /* load(エンディアン変換あり) */
    tail = pack_load (buff, (char*)"!d d d d2 d2 d3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(double)], tail);
    /* positiveテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* load(エンディアン変換なし) */
    tail = pack_load (buff, (char*)"d d d d2 d2 d3", &b[0], &b[1], &b[2], &b[3], &b[5], &b[7]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*sizeof(double)], tail);
    /* negativeテスト */
    for (int i=0; i<10; i++) {
	EXPECT_NE(a[i], b[i]);
    }
}

/* 型を混ぜた変数のsave/load */
TEST(pack, mixed_1) {
    char ac[10] = {1,2,3,4,5,6,7,8,9,10}, bc[10] = {};
    short ah[10] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10}, bh[10] = {};
    long al[10] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10}, bl[10] = {};
    int ai[10] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10}, bi[10] = {};
    float af[10] = {1,2,3,4,5,6,7,8,9,10}, bf[10] = {};
    double ad[10] = {1,2,3,4,5,6,7,8,9,10}, bd[10] = {};

    clear_buff();
    /* save(エンディアン変換なし) */
    tail = pack_save (buff, (char*)"c c9 h h9 l l9 i i9 f f9 d d9", ac[0], &ac[1], ah[0], &ah[1], al[0], &al[1], ai[0], &ai[1], af[0], &af[1], ad[0], &ad[1]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*(sizeof(char)+sizeof(short)+sizeof(long)+sizeof(int)+sizeof(float)+sizeof(double))], tail);
    /* load(エンディアン変換なし) */
    tail = pack_load (buff, (char*)"c c9 h h9 l l9 i i9 f f9 d d9", &bc[0], &bc[1], &bh[0], &bh[1], &bl[0], &bl[1], &bi[0], &bi[1], &bf[0], &bf[1], &bd[0], &bd[1]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*(sizeof(char)+sizeof(short)+sizeof(long)+sizeof(int)+sizeof(float)+sizeof(double))], tail);
    /* positiveテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(ac[i], bc[i]);
	EXPECT_EQ(ah[i], bh[i]);
	EXPECT_EQ(al[i], bl[i]);
	EXPECT_EQ(ai[i], bi[i]);
	EXPECT_EQ(af[i], bf[i]);
	EXPECT_EQ(ad[i], bd[i]);
    }
    clear_buff();
    /* save(エンディアン変換あり) */
    tail = pack_save (buff, (char*)"!c c9 h h9 l l9 i i9 f f9 d d9", ac[0], &ac[1], ah[0], &ah[1], al[0], &al[1], ai[0], &ai[1], af[0], &af[1], ad[0], &ad[1]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*(sizeof(char)+sizeof(short)+sizeof(long)+sizeof(int)+sizeof(float)+sizeof(double))], tail);
    /* load(エンディアン変換あり) */
    tail = pack_load (buff, (char*)"!c c9 h h9 l l9 i i9 f f9 d d9", &bc[0], &bc[1], &bh[0], &bh[1], &bl[0], &bl[1], &bi[0], &bi[1], &bf[0], &bf[1], &bd[0], &bd[1]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*(sizeof(char)+sizeof(short)+sizeof(long)+sizeof(int)+sizeof(float)+sizeof(double))], tail);
    /* positiveテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(ac[i], bc[i]);
	EXPECT_EQ(ah[i], bh[i]);
	EXPECT_EQ(al[i], bl[i]);
	EXPECT_EQ(ai[i], bi[i]);
	EXPECT_EQ(af[i], bf[i]);
	EXPECT_EQ(ad[i], bd[i]);
    }
    /* load(エンディアン変換なし) */
    tail = pack_load (buff, (char*)"c c9 h h9 l l9 i i9 f f9 d d9", &bc[0], &bc[1], &bh[0], &bh[1], &bl[0], &bl[1], &bi[0], &bi[1], &bf[0], &bf[1], &bd[0], &bd[1]);
    /* tailポインタのテスト */
    EXPECT_EQ(&buff[10*(sizeof(char)+sizeof(short)+sizeof(long)+sizeof(int)+sizeof(float)+sizeof(double))], tail);
    /* negativeテスト */
    for (int i=0; i<10; i++) {
	EXPECT_EQ(ac[i], bc[i]);
	EXPECT_NE(ah[i], bh[i]);
	EXPECT_NE(al[i], bl[i]);
	EXPECT_NE(ai[i], bi[i]);
	EXPECT_NE(af[i], bf[i]);
	EXPECT_NE(ad[i], bd[i]);
    }
} 

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
