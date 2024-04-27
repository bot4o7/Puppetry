﻿#pragma once
#include "base/texture.h"
#include "base/vertex_array.h"

namespace cheap {


	class graphics_entity
	{
	public:
		// 传 Top Bottom Left Right 的坐标 TBLR
		//TBLR,
			// 传 与 Top Bottom Left Right 之间的间隔距离 To TBLR
			//TO_TBLR,
			// 传 Bottom Left 的坐标 BL， 以及 宽度Width、高度Height， BLWH
			//BLWH,
			// 传 Bottom Left 的坐标 BL， 以及 高度 Height, （以及图片本身的宽高比，图片宽高比可以从这个类自己的成员mTexture中取得）
			//BLH,
			// 传 Bottom Left 的坐标 BL， 以及 高度 Width, （以及图片本身的宽高比，图片宽高比可以从这个类自己的成员mTexture中取得）
			//BLW

			// lbrt  path, true
		enum class LBRT { vertex_layout_placeholder };
		enum class TO_LBRT { vertex_layout_placeholder };
		enum class LBWH { vertex_layout_placeholder };
		enum class LBH_aspect_ratio { vertex_layout_placeholder };
		enum class LBW_aspect_ratio { vertex_layout_placeholder };

		// pass  left, bottom right,top
		graphics_entity(LBRT, const float aLeft, const float aBottom, const float aRight, const float aTop, const char* aPic_file_path, const bool aIs_RGBA = false);
		// pass to_top, to_bottom to_left to_right
		graphics_entity(TO_LBRT, const float aLeft, const float aBottom, const float aTo_right, const float aTo_top, const char* aPic_file_path, const bool aIs_RGBA = false);
		// pass left_bottom_position, width, height
		graphics_entity(LBWH, const float aLeft, const float aBottom, const float aWidth, const float aHeight, const char* aPic_file_path, const bool aIs_RGBA = false);

		// pass L B and height, and aspect_ratio
		// use picture's origin aspect ratio to calculate width
		graphics_entity(LBH_aspect_ratio, const float aLeft, const float aBottom, const float aHeight, const float aWindow_aspect_ratio, const char* aPic_file_path, const bool aIs_RGBA = false);
		// pass L B and width, and aspect_ratio
		// use picture's origin aspect ratio to calculate height
		graphics_entity(LBW_aspect_ratio, const float aLeft, const float aBottom, const float aWidth, const float aWindow_aspect_ratio, const char* aPic_file_path, const bool aIs_RGBA = false);


		~graphics_entity();


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
		void before_draw(const int aTexture_slot) const;

	private:
		texture* mTexture;
		vertex_array* mVertex_array;

		static vertex_array* get_vertex_array_by_proportion_of_edge_to_border(const float aTop, const float aBottom, const float aLeft, const float aRight);
	};
}