#include "Pixel.hpp"

namespace OpenCG {
    Pixel::Pixel() {
        character = '?';
        characterColor = RGB_Color(255, 192, 203);
    }

    Pixel::Pixel(char character, RGB_Color characterColor) {
        this->character = character;
        this->characterColor = characterColor;
    }

    char Pixel::GetCharacter() {
        return character;
    }

    RGB_Color Pixel::GetColor() {
        return characterColor;
    }
}