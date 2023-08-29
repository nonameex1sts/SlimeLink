#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "ShaderText.h"
#include <string>
#include <map>
#include "ft2build.h"
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    Vector2   Size;       // Size of glyph
    Vector2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Text {
private:
    FT_Library ft;
    FT_Face face;
    FT_GlyphSlot g;
    ShaderText* shaderText;

    unsigned int vboId;
    unsigned int vaoId;

public:
    Text();
    void RenderText(const char* text, float x, float y, float sx, float sy);
    ~Text();
};