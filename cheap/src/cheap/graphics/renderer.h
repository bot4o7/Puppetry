#pragma once

#include "graphics_entity.h"
#include "base/shader_program.h"
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
	#define ELEMENT_MODE GL_TRIANGLES
	// OPENGL glDrawElement(mode, count, type, indices)
	#define ELEMENT_COUNT 6
	// OPENGL glDrawElement(mode, count, type, indices)
	#define ELEMENT_TYPE GL_UNSIGNED_INT
	// OPENGL glDrawElement(mode, count, type, indices)
	#define ELEMENT_INDICES (void*)0
	// --------------------- OpenGL definitions ------------------------

	#define DEFAULT_RENDERER_CLEAR_COLOR 0.2f, 0.3f, 0.3f, 1.0f

	class renderer
	{
	public:
		explicit renderer(window* aWindow);

		~renderer();

		void add_draw_task(
			float          aX, float aY, float aZ,
			float          aHeight,
			const std::string& aPic_file_name, bool aIs_RGBA);

		void add_draw_task(
			float          aX, float    aY, float aZ,
			float          aWidth, bool aPlaceholder_height,
			const std::string& aPic_file_name, bool aIs_RGBA);

		void        add_draw_task(
			float          aX, float     aY, float aZ,
			float          aWidth, float aHeight,
			const std::string& aPic_file_name, bool aIs_RGBA);

		static void clear();

		void draw(int aTexture_slot = GL_TEXTURE0) const;

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
