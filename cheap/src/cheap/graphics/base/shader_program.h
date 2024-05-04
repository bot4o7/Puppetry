#pragma once
#include "transform.h"

namespace cheap {
	// TODO look up your shader files, confirm the names of uniforms

	#define VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME "uProjection"
	#define VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME "uView"
	#define VERTEX_SHADER_GLSL_UNIFORM_TRANSLATION_NAME "uTranslation"
	#define VERTEX_SHADER_GLSL_UNIFORM_ROTATION_NAME "uRotation"
	#define VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME "uScale"

	#define FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME "uTexture"
	#define FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME "uOpacity"
	// color multiplier ? 这个值会被乘到 FragColor上，或许还需要一个 相加的？
	#define FRAGMENT_SHADER_GLSL_UNIFORM_COLOR_NAME "uColor"

	// uniform  glm::vec4 color (0,0,0,0)
	#define UNIFORM_COLOR glm::vec4()
	// uniform  opacity
	#define UNIFORM_OPACITY 1.0f

	class shader_program
	{
	public:
		unsigned int mId;
		// constructor generates the shader on the fly
		// ----------------------------------
		shader_program(
			const char* aVertex_path,
			const char* aFragment_path,
			float       aAspect);
		~shader_program();

		void create_program(const char* aVertex_path, const char* aFragment_path) const;

		// activate the shader
		// ---------------------------
		void bind() const;

		static void unbind();

		void use(int aTexture_slot) const;


		void bind_color() const
		{
			set_vec4(FRAGMENT_SHADER_GLSL_UNIFORM_COLOR_NAME, mColor);
		}

		void set_color(
			const float aColor_r = 0.f,
			const float aColor_g = 0.f,
			const float aColor_b = 0.f
		)
		{
			mColor = glm::vec4(aColor_r, aColor_g, aColor_b, 0.f);
			bind_color();
		}

		void set_color(
			const glm::vec4 aColor = UNIFORM_COLOR)
		{
			mColor = aColor;
			bind_color();
		}

		void bind_projection() const;

		void set_projection_to_orthogonal(
			float aLeft,
			float aRight,
			float aBottom,
			float aTop,
			float aNear,
			float aFar
		);

		void set_projection_to_perspective(
			float aFov_degree,
			int   aAspect_numerator,
			int   aAspect_denominator,
			float aNear, float aFar);

		void bind_view() const;

		void set_view(
			float aPos_x,
			float aPos_y,
			float aPos_z,
			float aLook_x,
			float aLook_y,
			float aLook_z);

		void set_transform() const;

		void use_transform(int aTexture_slot, const glm::mat4& aTranslation = ID_MAT, const glm::mat4& aRotation = ID_MAT, const glm::mat4& aScale = ID_MAT, const float aOpacity = UNIFORM_OPACITY, const glm::vec4& aColor = UNIFORM_COLOR);

		void bind_translation() const;

		void set_translation(const glm::mat4& aMat);

		void set_rotation(const glm::mat4& aMat);

		void bind_rotation() const;

		void set_scale(const glm::mat4& aMat);

		void bind_scale() const;

		void set_texture_slot(int aTex_slot) const;
		void set_opacity(float aOpacity = UNIFORM_OPACITY);

		void bind_opacity() const;

		void use_projection(
			const glm::mat4& aProjection) const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME, aProjection);
		}
		void use_view(
			const glm::mat4& aView) const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME, aView);
		}
		void use_translation(
			const glm::mat4& aTranslation) const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_TRANSLATION_NAME, aTranslation);
		}
		void use_rotation(
			const glm::mat4& aRotation) const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_ROTATION_NAME, aRotation);
		}
		void use_scale(
			const glm::mat4& aScale) const
		{
			set_mat4(VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME, aScale);
		}

		void use_opacity(
			const float aOpacity) const
		{
			set_float(FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME, aOpacity);
		}

		void use_color(
			const glm::vec4 aColor) const
		{
			set_vec4(FRAGMENT_SHADER_GLSL_UNIFORM_COLOR_NAME, aColor);
		}


	private:
		float mOpacity;
		glm::vec4 mColor;

		glm::mat4 mProjection;
		glm::mat4 mView;
		glm::mat4 mTranslation;
		glm::mat4 mRotation;
		glm::mat4 mScale;


		// utility function for checking shader compilation/linking errors.
		// -------------
		static void check_compile_errors(GLuint aShader, unsigned int aType = 0);

		// utility uniform functions
		// --------
		void set_bool(const std::string& aName, bool aValue) const;
		// --------
		void set_int(const std::string& aName, int aValue) const;
		// 
		void set_float(const std::string& aName, float aValue) const;
		// 
		void set_vec2(const std::string& aName, const glm::vec2& aValue) const;

		void set_vec2(const std::string& aName, float aX, float aY) const;
		// -----------
		void set_vec3(const std::string& aName, const glm::vec3& aValue) const;

		void set_vec3(const std::string& aName, float aX, float aY, float aZ) const;
		// ------------
		void set_vec4(const std::string& aName, const glm::vec4& aValue) const;

		void set_vec4(const std::string& aName, float aX, float aY, float aZ, float aW) const;
		// --------------
		void set_mat2(const std::string& aName, const glm::mat2& aMat) const;
		// ---------------
		void set_mat3(const std::string& aName, const glm::mat3& aMat) const;
		// -----------------
		void set_mat4(const std::string& aName, const glm::mat4& aMat) const;
	};
}
