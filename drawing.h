#include <PNGdec.h>
PNG png;

#define MAX_IMAGE_WIDTH 135
int16_t xpos = 0;
int16_t ypos = 0;
uint16_t outlineC = 0;

#define HIGHLIGHT_COLOR 0xFFE0

// https://github.com/Bodmer/TFT_eSPI/blob/master/examples/PNG%20Images/Flash_transparent_PNG/png_support.ino
void pngDrawHelper(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WIDTH];          // Line buffer for rendering
  uint8_t  maskBuffer[1 + MAX_IMAGE_WIDTH / 8];  // Mask buffer

  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);

  if (png.getAlphaMask(pDraw, maskBuffer, 255)) {
    // Note: pushMaskedImage is for pushing to the TFT and will not work pushing into a sprite
    if (outlineC != 0) {
      tft.drawBitmap(xpos - 1, ypos + pDraw->y, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos + 1, ypos + pDraw->y, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos, ypos + pDraw->y - 1, maskBuffer, pDraw->iWidth, 1, outlineC);
      tft.drawBitmap(xpos, ypos + pDraw->y + 1, maskBuffer, pDraw->iWidth, 1, outlineC);
    }
    tft.pushMaskedImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer, maskBuffer);
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
  }
}

void drawPngOutline(const void *image, uint64_t size, int x, int y, uint16_t outline) {
  outlineC = outline;
  drawPng(image, size, x, y);
  outlineC = 0;
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