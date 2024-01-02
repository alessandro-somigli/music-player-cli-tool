#ifndef TIMESTAMP_H
#define TIMESTAMP_H

typedef struct {
    int sec;
    int min;
    int hr;
} Timestamp;

Timestamp get_timestamp(char* _str);

#endif