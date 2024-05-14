#pragma once

#include "../core/visual_novel.h"
#include "base/shader_program.h"
#include "../core/window.h"
#include "../events/input_event.h"
#include "../graphics/layers/layer_manager.h"
#include "animations/opacity_animation.h"
#include "animations/reflection_animation.h"
#include "animations/rotation_animation.h"
#include "animations/translation_animation.h"
#include "pages/page.h"

namespace cheap {
	struct page_param;

	// --------------------- file path ---------------------------------
	#define SHADER_PATH "data/shaders/"
	#define PIC_PATH "data/images/"
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

		// add to current_page
		void add_new_task(graphics_entity* aGraphics_entity) const
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->add_new_layer(aGraphics_entity);
		}

		void add_new_task(
			const unsigned int aPage_id, graphics_entity* aGraphics_entity)
		{
			if (mHash_page_list.contains(aPage_id)) {
				mHash_page_list[aPage_id]->add_new_layer(aGraphics_entity);
			} else {
				LOG_INFO("renderer::could not find page with id=" << aPage_id);
			}
		}

		void add_new_task_current_page(graphics_entity* aGraphics_entity) const
		{
			if (mCurrent_page != nullptr) {
				mCurrent_page->add_new_layer(aGraphics_entity);
			} else {
				LOG_INFO("renderer::current_page is null");
			}
		}

		void switch_current_page(
			const unsigned int aPage_id)
		{
			if (mCurrent_page->mId != aPage_id) {
				if (mHash_page_list.contains(aPage_id)) {
					mCurrent_page = mHash_page_list[aPage_id];
				}
			}
		}

		static void clear();
		// draw layers of page
		void draw_page(page* aPage, double current_time, int aTexture_slot = GL_TEXTURE0) const;

		void draw_page(
			const unsigned int aPage_id,
			const double       current_time,
			const int          aTexture_slot = GL_TEXTURE0)
		{
			if (mHash_page_list.contains(aPage_id)) {
				draw_page(mHash_page_list[aPage_id], current_time, aTexture_slot);
			} else {
				LOG_INFO("renderer::could not find page with id=" << aPage_id);
			}
		}

		// draw layers of current_page
		void draw_current_page(
			const double current_time,
			const int    aTexture_slot = GL_TEXTURE0) const
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
			bool to_reset_uniform[7] = { false, false, false, false, false, false, false };
			for (auto task = mCurrent_page->mLayer_manager.get_top_layer_level(); task != nullptr;)
				if (task->mLayer->is_show()) {
					mCurrent_page->mShader_program.set_opacity(task->mLayer->get_opacity());

					if (task->mLayer->get_anim() != nullptr) {
						//LOG_INFO("anim is not nullptr");
						if (animation* anim = task->mLayer->get_anim(); anim->is_to_play(current_time)) {
							//if (animation* anim = task->mLayer->get_anim(); !anim->is_graphics_entity_is_playing_anim() && anim->is_to_play(current_time)) {
							LOG_INFO("is to play : " << static_cast<unsigned int>(anim->get_type()));
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
									LOG_INFO("scale anime");
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
		void next_page(page* aPage)
		{
			if (aPage == mCurrent_page) return;


			mHash_page_list.erase(mCurrent_page->mId);
			delete mCurrent_page;
			mCurrent_page = aPage;
		}

		void prepare_page_param(page_param* aParam)
		{
			page* aPage = new page(aParam->id, (mShader_path + VERTEX_SHADER_FILENAME).c_str(),
				(mShader_path + FRAGMENT_SHADER_FILENAME).c_str(),
				mWindow->get_aspect_ratio());

			mHash_page_list[aParam->id] = aPage;
			LOG_INFO("NUMBER: " << aParam->graphics_entity_num);
			for (int i = 0; i < aParam->graphics_entity_num; ++i) {
				graphics_entity* layer_to_add = new graphics_entity(
					aParam->param_list[i]->mId,
					graphics_entity::type::OBJ,
					aParam->param_list[i]->mX,
					aParam->param_list[i]->mY,
					aParam->param_list[i]->mZ,
					aParam->param_list[i]->mHeight,
					1.f,
					aParam->param_list[i]->mPic_file_path,
					aParam->param_list[i]->mIs_RGBA,
					true,
					false,
					aParam->param_list[i]->mIs_receive_mouse,
					true
				);

				aPage->add_new_layer(layer_to_add);
			}
			next_page(aPage);
		}

		void init_current_page()
		{


			mCurrent_page = new page(0,
				(mShader_path + VERTEX_SHADER_FILENAME).c_str(),
				(mShader_path + FRAGMENT_SHADER_FILENAME).c_str(),
				mWindow->get_aspect_ratio()
			);

			mHash_page_list[0] = mCurrent_page;

			mCurrent_page->add_new_layer
			(new graphics_entity(
				0,
				graphics_entity::type::BG,
				0.f, 0.f, 0.9f,
				1.f,
				1.f,
				"data/images/egyptian-768x536.jpg",
				false,
				true,
				false,
				false,
				false
			));

			mCurrent_page->add_new_layer
			(new graphics_entity(
				1,
				graphics_entity::type::OBJ,
				-0.3f, -0.1f, 0.f,
				0.6f,
				1.f,
				"data/images/friends.png",
				true,
				true,
				false,
				false,
				false
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
				0.4f,
				1.f,
				"data/images/ys.png",
				true,
				true,
				false,
				false,
				false
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
		void reset_uniform(bool* aIndex) const
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->reset_uniform(aIndex);
		}

		void add_anime(
			const unsigned int aGraphics_entity_id,
			animation* aAnimation)const
		{
			if (mCurrent_page != nullptr)
				mCurrent_page->add_anime(aGraphics_entity_id, aAnimation);
		}


		[[nodiscard]] page* get_current_page() const
		{
			return mCurrent_page;
		}

		int key_call(key_event* aEvent)
		{
			switch (aEvent->get_action()) {
				case key_event::action::PRESS:
					PRINTLN("key_event::press");
					break;
				case key_event::action::RELEASE:
					PRINTLN("key_event::release");
					break;
				case key_event::action::REPEAT:
					PRINTLN("key_event::repeat");
					break;
				case key_event::action::TEXT_INPUT:
					PRINTLN("key_event::text_input");
					break;
				default:
					LOG_INFO("key_event no such action");
			}
			return -1;
		}
		int mouse_call(mouse_event* aEvent)
		{
			if (mCurrent_page == nullptr) return -1;

			return mCurrent_page->mouse_call(aEvent->get_action(), aEvent, glfwGetTime());
		}
		int inform_current_page_of_input_event(input_event* aEvent)
		{
			switch (aEvent->get_type()) {
				case input_event::type::KEYBOARD:
					return key_call(dynamic_cast<key_event*>(aEvent));
					break;
				case input_event::type::MOUSE:
					return mouse_call(dynamic_cast<mouse_event*>(aEvent));
					break;
				default:
					LOG_INFO("the input_event's get_type() is not KEYBOARD or MOUSE");
			}
		}

	private:
		std::string mShader_path;
		std::string mPic_path;
		std::string mVertex_shader_filename;
		std::string mFragment_shader_filename;

		// page_id to page
		std::unordered_map<unsigned int, page*> mHash_page_list;
		// 我还需要做一个 default page?真麻烦啊
		page* mCurrent_page;

		std::shared_ptr<window> mWindow;
	};
}
