#include <stdbool.h>
#include <malloc.h>

#include "database.h"

#include "../lib/string.h"
#include "../lib/err.h"

QueryRes* init_query_res(int _res_init_size, int _cols) {
    QueryRes* res = (QueryRes*)malloc(sizeof(QueryRes));

    if (res == NULL) PRINTERR(stderr, "query malloc failure\n", 2);

    res->cols = _cols;
    res->res_len = _res_init_size;
    res->rows = 0;
    res->res = (String**)malloc(sizeof(String*) * _res_init_size);

    if (res->res == NULL) PRINTERR(stderr, "query malloc failure\n", 2);

    for (int i=0; i<_res_init_size; i++) {
        res->res[i] = (String*)malloc(sizeof(String) * _cols);

        if (res->res[i] == NULL) PRINTERR(stderr, "query malloc failure\n", 2);

        for (int j=0; j<_cols; j++)
            DSTR(res->res[i][j], "");
    }

    return res;
}

void free_query_res(QueryRes* _res) {
    for (int i=0; i<_res->res_len; i++) {
        if (_res->res[i] == NULL) continue;

        for (int j=0; j<_res->cols; j++)
            free(_res->res[i][j].str);
    }

    free(_res->res);

    free(_res);
}

int query_callback(void* _res, int _ncol, char** _col_vals, char** _col_names) {
    QueryRes* res = (QueryRes*)_res;

    if (res->rows >= res->res_len) {
        String** tmp = (String**)realloc(res->res, sizeof(String*) * res->res_len * 2);

        if (tmp == NULL) PRINTERR(stderr, "query realloc failure\n", 2);
        else res->res = tmp;

        for (int i=0; i<res->res_len; i++)
            res->res[res->res_len + i] = NULL;
        
        res->res_len *= 2;
    }

    if (res->res[res->rows] == NULL) {
        res->res[res->rows] = (String*)malloc(sizeof(String) * res->cols);
        
        if (res->res[res->rows] == NULL) PRINTERR(stderr, "query malloc failure\n", 2);
    }
    
    for (int i=0; i<_ncol; i++)
        DSTR(res->res[res->rows][i], _col_vals[i]);

    res->rows += 1;

    return 0;
}

sqlite3* DB = NULL;

void db_connect() {
    int rc = sqlite3_open(DB_FULLNAME, &DB);
    
    // no need to sqlite_close(), PRINTERR exits the program.
    if (rc != SQLITE_OK) PRINTERR(stderr, "DB: %s\n", 2, sqlite3_errmsg(DB));
}

void db_close() {
    if (DB != NULL) sqlite3_close(DB);
}

QueryRes* db_query(const char* _query, QueryRes* _res) {
    if (DB == NULL) PRINTERR(stderr, "DB: DB not initialized", 2);

    char* err;
    int rc = sqlite3_exec(DB, _query, query_callback, _res, &err);

    // no need to sqlite_close(), PRINTERR exits the program.
    if (rc != SQLITE_OK) PRINTERR(stderr, "DB: %s\n", 2, err);

    return _res;
}
