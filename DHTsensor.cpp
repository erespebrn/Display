#include "Display.h"
#include "DHTsensor.h"

#define DHTPIN 2
#define DHTTYPE DHT22
DHT d(DHTPIN, DHTTYPE);

DHTsensor::DHTsensor() : dht(d)
{
    temperature = humidity = 0.0;
    tmark.set_position(1,1);
    hmark.set_position(21,1);
    tempdis[0].set_position(9,1);
    tempdis[1].set_position(13,1);
    humdis[0].set_position(28,1);
    humdis[1].set_position(32,1);
}

void DHTsensor::begin()
{
    dht.begin();
}

void DHTsensor::read()
{
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
}

int * DHTsensor::no_separator(const int & no)
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

void DHTsensor::show_dht()
{
    read();
    tempdis[0].set_text_colors(0,50,50);
    hmark.set_text_colors(0,50,50);
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
