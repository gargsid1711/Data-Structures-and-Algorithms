/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <iostream>
#include "Image.h"
class StickerSheet
{
public:
  StickerSheet(const Image &picture,unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  Image 	render () const;
  const StickerSheet& 	operator= (const StickerSheet &other);
  Image * 	getSticker (unsigned index);
  void copy(const StickerSheet & other);
  int 	addSticker (Image &sticker, unsigned x, unsigned y);
  bool 	translate (unsigned index, unsigned x, unsigned y);
  void 	removeSticker (unsigned index);
  void 	changeMaxStickers (unsigned max);
  void destroy();
private:
  Image ** stickers;
  Image * background;
  unsigned * layer;
  unsigned count;
  unsigned max_;
  unsigned * x;
  unsigned * y;
};
