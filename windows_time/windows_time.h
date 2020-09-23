#ifndef ___WINDOWS_TIME
#define ___WINDOWS_TIME

#include <Windows.h>
#include <iostream>

class win_time {
    LARGE_INTEGER freq;
    LARGE_INTEGER st, ed;

public:
    win_time();
    ~win_time();
    void start();
    void end();
    double get_time_ms() const;
    double get_time_s() const;
    void reset();
};
#endif //