#include <stdio.h>
#include "include/shelldisplay.h"

int main(){
  Texture t = allocTexture(50,50);
  drawCircle(t, (Vec2i){25,25}, 7, CLR_BLUE);
  printTexture(t, PIX_UPPER_HALF_BLOCK);
  freeTexture(t);
  return 0;
}