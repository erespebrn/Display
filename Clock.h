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
        const uint8_t y = 10;
        int dots_array[8] = {12+(y+2)*40, 12+(y+3)*40, 12+(y+5)*40, 12+(y+6)*40,
                             26+(y+2)*40, 26+(y+3)*40, 26+(y+5)*40, 26+(y+6)*40};
        Display dot;
        uint8_t begin_time;
        uint8_t *pd;
        uint8_t i = 0;
        uint8_t t_s1 = -1;
        uint8_t t_s2 = -1;
        uint8_t t_min1 = -1;
        uint8_t t_min2 = -1;
        uint8_t t_hour1 = -1;
        uint8_t t_hour2 = -1;
        bool both_sec = false;
        bool both_min = false;
        bool both_hour = false;
        bool first_run = true;
        uint8_t * no_separator(const uint8_t & no);
        void seconds();
        void minutes();
        void hours();
    public:
        Clock();
        bool ten_minutes();
        void show_time();
        void begin();
        void stop();
};

#endif
