#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
    Image bg;
    bg.readFromFile("alma.png");
    Image a;
    a.readFromFile("yoda.png");
    a.scale(0.25);
    StickerSheet sheet(bg, 5);
    sheet.addSticker(a, bg.width()-200, bg.height()-a.height());
    sheet.addSticker(a, 50, bg.height()-a.height());
    sheet.addSticker(a, bg.width()/2, bg.height()-a.height());
    sheet.addSticker(a, 200, bg.height()-a.height());
    Image expected = sheet.render();
    expected.writeToFile("myImage.png");

  return 0;
}
