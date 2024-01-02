
#ifndef DB_H
#define DB_H

#include "../lib/sqlite/sqlite3.h"
#include "../lib/string.h"

#define DB_PATH "db/"
#define DB_NAME "db.db"
#define DB_FULLNAME DB_PATH DB_NAME

#define INIT_DB_QUERY                                                       \
    "CREATE TABLE IF NOT EXISTS Songs ("                                    \
    "song_id INTEGER PRIMARY KEY,"                                          \
    "name TEXT UNIQUE NOT NULL,"                                            \
    "duration INTEGER NOT NULL,"                                            \
    "file_path TEXT NOT NULL"                                               \
    ");"                                                                    \
    "CREATE TABLE IF NOT EXISTS Lists ("                                    \
    "list_id INTEGER PRIMARY KEY,"                                          \
    "name TEXT UNIQUE NOT NULL"                                             \
    ");"                                                                    \
    "CREATE TABLE IF NOT EXISTS SongLists ("                                \
    "list_id INTEGER,"                                                      \
    "song_id INTEGER,"                                                      \
    "PRIMARY KEY (list_id, song_id),"                                       \
    "FOREIGN KEY (list_id) REFERENCES Lists(list_id) ON DELETE CASCADE,"    \
    "FOREIGN KEY (song_id) REFERENCES Songs(song_id) ON DELETE CASCADE"     \
    ");"

#define N_SONGS_PARAMS      4
#define N_LISTS_PARAMS      2
#define N_SONGLISTS_PARAMS  2

#define I_SONGS_SONG_ID     0
#define I_SONGS_NAME        1
#define I_SONGS_DURATION    2
#define I_SONGS_FILE_PATH   3

#define I_LISTS_LIST_ID     0
#define I_LISTS_NAME        1

#define I_SONGLISTS_LIST_ID 0
#define I_SONGLISTS_SONG_ID 1

typedef struct {
    int rows;
    int cols;

    String** res;
    int res_len;
} QueryRes;

extern sqlite3* DB;

void db_connect();
void db_close();
QueryRes* db_query(const char* _query, QueryRes* _res);

QueryRes* init_query_res(int _res_init_size, int _cols);
void free_query_res(QueryRes* _res);

#endif
