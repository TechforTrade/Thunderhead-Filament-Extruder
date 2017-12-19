/*
  Menu.h - Library for controlling LCD menus

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Menu_h
#define Menu_h

#include "Arduino.h"
//#include "MenuData.h"
#include <LiquidCrystal.h>
#include "Keypad.h"


class LiquidCrystal;
class Keypad;
class Menu
{
  public:
    enum ItemType {
      TITLE = 0, //Menu items are titles by default because TITLE is the first in the enum.
      TITLE_STRING,
      VALUE,
      ACTION,
      BOOLEAN,
      BOOLEAN_LOCKED,
      INT,
      INT_LOCKED,
      UNSIGNED_LONG,
      UNSIGNED_LONG_LOCKED,
      FLOAT,
      FLOAT_LOCKED,
      DOUBLE,
      DOUBLE_LOCKED,
      STRING,
      STRING_LOCKED
    } ;

    struct MenuItem {
      const char* text;
      int parent;
      int child;
      void* value;
      int precision;
      Menu::ItemType type;
      void (*_action)();
    };

    Menu(const MenuItem* menu, int menuSize, LiquidCrystal* lcd, Keypad* kpd);
    void up();
    void down();
    void back();
    void select();
	void increase();
	void decrease();
    void reset();
    void display();
    int getPrevious(int item);
    int getNext(int item);
    int getParent(int item);
    int getChild(int item);
    ItemType getType(int item);


    int       _menuSize;
    void      _setDisplay();
    void      _editValue(int item);
    void      _editString(int item);
    char*     _getText(char* str, int item);
    int       _getLength(int item);
    char*     _getValueStr(char* str, int item);
    void      _setValue(int item, void* f);
    int       _selectLineNumber;
    int       _getPrecision(int item);
    void*     _getValuePtr(int item);

    const MenuItem* _menu;
    int _firstItem;
    int _root;
    int _selectedItem;
    int _firstLine;
    int _currentItem;
    int _currentTitle;
    int _nextItem;
    int _displayed[4];

    LiquidCrystal* _lcd;
    Keypad* _kpd;
    char _key;

    char*     _title[21];
    char      _text[21];//holds a line of text for the LCD
	
	boolean printToSerialMonitor = true;
      private:

};

#endif
