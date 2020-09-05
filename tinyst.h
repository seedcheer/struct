#ifndef TINY_ST_H
#define TINY_ST_H
#include <stdio.h>
#include <arpa/inet.h>

#define HTONX(VAR, SIZE)    \
    if ((SIZE) == 2) {      \
        VAR = htons(VAR);   \
    } else if ((SIZE) == 4) {   \
        VAR = htonl(VAR);       \
    }                           \

#define NTOHX(VAR, SIZE)    \
    if ((SIZE) == 2) {      \
        VAR = ntohs(VAR);   \
    } else if ((SIZE) == 4) {   \
        VAR = ntohl(VAR);       \
    }

#define FIELD_VAR(TYPE, NAME)           TYPE NAME;
#define FIELD_ARRAY(TYPE, NAME, DIM)    TYPE NAME[DIM];

#define HTON_PROC_VAR(TYPE, NAME)  HTONX(ptr->NAME, sizeof(TYPE))
#define HTON_PROC_ARRAY(TYPE, NAME, DIM)    \
    if (sizeof(TYPE) > 1) {                 \
        int i;                              \
        for (i = 0; i < DIM; i++) {         \
            HTONX(ptr->NAME[i], sizeof(TYPE))   \
        }                                       \
    }

#define NTOH_PROC_VAR(TYPE, NAME)  NTOHX(ptr->NAME, sizeof(TYPE))
#define NTOH_PROC_ARRAY(TYPE, NAME, DIM)    \
    if (sizeof(TYPE) > 1) {                 \
        int i;                              \
        for (i = 0; i < DIM; i++) {         \
            NTOHX(ptr->NAME[i], sizeof(TYPE))   \
        }                                       \
    }

#define HTON_PROCESS_PACK(S)    \
    S(HTON_PROC_VAR, HTON_PROC_ARRAY)

#define NTOH_PROCESS_PACK(S)    \
    S(NTOH_PROC_VAR, NTOH_PROC_ARRAY)

#define TINY_ST_FUNC(S)     \
void S##_hton(struct S *ptr)    \
    HTON_PROCESS_PACK(S)        \
                                \
void S##_ntoh(struct S *ptr)    \
    NTOH_PROCESS_PACK(S)

#define TINY_ST_FMT(S)      \
    struct S S(FIELD_VAR, FIELD_ARRAY)

#define TINY_ST_ALL(S)      \
    TINY_ST_FMT(S);                \
    TINY_ST_FUNC(S)

#endif
