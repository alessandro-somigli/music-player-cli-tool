#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper/commands.h"
#include "helper/argparser.h"
#include "helper/database.h"

// api:
// mp song song-name 
// mp list playlist-name -x

// mp qsong -s -p -x -n name -m min-duration -M -max-duration
// mp qlist -s -p -x -n name

// mp song+ song-name-1 path-name-1 song-name-2 path-name-2
// mp list+ playlist-name-1 playlist-name-2

// mp song- song-name-1 song-name-2
// mp list- playlist-name-1 playlist-name-2

// mp ins playlist-name-1 playlist-name-2 : song-name-1 song-name-2
// mp auto path

// mp man

int main(int argc, char* argv[]) {
    db_connect();

    db_query(INIT_DB_QUERY, NULL);
    
    if (argc < 2) PRINTERR(stderr, "type 'man' to get list of commands\n", 1);

    if (strcmp(argv[1], "song") == 0)
        song_parser(argc, argv);
    
    else if (strcmp(argv[1], "list") == 0)
        list_parser(argc, argv);
    
    else if (strcmp(argv[1], "qsong") == 0)
        query_song_parser(argc, argv);
    
    else if (strcmp(argv[1], "qlist") == 0)
        query_list_parser(argc, argv);
    
    else if (strcmp(argv[1], "song+") == 0)
        add_song_parser(argc, argv);
    
    else if (strcmp(argv[1], "list+") == 0)
        add_list_parser(argc, argv);
    
    else if (strcmp(argv[1], "song-") == 0)
        rem_song_parser(argc, argv);
    
    else if (strcmp(argv[1], "list-") == 0)
        rem_list_parser(argc, argv);
    
    else if (strcmp(argv[1], "ins") == 0)
        ins_parser(argc, argv);
    
    else if (strcmp(argv[1], "auto") == 0)
        auto_parser(argc, argv);
    
    else if (strcmp(argv[1], "man") == 0) {
        if (argc > 2) PRINTERR(stderr, "too many arguments\n", 1);
        
        com_man();
    }
    
    else PRINTERR(stderr, "command '%s' was not recognized\n", 1, argv[1]);

    db_close();

    return EXIT_SUCCESS;
}