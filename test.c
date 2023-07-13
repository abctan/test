void de_copy(unsigned char *descLut, unsigned char *srcLut)
{
    unsigned short a = GET_BITS(*srcLut, 4, 7) | (*(srcLut + 1) << 4);
    unsigned short b = *(srcLut + 2) | (GET_BITS(*(srcLut + 3), 0, 3) << 8);
    printf("a = %d, b = %d\n", a, b);
    *descLut = GET_BITS(a, 0, 7);
    *(descLut + 1) = GET_BITS(a, 8, 11) | (GET_BITS(b, 0, 3) << 4);
    *(descLut + 2) = GET_BITS(b, 4, 11);
}
