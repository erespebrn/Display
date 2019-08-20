#ifndef _DISPLAY_H
#define _DISPLAY_H
#include <String.h>
#include <WString.h>
#include <Adafruit_NeoPixel.h>
#include <DS3231.h>
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <stdint.h>

class Display
{
    private:
        enum Mode {LET=1,NUM,CUS}; //Switching mode. NUM - numbers, LET - letters, CUS - custom array
        enum Letters {SMALL, BIG};
        String path;
        String text;
        uint8_t num;
        Mode mode;
        Letters font_s;
        bool fopen;
        uint8_t x_pos;
        uint8_t y_pos;
        int tab_all[50];
        int * tab_custom;
        uint8_t size;
        uint8_t r,g,b;
        uint8_t how_many;
        uint8_t r_bg,g_bg,b_bg;
        Adafruit_NeoPixel strip;
        void SD_reader();
        void display_pixels();
    public:
        Display();
        Display(int * tab, uint8_t sof);
        void show(const String & txt);
        void show(uint8_t no);
        void show();
        void begin();
        //void no_separator(const int & no);
        void set_position(uint8_t x, uint8_t y);
        void set_text_colors(uint8_t rc, uint8_t gc, uint8_t bc);
        void set_bg_colors(uint8_t rc, uint8_t gc, uint8_t bc);
        void erase_it();
        void font_size(uint8_t size);
        void clear_all();
};
#endif
