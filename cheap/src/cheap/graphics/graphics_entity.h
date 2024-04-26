#pragma once
#include "base/texture.h"
#include "base/vertex_array.h"

namespace cheap {


	class graphics_entity
	{
		//enum class layout_mode
		//{
		//	//rectangle's edges to screen top/bottom/left/right borders (value is proportion of edge to border
		//	//edge_to_screen_border_proportion,
		//	TOP_BOTTOM_LEFT_RIGHT_PROPORTION,
		//	// rectangle's bottom left pos to screen bottom left, width and height are also proportion of rectangle to screen
		//	LEFT_BOTTOM_WIDTH_HEIGHT_PROPORTION,
		//	// rectangle's bottom left pos to screen bottom left, width is also proportion of rectangle to screen
		//	// aspect_ratio == width / height
		//	LEFT_BOTTOM_WIDTH_ASPECT_RATIO_PROPORTION,
		//	// rectangle's bottom left pos to screen bottom left, height is also proportion of rectangle to screen
		//	// aspect_ratio == width / height
		//	LEFT_BOTTOM_HEIGHT_ASPECT_RATIO_PROPORTION
		//};
	public:
		// pass to_top, to_bottom to_left to_right
		graphics_entity(const float aTo_top, const float aTo_bottom, const float aTo_left, const float aTo_right, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mTexture(new texture(aPic_file_path, aIs_RGBA)),
			mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
				POS_TOP - aTo_top * 2.0f,
				POS_BOTTOM + aTo_bottom * 2.0f,
				POS_LEFT + aTo_left * 2.0f,
				POS_RIGHT - aTo_right * 2.0f))
		{
			LOG();
		}

		// use picture's origin aspect ratio to calculate width
		graphics_entity(const float aX, const float aY, const float aHeight, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mTexture(new texture(aPic_file_path, aIs_RGBA)),
			mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
				POS_BOTTOM + (aY + aHeight) * 2.0f,
				POS_BOTTOM + aY * 2.0f,
				POS_LEFT + aX * 2.0f,
				POS_LEFT + (aX + aHeight * mTexture->get_aspect_ration()) * 2.0f))
			/*(get_vertex_array_by_proportion_of_edge_to_border(
				1.0f,
				-1.0f,
				-1.0f,
				1.0f))*/
		{
			LOG();
		}
		// use picture's origin aspect ratio to calculate height
		graphics_entity(const bool aUse_wdith, const float aX, const float aY, const float aWidth, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mTexture(new texture(aPic_file_path, aIs_RGBA)),
			mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
				POS_BOTTOM + (aY + aWidth / mTexture->get_aspect_ration()) * 2.0f,
				POS_BOTTOM + aY * 2.0f,
				POS_LEFT + aX * 2.0f,
				POS_LEFT + (aX + aWidth) * 2.0f))
		{
			LOG();
		}
		// pass left_bottom_position, width, height
		graphics_entity(bool aLeft_bottom_width_height, const float aX, const float aY, const float aWidth, const float aHeight, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mTexture(new texture(aPic_file_path, aIs_RGBA)),
			mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
				POS_BOTTOM + (aY + aHeight) * 2.0f,
				POS_BOTTOM + aY * 2.0f,
				POS_LEFT + aX * 2.0f,
				POS_LEFT + (aX + aWidth) * 2.0f))
		{
			LOG();
		}
		// pass left_bottom_position height, aspect_ration
		graphics_entity(int aLeft_bottom_height_aspect_ration, const float aX, const float aY, const float aHeight, const float aAspect_ratio, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mTexture(new texture(aPic_file_path, aIs_RGBA)),
			mVertex_array(get_vertex_array_by_proportion_of_edge_to_border(
				POS_BOTTOM + (aY + aHeight) * 2.0f,
				POS_BOTTOM + aY * 2.0f,
				POS_LEFT + aX * 2.0f,
				POS_LEFT + (aX + aHeight * aAspect_ratio) * 2.0f))
		{
			LOG();
		}


		~graphics_entity()
		{
			LOG();
			delete mVertex_array;
			delete mTexture;
		}


		// before draw
		// 渲染前，再来绑定纹理 texture, 因为 texture 的数量有限，
		// 而绑定 texture 需要指定绑定在哪一个 texture slot，
		// 我自己显卡只有 16 个 texture slot，这个数量很少，所以 texture slot 平时一定很忙，经常改变。
		//
		// 相反的，VAO, VBO, IBO/EBO 就跟 texture buffer 一样可以有很多数量，但是不想 texture 这样受到 texture slot 的约束，可以在这个对象创建时就绑定好。
		// 但是绘制前就必须绑定 VAO 了
		//
		// shader_program.use() 的顺序跟VAO,texture的绑定没关系，draw之前调用即可
		//
		// 目前，VAO 和 texture 似乎不必手动 unbind, texture 似乎不必unbind，只需你不用的时候释放掉内存就行 glDeleteTextures
		void before_draw(const int aTexture_slot) const
		{
			//LOG();
			mTexture->bind(aTexture_slot);
			mVertex_array->bind_VAO();
		}


	private:
		texture* mTexture;
		vertex_array* mVertex_array;
		// TODO 下面这些代码，后面那些也不对，a b c d 的，妈的，很难看懂，不如直接多写几个构造函数
		//static vertex_array* get_vertex_array(const layout_mode aMode, const float a, const float b, const float c, const float d)
		//{
		//	switch (aMode) {
		//		case layout_mode::TOP_BOTTOM_LEFT_RIGHT_PROPORTION:
		//			// a = to_top
		//			// b = to_bottom
		//			// c = to_left
		//			// d = to_right
		//			return get_vertex_array_by_proportion_of_edge_to_border(
		//				POS_TOP - a * 2.0f,
		//				POS_BOTTOM + b * 2.0f,
		//				POS_LEFT + c * 2.0f,
		//				POS_RIGHT - d * 2.0f);
		//		case layout_mode::LEFT_BOTTOM_WIDTH_HEIGHT_PROPORTION:
		//			// a = to_left
		//			// b = to_bottom
		//			// c = width
		//			// d = height
		//			return get_vertex_array_by_proportion_of_edge_to_border(
		//				POS_BOTTOM + (b + d) * 2.0f,
		//				POS_BOTTOM + b * 2.0f,
		//				POS_LEFT + a * 2.0f,
		//				POS_LEFT + (a + c) * 2.0f);
		//		case layout_mode::LEFT_BOTTOM_WIDTH_ASPECT_RATIO_PROPORTION:
		//			// a = to_left
		//			// b = to_bottom
		//			// c = width
		//			// d = aspect_ratio
		//			return get_vertex_array_by_proportion_of_edge_to_border(
		//				POS_BOTTOM + c / d * 2.0f,
		//				POS_BOTTOM + b * 2.0f,
		//				POS_LEFT + a * 2.0f,
		//				POS_LEFT + c * 2.0f);
		//		case layout_mode::LEFT_BOTTOM_HEIGHT_ASPECT_RATIO_PROPORTION:
		//			// a = to_left
		//			// b = to_bottom
		//			// c = height
		//			// d = aspect_ration
		//			return get_vertex_array_by_proportion_of_edge_to_border(
		//				POS_BOTTOM + c * 2.0f,
		//				POS_BOTTOM + b * 2.0f,
		//				POS_LEFT + a * 2.0f,
		//				POS_LEFT + c * d * 2.0f);
		//	}

		//	LOG_INFO("no such layout_mode, return a null vertex_array");
		//	return nullptr;
		//}
		/**
			 *float vertices[] = {
				// positions          // texture coords
				 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
				 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
				-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
			};
			unsigned int indices[] = {
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};
			 */
		static vertex_array* get_vertex_array_by_proportion_of_edge_to_border(const float aTop, const float aBottom, const float aLeft, const float aRight)
		{
			LOG();
			const auto vertices = new float[VERTICES_LENGTH];
			const auto indices = new unsigned int[INDICES_LENGTH];
			// top right
			vertices[0] = aRight; // x pos
			vertices[1] = aTop; // y pos
			vertices[2] = POS_Z; // z pos
			vertices[3] = TEX_S_END; // S/U texCoords
			vertices[4] = TEX_T_END; // T/V texCoords

			// bottom right
			vertices[5] = aRight; // x pos
			vertices[6] = aBottom; // y pos
			vertices[7] = POS_Z; // z pos
			vertices[8] = TEX_S_END; // S/U texCoords
			vertices[9] = TEX_T_BEGIN; // T/V texCoords

			// bottom left
			vertices[10] = aLeft; // x pos
			vertices[11] = aBottom; // y pos
			vertices[12] = POS_Z; // z pos
			vertices[13] = TEX_S_BEGIN; // S/U texCoords
			vertices[14] = TEX_T_BEGIN; // T/V texCoords

			// top left
			vertices[15] = aLeft; // x pos
			vertices[16] = aTop; // y pos
			vertices[17] = POS_Z; // z pos
			vertices[18] = TEX_S_BEGIN; // S/U texCoords
			vertices[19] = TEX_T_END; // T/V texCoords

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
	};
}
