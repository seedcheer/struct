#include <stdio.h>
#include <arpa/inet.h>
#include "tinyst.h"


#define foo(VAR, ARRAY)     \
{                           \
    VAR(uint8_t, id)        \
    VAR(int16_t, count)    \
    VAR(uint32_t, num)      \
    ARRAY(uint16_t, ts, 3)  \
}

TINY_ST_ALL(foo)

int main()
{
    struct foo foo;

    foo.id = 1;
    foo.count = 3;
    foo.num = 4;
    foo.ts[0] = 5;
    foo.ts[1] = 6;
    foo.ts[2] = 7;

    printf("id=0x%x count=0x%x num=0x%x ts[0] = 0x%x  ts[1] = 0x%x  ts[2] = 0x%x\n",
           foo.id, foo.count, foo.num, foo.ts[0], foo.ts[1], foo.ts[2]);
    foo_hton(&foo);
    printf("id=0x%x count=0x%x num=0x%x ts[0] = 0x%x  ts[1] = 0x%x  ts[2] = 0x%x\n",
           foo.id, foo.count, foo.num, foo.ts[0], foo.ts[1], foo.ts[2]);
    foo_ntoh(&foo);
    printf("id=0x%x count=0x%x num=0x%x ts[0] = 0x%x  ts[1] = 0x%x  ts[2] = 0x%x\n",
           foo.id, foo.count, foo.num, foo.ts[0], foo.ts[1], foo.ts[2]);

    return 0;
}

