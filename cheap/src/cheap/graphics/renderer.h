#pragma once

#include "base/shader_program.h"
#include "../core/window.h"
#include "../graphics/layers/layer_manager.h"
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

	#define DEFAULT_RENDERER_CLEAR_COLOR 0.2f, 0.3f, 0.3f, 1.0f

	class renderer
	{
	public:
		explicit renderer(const std::shared_ptr<window>& aWindow);

		~renderer();

		void add_new_task(graphics_entity* aGraphics_entity) const
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->add_new_layer(aGraphics_entity);
		}

		static void clear();

		void draw_layers(page* aPage, double current_time, int aTexture_slot = GL_TEXTURE0);

		void draw(double current_time, int aTexture_slot = GL_TEXTURE0)
		{
			if (mCurrent_page == nullptr) return;

			mCurrent_page->bind();

			//static unsigned int current_page_id;
			// 0.proj
			// 1.view
			// 2.trans
			// 3.rotate
			// 4.scale
			// 5.opacity
			// 6.color
			static bool to_reset_uniform[7] = { false, false, false, false, false, false, false };
			for (auto task = mCurrent_page->mLayer_manager.get_top_layer_level(); task != nullptr;)
				if (task->mLayer->is_show()) {
					mCurrent_page->mShader_program.set_opacity(task->mLayer->get_opacity());

					if (task->mLayer->get_anim() != nullptr) {
						//LOG_INFO("anim is not nullptr");
						if (animation* anim = task->mLayer->get_anim(); anim->is_to_play(current_time)) {
							//LOG_INFO("is to play : " << static_cast<unsigned int>(anim->get_type()));
							switch (anim->get_type()) {
								case animation::type::TRANSLATION:
									to_reset_uniform[2] = true;
									mCurrent_page->mShader_program.use_translation(dynamic_cast<translation_animation*>(anim)->get(current_time));
									break;
								case animation::type::ROTATION:
									to_reset_uniform[3] = true;
									mCurrent_page->mShader_program.use_rotation(dynamic_cast<rotation_animation*>(anim)->get(current_time));
									break;
								case animation::type::OPACITY:
									to_reset_uniform[5] = true;
									mCurrent_page->mShader_program.use_opacity(dynamic_cast<opacity_animation*>(anim)->get(current_time));
									break;
								case animation::type::SCALE:
									to_reset_uniform[4] = true;
									mCurrent_page->mShader_program.use_scale(dynamic_cast<scale_animation*>(anim)->get(current_time));
									break;
								case animation::type::REFLECTION:
									/*mCurrent_page->mShader_program.use_scale(dynamic_cast<reflection_animation*>(anim)->get(current_time));*/
									break;
								case animation::type::COLOR:
									to_reset_uniform[6] = true;
								case animation::type::SHIFT:
								default:
									LOG_INFO("unkown animation type : " << static_cast<unsigned>(anim->get_type()));
							}
						}
					}
					task->mLayer->before_draw(aTexture_slot);
					glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);

					reset_uniform(to_reset_uniform);

					task = task->mBelow;
				}
		}

		void init_current_page()
		{
			mCurrent_page = new page(
				(mShader_path + VERTEX_SHADER_FILENAME).c_str(),
				(mShader_path + FRAGMENT_SHADER_FILENAME).c_str(),
				mWindow->get_aspect_ratio()
			);

			mCurrent_page->add_new_layer
			(new graphics_entity(
				0,
				graphics_entity::type::BG,
				0.f, 0.f, 0.9f,
				true,
				1.f,
				1.f,
				"data/images/egyptian-768x536.jpg",
				false,
				true,
				false,
				false,
				false
			));

			/*mCurrent_page->add_anime(0, new opacity_animation(
				0.2f,
				glfwGetTime(),
				10.0,
				9999,
				animation::relationship::LINEAR,
				true
			));*/


			mCurrent_page->add_new_layer
			(new graphics_entity(
				1,
				graphics_entity::type::OBJ,
				-0.3f, -0.1f, 0.f,
				true,
				0.6f,
				1.f,
				"data/images/friends.png",
				true,
				true,
				false,
				true,
				true
			));

			mCurrent_page->add_anime(1, new reflection_animation(
				glfwGetTime(),
				5.0,
				9999,
				animation::relationship::LINEAR,
				true,
				1.5f
			));

			mCurrent_page->add_new_layer
			(new graphics_entity(
				2,
				graphics_entity::type::OBJ,
				0.8f, 0.3f, 0.2f,
				true,
				0.4f,
				1.f,
				"data/images/ys.png",
				true,
				true,
				false,
				true,
				true
			));

			mCurrent_page->add_anime(2, new translation_animation(
				-1.6f, -0.6f, -0.4f,
				glfwGetTime(),
				5.0,
				9999,
				animation::relationship::LINEAR,
				true
			));
		}

		void update() const;

		// 0.proj
		// 1.view
		// 2.trans
		// 3.rotate
		// 4.scale
		// 5.opacity
		// 6.color
		// 7. tex NO
		void reset_uniform(bool* aIndex)
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->reset_uniform(aIndex);
		}

		void add_anime(unsigned int aGraphics_entity_id,
			animation* aAnimation)
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->add_anime(aGraphics_entity_id, aAnimation);
		}

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		// page_id to page
		std::unordered_map<unsigned int, page> mHash_page_list;
		// 我还需要做一个 default page?真麻烦啊
		page* mCurrent_page;

		std::shared_ptr<window> mWindow;
	};
}
