#include "Display.h"
#include "Clock.h"

#define NUMPIXELS 841
#define PIN 7

DS3231 a(SDA,SCL);
Time temp;

//Clock constructor
Clock::Clock() : rtc(a), t(temp), dot(dots_array,8)
{

    secs[0].set_position(29, y);
    secs[1].set_position(35, y);
    secs[0].font_size(1);
    secs[1].font_size(1);
    mins[0].set_position(15, y);
    mins[1].set_position(21, y);
    mins[0].font_size(1);
    mins[1].font_size(1);
    hour[0].set_position(1, y);
    hour[1].set_position(7, y);
    hour[0].font_size(1);
    hour[1].font_size(1);
}

//Clock begin method
void Clock::begin()
{
    rtc.begin();
    t = rtc.getTime();
    begin_time = t.min;
}

//Method for separating numbers into single digits
uint8_t * Clock::no_separator(const uint8_t & no)
{
    uint8_t tab_size = 0;
    if(no/10 == 0)
    {
        tab_size = 1;
    }
    else
    {
        tab_size = 2;
    }

    uint8_t *help_tab = new uint8_t[tab_size];
    help_tab[0] = 0;
    help_tab[1] = 0;
    uint8_t number = no;
    uint8_t i = 0;
    uint8_t cyfra = 0;
    uint8_t z;

    while(number>0)
    {
        cyfra = number % 10;
        help_tab[i] = cyfra;
        number /= 10;
        i++;
    }

    z = help_tab[0];
    help_tab[0] = help_tab[1];
    help_tab[1] = z;
    return help_tab;

}

//Method for showing time
void Clock::show_time()
{

    t = rtc.getTime();
    pd = no_separator(t.sec);
    seconds();
    pd = no_separator(t.min);
    minutes();
    pd = no_separator(t.hour);
    hours();
    first_run = false;
}

//Private method for showing seconds. Called from show_time()
void Clock::seconds()
{
    if(t_s1 != pd[0] && t_s2 != pd[1])
    {
        secs[0].erase_it();
        secs[1].erase_it();
        secs[0].show(pd[0]);
        secs[1].show(pd[1]);

        if(mode == 0)
        {
            dot.erase_it();
            mode = ON;
        }
        else if(mode == 1)
        {
            dot.show();
            mode = OFF;
        }
        both_sec = true;
    }
    if(both_sec == false)
    {
        if(t_s2 != pd[1] || first_run == true)
        {
            secs[1].erase_it();
            secs[1].show(pd[1]);

            if(mode == 0)
            {
                dot.erase_it();
                mode = ON;
            }
            else if(mode == 1)
            {
                dot.show();
                mode = OFF;
            }
        }
    }

    t_s1 = pd[0];
    t_s2 = pd[1];
    both_sec = false;
    delete [] pd;
}

//Private method for showing minutes. Called from show_time()
void Clock::minutes()
{
    if(t_min1 != pd[0] && t_min2 != pd[1])
    {
        mins[0].erase_it();
        mins[1].erase_it();
        mins[0].show(pd[0]);
        mins[1].show(pd[1]);
        both_min = true;
    }

    if(both_min == false)
    {
        if(t_min2 != pd[1] || first_run == true)
        {
            mins[1].erase_it();
            mins[1].show(pd[1]);
        }
    }

    t_min1 = pd[0];
    t_min2 = pd[1];
    both_min = false;
    delete [] pd;

}

//Private method for showing hours. Called from show_time()
void Clock::hours()
{
    if(t_hour1 != pd[0] && t_hour2 != pd[1])
    {
        hour[0].erase_it();
        hour[1].erase_it();
        hour[0].show(pd[0]);
        hour[1].show(pd[1]);
        both_hour = true;
    }

    if(both_hour == false || first_run == true)
    {
        if(t_hour2 != pd[1] || first_run == true)
        {
            hour[1].erase_it();
            hour[1].show(pd[1]);
        }
    }

    t_hour1 = pd[0];
    t_hour2 = pd[1];
    both_hour = false;
    delete [] pd;

}

//Return true if 10 minutes passed. For DHT updating
bool Clock::ten_minutes()
{
    if(begin_time+5 > 59)
    {
        begin_time = 0;
    }
    else if(begin_time + 5 == t.min && t.sec == 0)
    {
        return true;
        begin_time = t.min;
    }
    else
    {
        return false;
    }
}

//Stop method for relaunching clock
void Clock::stop()
{
    first_run = true;
    t_s1 = 0;
    t_s2 = 0;
    t_min1 = 0;
    t_min2 = 0;
    t_hour1 = 0;
    t_hour2 = 0;
    both_sec = false;
    both_min = false;
    both_hour = false;
    first_run = true;
}
