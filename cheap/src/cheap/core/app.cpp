#include "pch.h"
#include "app.h"

#include "../events/event.h"
#include "../graphics/renderer.h"
#include "../graphics/animations/scale_animation.h"
#include "../graphics/animations/translation_animation.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(unsigned int aWidth, unsigned int aHeight)
		:
		mWindow(
			std::make_shared<window>(
				DEFAULT_TITLE,
				aWidth,
				aHeight,
				[this](event* aEvent) {this->on_event(aEvent); },
				[this]() {this->update(); })),
		mRenderer(std::make_shared<renderer>(mWindow)),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())
		),
		mEvent_system(std::make_shared <event_system>(mWindow, mRenderer, mInput_system))
	{
		LOG();
	}
	app::~app()
	{
		LOG();
	}


	void app::run()
	{
		LOG();

		//const renderer                      my_renderer(mWindow, mLayer_manager);
		//const float                   begin_frame = static_cast<float>(glfwGetTime());
		//float     last_frame = begin_frame;


		/*graphics_entity task(
			1,
			graphics_entity::type::OBJ,
			0.5f, 0.0f, -0.1f,
			true,
			0.5f,
			1.0f,
			"data/images/ys.png",
			true,
			true,
			false,
			true,
			true);
		graphics_entity task2(
			2,
			graphics_entity::type::OBJ,
			-0.2f, 0.0f, 0.1f,
			true, 0.5f,
			1.0f,
			"data/images/friends.png",
			true,
			true,
			false,
			true,
			true);

		page mPage(0, "src/cheap/graphics/base/shaders/vertex", "src/cheap/graphics/base/shaders/fragment", mWindow->get_aspect_ratio());

		mPage.mLayer_manager.add_layer(&task);
		mPage.mLayer_manager.add_layer(&task2);
		double a_time = glfwGetTime();



		animation* anim1 = new translation_animation(-0.5f, -0.2f, 1.0f, a_time, 4, 999, animation::relationship::LINEAR, true);
		animation* anim2 = new scale_animation(-1.5f, 1.5f, 1.0f, a_time, 4, 999, animation::relationship::LINEAR, false);




		anim1->set_graphics_entity(&task);
		anim2->set_graphics_entity(&task2);


		mPage.mLayer_manager.add_anime(anim1->get_graphics_entity_id(), anim1);
		mPage.mLayer_manager.add_anime(anim2->get_graphics_entity_id(), anim2);
*/


//anim1->replay(a_time + 1);
//anim2->replay(a_time + 2);
		while (app::is_running()) {
			/*if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				last_frame = current_frame;
			}*/
			float current = glfwGetTime();



			/*if (anim1->is_finished())
				anim1->replay(current);
			if (anim2->is_finished())
				anim2->replay(current);*/

			mRenderer->clear();
			//mRenderer->draw_layers(&mPage, current);
			mRenderer->draw_current_page(current);
			mRenderer->update();

		}
	}
	void app::clear() const
	{
		LOG();
		// Clear past events
		//m_event_system_->clear();
		// Clear old graphics and poll events
		mWindow->clear();
	}
	void app::update() const
	{
		LOG();
		// Set the active entities to be processed in this frame
		//m_event_system_->SetEntities(mEntityManager->GetEntities());
		// Render all graphics visible in this frame
		//m_renderer_->submit(mEntityManager->GetEntities());
		//m_renderer_->submit();
		// Update the graphics in the window
		mWindow->update();
	}
	bool app::is_running() const
	{
		//LOG();
		return !mWindow->is_closed();
	}
	void app::exit()
	{
		LOG();
		mWindow->close();
	}

	void app::on_event(event* aNew_event)
	{
		LOG();
		mEvent_system->handle(aNew_event);
	}

	// input* get_input() const;
	window* app::get_window() const
	{
		//LOG();
		return mWindow.get();
	}
	// cursor_system* get();
	// entity_system* get();
	// state_system* get();
	// font_system* get();
	// audio_system get();
	// file_system get();
}
#endif
