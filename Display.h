#ifndef _DISPLAY_H
#define _DISPLAY_H
#include <String.h>
#include <WString.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class Display
{
    private:
        enum Mode {LET=1,NUM,CUS};
        enum Letters {SMALL, BIG};
        String path;
        String text;
        int num;
        Mode mode;
        Letters font_s;
        bool fopen;
        int x_pos;
        int y_pos;
        int tab_all[50];
        int * tab_custom;
        int size;
        int r,g,b;
        int *pt_x;
        int *pt_y;
        int how_many;
        int r_bg,g_bg,b_bg;
        Adafruit_NeoPixel strip;
        void SD_reader();
        void display_pixels();
    public:
        Display();
        Display(int * tab, int sof);
        void show(const String text);
        void show(int no);
        void show();
        void begin();
        //void no_separator(const int & no);
        void set_position(int x, int y);
        void set_text_colors(int rc, int gc, int bc);
        void set_bg_colors(int rc, int gc, int bc);
        void erase_it();
        void font_size(int size);
        void clear_all();
};
#endif
