#include <stdio.h>

static unsigned long rev(unsigned long v) {
    unsigned long s = 8 * sizeof(v); // bit size; must be power of 2
    unsigned long mask = ~0;
    while ((s >>= 1) > 0) {
        mask ^= (mask << s);
        v = ((v >> s) & mask) | ((v << s) & ~mask);
    }
    return v;
}


// 辅助理解 redis/dict.c/dictScan 游标v的变化方式
unsigned long t = 0;

int main(int argc, char *argv[]) {
    unsigned long m0 = 0b111;

    unsigned long v = 0;

    do
    {
    	printf("%lu\n", v);
    	v |= ~m0;
	    v = rev(v);
	    v++;
	    v = rev(v);
    } while (v != 0);
    

    printf("=============================================\n");

    do
    {
    	if (++t == 6)
    	{
    		m0 = 0b11111;
    	}
    	printf("%lu\n", v);
    	v |= ~m0;
	    v = rev(v);
	    v++;
	    v = rev(v);
    } while (v != 0);
}

/*
m0为 0b111
0
4
2
6
1
5
3
7

0
4
2
6
1
m0从此变为 0b11111
5      101
21   10101
13	 01101
29   11101

3	  011
19	10011
11	01011
27	11011

7	  111
23	10111
15	01111
31	11111
*/