#include "pch.h"
#include "graphics_rectangle.h"

namespace cheap {
	graphics_rectangle::graphics_rectangle(const float aX, const float aY, const float aZ, const float aWidth,
		const float aHeight, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array(aWidth, aHeight,
			aX, aY, aZ))
	{
		LOG();
	}

	graphics_rectangle::graphics_rectangle(const float aX, const float aY, const float aZ, const float aWidth,
		bool aPlaceholder_height, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array(aWidth, aWidth / mTexture->get_aspect_ratio(),
			aX, aY, aZ))
	{
		LOG();
	}

	graphics_rectangle::graphics_rectangle(const float aX, const float aY, const float aZ, bool aPlaceholder_width,
		const float aHeight, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array(aHeight* mTexture->get_aspect_ratio(), aHeight,
			aX, aY, aZ))
	{
		LOG();
	}
	graphics_rectangle::graphics_rectangle(const float aX, const float aY, const float aZ, bool aPlaceholder_width, bool aPlaceholder_height, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array(1.0f, 1.0f,
			aX, aY, aZ))
	{
		LOG();
	}

	graphics_rectangle::~graphics_rectangle()
	{
		LOG();
		delete mVertex_array;
		delete mTexture;
	}

	void graphics_rectangle::before_draw(const int aTexture_slot) const
	{
		mTexture->bind(aTexture_slot);
		mVertex_array->bind_VAO();
	}

	vertex_array* graphics_rectangle::get_vertex_array(
		const float aWidth,
		const float aHeight,
		const float aX, const float aY, const float aZ)
	{
		LOG();
		const auto vertices = new float[VERTICES_LENGTH + LAYOUT_LENGTH];
		const auto indices = new unsigned int[INDICES_LENGTH];

		// top right
		vertices[0] = aWidth;    // x pos
		vertices[1] = aHeight;      // y pos
		vertices[2] = POS_Z;     // z pos
		vertices[3] = TEX_S_END; // S/U texCoords
		vertices[4] = TEX_T_END; // T/V texCoords
		// bottom right
		vertices[5] = aWidth;      // x pos
		vertices[6] = -aHeight;     // y pos
		vertices[7] = POS_Z;       // z pos
		vertices[8] = TEX_S_END;   // S/U texCoords
		vertices[9] = TEX_T_BEGIN; // T/V texCoords
		// bottom left
		vertices[10] = -aWidth;       // x pos
		vertices[11] = -aHeight;     // y pos
		vertices[12] = POS_Z;       // z pos
		vertices[13] = TEX_S_BEGIN; // S/U texCoords
		vertices[14] = TEX_T_BEGIN; // T/V texCoords
		// top left
		vertices[15] = -aWidth;       // x pos
		vertices[16] = aHeight;        // y pos
		vertices[17] = POS_Z;       // z pos
		vertices[18] = TEX_S_BEGIN; // S/U texCoords
		vertices[19] = TEX_T_END;   // T/V texCoords

		// first triangle
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 3;
		// second triangle
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;

		// layout x y z
		vertices[20] = aX;
		vertices[21] = aY;
		vertices[22] = aZ;
		vertices[23] = aX;
		vertices[24] = aY;
		vertices[25] = aZ;
		vertices[26] = aX;
		vertices[27] = aY;
		vertices[28] = aZ;
		vertices[29] = aX;
		vertices[30] = aY;
		vertices[31] = aZ;

		return new vertex_array(vertices, indices);
	}
}
