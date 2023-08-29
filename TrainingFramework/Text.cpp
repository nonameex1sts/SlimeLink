#include "stdafx.h"
#include "Text.h"
#include "Globals.h"

Text::Text()
{
    int temp;
    shaderText = new ShaderText;
    temp = shaderText->Init();

	FT_Init_FreeType(&ft);
	if (FT_Init_FreeType(&ft))
	{
		printf("1\n");
		//Try catch
	}

	if (FT_New_Face(ft, "../Resources/Fonts/FreeSans.ttf", 0, &face))
	{
		printf("2\n");
		//Try catch
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    if (FT_Load_Char(face, 'a', FT_LOAD_RENDER))
    {
        printf("3\n");
    }

    //for (unsigned char c = 0; c < 128; c++)
    //{
    //    // load character glyph 
    //    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    //    {
    //        printf("3\n");
    //        continue;
    //    }
    //}

    g = face->glyph;
}

void Text::RenderText(const char* text, float x, float y, float sx, float sy)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    glUseProgram(shaderText->GetProgram());

    glGenBuffers(1, &vboId);
    glEnableVertexAttribArray(shaderText->GetCoordAttribute());
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glVertexAttribPointer(shaderText->GetCoordAttribute(), 4, GL_FLOAT, GL_FALSE, 0, 0);

    glUniform1i(shaderText->GetColorUniform(), 0);
    glUniform1i(shaderText->GetTextUniform(), 0);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        g->bitmap.width,
        g->bitmap.rows,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        g->bitmap.buffer
    );

    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;

    GLfloat box[4][4] = {
        {x2,     -y2    , 0, 0},
        {x2 + w, -y2    , 1, 0},
        {x2,     -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    const char* p;

    //for (p = text; *p != '\0'; p++) {
    //    if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
    //        continue;

    //    glTexImage2D(
    //        GL_TEXTURE_2D,
    //        0,
    //        GL_RGB,
    //        g->bitmap.width,
    //        g->bitmap.rows,
    //        0,
    //        GL_RGB,
    //        GL_UNSIGNED_BYTE,
    //        g->bitmap.buffer
    //    );

    //    float x2 = x + g->bitmap_left * sx;
    //    float y2 = -y - g->bitmap_top * sy;
    //    float w = g->bitmap.width * sx;
    //    float h = g->bitmap.rows * sy;

    //    GLfloat box[4][4] = {
    //        {x2,     -y2    , 0, 0},
    //        {x2 + w, -y2    , 1, 0},
    //        {x2,     -y2 - h, 0, 1},
    //        {x2 + w, -y2 - h, 1, 1},
    //    };

    //    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    //    glDrawArrays(GL_TRIANGLES, 0, 3);

    //    x += (g->advance.x / 64) * sx;
    //    y += (g->advance.y / 64) * sy;
    //}
}

Text::~Text()
{
    delete shaderText;
}
