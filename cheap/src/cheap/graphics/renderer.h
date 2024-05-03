#pragma once

#include "base/shader_program.h"
#include "../core/window.h"
#include "../graphics/layers/layer_manager.h"

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
		explicit renderer(const std::shared_ptr<window>& aWindow, const std::shared_ptr<layer_manager>& aLayer_manager);

		~renderer();

		void add_new_task(graphics_entity* aGraphics_entity) const
		{
			mLayer_manager->add_layer(aGraphics_entity);
		}

		static void clear();

		void draw_layers(int aTexture_slot = GL_TEXTURE0);

		void update() const;

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		std::shared_ptr<window> mWindow;
		std::shared_ptr<layer_manager> mLayer_manager;
		shader_program mShader_program;
	};
}
