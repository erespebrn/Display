#include "Display.h"

#define NUMPIXELS 841
#define PIN 7

extern int r_b;
extern int g_b;
extern int b_b;


Adafruit_NeoPixel st = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Default constructor for Display class
Display::Display() : strip(st)
{
    x_pos = 1;
    y_pos = 1;
    g=20;
    r=60;
    b=20;
    r_bg = r_b;
    g_bg = g_b;
    b_bg = b_b;
}

//Alternative constructor with pixels array as an argument
Display::Display(int * tab, uint8_t sof)
{
    strip = st;
    x_pos = 1;
    y_pos = 1;
    g=20;
    r=60;
    b=20;
    r_bg = r_b;
    g_bg = g_b;
    b_bg = b_b;
    mode = CUS;
    tab_custom = tab;
    size = sof;
}

//Begin method for display class
void Display::begin()
{
    Serial.begin(9600);
    strip.begin();
    Serial.print("Initializing SD card connection...");
    if (!SD.begin(4))
    {
        Serial.println("initialization failed!");
        return;
    }
    Serial.println("initialization done.");
}

//Method to display numbers
void Display::show(uint8_t no)
{
    mode = NUM;
    num = no;
    uint8_t x_temp = x_pos;
    if(font_s == 0)
        path = "patterns/numbers/small/" + String(no) + ".txt";
    else if(font_s == 1)
        path = "patterns/numbers/" + String(no) + ".txt";
    SD_reader();
    display_pixels();
    strip.show();
    x_pos = x_temp;
}
//Method for displaying text
void Display::show(const String & txt)
{
    mode = LET;
    text = txt;
    uint8_t z = text.length();
    uint8_t t = 0;
    uint8_t i = 0;
    String text_tab[z];
    uint8_t x_temp = x_pos;
    uint8_t y_temp = y_pos;


    for(i, t; i<z; i++, t++)
    {
        String a ="";
        char c = text.charAt(i);

        if(c == '%')
        {
            i++;
            uint8_t y = i;
            String mark = "";
            for(y; y<i+3; y++)
                mark += text.charAt(y);

            text_tab[t] = a+mark;
            i=y-1;
            continue;
        }

        text_tab[t] = a+c;
    }
    z = t;

    for(uint8_t i = 0; i <z; i++)
    {
        path = "patterns/letters/" + text_tab[i] + ".txt";
        SD_reader();
        display_pixels();

        if(text_tab[i] == "W" || text_tab[i] == "M" || text_tab[i] == "N" || text_tab[i] == "X" || text_tab[i] == "Y" || text_tab[i] == "Z" || text_tab[i] == "T")
            x_pos += 6;
        else if(text_tab[i] == "I")
            x_pos += 3;
        else if(text_tab[i] == "col")
            x_pos += 2;
        else
            x_pos += 5;
    }

    x_pos = x_temp;
    y_pos = y_temp;
    strip.show();
}
//Method for displaying custom pixels array
void Display::show()
{
    display_pixels();
    strip.show();
}
//Method for erasing (displaying in background color)
void Display::erase_it()
{
    uint8_t r_temp = r;
    uint8_t g_temp = g;
    uint8_t b_temp = b;
    r=r_bg;
    g=g_bg;
    b=b_bg;
    if(mode == 1)
    {
        this->show(text);
    }
    else if(mode == 2)
    {
        this->show(num);
    }
    else
    {
        this->show();
    }
    r = r_temp;
    g = g_temp;
    b = b_temp;
}

//Method for digits/letters color setup
void Display::set_text_colors(uint8_t rc, uint8_t gc, uint8_t bc)
{
    r = rc;
    g = gc;
    b = bc;
}

//Method for background color setup
void Display::set_bg_colors(uint8_t rc, uint8_t gc, uint8_t bc)
{
    r_bg = rc;
    g_bg = gc;
    b_bg = bc;
}

//Method for objects position setup
void Display::set_position(uint8_t x, uint8_t y)
{
    x_pos = x;
    y_pos = y;
}

//Private method for SD Card reading - using SD.h class
void Display::SD_reader()
{
    File myFile;
    myFile = SD.open(path);
    fopen = myFile;

    if (fopen)
    {
        char inChar;
        char inData[3];
        uint8_t index;
        uint8_t i = 0;
        int tab_x[50];
        int tab_y[50];
        bool started = false;
        bool ended = false;
        bool isthisx = false;
        bool timefory = false;
        bool isthisy = false;

        while(myFile.available())
        {
            inChar = myFile.read();
            if (inChar == '<')
            {
                started = true;
                index = 0;
                inData[index] = '\0';
            }
            else if (inChar == '>')
            {
                ended = true;
            }
            else if (inChar == '&')
            {
                timefory = true;
                i = 0;
            }
            else if(started)
            {
                inData[index] = inChar;
                index++;
                inData[index] = '\0';
            }

            if(started && ended)
            {
                // Convert the string to an integer
                int inInt = atoi(inData);
                // Use the value
                if (!timefory)
                {
                    tab_x[i] = x_pos + inInt;
                    i++;
                }
                else
                {
                    tab_y[i] = y_pos + inInt;
                    i++;
                }
                // Get ready for the next time
                started = false;
                ended = false;
                isthisx = false;
                isthisy = false;
                index = 0;
                inData[index] = '\0';
            }
        }
        timefory = false;
        for(uint8_t h = 0; h<i; h++)
        {
            tab_all[h] = (tab_x[h]-1)+(tab_y[h]-1)*40;
        }
        how_many = i;
    }
    else
        Serial.print("Blad otwarcia pliku");

    myFile.close();

}

//Method for changing numbers size
void Display::font_size(uint8_t size)
{
    if(size == 0)
        font_s = SMALL;
    else if(size == 1)
        font_s = BIG;
}

//Method for clearing all display (setting all for background color)
void Display::clear_all()
{
    for(int i = 0 ; i < NUMPIXELS; i++)
    {
         strip.setPixelColor(i, strip.Color(r_b,g_b,b_b));
    }
    strip.show();
}

//Method for setting up pixels for next display.
void Display::display_pixels()
{
    uint8_t i = 0;
    if(mode != 3)
    {
        if(fopen)
        {
            while (i < how_many)
            {
                strip.setPixelColor(tab_all[i], strip.Color(g,r,b));
                i++;
            }
        }
    }
    else
    {
        while(i < size)
        {
            strip.setPixelColor(tab_custom[i], strip.Color(g,r,b));
            i++;
        }
    }
}


