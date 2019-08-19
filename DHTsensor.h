#ifndef _DHTSENSOR_H
#define _DHTSENSOR_H
#include <String.h>
#include <WString.h>
#include <Display.h>
#include <DHT.h>

class DHTsensor
{
    private:
        DHT dht;
        Display tempdis[2];
        Display tmark;
        Display hmark;
        Display humdis[2];
        Display bgcol;
        bool both_temp = false;
        bool both_hum = false;
        int t1 = -1;
        int t2 = -1;
        int h1 = -1;
        int h2 = -1;
        int *pd;
        float temperature;
        float humidity;
        void read();
        int * no_separator(const int & no);
        void show_temp();
        void show_hum();
    public:
        void begin();
        DHTsensor();
        void show_dht();
};

#endif
