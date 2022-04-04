#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  t=NULL;
  unsigned int w = 0;
  unsigned int h = 0;
  unsigned int base_w = base_.width();
  unsigned int base_h = base_.height();
  //std::cout<<"hi";
  points_.resize(base_w, std::vector<bool>(base_h));
  while(w < base_w ){
    while(h < base_h){
      points_[w][h]=false;
      h++;

    }
    w++;

  }
}


bool ImageTraversal::Iterator::isAllowed(Point p)
{
  Point temp = p;
  if(temp.y>=base_.height() || temp.x>=base_.width()) return false;
  if(temp.y<base_.height() && temp.x<base_.width()){
    HSLAPixel & begin = base_.getPixel(start_.x,start_.y);
    HSLAPixel & position = base_.getPixel(temp.x,temp.y);
    if(calculateDelta(begin,position)<tolerance_){
      if(points_[temp.x][temp.y]==false){
        return true;

      }
    }
  }
  return false;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* imaget,PNG png, Point p, double d)
{
  t = imaget;
  tolerance_ = d;
  position_= p;
  start_=p;
  base_ = png;
  unsigned int base_h = base_.height();
  unsigned int base_w= base_.width();
  unsigned int height = 0;
  unsigned int width = 0;

  points_.resize(base_w,std::vector<bool>(base_h));

  while(width<base_w){
    height = 0;
    while(height<base_h){
      points_[width][height]=false;
      height++;
    }
    width++;
  }

  if(!isAllowed(position_)==false){
    points_[position_.x][position_.y]=true;
  }

}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  points_[position_.x][position_.y] = true;
  Point right, left, up, down;
  right = Point(position_.x+1,position_.y);
  left = Point(position_.x-1,position_.y);
  up = Point(position_.x,position_.y-1);
  down = Point(position_.x,position_.y+1);
  if(isAllowed(right)){
    t->add(right);
  }
  if(isAllowed(down)){
    t->add(down);
  }
  if(isAllowed(left)) {
    t->add(left);
  }
  if(isAllowed(up)) {
    t->add(up);
  }

  while(t->empty()!=true && isAllowed(t->peek())!=true){
    t->pop();
    if(t->empty()){
      return *this;

    }
  }
  if(t->empty()==false){
    position_ = t->peek();
    return *this;

  }
  else{
    t = NULL;
    return *this;

  }
  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return position_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

 if(t == NULL){
   thisEmpty = true;
 }

 if(other.t == NULL){
   otherEmpty = true;
 }

 if(!thisEmpty){
   thisEmpty = t->empty();
 }
 if(!otherEmpty){
   otherEmpty = other.t->empty();
 }

 if(thisEmpty && otherEmpty) return false;

 else if((!thisEmpty)&&(!otherEmpty)) return (t != other.t);

 else return true;
}
