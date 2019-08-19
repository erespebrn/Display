#include "Display.h"
#include "Clock.h"

#define NUMPIXELS 841
#define PIN 7

DS3231 a(SDA,SCL);
Time temp;

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

void Clock::begin()
{
    rtc.begin();
}
#define DHTPIN 2
#define DHTTYPE DHT22
int * Clock::no_separator(const int & no)
{
    int tab_size = 0;
    if(no/10 == 0)
    {
        tab_size = 1;
    }
    else
    {
        tab_size = 2;
    }

    int *help_tab = new int[tab_size];
    help_tab[0] = 0;
    help_tab[1] = 0;
    int number = no;
    int i = 0;
    int cyfra = 0;
    int z;

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
