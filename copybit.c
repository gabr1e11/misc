
#include <stdio.h>

void copy_bit(unsigned char *source, unsigned int sourceStartBit,
              unsigned char *target, unsigned int targetStartBit)
{
    unsigned char value = (source[sourceStartBit/8]>>(7-(sourceStartBit%8)))&0x1;
    unsigned char mask = 1<<(7-(targetStartBit%8));

    if (value == 0) { target[targetStartBit/8] &= ~mask; }
    else            { target[targetStartBit/8] |= mask;  }
}
void copy_bit_string(unsigned char *source, unsigned int sourceStartBit,
                     unsigned char *target, unsigned int targetStartBit,
                     unsigned int bitLength)
{
    unsigned int i;

    for (i=0; i<bitLength; ++i) {
        copy_bit(source, sourceStartBit++, target, targetStartBit++);
    }
}

int main()
{
    unsigned char s[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
    unsigned char t[8] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    int bs = 3, bt = 12, length = 19;

    copy_bit_string(s, bs, t, bt, length);

    printf("s: %02x%02x%02x%02x%02x%02x%02x%02x\n", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7]);
    printf("t: %02x%02x%02x%02x%02x%02x%02x%02x\n", t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);

    return 0;
}
