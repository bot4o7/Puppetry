﻿#include "pch.h"
#include "renderer.h"

#include "animations/opacity_animation.h"
#include "animations/translation_animation.h"
#include "animations/rotation_animation.h"
#include "animations/scale_animation.h"

namespace cheap {
	renderer::renderer(const std::shared_ptr<window>& aWindow, const std::shared_ptr<layer_manager>& aLayer_manager) :
		mShader_path(SHADER_PATH),
		mPic_path(PIC_PATH),
		mVertex_shader_filename(VERTEX_SHADER_FILENAME),
		mFragment_shader_filename(FRAGMENT_SHADER_FILENAME),
		mWindow(aWindow),
		mLayer_manager(aLayer_manager),
		mShader_program(
			shader_program(
				(mShader_path + mVertex_shader_filename).c_str(),
				(mShader_path + mFragment_shader_filename).c_str(),
				aWindow->get_aspect_ratio())
		)
	{
		LOG();
		if (mWindow == nullptr)
			LOG_INFO("aWindow ptr is nullptr");
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		mShader_program.bind();
	}

	renderer::~renderer()
	{
		LOG();
	}

	void renderer::clear()
	{
		glClearColor(DEFAULT_RENDERER_CLEAR_COLOR);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void renderer::draw_layers(const double current_time, const int aTexture_slot)
	{
		for (auto task = mLayer_manager->get_top_layer_level(); task != nullptr;) {
			if (task->mLayer->is_show()) {
				mShader_program.set_opacity(task->mLayer->get_opacity());
				if (task->mLayer->get_anim() != nullptr) {
					if (animation* anim = task->mLayer->get_anim(); anim->is_to_play(current_time)) {
						LOG_INFO(3);
						switch (anim->get_type()) {
							case animation::type::TRANSLATION:
								mShader_program.use_translation(dynamic_cast<translation_animation*>(anim)->get(current_time));
								break;
							case animation::type::ROTATION:
								mShader_program.use_rotation(dynamic_cast<rotation_animation*>(anim)->get(current_time));
								break;
							case animation::type::OPACITY:
								mShader_program.use_opacity(dynamic_cast<opacity_animation*>(anim)->get(current_time));
								break;
							case animation::type::SCALE:
								mShader_program.use_scale(dynamic_cast<scale_animation*>(anim)->get(current_time));
								break;
							case animation::type::REFLECTION:
							case animation::type::COLOR:
							case animation::type::SHIFT:
							default:
								LOG_INFO("unkown animation type : " << static_cast<unsigned>(anim->get_type()));
						}
					}
				} else {
					mShader_program.set_transform();
				}

				task->mLayer->before_draw(aTexture_slot);
				glDrawElements(ELEMENT_MODE, ELEMENT_COUNT, ELEMENT_TYPE, ELEMENT_INDICES);
				task = task->mBelow;
			}
		}
	}

	void renderer::update() const
	{
		glfwSwapBuffers(mWindow->get_raw_window());
		glfwPollEvents();
	}
}
