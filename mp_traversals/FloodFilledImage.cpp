#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png){
  /** @todo [Part 2] */
  base_ = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  ImageTraversal* temp = &traversal;
  path.push_back(temp);
  ColorPicker* color = &colorPicker;
  colors.push_back(color);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(*base_);
  for(int i = 0; i < (int)path.size(); i++){
    ImageTraversal::Iterator begin = path[i]->begin();
    ImageTraversal::Iterator end = path[i]->end();
    unsigned update = 0;

    for(ImageTraversal::Iterator iterator = begin; iterator != end; ++iterator){
      if(update == frameInterval){
        animation.addFrame(*base_);
        update = 0;

      }
      update++;
      cs225::HSLAPixel& base = base_->getPixel((*iterator).x, (*iterator).y);
      cs225::HSLAPixel new_pixel = colors[i]->getColor((*iterator).x, (*iterator).y);
      base.h = new_pixel.h;
      base.s = new_pixel.s;
      base.l = new_pixel.l;
      base.a = new_pixel.a;
    }
  }
  animation.addFrame(*base_);

  return animation;
}
