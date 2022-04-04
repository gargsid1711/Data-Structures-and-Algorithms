#include "StickerSheet.h"
#include "Image.h"
#include "cs225/HSLAPixel.h"

StickerSheet::StickerSheet(const Image & p, unsigned max){

  max_=max;
  count=0;
  y = new unsigned[max];
  x = new unsigned[max];
  stickers=new Image*[max];
  this->background = new Image(p);
  layer = new unsigned[max];
  for (unsigned i = 0; i < max; i++) {
         stickers[i] = NULL;
         x[i]=0;
         y[i]=0;
         layer[i]=0;
     }
}

StickerSheet::~StickerSheet(){
  destroy();
}


StickerSheet::StickerSheet(const StickerSheet & other)
{
  copy(other);
}

const StickerSheet &    StickerSheet::operator= (const StickerSheet &other){
  destroy();
  copy(other);
  return *this;
}

void    StickerSheet::changeMaxStickers (unsigned max){
  if(max_==max){
    return;
  }
  Image* b= new Image(*background);
  Image ** stickerstemp = new Image *[max];
  unsigned *ty = new unsigned[max];
  unsigned *tx = new unsigned[max];
  unsigned *l2 = new unsigned[max];
  unsigned sc=0;
  if(max>max_){
    for(unsigned i=0;i<max;i++){
      l2[i]=0;
      stickerstemp[i]=NULL;
    }
  }
  if(max<max_){
    for(unsigned i=max;i<max_;i++){
      if(layer[i]!=0){
        delete stickers[i];
        layer[i]=0;
      }
    }
    max_=max;
  }
  for(unsigned i = 0;i<max_;i++){
    if(i>=max){
      break;
    }
    if(layer[i]!=0){
      sc++;
      stickerstemp[i]=new Image(*stickers[i]);
      tx[i]=x[i];
      ty[i]=y[i];
      l2[i]=layer[i];
    }
    else{
      stickerstemp[i]=NULL;
      tx[i]=-1;
      ty[i]=-1;
      l2[i]=0;
    }
  }
  destroy();
  stickers=stickerstemp;
  x=tx;
  layer=l2;
  count=sc;
  y=ty;
  max_=max;
  background=b;
}
int StickerSheet::addSticker (Image &sticker, unsigned x1, unsigned y1){
  unsigned i=0;
  if(count<max_){
    while(i<max_){
      if(layer[i]==0){
        stickers[i]=new Image(sticker);
        x[i]=x1;
        y[i]=y1;
        count++;
        layer[i]=1;
        return i;
      }
      i++;
    }
   }
  return -1;
}
bool    StickerSheet::translate (unsigned index, unsigned x1, unsigned y1){
  if(index>=max_ || layer[index]==0){
    return false;
  }
  else{
    x[index]=x1;
    y[index]=y1;
    return true;
  }
}

void    StickerSheet::removeSticker (unsigned index){
  if(index<max_ && layer[index] !=0){
    delete stickers[index];
    stickers[index]=NULL;
    x[index]=-1;
    y[index]=-1;
    count-=1;
    layer[index]=0;
  }
}

Image *     StickerSheet::getSticker (unsigned index){
  if(index>=max_ ||layer[index]==0) return NULL;
  return stickers[index];
}

Image   StickerSheet::render () const{
  unsigned finalx=background->width();
  unsigned finaly=background->height();

  for(unsigned int a = 0; a<max_;a++){
    if(layer[a]!=0){
      if(finalx<stickers[a]->width()+x[a]){
        finalx=stickers[a]->width()+x[a];
      }
      if(finaly<stickers[a]->height()+y[a]){
        finalx=stickers[a]->height()+x[a];
      }
    }
  }
  Image * out = new Image(*background);
  out->resize(finalx,finaly);
  for(unsigned i = 0; i<max_;i++){
    if(layer[i]!=0){
      Image s = *stickers[i];
      unsigned stickerxmax = s.width();
      unsigned stickerymax = s.height();
      for(unsigned xco =x[i]; xco<x[i]+stickerxmax;xco++){
        for(unsigned yco =y[i]; yco<y[i]+stickerymax;yco++){
          cs225::HSLAPixel & pixel1 = s.getPixel(xco-x[i], yco-y[i]);
          cs225::HSLAPixel & pixel2 = out->getPixel(xco, yco);
          if(pixel1.a!=0){
            pixel2.h=pixel1.h;
            pixel2.l=pixel1.l;
            pixel2.s=pixel1.s;
            pixel2.a=pixel1.a;
          }
        }
      }
    }
  }
  Image background2 = *out;
  delete out;
  return background2;
}


void StickerSheet::copy(const StickerSheet & other){
  max_=other.max_;
  count=other.count;
  stickers=new Image*[max_];
  background = new Image(*(other.background));
  x=new unsigned[max_];
  y=new unsigned[max_];
  layer=new unsigned[max_];
  for(unsigned i =0; i<max_;i++){
    if(other.layer[i]!=0){
      layer[i]=other.layer[i];
      stickers[i]=new Image(*(other.stickers[i]));
      y[i]=other.y[i];
      x[i]=other.x[i];
    }
    else{
      stickers[i]=NULL;
      layer[i]=0;
      y[i]=0;
      x[i]=0;

    }
  }

}

void StickerSheet::destroy(){
  delete []y;
  delete []x;
  for(int i = 0; i<(int)max_;i++)
  {
      delete stickers[i];
      stickers[i]=NULL;
  }
  delete background;
  delete[] layer;
  delete[] stickers;
}
