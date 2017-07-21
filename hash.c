#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "message.h"


void hash() {
    unsigned long r[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

    unsigned long k[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};


    unsigned long h0 = 0x67452301;
    unsigned long h1 = 0xefcdab89;
    unsigned long h2 = 0x98badcfe;
    unsigned long h3 = 0x10325476;

    unsigned long a = h0;
    unsigned long b = h1;
    unsigned long c = h2;
    unsigned long d = h3;

    unsigned long f;
    unsigned long g;

    for (int i = 0; i < 64; i++) {
        if ( i < 16 ) {
            f = F(b,c,d);
            g = i;
        } else if (i < 32) {
            f = G(b,c,d);
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(b,c,d);
            g = (3 * i + 5) % 16;
        } else if (i < 64) {
            f = I(b,c,d);
            g = (7 * i) % 16;
        }
        unsigned long tmp = d;
        d = c;
        c = b;
        //b = b + left_rotate(a + f + k[i] + w[g], r[i]);
        a = tmp;
    }

}

unsigned long F(unsigned long b, unsigned long c, unsigned long d) {
    return ((b & c) | (~b & d));
}

unsigned long G(unsigned long b, unsigned long c, unsigned long d) {
    return ((b & d) | (c & ~d));
}

unsigned long H(unsigned long b, unsigned long c, unsigned long d) {
    return (b ^ c ^ d);
}

unsigned long I(unsigned long b, unsigned long c, unsigned long d) {
    return (c ^ (b | ~d));
}

unsigned long left_rotate(unsigned long n, unsigned long r) {
    return ((n << r) | (n >> (32 - r)));
}
