#include "User/Inc/ssd1306/display.h"

void ssd1306_set_position(uint8_t x, uint8_t y) {
    ssd1306_write_cmd(0xb0 + y);
    ssd1306_write_cmd(((x & 0xf0) >> 4) | 0x10);
    ssd1306_write_cmd(x & 0x0f);
}

void ssd1306_display_char(uint8_t x,
                          uint8_t y,
                          uint8_t ch,
                          uint8_t font,
                          uint8_t color) {
    uint8_t offset = ch - ' ';
    ssd1306_set_position(x, y);
    if (font == SSD1306_FONT_TYPE_ASCII_8X16) {
        for (uint8_t i = 0; i < 8; i++) {
            ssd1306_write_data(color == SSD1306_FONT_DISPLAY_COLOR_WHITE ? SSD1306_FONT_TYPE_ASCII_8X16_LIB[offset][i] : ~SSD1306_FONT_TYPE_ASCII_8X16_LIB[offset][i]);
        }
        ssd1306_set_position(x, y + 1);
        for (uint8_t i = 0; i < 8; i++) {
            ssd1306_write_data(color == SSD1306_FONT_DISPLAY_COLOR_WHITE ? SSD1306_FONT_TYPE_ASCII_8X16_LIB[offset][i + 8] : ~SSD1306_FONT_TYPE_ASCII_8X16_LIB[offset][i + 8]);
        }
    } else if (font == SSD1306_FONT_TYPE_ASCII_8X6) {
        for (uint8_t i = 0; i < 6; i++) {
            ssd1306_write_data(color == SSD1306_FONT_DISPLAY_COLOR_WHITE ? SSD1306_FONT_TYPE_ASCII_8X6_LIB[offset][i] : ~SSD1306_FONT_TYPE_ASCII_8X6_LIB[offset][i]);
        }
    }
}

void ssd1306_display_string(uint8_t x,
                            uint8_t y,
                            const char* str,
                            uint8_t font,
                            uint8_t color) {
    uint8_t i = 0;
    while (str[i] != '\0') {
        ssd1306_display_char(x, y, str[i], font, color);
        x += (font == SSD1306_FONT_TYPE_ASCII_8X16) ? 8 : 6;
        if (x > 112) {
            x = 0;
            y += (font == SSD1306_FONT_TYPE_ASCII_8X16) ? 2 : 1;
        }
        i++;
    }
}

void ssd1306_display_bitmap(uint8_t start_x,
                            uint8_t start_y,
                            uint8_t width,
                            uint8_t height,
                            const uint8_t bitmap[],
                            uint8_t color) {
    for (uint8_t y = 0; y < height; y++) {
        ssd1306_set_position(start_x, start_y + y);
        for (uint8_t x = 0; x < width; x++) {
            ssd1306_write_data((color == SSD1306_FONT_DISPLAY_COLOR_WHITE) ? bitmap[y * width + x] : ~bitmap[y * width + x]);
        }
    }
}
