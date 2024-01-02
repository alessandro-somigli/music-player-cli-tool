
typedef enum {
    PLAY    = 'p',
    SHOW    = 's',
    MIX     = 'x',
    NAME    = 'n',
    MIN_D   = 'm',
    MAX_D   = 'M'
} Flag;

Flag get_flag(char* _flag);

void song_parser(int argc, char* argv[]);
void list_parser(int argc, char* argv[]);

void query_song_parser(int argc, char* argv[]);
void query_list_parser(int argc, char* argv[]);

void add_song_parser(int argc, char* argv[]);
void add_list_parser(int argc, char* argv[]);

void rem_song_parser(int argc, char* argv[]);
void rem_list_parser(int argc, char* argv[]);

void ins_parser(int argc, char* argv[]);

void auto_parser(int argc, char* argv[]);