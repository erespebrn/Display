#include "Display.h"
#include "DHTsensor.h"

#define DHTPIN 2
#define DHTTYPE DHT22
DHT d(DHTPIN, DHTTYPE);

//DHTsensor contructor
DHTsensor::DHTsensor() : dht(d)
{
    temperature = humidity = 0.0;
    tmark.set_position(1,1);
    hmark.set_position(21,1);
    hmark.set_text_colors(50,50,0);
    tmark.set_text_colors(50,50,0);
    tempdis[0].set_text_colors(50,50,0);
    tempdis[1].set_text_colors(50,50,0);
    humdis[0].set_text_colors(50,50,0);
    humdis[1].set_text_colors(50,50,0);
    tempdis[0].set_position(9,1);
    tempdis[1].set_position(13,1);
    humdis[0].set_position(28,1);
    humdis[1].set_position(32,1);
}

//DHTsensor begin function
void DHTsensor::begin()
{
    dht.begin();
}

//Method for reading from sensor, using DHT.H library
void DHTsensor::read()
{
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
}

//Method for separation numbers into single digits
uint8_t * DHTsensor::no_separator(const uint8_t & no)
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

//Method for displaying temp and humidity
void DHTsensor::show_dht()
{
    read();
    tmark.set_position(1,1);
    tmark.show("T%col");
    pd = no_separator(temperature);
    show_temp();
    tmark.set_position(15,1);
    tmark.show("%deg");
    hmark.set_position(21,1);
    hmark.show("H%col");
    pd = no_separator(humidity);
    show_hum();
    hmark.set_position(35,1);
    hmark.show("%per");
}

//Private method for showing temp. Called from show_dht()
void DHTsensor::show_temp()
{
    if(t1 != pd[0] && t2 != pd[1])
    {
        tempdis[0].erase_it();
        tempdis[1].erase_it();
        tempdis[0].show(pd[0]);
        tempdis[1].show(pd[1]);
        both_temp = true;
    }

    if(both_temp == false)
    {
        if(t2 != pd[1])
        {
            tempdis[1].erase_it();
            tempdis[1].show(pd[1]);
        }
    }

    t1 = pd[0];
    t2 = pd[1];
    both_temp = false;
    delete [] pd;

}

//Private method for showing hum. Called from show_dht()
void DHTsensor::show_hum()
{
    if(h1 != pd[0] && h2 != pd[1])
    {
        humdis[0].erase_it();
        humdis[1].erase_it();
        humdis[0].show(pd[0]);
        humdis[1].show(pd[1]);
        both_hum = true;
    }

    if(both_hum == false)
    {
        if(h2 != pd[1])
        {
            humdis[1].erase_it();
            humdis[1].show(pd[1]);
        }
    }

    h1 = pd[0];
    h2 = pd[1];
    both_hum = false;
    delete [] pd;
}
