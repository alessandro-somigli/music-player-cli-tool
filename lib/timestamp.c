#include "timestamp.h"
#include "err.h"

Timestamp get_timestamp(char* _str) {
    Timestamp tm = { 0, 0, 0 };

    switch (sscanf(_str, "%d:%d:%d", &tm.hr, &tm.min, &tm.sec)) {
    case EOF:
    case 0:
        PRINTERR(stderr, "'%s' is not a valid date format\n", 1, _str);
    case 1:
        tm.sec = tm.hr;
        tm.min = 0;
        tm.hr = 0;
        break;
    case 2:
        tm.sec = tm.min;
        tm.min = tm.hr;
        tm.hr = 0;
        break;
    case 3:
        break;
    }

    if (tm.sec > 59 || tm.sec < 0) PRINTERR(stderr, "invalid timestamp has '%d' seconds\n", 1, tm.sec);
    if (tm.min > 59 || tm.min < 0) PRINTERR(stderr, "invalid timestamp has '%d' minutes\n", 1, tm.min);
    if (tm.hr > 23 || tm.hr < 0) PRINTERR(stderr, "invalid timestamp has '%d' hours\n", 1, tm.hr);

    return tm;
}
