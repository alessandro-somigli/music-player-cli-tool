#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../lib/string.h"
#include "../lib/err.h"
#include "../lib/timestamp.h"

#include "argparser.h"
#include "commands.h"

Flag get_flag(char* _flag) {
    if (_flag[0] != '-' || strlen(_flag) != 2) return -1;

    switch (_flag[1]) {
    case 'x': return MIX;
    case 'p': return PLAY;
    case 's': return SHOW;
    case 'n': return NAME;
    case 'm': return MIN_D;
    case 'M': return MAX_D;
    default: return -1;
    }
}

void song_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);
    if (argc > 3) PRINTERR(stderr, "too many arguments\n", 1);

    String name; SSTR(name, argv[2]);
    com_play_song(name);
}

void list_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);
    if (argc > 4) PRINTERR(stderr, "too many arguments\n", 1);

    String name; SSTR(name, argv[2]);
    bool mix = (argc > 3 && get_flag(argv[3]) == MIX)? true : false;

    com_play_list(name, mix);
}

void query_song_parser(int argc, char* argv[]) {
    if (argc > 11) PRINTERR(stderr, "too many arguments\n", 1);

    String nameq = STR("*");
    bool mix = false;
    bool play = false;
    bool show = false;
    Timestamp mind = { 0, 0, 0 };
    Timestamp maxd = { 23, 59, 59 };

    for (int i=2; i<argc; i++) {
        switch (get_flag(argv[i])) {
        case MIX:
            mix = true;
            break;
        case PLAY:
            play = true;
            break;
        case SHOW:
            show = true;
            break;
        case NAME: 
            i++;
            if (i < argc) SSTR(nameq, argv[i]);
            else PRINTERR(stderr, "'-%c' flag requires argument\n", 1, NAME);
            break;
        case MIN_D:
            i++;
            if (i < argc) mind = get_timestamp(argv[i]);
            else PRINTERR(stderr, "'-%c' flag requires argument\n", 1, MIN_D);
            break;
        case MAX_D:
            i++;
            if (i < argc) maxd = get_timestamp(argv[i]);
            else PRINTERR(stderr, "'-%c' flag requires argument\n", 1, MAX_D);
            break;
        case -1:
            PRINTERR(stderr, "flag '%s' is not recognized\n", 1, argv[i]);
        default:
            PRINTERR(stderr, "flag '%s' is not accepted by '%s' \n", 1, argv[i], argv[1]);
        }
    }

    com_query_song(nameq, show, play, mix, mind, maxd);
}

void query_list_parser(int argc, char* argv[]) {
    if (argc > 7) PRINTERR(stderr, "too many arguments\n", 1);

    String nameq = STR("*");
    bool mix = false;
    bool play = false;
    bool show = false;

    for (int i=2; i<argc; i++) {
        switch (get_flag(argv[i])) {
        case MIX:
            mix = true;
            break;
        case PLAY:
            play = true;
            break;
        case SHOW:
            show = true;
            break;
        case NAME: 
            i++;
            if (i < argc) SSTR(nameq, argv[i]);
            else PRINTERR(stderr, "'-%c' flag requires argument\n", 1, NAME);
            break;
        case -1:
            PRINTERR(stderr, "flag '%s' is not recognized\n", 1, argv[i]);
        default:
            PRINTERR(stderr, "flag '%s' is not accepted by '%s'\n", 1, argv[i], argv[1]);
        }
    }

    com_query_list(nameq, show, play, mix);
}

void add_song_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);

    String names[256];
    String paths[256];
    uint8_t inames = 0;
    uint8_t ipaths = 0;

    for (int i=2; i<argc; i+=2) {
        if (i+1 >= argc) PRINTERR(stderr, "song '%s' does not have a corresponding path\n", 1, argv[i]);

        SSTR(names[inames], argv[i]);
        SSTR(paths[ipaths], argv[i+1]);
        inames++;
        ipaths++;
    }

    com_add_song(names, inames, paths, ipaths);
}

void add_list_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);

    String names[256];
    uint8_t inames = 0;

    for (int i=2; i<argc; i++) {
        SSTR(names[inames], argv[i]);
        inames++;
    }

    com_add_list(names, inames);
}

void rem_song_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);

    String names[256];
    uint8_t inames = 0;

    for (int i=2; i<argc; i++) {
        SSTR(names[inames], argv[i]);
        inames++;
    }

    com_rem_song(names, inames);
}

void rem_list_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);

    String names[256];
    uint8_t inames = 0;

    for (int i=2; i<argc; i++) {
        SSTR(names[inames], argv[i]);
        inames++;
    }

    com_rem_list(names, inames);
}

void ins_parser(int argc, char* argv[]) {
    if (argc < 3) PRINTERR(stderr, "too few arguments\n", 1);

    String pnames[256];
    String snames[256];
    uint8_t ipnames = 0; // index playlist names
    uint8_t isnames = 0; // index song names

    for (int i=2; strcmp(argv[i], ":") != 0; i++) {
        // i starts from 0 but argc starts from 1, so increment before checking
        if (i+1 >= argc) PRINTERR(stderr, "no ' : ' separator found\n", 1);

        SSTR(pnames[ipnames], argv[i]);
        ipnames++;
    }

    if (ipnames+3 == argc) PRINTERR(stderr, "no songs after separator\n", 1);

    for (int i=ipnames+3; i<argc; i++) {
        SSTR(snames[isnames], argv[i]);
        isnames++;
    }

    com_ins(pnames, ipnames, snames, isnames);
}

void auto_parser(int argc, char* argv[]) {
    if (argc > 3) PRINTERR(stderr, "too many arguments\n", 1);

    String path;
    if (argc > 2) SSTR(path, argv[2]);
    else path = STR("./auto");
    
    com_auto(path);
}
