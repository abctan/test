//用于获取x的第n到第m位的值
#define GET_BITS(x, n, m)      (((unsigned int)(x) << (31 - (m))) >> ((31 - (m)) + (n)))

void de_copy(unsigned char *descLut, unsigned char *srcLut)
{
    unsigned short a = GET_BITS(*srcLut, 4, 7) | (*(srcLut + 1) << 4);
    unsigned short b = *(srcLut + 2) | (GET_BITS(*(srcLut + 3), 0, 3) << 8);
    printf("a = %d, b = %d\n", a, b);
    *descLut = GET_BITS(a, 0, 7);
    *(descLut + 1) = GET_BITS(a, 8, 11) | (GET_BITS(b, 0, 3) << 4);
    *(descLut + 2) = GET_BITS(b, 4, 11);
}


void cp_one_plane_data(unsigned char *leftLut, unsigned char *rightLut, unsigned char *lut, int multTableH)
{
    int signalNum = 241;
    int multNum = multTableH;

    unsigned char *left = leftLut;
    unsigned char *right = rightLut;
    int step;

    memcpy(lut, left, multNum / 10 * 16);  // cp 左边一段数据
    lut += multNum / 10 * 16;
    left += multNum / 10 * 16;

    right++;
    for (int i = 0; i < multNum / 10 * 5; i++) {    // cp 右边一段数据
        if ((i + 1) % 5 == 0) {
            step = 1;
        } else {
            step = 0;
        }
        de_copy_step(lut, right, step);
        if (step == 1) {
            *(lut + 3) = 0; // 最后一个字节填0
            lut += 3 + 1;
            right += 3 + 1;
        } else {
            lut += 3;
            right += 3;
        }

        // 处理最后一行数据
        memset(lut, 0, 16); // 先把最后一行清0
        de_copy_step(lut, right, 0);
    }

}
