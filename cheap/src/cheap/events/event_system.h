#pragma once

#include "app_event.h"
#include "input_event.h"
#include "game_event.h"
#include "input_system.h"

#include "../graphics/renderer.h"

namespace cheap {
	class event_system
	{
	public:
		event_system(
			const std::shared_ptr<window>& aWindow,
			const std::shared_ptr<renderer>& aRenderer,
			const std::shared_ptr<input_system>& aInput_system
		) :
			mWindow(aWindow),
			mRenderer(aRenderer),
			mInput_system(aInput_system),
			mEvent_list_per_frame(std::vector<event*>())
		{
			LOG();
		}

		~event_system()
		{
			LOG();
		}


		void handle(event* aEvent)
		{
			switch (aEvent->get_category()) {
				case event::category::APP:
					handle_app(dynamic_cast<app_event*>(aEvent));
					break;
				case event::category::INPUT:
					LOG_INFO("is input event");
					handle_input(dynamic_cast<input_event*>(aEvent));
					break;
				case event::category::GAME:
					handle_game(dynamic_cast<game_event*>(aEvent));
					break;
				default:
					LOG_INFO("no such category");
			}

			delete aEvent;
		}

		void set_vn(visual_novel* mVN)
		{
			mVisual_novel = mVN;
		}


	private:
		std::shared_ptr<window> mWindow;
		std::shared_ptr<renderer> mRenderer;
		std::shared_ptr<input_system> mInput_system;
		visual_novel* mVisual_novel;


		std::vector <event*> mEvent_list_per_frame;

		void handle_app(app_event* aEvent) const
		{
			switch (aEvent->get_type()) {
				case app_event::type::RENDER:
					PRINTLN("app_event::render");
					break;
				case app_event::type::UPDATE:
					PRINTLN("app_event::update");
					break;
				case app_event::type::WINDOW_RESIZE:
					// TODO
					mWindow->keep_aspect_ratio();
					PRINTLN("app_event::window_resize");
					break;
				case app_event::type::WINDOW_FULLSCREEN_MODE_UPDATE:
					PRINTLN("app_event::window_fullscreen_mode_update");
					break;
				case app_event::type::WINDOW_CLOSE:
					PRINTLN("app_event::window_close");
					break;
				default:
					LOG_INFO("ERROR::No such app_event::type " << static_cast<int>(dynamic_cast<app_event*>(aEvent)->get_type()));
			}
		}

		void handle_input(input_event* aEvent)
		{
			int id = mRenderer->inform_current_page_of_input_event(aEvent);


			if (aEvent->get_type() == input_event::type::MOUSE && dynamic_cast<mouse_event*>(aEvent)->is_action(mouse_event::PRESS) && mVisual_novel != nullptr) {
				LOG_INFO("Mouse Press, then update visual novel");
				mVisual_novel->update_is_ready_to_page(id);
			}
		}


		void handle_game(game_event* aEvent)
		{
		}
	};
}
