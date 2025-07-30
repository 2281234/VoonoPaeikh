#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include "VoonoPaeikh.hpp"


void EnableAnsiColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

std::map<int, time_t> game::timeOfPress;
std::map<int, bool> game::keyIsPressed;

// Добавим функцию для скрытия/показа курсора
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

    colorsy::colorsy() {
        symbol = WHITE;
        back = BLACK;
    }

    colorsy::colorsy(unsigned char colorSymbol, unsigned char backColor) {
        symbol = colorSymbol;
        back = backColor;
    }

    void colorsy::operator=(const colorsy& color) {
        symbol = color.symbol;
        back = color.back;
    }

    bool colorsy::operator== (const colorsy & color) const {
        return symbol == color.symbol and back == color.back;
    }

    bool colorsy::operator!= (const colorsy & color) const {
        return !(symbol == color.symbol and back == color.back);
    }

std::map<unsigned char, std::string> SYMBOL_COLOR_TO_STR = {
    {colorsy::BLACK, "\x1b[30m"},    // Черный
    {colorsy::BLUE, "\x1b[34m"},     // Синий
    {colorsy::GREEN, "\x1b[32m"},    // Зеленый
    {colorsy::AQUA, "\x1b[36m"},     // Голубой (Циан)
    {colorsy::RED, "\x1b[31m"},      // Красный
    {colorsy::PURPLE, "\x1b[35m"},   // Пурпурный (Магента)
    {colorsy::YELLOW, "\x1b[33m"},   // Желтый
    {colorsy::WHITE, "\x1b[37m"},    // Белый
    {colorsy::GREY, "\x1b[90m"},     // Серый (Ярко-черный, чаще используется для серого)
    {colorsy::LI_BLUE, "\x1b[94m"},  // Ярко-синий
    {colorsy::LI_GREEN, "\x1b[92m"}, // Ярко-зеленый
    {colorsy::LI_AQUA, "\x1b[96m"},  // Ярко-голубой
    {colorsy::LI_RED, "\x1b[91m"},   // Ярко-красный
    {colorsy::LI_PURPLE, "\x1b[95m"},// Ярко-пурпурный
    {colorsy::LI_YELLOW, "\x1b[93m"},// Ярко-желтый
    {colorsy::BR_WHITE, "\x1b[97m"}  // Ярко-белый
};

std::map<char, unsigned char> CHAR_TO_COLOR = {
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'a', 10},
    {'b', 11},
    {'c', 12},
    {'d', 13},
    {'e', 14},
    { 'f', 15}
};

std::map<unsigned char, std::string> BACK_COLOR_TO_STR = {
    {colorsy::BLACK, "\x1b[40m"},    // Черный фон
    {colorsy::BLUE, "\x1b[44m"},     // Синий фон
    {colorsy::GREEN, "\x1b[42m"},    // Зеленый фон
    {colorsy::AQUA, "\x1b[46m"},     // Голубой (Циан) фон
    {colorsy::RED, "\x1b[41m"},      // Красный фон
    {colorsy::PURPLE, "\x1b[45m"},   // Пурпурный (Магента) фон
    {colorsy::YELLOW, "\x1b[43m"},   // Желтый фон
    {colorsy::WHITE, "\x1b[47m"},    // Белый фон
    {colorsy::GREY, "\x1b[100m"},    // Серый фон (Ярко-черный фон)
    {colorsy::LI_BLUE, "\x1b[104m"}, // Ярко-синий фон
    {colorsy::LI_GREEN, "\x1b[102m"},// Ярко-зеленый фон
    {colorsy::LI_AQUA, "\x1b[106m"}, // Ярко-голубой фон
    {colorsy::LI_RED, "\x1b[101m"},  // Ярко-красный фон
    {colorsy::LI_PURPLE, "\x1b[105m"},// Ярко-пурпурный фон
    {colorsy::LI_YELLOW, "\x1b[103m"},// Ярко-желтый фон
    {colorsy::BR_WHITE, "\x1b[107m"} // Ярко-белый фон
};


    cell::cell(unsigned char symb, unsigned char colorSymbol, unsigned char backColor) {
        symbol = symb;
        color.symbol = colorSymbol;
        color.back = backColor;
    }
    cell::cell() {
        symbol = ' ';
        color.symbol = colorsy::WHITE;
        color.back = colorsy::BLACK;
    }
    cell::cell(unsigned char symb, colorsy clr) {
        symbol = symb;
        color = clr;
    }
    void cell::operator=(const cell a) {
        symbol = a.symbol;
        color = a.color;
    }
    bool cell::operator==(const cell celly) const {
        return symbol == celly.symbol and color == celly.color;
    }
    bool cell::operator!=(const cell celly) const {
        return !(symbol == celly.symbol and color == celly.color);
    }

    element::element() {
        xpos = 0;
        ypos = 0;
    }

    void element::draw(std::vector<std::vector<cell>>& screen) {}

    void element::loadColor(std::string colorSymbol, std::string backColor) {
        color.clear();
        std::ifstream file1(colorSymbol);
        std::string strOfFile1;
        std::ifstream file2(backColor);
        std::string strOfFile2;
        std::vector<std::vector<unsigned char>> colorsFile1;
        std::vector<std::vector<unsigned char>> colorsFile2;
        while (std::getline(file1, strOfFile1)) {
            colorsFile1.push_back({});
            for (int i = 0; i < strOfFile1.size(); i++) {
                colorsFile1[colorsFile1.size() - 1].push_back(CHAR_TO_COLOR[strOfFile1[i]]);
            }
        }
        while (std::getline(file2, strOfFile2)) {
            colorsFile2.push_back({});
            for (int i = 0; i < strOfFile2.size(); i++) {
                colorsFile2[colorsFile2.size() - 1].push_back(CHAR_TO_COLOR[strOfFile2[i]]);
            }
        }
        for (int i = 0; i < colorsFile1.size(); i++) {
            color.push_back({});
            for (int j = 0; j < colorsFile1[i].size(); j++) {
                color[color.size() - 1].push_back(colorsy(colorsFile1[i][j], colorsFile2[i][j]));
            }
        }

        file1.close();
        file2.close();
    }

    void element::drawBack(std::vector<std::vector<cell>>& screen) {}

    void element::drawSymbol(std::vector<std::vector<cell>>& screen) {}

    void element::setMonoColor(colorsy colora) {}

    std::vector<std::vector<colorsy>> element::getColorFromFile(std::string colorSymbol, std::string backColor) {
        std::vector<std::vector<colorsy>> output;
        std::ifstream file1(colorSymbol);
        std::string strOfFile1;
        std::ifstream file2(backColor);
        std::string strOfFile2;
        std::vector<std::vector<unsigned char>> colorsFile1;
        std::vector<std::vector<unsigned char>> colorsFile2;
        while (std::getline(file1, strOfFile1)) {
            colorsFile1.push_back({});
            for (int i = 0; i < strOfFile1.size(); i++) {
                colorsFile1[colorsFile1.size() - 1].push_back(CHAR_TO_COLOR[strOfFile1[i]]);
            }
        }
        while (std::getline(file2, strOfFile2)) {
            colorsFile2.push_back({});
            for (int i = 0; i < strOfFile2.size(); i++) {
                colorsFile2[colorsFile2.size() - 1].push_back(CHAR_TO_COLOR[strOfFile2[i]]);
            }
        }
        for (int i = 0; i < colorsFile1.size(); i++) {
            output.push_back({});
            for (int j = 0; j < colorsFile1[i].size(); j++) {
                output[output.size() - 1].push_back(colorsy(colorsFile1[i][j], colorsFile2[i][j]));
            }
        }

        file1.close();
        file2.close();
        return output;
    }

    void element::operator=(const element elemy) {}
    bool element::operator==(const element elemy) const {}
    bool element::operator!=(const element elemy) const {}
    element::~element() {};

    rect::rect(std::string a, std::vector<colorsy>& b, int x, int y) {
        text = a;
        if (color.empty()) {
            color.push_back({});
        }
        color[0] = b;
        xpos = x;
        ypos = y;
    }

    rect::rect() {
        text = "";
        if (color.empty()) {
            color.push_back({});
        }
        color[0] = std::vector<colorsy>{};
        xpos = 0;
        ypos = 0;
    }

    rect::rect(std::string a, colorsy b, int x, int y) {
        text = a;
        if (color.empty()) {
            color.push_back({});
        }
        for (int i = 0; i < a.size(); i++) {
            color[0].push_back(b);
        }
        xpos = x;
        ypos = y;
    }
    
    rect::rect(std::string inputText, int x, int y) {
        text = inputText;
        xpos = x;
        ypos = y;
    }

    void rect::draw(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < text.size(); i++) {
            if (i + xpos < screen[0].size() and ypos < screen.size() and i + xpos >= 0 and ypos >= 0) {
                screen[ypos][i + xpos].symbol = text[i];
                screen[ypos][i + xpos].color = color[0][i];
            }
        }
    }

    void rect::drawBack(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < text.size(); i++) {
            if (i + xpos < screen[0].size() and ypos < screen.size() and i + xpos >= 0 and ypos >= 0) {
                screen[ypos][i + xpos].color.back = color[0][i].back;
            }
        }
    }

    void rect::drawSymbol(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < text.size(); i++) {
            if (i + xpos < screen[0].size() and ypos < screen.size() and i + xpos >= 0 and ypos >= 0) {
                screen[ypos][i + xpos].symbol = text[i];
                screen[ypos][i + xpos].color.symbol = color[0][i].symbol;
            }
        }
    }

    void rect::setMonoColor(colorsy colora)  {
        color.clear();
        color.push_back({});
        for (int i = 0; i < text.size(); i++) {
            color[0].push_back(colora);
        }
    }

    void rect::operator=(rect recty) {
        text = recty.text;
        color = recty.color;
    }

    bool rect::operator==(const rect recty) const {
        return text == recty.text and color == recty.color;
    }

    bool rect::operator!=(const rect recty) const {
        return !(text == recty.text and color == recty.color);
    }


    sprit::sprit(std::vector<std::string> a, std::vector<std::vector<colorsy>> b, int x, int y) {
        image = a;
        color = b;
        xpos = x;
        ypos = y;
    }

    sprit::sprit() {
        image = std::vector<std::string>{};
        color = std::vector<std::vector<colorsy>>{};
        xpos = 0;
        ypos = 0;
    }

    sprit::sprit(std::vector<std::string> a, colorsy b, int x, int y) {
        image = a;
        for (int i = 0; i < a.size(); i++) {
            color.push_back({});
            for (int j = 0; j < a[i].size(); j++) {
                color[i].push_back(b);
            }
        }
        xpos = x;
        ypos = y;
    }

    sprit::sprit(int x, int y) {
        xpos = x;
        ypos = y;
    }

    void sprit::loadImage(std::string filename) {
        image.clear();
        std::ifstream file(filename);
        std::string strOfFile;
        int iter = 0;
        while (std::getline(file, strOfFile)) {
            image.push_back({});
            image[image.size() - 1] = strOfFile;
        }
        file.close();
    }

    int sprit::width() {
        int w = 0;
        for (int i = 0; i < image.size(); i++) {
            if (image[i].size() > w) {
                w = image[i].size();
            }
        }
        return w;
    }

    int sprit::height() {
        return image.size();
    }

    void sprit::setMonoColor(colorsy colora) {
        color.clear();
        for (int i = 0; i < image.size(); i++) {
            color.push_back({});
            for (int j = 0; j < image[i].size(); j++) {
                color[i].push_back(colora);
            }
        }
    }

    void sprit::draw(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                if (i < color.size() && j < color[i].size() && // Проверка на допустимый индекс color
                    j + xpos < screen[i].size() && i + ypos < screen.size() &&
                    image[i][j] != ',' && j + xpos >= 0 && i + ypos >= 0) {
                    screen[i + ypos][j + xpos] = cell(image[i][j], color[i][j]);
                }
            }
        }
    }

    void sprit::drawBack(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                if (j + xpos < screen[i].size() and i + ypos < screen.size() and image[i][j] != ',' and j + xpos >= 0 and i + ypos >= 0) {
                    screen[i + ypos][j + xpos].color.back = color[i][j].back;
                }
            }
        }
    }

    void sprit::drawSymbol(std::vector<std::vector<cell>>& screen)  {
        for (int i = 0; i < image.size(); i++) {
            for (int j = 0; j < image[i].size(); j++) {
                if (j + xpos < screen[i].size() and i + ypos < screen.size() and image[i][j] != ',' and j + xpos >= 0 and i + ypos >= 0) {
                    screen[i + ypos][j + xpos].color.symbol = color[i][j].symbol;
                    screen[i + ypos][j + xpos].symbol = image[i][j];
                }
            }
        }
    }

    void sprit::operator=(const sprit sprity) {
        image = sprity.image;
        color = sprity.color;
    }

    bool sprit::operator==(const sprit sprity) const {
        return image == sprity.image and color == sprity.color;
    }

    bool sprit::operator!=(const sprit sprity) const {
        return !(image == sprity.image and color == sprity.color);
    }



    void game::createScreen(int w, int h) {
        screenHeight = h;
        screenWidth = w;
        screen = std::vector<std::vector<cell>>(h, std::vector<cell>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                screen[i][j] = cell(' ', colorsy::WHITE, colorsy::BLACK);
            }
        }
        EnableAnsiColors();
        ShowConsoleCursor(false);
    }

    void game::clearScreen() {
        for (int i = 0; i < screenHeight; i++) {
            for (int j = 0; j < screenWidth; j++) {
                screen[i][j] = cell(' ', colorsy::WHITE, colorsy::BLACK);
            }
        }
    }

    long long game::indexSearchInElemets(element* address) {
        for (long long i = 0; i < elements.size(); i++) {
            if (elements[i] == address) {
                return i;
            }
        }
        return -1;
    }

    bool game::GetKey(int vKey) {
        return GetAsyncKeyState(vKey) & 0x8000;
    }

    bool game::GetKeyDown(int vKey, time_t timeSleep) {
        if (GetAsyncKeyState(vKey) & 0x8000) {
            if (!timeOfPress.count(vKey) or time(0) - timeOfPress[vKey] >= timeSleep) {
                timeOfPress[vKey] = time(0);
                return true;
            }
            else {
                return 0;
            }
        }
        else {
            timeOfPress[vKey] = 0;
            return 0;
        }
    }

    bool game::GetKeyUp(int vKey) {
        bool output = 0;
        if (GetAsyncKeyState(vKey) & 0x8000) {
            keyIsPressed[vKey] = 1;
            return 0;
        }
        else {
            if (keyIsPressed[vKey] == 1) {
                output = 1;
            }
            else {
                output = 0;
            }
            keyIsPressed[vKey] = 0;
        }
        return output;
    }

    std::string game::outputScreen() {
        std::string osc;

        osc += "\x1b[H";
        cell lastCell;
        bool firstCell = 1;
        for (int i = 0; i < screen.size(); i++) {
            for (int j = 0; j < screen[i].size(); j++) {
                if (firstCell or screen[i][j].color.symbol != lastCell.color.symbol) {
                    osc += SYMBOL_COLOR_TO_STR[screen[i][j].color.symbol];
                }
                if (firstCell or screen[i][j].color.back != lastCell.color.back) {
                    osc += BACK_COLOR_TO_STR[screen[i][j].color.back];
                }
                firstCell = false;
                osc += screen[i][j].symbol;
                lastCell = screen[i][j];
            }
            osc += '\n';
        }
        osc += "\x1b[0m";
        return osc;
    }

    void game::addElement(element* elemy) {
        elements.push_back(elemy);
    }

    void game::nuke() {
        std::vector<int> aaa;
        std::cout << aaa[1];
        // данный метод предназначен для завершения программы ошибкой
    }


    game::~game() {
        for (element* elemy : elements) {
            delete elemy;
        }
        elements.clear();
        screen.clear();
    }