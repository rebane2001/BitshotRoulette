#include <PNGdec.h>
PNG png;

#define MAX_IMAGE_WIDTH 135
int16_t xpos = 0;
int16_t ypos = 0;
uint16_t outlineC = 1;

#define VIC_BLACK        0x0000
#define VIC_WHITE        0xFFFF
#define VIC_BROWN_DARK   0xA389
#define VIC_BROWN_LIGHT  0xE590
#define VIC_RED_DARK     0x7165
#define VIC_RED_LIGHT    0xB34C
#define VIC_SKY_DARK     0x869B
#define VIC_SKY_LIGHT    0xC7FF
#define VIC_PINK_DARK    0xA2F6
#define VIC_PINK_LIGHT   0xE4FE
#define VIC_GREEN_DARK   0x54E9
#define VIC_GREEN_LIGHT  0x96F0
#define VIC_BLUE_DARK    0x41B1
#define VIC_BLUE_LIGHT   0x7B99
#define VIC_YELLOW_DARK  0xBE4E
#define VIC_YELLOW_LIGHT 0xFFF5

uint16_t vic_colors[] = { VIC_BLACK, VIC_WHITE, VIC_BROWN_DARK, VIC_BROWN_LIGHT, VIC_RED_DARK, VIC_RED_LIGHT, VIC_SKY_DARK, VIC_SKY_LIGHT, VIC_PINK_DARK, VIC_PINK_LIGHT, VIC_GREEN_DARK, VIC_GREEN_LIGHT, VIC_BLUE_DARK, VIC_BLUE_LIGHT, VIC_YELLOW_DARK, VIC_YELLOW_LIGHT };

#define HIGHLIGHT_COLOR 0xFFE0

// https://github.com/Bodmer/TFT_eSPI/blob/master/examples/PNG%20Images/Flash_transparent_PNG/png_support.ino
void pngDrawHelper(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];          // Line buffer for rendering
  uint8_t  maskBuffer[1 + MAX_IMAGE_WIDTH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, maskBuffer, 255)) {
    // Note: pushMaskedImage is for pushing to the TFT and will not work pushing into a sprite
    if (outlineC != 1) {
      tft.drawBitmap(xpos - 1, ypos + pDraw->y, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos + 1, ypos + pDraw->y, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos, ypos + pDraw->y - 1, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos, ypos + pDraw->y + 1, maskBuffer, pDraw->iWidth, 1, outlineC);
    } else {
      tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
    }
  }
}

void drawPng(const void *image, uint64_t size, int x, int y) {
  xpos = x;
  ypos = y;
  uint16_t pngw = 0, pngh = 0;
  int16_t rc = png.openFLASH((uint8_t *)image, size, pngDrawHelper);

  if (rc == PNG_SUCCESS) {
    pngw = png.getWidth();
    pngh = png.getHeight();

    tft.startWrite();
    rc = png.decode(NULL, 0);
    tft.endWrite();
    png.close();
  } else {
    Serial.println("ERROR DECODING IMAGE"); 
  }
}

void drawPngOutline(const void *image, uint64_t size, int x, int y, uint16_t outline) {
  outlineC = outline;
  drawPng(image, size, x, y);
  outlineC = 1;
}

void drawPngOutline(const void *image, uint64_t size, int x, int y) {
  drawPngOutline(image, size, x, y, HIGHLIGHT_COLOR);
}

void drawPngOutline(const void *image, uint64_t size, uint16_t outline) {
  drawPngOutline(image, size, 0, 0, outline);
}

void drawPngOutline(const void *image, uint64_t size) {
  drawPngOutline(image, size, 0, 0);
}

void drawPng(const void *image, uint64_t size) {
  drawPng(image, size, 0, 0);
}