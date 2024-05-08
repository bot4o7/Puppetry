#pragma once

#include <ranges>

#include "../../entity/graphics_entity.h"
#include "../animations/animation.h"
#include "../animations/translation_animation.h"
#include "../animations/scale_animation.h"
#include "../animations/opacity_animation.h"
#include "../base/shader_program.h"

namespace cheap {
	class page
	{
	public:
		//struct item
		//{
		//	graphics_entity* mGraphics_entity;
		//	std::vector<animation*> mAnimation_list;

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
		//animation* mOn_hover_animation;
		// TODO
		static void add_hover_animation_to_layer(unsigned int aGraphics_entity_id, const double current_time)
		{
			/*if (layer* target_layer = mLayer_manager.get_layer(aGraphics_entity_id); target_layer != nullptr) {
				target_layer->set_anim(new animation())
			}*/
		}



		page(
			const unsigned int aId,
			const char* aVertex_path,
			const char* aFragment_path,
			const float aWindow_aspect_ratio)
			:
			mId(aId),
			mHash_graphics_entity(std::unordered_map<unsigned int, element*>()),
			mShader_program(
				aVertex_path,
				aFragment_path,
				aWindow_aspect_ratio)
		{
			LOG();
		}

		page(
			page&& aPage) noexcept
			:
			mId(aPage.mId),
			mHash_graphics_entity(aPage.mHash_graphics_entity),
			mShader_program(
				aPage.mShader_program)
		{
			LOG();
		}

		// TODO 我现在把 gfx entity 生命周期在page里结束，但以后我要
		// 在其他地方单独管理 gfx entity 生命周期？
		~page()
		{
			for (const auto gfx_entity : mHash_graphics_entity | std::views::values)
				delete gfx_entity;
		}


		void bind() const
		{
			mShader_program.bind();
		}


		//TODO
		// add on top
		void add_new_layer(graphics_entity* aGraphics_entity)
		{
			//mLayer_manager.add_layer(aGraphics_entity);
			mHash_graphics_entity.emplace(aGraphics_entity->mId, new element(aGraphics_entity));
		}

		// TODO
		// remove
		void remove_and_delete_layer(
			const unsigned int aGraphics_entity_id)
		{
			//mLayer_manager.remove_and_delete_layer(aGraphics_entity_id);
		}

		// set graphics_entity invisible or visible
		void set_graphics_entity_visible(
			const unsigned int aGraphics_entity_id, const bool aIs_visible = true)
		{
			if (mHash_graphics_entity.contains(aGraphics_entity_id))
				mHash_graphics_entity[aGraphics_entity_id]->mGraphics_entity->mIs_visible = aIs_visible;
		}

		// 我认为，“收到输入事件后，决定做什么” 并不是 graphics_entity 的职责
		// graphics_entity，甚至 graphics 相关的类，都应该只是负责图形相关的内容，
		// 事件处理什么的，顶多做到 “记录事件处理器的id”、”记录详细处理事件的类的指针“ 之类的



		void use_gfx_entity_uniform(
			const graphics_entity* aGraphics_entity) const
		{
			mShader_program.bind_projection();
			mShader_program.bind_view();

			mShader_program.use_translation(aGraphics_entity->mUniform.mTranslation);
			mShader_program.use_rotation(aGraphics_entity->mUniform.mRotation);
			mShader_program.use_scale(aGraphics_entity->mUniform.mScale);

			mShader_program.use_opacity(aGraphics_entity->mUniform.mOpacity);



			mShader_program.use_color(aGraphics_entity->mUniform.mColor);


		}

		void static update_gfx_entity_animation(animation* aAnimation,
			const double current_time)
		{
			if (aAnimation->is_to_play(current_time)) {
				switch (aAnimation->get_type()) {
					case animation::type::SCALE:
						dynamic_cast<scale_animation*>(aAnimation)->set(current_time);
						break;
					case animation::type::OPACITY:
						dynamic_cast<opacity_animation*>(aAnimation)->set(current_time);
					case animation::type::COLOR:
						break;
					case animation::type::REFLECTION:
						break;
					case animation::type::ROTATION:
						break;
					case animation::type::SHIFT:
						break;
					case animation::type::TRANSLATION:
						dynamic_cast<translation_animation*>(aAnimation)->set(current_time);
					default:
						LOG_INFO("no such type");
				}
			}
		}

		void draw(
			const unsigned int aTexture_slot,
			const double       current_time) const
		{
			mShader_program.use(aTexture_slot);

			for (const auto val : mHash_graphics_entity | std::views::values) {
				val->mGraphics_entity->before_draw(aTexture_slot);
				for (const auto anim : val->mAnimation_list) {
					update_gfx_entity_animation(anim, current_time);
				}
				use_gfx_entity_uniform(val->mGraphics_entity);

				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			}
		}

		// TODO
		void add_anime(
			const unsigned int aGraphics_entity_id,
			animation* aAnimation)
		{
			if (mHash_graphics_entity.contains(aGraphics_entity_id)) {
				aAnimation->set_graphics_entity(mHash_graphics_entity[aGraphics_entity_id]->mGraphics_entity);
				mHash_graphics_entity[aGraphics_entity_id]->mAnimation_list.emplace_back(aAnimation);
			}
		}

		struct element
		{
			graphics_entity* mGraphics_entity;
			std::vector<animation*> mAnimation_list;

			explicit element(graphics_entity* aGraphics_entity) :
				mGraphics_entity(aGraphics_entity),
				mAnimation_list(std::vector<animation*>())
			{
				LOG();
			}
			~element()
			{
				delete mGraphics_entity;
				for (const auto animation : mAnimation_list)
					delete animation;
			}
		};


		std::unordered_map<unsigned int, element*> mHash_graphics_entity;
		shader_program mShader_program;

	};
}
