#include "pch.h"
#include "graphics_entity.h"

namespace cheap {
	graphics_entity::graphics_entity(LBRT, const float aLeft, const float aBottom, const float aRight, const float aTop,
		const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
			aTop,
			aBottom,
			aLeft,
			aRight))
	{
		LOG();
	}

	graphics_entity::graphics_entity(TO_LBRT, const float aLeft, const float aBottom, const float aTo_right,
		const float aTo_top, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
			POS_TOP - aTo_top * 2.0f,
			POS_BOTTOM + aBottom * 2.0f,
			POS_LEFT + aLeft * 2.0f,
			POS_RIGHT - aTo_right * 2.0f))
	{
		LOG();
	}

	graphics_entity::graphics_entity(LBWH, const float aLeft, const float aBottom, const float aWidth,
		const float aHeight, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
			POS_BOTTOM + (aBottom + aHeight) * 2.0f,
			POS_BOTTOM + aBottom * 2.0f,
			POS_LEFT + aLeft * 2.0f,
			POS_LEFT + (aLeft + aWidth) * 2.0f))
	{
		LOG();
	}

	graphics_entity::graphics_entity(LBH_aspect_ratio, const float aLeft, const float aBottom, const float aHeight,
		const float aWindow_aspect_ratio, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
			POS_BOTTOM + (aBottom + aHeight) * 2.0f,
			POS_BOTTOM + aBottom * 2.0f,
			POS_LEFT + aLeft * 2.0f,
			POS_LEFT + (aLeft + aHeight * mTexture->get_aspect_ration()) * 2.0f / aWindow_aspect_ratio))
	{
		LOG();
	}

	graphics_entity::graphics_entity(LBW_aspect_ratio, const float aLeft, const float aBottom, const float aWidth,
		const float aWindow_aspect_ratio, const char* aPic_file_path, const bool aIs_RGBA) :
		mTexture(new texture(aPic_file_path, aIs_RGBA)),
		mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
			POS_BOTTOM + (aBottom + aWidth / mTexture->get_aspect_ration()) * 2.0f * aWindow_aspect_ratio,
			POS_BOTTOM + aBottom * 2.0f,
			POS_LEFT + aLeft * 2.0f,
			POS_LEFT + (aLeft + aWidth) * 2.0f))
	{
		LOG();
	}

	graphics_entity::~graphics_entity()
	{
		LOG();
		delete mVertex_array;
		delete mTexture;
	}

	void graphics_entity::before_draw(const int aTexture_slot) const
	{
		//LOG();
		mTexture->bind(aTexture_slot);
		mVertex_array->bind_VAO();
	}

	vertex_array* graphics_entity::get_vertex_array_by_proportion_of_edge_to_border(const float aTop,
		const float aBottom, const float aLeft, const float aRight)
	{
		LOG();
		const auto vertices = new float[VERTICES_LENGTH];
		const auto indices = new unsigned int[INDICES_LENGTH];
		// top right
		vertices[0] = aRight;    // x pos
		vertices[1] = aTop;      // y pos
		vertices[2] = POS_Z;     // z pos
		vertices[3] = TEX_S_END; // S/U texCoords
		vertices[4] = TEX_T_END; // T/V texCoords

		// bottom right
		vertices[5] = aRight;      // x pos
		vertices[6] = aBottom;     // y pos
		vertices[7] = POS_Z;       // z pos
		vertices[8] = TEX_S_END;   // S/U texCoords
		vertices[9] = TEX_T_BEGIN; // T/V texCoords

		// bottom left
		vertices[10] = aLeft;       // x pos
		vertices[11] = aBottom;     // y pos
		vertices[12] = POS_Z;       // z pos
		vertices[13] = TEX_S_BEGIN; // S/U texCoords
		vertices[14] = TEX_T_BEGIN; // T/V texCoords

		// top left
		vertices[15] = aLeft;       // x pos
		vertices[16] = aTop;        // y pos
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

		return new vertex_array(vertices, indices);
	}
}
