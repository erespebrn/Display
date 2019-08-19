#ifndef _CLOCK_H
#define _CLOCK_H
#include <String.h>
#include <WString.h>
#include <Display.h>
#include <DS3231.h>

class Clock
{
    private:
        enum DotsOn {OFF, ON};
        DotsOn mode = OFF;
        DS3231 rtc;
        Time t;
        Display secs[2];
        Display mins[2];
        Display hour[2];
        const int y = 10;
        int dots_array[8] = {12+(y+2)*40, 12+(y+3)*40, 12+(y+5)*40, 12+(y+6)*40,
                             26+(y+2)*40, 26+(y+3)*40, 26+(y+5)*40, 26+(y+6)*40};
        Display dot;
        int *pd;
        int i = 0;
        int t_s1 = -1;
        int t_s2 = -1;
        int t_min1 = -1;
        int t_min2 = -1;
        int t_hour1 = -1;
        int t_hour2 = -1;
        bool both_sec = false;
        bool both_min = false;
        bool both_hour = false;
        bool first_run = true;
        int * no_separator(const int & no);
        void seconds();
        void minutes();
        void hours();
    public:
        Clock();
        void show_time();
        void begin();
        void stop();
};

#endif
