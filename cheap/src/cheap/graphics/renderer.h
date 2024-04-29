#pragma once

#include "graphics_entity.h"
#include "base/shader_program.h"
#include "base/transform.h"
#include "../core/window.h"

namespace cheap {


	// --------------------- file path ---------------------------------
	#define SHADER_PATH "src/cheap/graphics/base/shaders/"
	#define PIC_PATH "src/cheap/graphics/pic/"
	#define VERTEX_SHADER_FILENAME "vertex"
	#define FRAGMENT_SHADER_FILENAME "fragment"
	// --------------------- file path ---------------------------------

	// --------------------- OpenGL definitions ------------------------
	// OPENGL glDrawElement(mode, count, type, indices)
	// mode
	//		Specifies what kind of primitives to render.Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY and GL_TRIANGLES_ADJACENCY are accepted.
	#define ELEMENT_MODE GL_TRIANGLES
	// OPENGL glDrawElement(mode, count, type, indices)
	// count
	//		Specifies the number of elements to be rendered.
	#define ELEMENT_COUNT 6
	// OPENGL glDrawElement(mode, count, type, indices)
	// type
	//		Specifies the type of the values in indices.Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
	#define ELEMENT_TYPE GL_UNSIGNED_INT
	// OPENGL glDrawElement(mode, count, type, indices)
	// indices
	//		Specifies an offset of the first index in the array in the data store of the buffer currently bound to the GL_ELEMENT_ARRAY_BUFFER target.
	#define ELEMENT_INDICES (void*)0
	// --------------------- OpenGL definitions ------------------------

	//#define DEFAULT_NEAR (-1000.0f)
	//#define	DEFAULT_FAR (1000.0f)

	class renderer
	{
	public:
		explicit renderer(window* aWindow);

		~renderer();

		//void ResetProjectionMatrix(float xMin=0.0f, float yMin=0.0f, float xMax=window.width, float yMax=window.height)

		// TODO 屏幕空间是 -1.0 ~ 1.0 的正方形空间，但是屏幕是有宽高比的， 所以一张正方形图片会在长方形的窗口中显示为长方形。
		// TODO 解决方法：1.在 shader 中设置一个 scale 缩放矩阵，修正屏幕宽高比的影响
		// TODO 2. 在设置 图片/物体的 顶点数据时，就进行修正
		// TODO 但是在方法1，目前，我使用uniform在shader中修正宽高比后，图片/物体会被拉到屏幕中央，我不知道原因。
		//void reset_projection_matrix(const float aWindow_aspect_ration)
		//{
		//	// Set the projection matrix in the shader according to the window size
		//	//mShader_program.set_scale(glm::ortho(-aWindow_aspect_ration, aWindow_aspect_ration, -1.0f, 1.0f, -1000.0f, 1000.0f));
		//	//mShader_program.set_scale(glm::ortho(xMin, xMax, yMin, yMax, -1000.0f, 1000.0f));
		//}

		// pass left, bottom, right, top's proportion
		void add_draw_task_LBRT(const std::string& aPic_file_name, const float aLeft, const float aBottom, const float aWidth, const float aHeight, const bool aIs_RGBA);
		// pass TO left, bottom, right, top's proportion
		void add_draw_task_TO_LBRT(const std::string& aPic_file_name, const float aLeft, const float aBottom, const float aWidth, const float aHeight, const bool aIs_RGBA);
		// pass left, bottom, height, width's proportion
		void add_draw_task_LBHW(const std::string& aPic_file_name, const float aLeft, const float aBottom, const float aWidth, const float aHeight, const bool aIs_RGBA);
		// use picture's origin aspect ratio to calculate width
		void add_draw_task_LBH(const std::string& aPic_file_name, const float aLeft, const float aBottom, const float aHeight, const bool aIs_RGBA);
		// use picture's origin aspect ratio to calculate height
		void add_draw_task_LBW(bool aUse_width, const std::string& aPic_file_name, const float aLeft, const float aBottom, const float aWidth, const bool aIs_RGBA);

		static void clear();

		void draw(const int aTexture_slot = GL_TEXTURE0) const;

		void update() const;

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		window* mWindow;
		shader_program mShader_program;

		std::vector<graphics_entity*> mDraw_tasks;
	};
}
