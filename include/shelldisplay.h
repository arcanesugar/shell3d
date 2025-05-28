#pragma once

#include <stdbool.h>

typedef struct Color{
  double r,g,b;
}Color;

#define CLR_RED ((Color){1,0,0})
#define CLR_GREEN ((Color){0,1,0})
#define CLR_BLUE ((Color){0,0,1})

#define CLR_CYAN ((Color){0,1,1})
#define CLR_MAGENTA ((Color){1,0,1})
#define CLR_YELLOW ((Color){1,1,0})

#define CLR_BLACK ((Color){0,0,0})
#define CLR_WHITE ((Color){1,1,1})
#define CLR_GRAY ((Color){0.5,0.5,0.5})

typedef struct Texture{
  unsigned int width, height;
  Color* pixels;
}Texture;

enum SampleMethods{
  SAMPLE_NEAREST,
  SAMPLE_BILINEAR
};

enum PixelTypes{
  //because characters are twice as tall as they are wide, some pixel types are rectangular
  PIX_DOUBLE_SPACE,//pixels are 2x1 chars(square)
  PIX_SINGLE_SPACE,//pixels are 1x1 chars(rect)
  PIX_UPPER_HALF_BLOCK,//pixels are 1x0.5 chars(square) requires unicode
};

enum colorModes{
  CM_TRUECOLOR,
  CM_ANSICOLOR
};

enum textStyles{
  S_BOLD          = 0b00000001,
  S_DIM           = 0b00000010,
  S_ITALIC        = 0b00000100,
  S_UNDERLINE     = 0b00001000,
  S_BLINK         = 0b00010000,
  S_INVERSE       = 0b00100000,
  S_HIDDEN        = 0b01000000,
  S_STRIKETHROUGH = 0b10000000
};

// -------shelldisplay.c-------
_Noreturn void raiseError(char* fmt, ...);
void setColorMode(int mode);
void setStyle(int style);
void setColor(bool background, Color color);
void resetColor();
void clearScreen();
Color invertColor(Color c);
Color lerpColors(Color a, Color b, double x);
Color multiplyColors(Color a, Color b);
bool compareColors(Color a, Color b);

// -------texture.c-------
Texture allocTexture(int width, int height);
void freeTexture(Texture t);
void setPixel(Texture t, int x, int y, Color c);
Color getPixel(Texture t, int x, int y);
void fillTexture(Texture t, Color c);
Color sampleTexture(Texture t, double x, double y, int method);
Texture resampleTexture(Texture t, int width, int height, int method);
void printTexture(Texture t, int pixelType);

// -------drawing.c-------
typedef struct Vec2i{
  int x;
  int y;
}Vec2i;

void drawLine(Texture t, Vec2i a, Vec2i b, Color c);
void drawCircle(Texture tex, Vec2i pos, int radius, Color color);
void drawTriangle(Texture tex, Vec2i a, Vec2i b, Vec2i c, Color color, bool filled);
void drawRect(Texture tex, Vec2i tl, Vec2i br, Color color);
void drawPolygon(Texture tex, Vec2i* vertices, int numVertices, Color color, bool filled);