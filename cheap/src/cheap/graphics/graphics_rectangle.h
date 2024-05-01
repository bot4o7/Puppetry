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
		void update()
		{
			LOG_INFO("graphics_rectangle::update() : NOT IMPLEMENTED YET.......");
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
