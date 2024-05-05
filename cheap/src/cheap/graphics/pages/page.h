﻿#pragma once

#include <ranges>

#include "../layers/layer_manager.h"
#include "../../entity/graphics_entity.h"
#include "../animations/animation.h"
#include "../base/shader_program.h"

namespace cheap {
	class page
	{
	public:
		struct item
		{
			graphics_entity* mGraphics_entity;
			std::vector<animation*> mAnimation_list;

			// 初始化时，由高层往底层遍历、添加，这样如果有拦截的，就可以直接结束遍历了
			std::vector<unsigned int> mOn_hover_list;
			std::vector<unsigned int> mOn_click_list;
			std::vector<unsigned int> mOn_key_press_list;
			std::vector<unsigned int> mOn_key_repeat_list;
		};
		// 程序在页面page切换时，记录当前page为current page
		// 用户点击屏幕时，程序得到一个点击事件、移动光标时，也得到点击事件
		// 点击事件会被拿到current page检查是否有接受点击的，如果有，那么接收后做什么
		// 光标悬停事件也如此。


		page(
			const char* aVertex_path,
			const char* aFragment_path,
			const float aWindow_aspect_ratio)
			:
			mHash_graphics_entity(std::unordered_map<unsigned int, graphics_entity*>()),
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
		layer_manager mLayer_manager;
		shader_program mShader_program;
	};
}
