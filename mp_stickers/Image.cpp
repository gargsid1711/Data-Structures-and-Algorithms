#include"Image.h"
#include<cmath>

  void Image::lighten(){
    for(unsigned x=0; x<width(); x++){
      for(unsigned y=0; y<height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.l + 0.1 > 1.0) {
          p.l = 1.0;
          continue;
        }
        p.l += 0.1;
      }
    }
  }

  void Image::lighten(double amount){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.l + amount > 1.0){
          p.l = 1.0;
          continue;
        }
        p.l += amount;
      }
    }
  }

  void Image::darken(){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.l < 0.1){
          p.l = 0.0;
          continue;
        }
        p.l -= 0.1;
      }
    }
  }
  void Image::darken(double amount){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.l < amount){
          p.l = 0.0;
          continue;
        }
        p.l -= amount;
      }
    }
  }

  void Image::saturate(){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.s + 0.1 > 1.0) continue;

        p.s += 0.1;
      }
    }
  }

  void Image::saturate(double amount){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.s + amount > 1.0){
          p.s = 1.0;
          continue;
        }
        p.s += amount;
      }
    }
  }

  void Image::desaturate(){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.s < 0.1){
          p.s = 0.0;
          continue;
        }
        p.s -= 0.1;
      }
    }
  }

  void Image::desaturate(double amount){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.s < amount){
          p.s = 0.0;
          continue;
        }
        p.s -= amount;
      }
    }
  }

  void Image::grayscale(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        cs225::HSLAPixel & p = this->getPixel(x, y);
        p.s = 0;
      }
    }
  }

  void Image::rotateColor(double degrees){
    for(unsigned x=0; x<this->width(); x++){
      for(unsigned y=0; y<this->height(); y++){
        cs225::HSLAPixel & p = this->getPixel(x,y);
        if(p.h + degrees > 360){
          p.h += degrees - 360;
        }else if(p.h + degrees < 0){
            p.h += degrees + 360;
        }else p.h += degrees;
      }
    }
  }

  void Image::illinify(){
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          if(pixel.h >= 113.5 && pixel.h <= 282.5){
            pixel.h = 216;
          }else pixel.h = 11;
      }
    }
  }

  void Image::scale(double factor){
    cs225::PNG image(*this);

    unsigned int n_height=this->height()*factor;
    unsigned int n_width=this->width()*factor;


    double y1=this->height()/(double)n_height;
    double x1=this->width()/(double)n_width;


    if(x1>y1){
      x1=y1;
    }
    else{
      y1=x1;
    }

      this->resize(ceil(n_width),ceil(n_height));
      for(unsigned int x = 0; x<n_width;x++)
      {
        for(unsigned int y=0; y<n_height;y++)
        {
          int x2 = x*x1;
          int y2 = y*y1;
          this->getPixel(x,y)=image.getPixel(x2,y2);
        }
      }
  }


  void Image::scale(unsigned w, unsigned h){

    unsigned int n_width = w;
    unsigned int n_height = h;
    double x1 = (double)n_width/(this->width());
    double y1 = (double)n_height/(this->height());

    if(y1>x1){
      scale(x1);
    }
    else{
      scale(y1);
    }
  }
