#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../lib/timestamp.h"
#include "../lib/string.h"
#include "../lib/err.h"

#include "database.h"

void com_play_song(String _name) {
    QueryRes* res = init_query_res(1, N_SONGS_PARAMS);
    
    char query[256];
    sprintf(query, "SELECT * FROM Songs WHERE Songs.name = '%s';", _name.str);

    db_query(query, res);

    if (res->rows == 0) PRINTERR(stderr, "no such song was found\n", 1);

    int duration = atoi(res->res[0][I_SONGS_DURATION].str);
    String path = res->res[0][I_SONGS_FILE_PATH];

    free_query_res(res);

    // put song in play stack
    // open player
}

void com_play_list(String _name, bool _mix) {
    // query db to get all songs in playlist
    // put songs in play stack
    // open player
}

void com_query_song(String _qname, bool _show, bool _play, bool _mix, Timestamp _mind, Timestamp _maxd) {
    // query db to get all songs that match query
    // put songs in play stack
    // open player
}

void com_query_list(String _qname, bool _show, bool _play, bool _mix) {
    // query db to get all playlists that match query
    // put all songs of matching playlists in play stack
    // open player
}

void com_add_song(String* _names, int _inames, String* _paths, int _ipaths) {
    // copy all files from specified path to local path
    // query db to add all new songs
}

void com_add_list(String* _names, int _inames) {
    // query db to add all new playlists
}

void com_rem_song(String* _names, int _inames) {
    // query db to remove all songs
}

void com_rem_list(String* _names, int _inames) {
    // query db to remove all playlists
}

void com_ins(String* _pnames, int _ipnames, String* _snames, int _isnames) {
    // query db to insert every song in every playlist
}

void com_auto(String _path) {
    // get all files in specified path and copy them to local path
    // 
}

void com_man() {
    printf("flags:\n"
        "-x: mix a set of songs before playing\n"
        "-s: show the results of a query on screen\n"
        "-p: play the results of a query\n"
        "-n: name to query a set of songs\n"
        "-m & -M: query specifiers for min duration and max duration of a song\n\n"

        "commands:\n"
        " - song (song-name) -x\n"
        "   plays a specific song.\n\n"

        " - list (playlist-name) -x\n"
        "   plays a specific playlist.\n\n"

        " - qsong -s -p -x -n (song-name) -m (min-duration) -M (max-duration)\n"
        "   makes a query to find all the songs that match the query params.\n\n"

        " - qlist -s -p -x -n (playlist-name)\n"
        "   makes a query to find all the playlists that match the query params.\n\n"

        " - song+ (song-name-1) (path-name-1) (song-name-2) (path-name-2) ...\n"
        "   creates a number of songs given the new name and a filepath (the media file gets copied).\n\n"

        " - list+ (playlist-name-1) (playlist-name-2) ...\n"
        "   creates a number of playlists.\n\n"

        " - song- (song-name-1) (song-name-2) ...\n"
        "   delete some songs and their media files.\n\n"

        " - list- (playlist-name-1) (playlist-name-2) ...\n"
        "   delete some playlists.\n\n"

        " - ins (playlist-name-1) (playlist-name-2) ... : (song-name-1) (song-name-2) ...\n"
        "   insert into various playlists all the specified songs (use the ' : ' separator to divide songs and playlists).\n\n"

        " - auto (optional-folder-path)\n"
        "   take all the files in the specified folder and make them into songs (the song name is derived from the file name).\n\n"
    );
}
