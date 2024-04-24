#pragma once
#include "texture.h"
#include "vertex_array.h"

namespace cheap {
	class graphics_entity
	{
	public:

		/*graphics_entity(const float aTo_top, const float aTo_bottom, const float aTo_left, const float aTo_right, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mVertex_array(set_vertex_array(
				POS_TOP - aTo_top / 2.0f,
				POS_BOTTOM + aTo_bottom / 2.0f,
				POS_LEFT + aTo_left / 2.0f,
				POS_RIGHT - aTo_right / 2.0f)),
			mTexture(new texture(aPic_file_path, aIs_RGBA))
		{
			LOG();
			cheap::vertex_array::unbind();
		}*/

		/*graphics_entity(int aUse_pos_and_size, const float aX, const float aY, const float aWidth, const float aHeight, const char* aPic_file_path, const bool aIs_RGBA = false)
			:
			mVertex_array(set_vertex_array(
				POS_BOTTOM + (aY + aHeight) / 2.0f,
				POS_BOTTOM + aY / 2.0f,
				POS_LEFT + aX / 2.0f,
				POS_LEFT + (aX + aWidth) / 2.0f)),
			mTexture(new texture(aPic_file_path, aIs_RGBA))
		{
			LOG();
			cheap::vertex_array::unbind();
		}*/

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
			LOG();
			mTexture->bind(aTexture_slot);
			mVertex_array->bind_VAO();
		}


	private:
		vertex_array* mVertex_array;
		texture* mTexture;

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
			 //static vertex_array* set_vertex_array(const float aTop, const float aBottom, const float aLeft, const float aRight)
			 //{
			 //	LOG();
			 //	const auto vertices = new float[VERTICES_LENGTH];
			 //	const auto indices = new unsigned int[INDICES_LENGTH];
			 //	// top right
			 //	vertices[0] = aRight; // x pos
			 //	vertices[1] = aTop; // y pos
			 //	vertices[2] = POS_Z; // z pos
			 //	vertices[3] = TEX_S_END; // S/U texCoords
			 //	vertices[4] = TEX_T_END; // T/V texCoords

			 //	// bottom right
			 //	vertices[5] = aRight; // x pos
			 //	vertices[6] = aBottom; // y pos
			 //	vertices[7] = POS_Z; // z pos
			 //	vertices[8] = TEX_S_END; // S/U texCoords
			 //	vertices[9] = TEX_T_BEGIN; // T/V texCoords

			 //	// bottom left
			 //	vertices[10] = aLeft; // x pos
			 //	vertices[11] = aBottom; // y pos
			 //	vertices[12] = POS_Z; // z pos
			 //	vertices[13] = TEX_S_BEGIN; // S/U texCoords
			 //	vertices[14] = TEX_T_BEGIN; // T/V texCoords

			 //	// top left
			 //	vertices[15] = aLeft; // x pos
			 //	vertices[16] = aTop; // y pos
			 //	vertices[17] = POS_Z; // z pos
			 //	vertices[18] = TEX_S_BEGIN; // S/U texCoords
			 //	vertices[19] = TEX_T_END; // T/V texCoords

			 //	// first triangle
			 //	indices[0] = 0;
			 //	indices[1] = 1;
			 //	indices[2] = 3;
			 //	// second triangle
			 //	indices[3] = 1;
			 //	indices[4] = 2;
			 //	indices[5] = 3;

			 //	return new vertex_array(vertices, indices);
			 //}
	};
}
