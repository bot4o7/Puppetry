#pragma once
#include "base/texture.h"
#include "base/vertex_array.h"

namespace cheap {


	class graphics_rectangle
	{
	public:
		// pass the position (x,y,z)of the center of rectangle picture
		// pass the width and height of the rectangle picture
		graphics_rectangle(
			float   aX, float            aY, float aZ,
			float   aWidth, float        aHeight,
			const char* aPic_file_path, bool aIs_RGBA = false);
		// pass the position (x,y,z)of the center of rectangle picture
		// pass the height of the rectangle picture,
		// use picture's origin aspect to calculate width
		graphics_rectangle(
			float   aX, float            aY, float aZ,
			float   aWidth, bool         aPlaceholder_height,
			const char* aPic_file_path, bool aIs_RGBA = false);
		// pass the position (x,y,z)of the center of rectangle picture
		// pass the width of the rectangle picture,
		// use picture's origin aspect to calculate height
		graphics_rectangle(
			float   aX, float                 aY, float aZ,
			bool        aPlaceholder_width, float aHeight,
			const char* aPic_file_path, bool      aIs_RGBA = false);
		// pass position of xyz.   set width and height to 1.0f
		graphics_rectangle(float       aX, float aY, float aZ, bool aPlaceholder_width, bool aPlaceholder_height,
			const char* aPic_file_path, bool aIs_RGBA);

		~graphics_rectangle();


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
		void before_draw(int aTexture_slot) const;


		// TODO
		void update_translation(
			const float aX_offset,
			const float aY_offset,
			const float aZ_offset) const
		{
			LOG();

			float* vertices = mVertex_array->get_vertices();

			vertices[20] += aX_offset;
			vertices[21] += aY_offset;
			vertices[22] += aZ_offset;

			vertices[23] += aX_offset;
			vertices[24] += aY_offset;
			vertices[25] += aZ_offset;

			vertices[26] += aX_offset;
			vertices[27] += aY_offset;
			vertices[28] += aZ_offset;

			vertices[29] += aX_offset;
			vertices[30] += aY_offset;
			vertices[31] += aZ_offset;

			mVertex_array->update_vbo();
		}
		// TODO 暂时真不想做旋转的更新，等会
		void update_rotation(
			float   aX,
			float            aY,
			float aZ,
			bool   aPlaceholder_width,
			float        aHeight)
		{
		}
		// TODO  暂时不考虑 z 轴的缩放。。。。因为都是图片
		void update_scale(
			float   aX_scale,
			float   aY_scale,
			float   aZ_scale)
		{
			LOG();

			float* vertices = mVertex_array->get_vertices();

			// top right
			vertices[0] *= aX_scale;
			vertices[1] *= aY_scale;
			//vertices[2] *= aZ_scale;

			// bottom ri*=aX_scale;
			vertices[5] *= aX_scale;
			vertices[6] *= aY_scale;
			//vertices[7] *= aZ_scale;

			// bottom le*=aX_scale;
			vertices[10] *= aX_scale;
			vertices[11] *= aY_scale;
			//vertices[12] *= aZ_scale;

			// top left	*=aX_scale;
			vertices[15] *= aX_scale;
			vertices[16] *= aY_scale;
			//vertices[17] *= aZ_scale;

			mVertex_array->update_vbo();
		}

		[[nodiscard]] bool is_pos_in_rectangle2D(const double aPos_x, const double aPos_y)const
		{
			// right
			if (mVertex_array->is_beyond_right_border(aPos_x)) return false;

			// top
			if (mVertex_array->is_beyond_top_border(aPos_y)) return false;

			// left
			if (mVertex_array->is_beyond_left_border(aPos_x)) return false;

			// bottom
			if (mVertex_array->is_beyond_bottom_border(aPos_y)) return false;

			LOG_INFO("in rectangle region");

			return true;
		}

	private:
		texture* mTexture;
		vertex_array* mVertex_array;

		static vertex_array* get_vertex_array(
			float aWidth,
			float aHeight,
			float aX, float aY, float aZ);
	};
}
