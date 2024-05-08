#pragma once

#include "base/shader_program.h"
#include "../core/window.h"
#include "animations/opacity_animation.h"
#include "animations/reflection_animation.h"
#include "animations/rotation_animation.h"
#include "animations/translation_animation.h"
#include "pages/page.h"

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
	/*void draw_call()
	{
		glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
	}*/

	#define DEFAULT_RENDERER_CLEAR_COLOR 0.2f, 0.3f, 0.3f, 1.0f

	class renderer
	{
	public:
		explicit renderer(const std::shared_ptr<window>& aWindow);

		~renderer();

		// add to current_page
		void add_new_task(graphics_entity* aGraphics_entity) const;

		void add_new_task(unsigned int aPage_id, graphics_entity* aGraphics_entity);

		void switch_current_page(unsigned int aPage_id);

		static void clear();
		// draw layers of page

		// draw layers of current_page
		void draw_current_page(double current_time, int aTexture_slot = GL_TEXTURE0);


		void init_current_page();

		void update() const;

		void add_anime(unsigned int aGraphics_entity_id,
			animation* aAnimation);

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		// page_id to page
		std::unordered_map<unsigned int, page*> mHash_page_list;
		std::vector<page*> mPage_list;
		// 我还需要做一个 default page?真麻烦啊
		page* mCurrent_page;

		std::shared_ptr<window> mWindow;
	};
}
