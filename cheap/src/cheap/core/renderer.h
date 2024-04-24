//#pragma once
//
//#include "graphics_entity.h"
//#include "shader_program.h"
//#include "transform.h"
//#include "window.h"
//
//namespace cheap {
//
//	#define SHADER_PATH "src/cheap/core/shaders/"
//	#define PIC_PATH "src/cheap/core/pic/"
//	#define VERTEX_SHADER_FILENAME "src/cheap/core/shaders/vertex"
//	#define FRAGMENT_SHADER_FILENAME "src/cheap/core/shaders/fragment"
//
//	class renderer
//	{
//	public:
//		explicit renderer(window* aWindow)
//			:
//			mShader_path(SHADER_PATH),
//			mPic_path(PIC_PATH),
//			mVertex_shader_filename(VERTEX_SHADER_FILENAME),
//			mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
//			mWindow(aWindow),
//			mShader_program(
//				shader_program(
//					//mShader_path + mVertex_shader_filename,
//					VERTEX_SHADER_FILENAME,
//					//mShader_path + mFragment_shader_filename)
//					FRAGMENT_SHADER_FILENAME)
//			),
//			task(graphics_entity(1, 0.0f, 0.0f, 0.2f, 0.29228f, "friends.png", true)),
//			/*mShader_program(
//				shader_program(
//					mShader_path + mVertex_shader_filename,
//					mShader_path + mFragment_shader_filename)
//			),*/
//			//mDraw_tasks(std::vector<graphics_entity*>()),
//			mTransform(transform())
//		{
//			LOG();
//			if (mWindow == nullptr)
//				LOG_INFO("aWindow ptr is nullptr");
//
//			/*mShader_program = new
//				shader_program(
//					mShader_path + mVertex_shader_filename,
//					mShader_path + mFragment_shader_filename);*/
//					//set_shader(ptr);
//
//		}
//
//		/*void set_shader(shader_program* ptr)
//		{
//			mShader_program = ptr;
//		}*/
//
//		~renderer()
//		{
//			LOG();
//			//delete mShader_program;
//			//for (const auto task : mDraw_tasks)
//			//delete task;
//		}
//
//		void add_draw_task(const std::string& aPic_file_name, const float aX, const float aY, const float aWidth, const float aHeight, const bool aIs_RGBA)
//		{
//			LOG();
//			//mDraw_tasks.emplace_back(
//			//delete task;
//			task = graphics_entity(1, aX, aY, aWidth, aHeight, (PIC_PATH + aPic_file_name).c_str(), aIs_RGBA);
//			//);
//		}
//
//		static void clear()
//		{
//			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT);
//		}
//
//		void draw()
//		{
//			//for (const auto task : mDraw_tasks) {
//				//mShader_program.use(mTransform.get(), GL_TEXTURE0);
//
//
//			/*task = graphics_entity(1, 0.0f, 0.0f, 0.2f, 0.29228f, "friends.png", true);*/
//			mShader_program.use(glm::mat4(1.0f), GL_TEXTURE0);
//			LOG();
//			task.before_draw(GL_TEXTURE0);
//
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//			//}
//
//			glfwSwapBuffers(mWindow->get_raw_window());
//			glfwPollEvents();
//		}
//
//
//
//	private:
//		std::string mShader_path;
//		std::string mPic_path;
//		std::string mVertex_shader_filename;
//		std::string mFragment_shader_filename;
//
//		window* mWindow;
//		//shader_program* mShader_program;
//		shader_program mShader_program;
//
//		//std::vector<graphics_entity*> mDraw_tasks;
//		graphics_entity task;
//		transform mTransform;
//	};
//}
