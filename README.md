# VoonoPaeikh -- C++ library for creating console games.

When connecting VoonoPaeikh, the standard libraries
iostream, vector, windows.h, string, map, fstream, algorithm, map are also connected.
VoonoPaeikh has 6 classes for work:\
1. **colorsy** -- class for storing the color of the symbol.\
***Fields***:

\
**unsigned char symbol** -- field for storing the color code of the symbol;

**unsigned char back** -- field for storing the background color code;

there are also static constants for 16 colors, from black to
bright white.

\
***Methods*** :

\
**colorsy()** -- colorsy constructor with a white symbol and a black background;

**colorsy(unsigned char colorSymbol, unsigned char backColor)** --
a constructor that takes the symbol color and the background color (colorSymbol and backColor, respectively);

\
**void operator=(colorsy color)** -- sets the colorsy fields symbol and back to the same as those of the color operant;

\
**bool operator==(colorsy color)** -- returns true if the symbol and
back fields of both operants match;

**bool operator!=(colorsy color)** -- returns false if the symbol
and back fields of both operants match;

2\. **cell** -- a class for storing a screen cell.\

***Fields***:

\
**unsigned char symbol** -- stores the symbol written to the cell;\
**colorsy color ** -- stores the cell color.

***Methods:***

**cell(unsigned char symb, unsigned char colorSymbol, unsigned char
backColor)** -- constructor with symbol, symbol color, and background color;

**cell()** -- constructor that sets symbol = \' \'; color.symbol =
colorsy::WHITE; color.back = colorsy::BLACK;

**cell(unsigned char symb, colorsy clr)** -- constructor that takes
symbol and color;\
Operator= sets symbol and color fields the same as the second operant.

3\. **element** -- abstract class for game elements.

***Fields***:

\
**int xpos** -- position along the X axis;

**int ypos** -- position along the Y axis;

**std::vector\<std::vector\<colorsy\>\> color** -- two-dimensional vector for
element colors.

*** Methods***:

**element()** -- sets coordinates 0;0 ;

**void draw(std::vector\<std::vector\<cell\>\>& screen)** -- abstract
method for displaying an element on the screen;

**void element::loadColor(std::string colorSymbol, std::string
backColor)** -- method for setting the color of an element, principle of operation:\
1. Files named colorSymbol and backColor are opened (any text format will do, but for convenience it is better to use .csg and .bcg
for colorSymbol and BackColor respectively)

2\. texts in files are saved in two-dimensional unsigned char vectors

3\. using the global dictionary \<char, unsigned char\> CHAR_TO_COLOR
(converts a character from a file to a color value) writes the value to
color;

**setMonoColor(colorsy colora)** -- abstract method for setting a single
color for the entire element;

**drawBack(std::vector\<std::vector\<cell\>\>& screen)** -- abstract
method for drawing only the element's characters;

**drawSymbol(std::vector\<std::vector\<cell\>\>& screen)** --
abstract method for drawing only the element's background;

**Operators** are not defined for the abstract element, but are defined in
child classes, i.e. operators cannot be used with
element objects, but can be used with its child ones;

The \',\' symbol is not drawn, this is done so that it is possible to
make transparent parts of elements.

4\. **rect** -- child class element for single-line text.

***Fields***:

**std::string text** -- text.

***Methods*** :

**rect(std:: texta, std::vector\<colorsy\>& colora, int x, int y)** --
constructor accepting text, two-dimensional vector colory and coordinates;

**rect()** -- constructor setting text = ""; adding to color
subvector colorsy; and coordinates 0;0 ;

**rect(std::string a, colorsy b, int x, int y)** -- text = a; all colosy
in color = b; coordinates = x;y ;

**rect(std::string texta, int x, int y)** -- text = texta; coordinates =
x;y ; color is left empty;

operators(=, == and !=) ignore coordinates, i.e. operator = assigns
only text and color fields, and operators == and != compare only
text and color fields;

5\. **sprit** -- child class of element for pseudo-graphics sprites.

***Fields***:

**std::vector\<std::string\> image** -- image used for
the sprite

***Methods***:

**sprit(std::vector\<std::string\> texta,
std::vector\<std::vector\<colorsy\>\> colora, int x, int y)** -- image =
texta; color = colora; coordinates = x;y ;

**sprit() **-- only coordinates 0;0 are set;

sprit(std::vector\<std::string\> a, colorsy b, int x, int y);

sprit(int x, int y);

**void loadImpage(std::string filename)** -- loads a text file into
impage (any text format is suitable);

**int width()** -- returns the width of the image;

**int height()** -- returns the height of the image;

operators (=, == and !=) ignore coordinates, i.e. the = operator assigns
only the impage and color fields, and the == and != operators compare only the
impage and color fields;

6\. **game** -- a class for working with a specific game (switching between
games without leaving the console is possible).

***Fields***:

**static std::map\<int, time_t\> timeOfPress** and

**static std::map\<int, bool\> keyIsPressed** for GetKeyDown and GetKeyUp
respectively;

**std::vector\<std::vector\<cell\>\> screen** -- screen on which the elements will
be displayed;

**std::vector\<element\*\> elements** -- list of game elements (more precisely,
pointers to them);

**unsigned int screenHeight and unsigned int screenWidth** to store the screen height and width, respectively;

**void createScreen(int w, int h)** -- creates a screen;

**void clearScreen()** -- clears the screen;

**long long indexSearchInElemets(element\* address)** -- returns
the index of the pointer to the element in elements;

**static bool GetKey(int vKey)** -- returns true while the key is pressed;

**static bool GetKeyDown(int vKey, time_t timeSleep)** -- single
returns true when the key is pressed, timeSleep shows
the interval between presses if the key is held down;

**static bool GetKeyUp(int vKey)** -- returns true if the key was
pressed and then released;

**std::string outputScreen()** -- converts the screen to a string for output
to the console;

**void addElement(element\* elemy)** -- adds an element to the end of
elements;

**static void nuke()** -- terminates the program with an error
-1073741819(0xC0000005) Access Violation;

There is no logic for **operators**.

After familiarizing yourself with the standard classes of the VoonoPaeikh library, you are
ready to create your first game, let's look at an example with Hello World;\

```cpp
#include "VoonoPaeikh.hpp"

int main () {

game HelloWorld;

HelloWorld.createScreen(200, 40);

rect\* hw = new rect("Hello World", colorsy(colorsy::WHITE,
colorsy::BLACK), 0, 0);

HelloWorld.addElement(hw);

while (true) {

HelloWorld.clearScreen();

HelloWorld.elements\[0\]-\>draw(HelloWorld.screen);

if (game::GetKey(\'A\')) {

hw-\>xpos -= 1;

}

if (game::GetKey(\'D\') {

hw-\>xpos += 1;

}

if (game::GetKeyDown(VK_SPACE, 100) {\
game::nuke();

}

Sleep(50);

}

}
```

1\. To get started, you need to include the header file of the library
**VoonoPaeikh.hpp**

2\. A HelloWorld object of the game class is created

3\. A screen of 200 by 40 dimensions is created for HelloWorld

4\. A pointer to a new variable of the rect class is created with the text "Hello
World", in white-black colors at coordinates 0;0

5\. Add hw to HelloWorld.elements

6\. In an eternal loop, clear the screen and draw hw

7\. If A is pressed, then move hw to the left, D -- right

8\. If the space key is pressed, then close the program using nuke()
(the second argument 100 shows that 100 seconds will pass between readings of the space key press
while holding it down)

9\. After each drawing, wait 50 ms before the next one to control the frame rate.

It is advisable to use the draw method and similar ones for drawing before
the logic, otherwise the control will feel less responsive.
