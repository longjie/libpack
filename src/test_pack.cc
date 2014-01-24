#include <gtest/gtest.h>
#include "pack.h"

char buff[1024];

TEST(pack, save_char) {
    char a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    pack_save (buff, (char*)"c10", a);
    pack_load (buff, (char*)"c10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

TEST(pack, save_short) {
    short a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {};

    /* エンディアン変換なし */
    pack_save (buff, (char*)"h10", a);
    pack_load (buff, (char*)"h10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
}

TEST(pack, save_int) {
    int a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {}, c[10] = {};

    /* エンディアン変換なし */
    pack_save (buff, (char*)"i10", a);
    pack_load (buff, (char*)"i10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    pack_save (buff, (char*)"!i10", a);
    pack_load (buff, (char*)"!i10", c);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], c[i]);
    }
}

TEST(pack, save_long) {
    long a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {}, c[10] = {};

    /* エンディアン変換なし */
    pack_save (buff, (char*)"l10", a);
    pack_load (buff, (char*)"l10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    pack_save (buff, (char*)"!l10", a);
    pack_load (buff, (char*)"!l10", c);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], c[i]);
    }
}

TEST(pack, save_float) {
    float a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {}, c[10] = {};

    /* エンディアン変換なし */
    pack_save (buff, (char*)"f10", a);
    pack_load (buff, (char*)"f10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    pack_save (buff, (char*)"f10", a);
    pack_load (buff, (char*)"f10", c);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], c[i]);
    }
}

TEST(pack, save_double) {
    double a[10] = {1,2,3,4,5,6,7,8,9,10}, b[10] = {}, c[10] = {};

    /* エンディアン変換なし */
    pack_save (buff, (char*)"d10", a);
    pack_load (buff, (char*)"d10", b);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], b[i]);
    }
    /* エンディアン変換あり */
    pack_save (buff, (char*)"!d10", a);
    pack_load (buff, (char*)"!d10", c);
    for (int i=0; i<10; i++) {
	EXPECT_EQ(a[i], c[i]);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
