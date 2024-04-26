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

	class renderer
	{
	public:
		explicit renderer(window* aWindow)
			:
			mShader_path(SHADER_PATH),
			mPic_path(PIC_PATH),
			mVertex_shader_filename(VERTEX_SHADER_FILENAME),
			mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
			mWindow(aWindow),
			mShader_program(
				shader_program(
					(mShader_path + mVertex_shader_filename).c_str(),
					(mShader_path + mFragment_shader_filename).c_str())
			),
			mDraw_tasks(std::vector<graphics_entity*>()),
			mTransform(transform())
		{
			LOG();
			if (mWindow == nullptr)
				LOG_INFO("aWindow ptr is nullptr");

			mShader_program.bind();
			reset_projection_matrix(aWindow->get_aspect_ration());
		}

		~renderer()
		{
			LOG();
			for (const auto task : mDraw_tasks)
				delete task;
		}


		//void ResetProjectionMatrix(float xMin=0.0f, float yMin=0.0f, float xMax=window.width, float yMax=window.height)

		// TODO 屏幕空间是 -1.0 ~ 1.0 的正方形空间，但是屏幕是有宽高比的， 所以一张正方形图片会在长方形的窗口中显示为长方形。
		// TODO 解决方法：1.在 shader 中设置一个 scale 缩放矩阵，修正屏幕宽高比的影响
		// TODO 2. 在设置 图片/物体的 顶点数据时，就进行修正
		// TODO 但是在方法1，目前，我使用uniform在shader中修正宽高比后，图片/物体会被拉到屏幕中央，我不知道原因。
		void reset_projection_matrix(const float aWindow_aspect_ration)
		{
			// Set the projection matrix in the shader according to the window size
			mShader_program.set_scale(glm::ortho(-aWindow_aspect_ration, aWindow_aspect_ration, -1.0f, 1.0f, -1000.0f, 1000.0f));
			//mShader_program.set_scale(glm::ortho(xMin, xMax, yMin, yMax, -1000.0f, 1000.0f));
		}
		// pass x, y, height, width's proportion
		void add_draw_task(const std::string& aPic_file_name, const float aX, const float aY, const float aWidth, const float aHeight, const bool aIs_RGBA)
		{
			LOG();
			mDraw_tasks.emplace_back(new graphics_entity(
				true, aX, aY, aWidth, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
			);
		}
		// use picture's origin aspect ratio to calculate width
		void add_draw_task(const std::string& aPic_file_name, const float aX, const float aY, const float aHeight, const bool aIs_RGBA)
		{
			LOG();
			mDraw_tasks.emplace_back(new graphics_entity(
				aX, aY, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
			);
		}
		// use picture's origin aspect ratio to calculate height
		void add_draw_task(bool aUse_width, const std::string& aPic_file_name, const float aX, const float aY, const float aWidth, const bool aIs_RGBA)
		{
			LOG();
			mDraw_tasks.emplace_back(new graphics_entity(
				true, aX, aY, aWidth, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA)
			);
		}


		static void clear()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void draw(const int aTexture_slot)
		{
			for (const auto task : mDraw_tasks) {
				mShader_program.use(mTransform.get(), GL_TEXTURE0);

				//LOG();
				task->before_draw(aTexture_slot);

				glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
			}
		}

		void update() const
		{
			glfwSwapBuffers(mWindow->get_raw_window());
			glfwPollEvents();
		}

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		window* mWindow;
		shader_program mShader_program;

		std::vector<graphics_entity*> mDraw_tasks;
		transform mTransform;
	};
}
