#include "windows_time.h"

win_time::win_time() 
{
    QueryPerformanceFrequency(&freq);
    st.QuadPart = ed.QuadPart = 0;
}

win_time::~win_time(){}

void win_time::start() 
{
    if (!QueryPerformanceCounter(&st)) 
    {
        std::cerr << "[ERROR]\n" << __func__ << std::endl;
        exit;
    }
}
void win_time::end() 
{
    if (!QueryPerformanceCounter(&ed)) 
    {
        std::cerr << "[ERROR]\n" << __func__ << std::endl;
        exit;
    }
}

double win_time::get_time_ms() const 
{
    return  static_cast<double>(ed.QuadPart - st.QuadPart) * 1e3 / freq.QuadPart;
}

double win_time::get_time_s() const 
{
    return  static_cast<double>(ed.QuadPart - st.QuadPart) * 1e6 / freq.QuadPart;
}

void win_time::reset() 
{
    QueryPerformanceFrequency(&freq);
    st.QuadPart = ed.QuadPart = 0;
}