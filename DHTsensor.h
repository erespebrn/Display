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
        uint8_t t1 = -1;
        uint8_t t2 = -1;
        uint8_t h1 = -1;
        uint8_t h2 = -1;
        uint8_t *pd;
        float temperature;
        float humidity;
        void read();
        uint8_t * no_separator(const uint8_t & no);
        void show_temp();
        void show_hum();
    public:
        void begin();
        DHTsensor();
        void show_dht();
};

#endif
