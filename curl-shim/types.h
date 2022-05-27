#pragma once

typedef struct CURL CURL;

typedef enum {
    CURL_LAST
} CURLcode;

typedef enum {
    CURLOPT_LASTENTRY
} CURLoption;

typedef enum {
    CURLINFO_NONE
} CURLINFO;

#define CURLINFO_STRING   0x100000
#define CURLINFO_LONG     0x200000
#define CURLINFO_DOUBLE   0x300000
#define CURLINFO_SLIST    0x400000
#define CURLINFO_SOCKET   0x500000
#define CURLINFO_MASK     0x0fffff
#define CURLINFO_TYPEMASK 0xf00000