#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <map>


void EnableAnsiColors();
void ShowConsoleCursor(bool showFlag);
class colorsy {
    public:
        static const unsigned char BLACK = 0;
        static const unsigned char BLUE = 1;
        static const unsigned char GREEN = 2;
        static const unsigned char AQUA = 3;
        static const unsigned char RED = 4;
        static const unsigned char PURPLE = 5;
        static const unsigned char YELLOW = 6;
        static const unsigned char WHITE = 7;
        static const unsigned char GREY = 8;
        static const unsigned char LI_BLUE = 9;
        static const unsigned char LI_GREEN = 10;
        static const unsigned char LI_AQUA = 11;
        static const unsigned char LI_RED = 12;
        static const unsigned char LI_PURPLE = 13;
        static const unsigned char LI_YELLOW = 14;
        static const unsigned char BR_WHITE = 15;

        unsigned char symbol;
        unsigned char back;
        colorsy();
        colorsy(unsigned char colorSymbol, unsigned char backColor);
        void operator=(const colorsy& a);
        bool operator== (const colorsy& a) const;
        bool operator!= (const colorsy& a) const;
};

extern std::map<unsigned char, std::string> SYMBOL_COLOR_TO_STR;
extern std::map<char, unsigned char> CHAR_TO_COLOR;
extern std::map<unsigned char, std::string> BACK_COLOR_TO_STR;

class cell {
public:
    unsigned char symbol;
    colorsy color;
    cell(unsigned char symb, unsigned char symbolColor, unsigned char backColor);
    cell();
    cell(unsigned char a, colorsy b);
    void operator=(const cell a);
    bool operator==(const cell a) const;
    bool operator!=(const cell a) const;
};
class element {
public:
    int xpos;
    int ypos;
    std::vector<std::vector<colorsy>> color;
    element();

    void virtual draw(std::vector<std::vector<cell>>& screen);
    void loadColor(std::string colorSymbol, std::string backColor);
    void virtual drawBack(std::vector<std::vector<cell>>& screen);
    void virtual drawSymbol(std::vector<std::vector<cell>>& screen);
    void virtual setMonoColor(colorsy colora);
    std::vector<std::vector<colorsy>> getColorFromFile(std::string colorSymbol, std::string backColor);


    void operator=(const element elemy);
    bool operator==(const element elemy) const;
    bool operator!=(const element elemy) const;
    virtual ~element();
};
class rect : public element {
public:
    std::string text;

    rect(std::string texta, std::vector<colorsy>& colora, int x, int y);
    rect();
    rect(std::string texta, colorsy b, int x, int y);
    rect(std::string texta, int x, int y);

    void setMonoColor(colorsy colora) override;
    void draw(std::vector<std::vector<cell>>& screen) override;
    void drawBack(std::vector<std::vector<cell>>& screen) override;
    void drawSymbol(std::vector<std::vector<cell>>& screen) override;

    void operator=(const rect recty);
    bool operator==(const rect recty) const;
    bool operator!=(const rect recty) const;
};
class sprit : public element {
public:
    std::vector<std::string> image;

    sprit(std::vector<std::string> texta, std::vector<std::vector<colorsy>> colora, int x, int y);
    sprit();
    sprit(std::vector<std::string> a, colorsy b, int x, int y);
    sprit(int x, int y);

    void loadImage(std::string filename);
    int width();
    int height();

    void setMonoColor(colorsy colora) override;
    void draw(std::vector<std::vector<cell>>& screen) override;
    void drawBack(std::vector<std::vector<cell>>& screen) override;
    void drawSymbol(std::vector<std::vector<cell>>& screen) override;

    void operator=(const sprit sprity);
    bool operator==(const sprit sprity) const;
    bool operator!=(const sprit sprity) const;
};
class game {
public:
    static std::map<int, time_t> timeOfPress;
    static std::map<int, bool> keyIsPressed;
    std::vector<std::vector<cell>> screen;
    std::vector<element*> elements;

    unsigned int screenHeight;
    unsigned int screenWidth;

    void createScreen(int w, int h);
    void clearScreen();
    long long indexSearchInElemets(element* address);
    static bool GetKey(int vKey);
    static bool GetKeyDown(int vKey, time_t timeSleep);
    static bool GetKeyUp(int vKey);
    std::string outputScreen();
    void addElement(element* elemy);

    static void nuke();

    ~game();
};