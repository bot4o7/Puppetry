#include "pch.h"
#include "renderer.h"

#include "animations/opacity_animation.h"
#include "animations/translation_animation.h"
#include "animations/rotation_animation.h"
#include "animations/scale_animation.h"

namespace cheap {



	renderer::renderer(const std::shared_ptr<window>& aWindow) :
		mShader_path(SHADER_PATH),
		mPic_path(PIC_PATH),
		mVertex_shader_filename(VERTEX_SHADER_FILENAME),
		mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
		mHash_page_list(std::unordered_map<unsigned int, page*>()),
		mPage_list(std::vector<page*>()),
		mCurrent_page(nullptr),
		mWindow(aWindow)
	{
		LOG();
		if (mWindow == nullptr)
			LOG_INFO("aWindow ptr is nullptr");
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		if (mCurrent_page != nullptr)
			mCurrent_page->bind();

		init_current_page();
	}

	renderer::~renderer()
	{
		LOG();
	}

	void renderer::add_new_task(
		graphics_entity* aGraphics_entity) const
	{
		if (mCurrent_page != nullptr)
			mCurrent_page->add_new_layer(aGraphics_entity);
	}

	void renderer::add_new_task(
		unsigned aPage_id,
		graphics_entity* aGraphics_entity)
	{
		if (mHash_page_list.contains(aPage_id)) {
			mHash_page_list[aPage_id]->add_new_layer(aGraphics_entity);
		} else {
			LOG_INFO("renderer::could not find page with id=" << aPage_id);
		}
	}

	void renderer::switch_current_page(
		unsigned aPage_id)
	{
		if (mCurrent_page->mId != aPage_id) {
			if (mHash_page_list.contains(aPage_id)) {
				mCurrent_page = mHash_page_list[aPage_id];
			}
		}
	}



	void renderer::draw_current_page(
		double current_time,
		int aTexture_slot)
	{
		if (mCurrent_page == nullptr) return;

		mCurrent_page->bind();

		mCurrent_page->draw(aTexture_slot, current_time);
	}

	void renderer::init_current_page()
	{
		mCurrent_page = new page(0,
			(mShader_path + VERTEX_SHADER_FILENAME).c_str(),
			(mShader_path + FRAGMENT_SHADER_FILENAME).c_str(),
			mWindow->get_aspect_ratio());

		mHash_page_list[0] = mCurrent_page;
		mPage_list.emplace_back(mCurrent_page);

		mCurrent_page->add_new_layer
		(new graphics_entity(
			0,
			graphics_entity::type::BG,
			0.f, 0.f, 0.9f,
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
			0.4f,
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

	void renderer::add_anime(
		unsigned aGraphics_entity_id,
		animation* aAnimation)
	{
		if (mCurrent_page != nullptr)
			mCurrent_page->add_anime(aGraphics_entity_id, aAnimation);
	}

	void renderer::clear()
	{
		glClearColor(DEFAULT_RENDERER_CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void renderer::update() const
	{
		glfwSwapBuffers(mWindow->get_raw_window());
		glfwPollEvents();
	}
}
