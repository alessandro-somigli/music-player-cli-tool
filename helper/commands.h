#include <stdbool.h>

#include "../lib/string.h"
#include "../lib/timestamp.h"
#include "../lib/err.h"

void com_play_song(String _name);
void com_play_list(String _name, bool _mix);

void com_query_song(String _qname, bool _show, bool _play, bool _mix, Timestamp _mind, Timestamp _maxd);
void com_query_list(String _qname, bool _show, bool _play, bool _mix);

void com_add_song(String* _names, int _inames, String* _paths, int _ipaths);
void com_add_list(String* _names, int _inames);

void com_rem_song(String* _names, int _inames);
void com_rem_list(String* _names, int _inames);

void com_ins(String* _pnames, int _ipnames, String* _snames, int _isnames);
void com_auto(String _path);

void com_man();
