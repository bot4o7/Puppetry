#pragma once

#include <ranges>

#include "../layers/layer_manager.h"
#include "../../entity/graphics_entity.h"
#include "../animations/animation.h"
#include "../base/shader_program.h"
#include "../../events/input_event.h"
#include "../animations/scale_animation.h"

namespace cheap {
	class page
	{
	public:
		//	// 初始化时，由高层往底层遍历、添加，这样如果有拦截的，就可以直接结束遍历了
		//	std::vector<unsigned int> mOn_hover_list;
		//	std::vector<unsigned int> mOn_click_list;
		//	std::vector<unsigned int> mOn_key_press_list;
		//	std::vector<unsigned int> mOn_key_repeat_list;
		//};
		// 程序在页面page切换时，记录当前page为current page
		// 用户点击屏幕时，程序得到一个点击事件、移动光标时，也得到点击事件
		// 点击事件会被拿到current page检查是否有接受点击的，如果有，那么接收后做什么
		// 光标悬停事件也如此。


		unsigned int mId;


		std::vector<unsigned int> mOn_hover_list;

		int mouse_call(mouse_event::action aAction, mouse_event* aEvent, double current_time)
		{
			LOG_INFO("interactive_list :" << mInteractive_entity_list.size());
			LOG_INFO("action :" << static_cast<unsigned>(aAction));
			static graphics_entity* current_highlight_gfx_entity = nullptr;

			static double pos_x;
			static double pos_y;
			if (aAction == mouse_event::MOVE) {
				pos_x = ((mouse_move_event*)aEvent)->mX;
				pos_y = ((mouse_move_event*)aEvent)->mY;

				if (current_highlight_gfx_entity != nullptr) {
					if (!current_highlight_gfx_entity->is_pos_in_region(pos_x, pos_y)) {
						LOG();
						mLayer_manager.add_anime(current_highlight_gfx_entity->mId, new scale_animation(0.8f, 0.8f, 1.f, current_time, 0.05, animation::relationship::LINEAR, false, current_highlight_gfx_entity));
						current_highlight_gfx_entity = nullptr;
					}
				} else {
					LOG_INFO("current is null");
				}
			} else {
				LOG_INFO("action is not MOVE");
			}

			int id = -1;
			float z = 2.f;
			graphics_entity* gfx = nullptr;
			for (auto gfx_entity : mInteractive_entity_list) {
				LOG_INFO("for loop");
				if (gfx_entity->mIs_receive_mouse) {
					switch (aAction) {
						case mouse_event::MOVE:
							LOG_INFO("not here");
							if (gfx_entity != current_highlight_gfx_entity && gfx_entity->is_pos_in_region(pos_x, pos_y)) {
								LOG_INFO("here");
								if (gfx == nullptr) {
									gfx = gfx_entity;
								} else if (gfx_entity->mZ < gfx->mZ) {
									gfx = gfx_entity;
								}
							}
							break;
						case mouse_event::PRESS:
							if (gfx_entity->is_pos_in_region(pos_x, pos_y)) {
								if (gfx_entity->mZ < z) {
									id = gfx_entity->mId;
									z = gfx_entity->mZ;
								}
							}
							break;
						case mouse_event::SCROLL:
							break;
						case mouse_event::RELEASE:

							break;
					}
				} else {
					LOG_INFO("no receive mouse");
				}
			}
			if (aAction == mouse_event::MOVE && gfx != nullptr) {
				mLayer_manager.add_anime(gfx->mId, new scale_animation(1.25f, 1.25f, 1.f, current_time, 0.05, animation::relationship::LINEAR, false, gfx));
				current_highlight_gfx_entity = gfx;
			}
			return id;
		}

		page(
			const unsigned int aId,
			const char* aVertex_path,
			const char* aFragment_path,
			const float aWindow_aspect_ratio)
			:
			mId(aId),
			mHash_graphics_entity(std::unordered_map<unsigned int, graphics_entity*>()),
			mInteractive_entity_list(std::vector<graphics_entity*>()),
			mLayer_manager(layer_manager()),
			mShader_program(
				aVertex_path,
				aFragment_path,
				aWindow_aspect_ratio)
		{

		}

		// TODO 我现在把 gfx entity 生命周期在page里结束，但以后我要
		// 在其他地方单独管理 gfx entity 生命周期？
		~page()
		{
			LOG();
			for (const auto gfx_entity : mHash_graphics_entity | std::views::values)
				delete gfx_entity;
		}


		void bind()
		{
			mShader_program.bind();
		}


		layer_manager* get_layer_manager()
		{
			return &mLayer_manager;
		}

		// add on top
		void add_new_layer(graphics_entity* aGraphics_entity)
		{
			mLayer_manager.add_layer(aGraphics_entity);
			if (aGraphics_entity->mIs_receive_keyboard || aGraphics_entity->mIs_receive_mouse) {
				LOG_INFO("add interactive");
				mInteractive_entity_list.emplace_back(aGraphics_entity);
			}
		}

		// remove
		void remove_and_delete_layer(
			const unsigned int aGraphics_entity_id)
		{
			mLayer_manager.remove_and_delete_layer(aGraphics_entity_id);
		}

		// set graphics_entity invisible or visible
		void set_graphics_entity_visible(
			const unsigned int aGraphics_entity_id, const bool aIs_visible = true)
		{
			if (mHash_graphics_entity.contains(aGraphics_entity_id))
				mHash_graphics_entity[aGraphics_entity_id]->mIs_visible = aIs_visible;
		}

		// 我认为，“收到输入事件后，决定做什么” 并不是 graphics_entity 的职责
		// graphics_entity，甚至 graphics 相关的类，都应该只是负责图形相关的内容，
		// 事件处理什么的，顶多做到 “记录事件处理器的id”、”记录详细处理事件的类的指针“ 之类的

		//std::unordered_map<unsigned int, graphics_entity> mHash_graphics_entity;




		void add_anime(unsigned int aGraphics_entity_id,
			animation* aAnimation)
		{
			mLayer_manager.add_anime(aGraphics_entity_id,
				aAnimation);
		}

		void reset_uniform(bool* aIndex)
		{
			if (aIndex[0])
				mShader_program.bind_projection();
			if (aIndex[1])
				mShader_program.bind_view();
			if (aIndex[2])
				mShader_program.bind_translation();
			if (aIndex[3])
				mShader_program.bind_rotation();
			if (aIndex[4])
				mShader_program.bind_scale();
			if (aIndex[5])
				mShader_program.bind_opacity();
			if (aIndex[6])
				mShader_program.bind_color();
		}




		std::unordered_map<unsigned int, graphics_entity*> mHash_graphics_entity;

		std::vector<graphics_entity*> mInteractive_entity_list;

		layer_manager mLayer_manager;
		shader_program mShader_program;



	};
}
