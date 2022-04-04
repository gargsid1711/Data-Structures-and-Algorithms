#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
 MyColorPicker::MyColorPicker(){ }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double hue = 0;
  for(unsigned i = 0; i < x; i++){
    for(unsigned j = 0; j < y; j++){
        if(hue == 360){
          hue = 0;
        }else hue++;
    }
  }

  HSLAPixel pixel(hue, 1, 0.5);

  return pixel;
}
