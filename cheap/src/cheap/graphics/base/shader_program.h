#pragma once
#include "transform.h"

namespace cheap {
	// TODO look up your shader files, confirm the names of uniforms

	#define VERTEX_SHADER_GLSL_UNIFORM_PROJECTION_NAME "uProjection"
	#define VERTEX_SHADER_GLSL_UNIFORM_VIEW_NAME "uView"
	#define VERTEX_SHADER_GLSL_UNIFORM_TRANSLATE_NAME "uTranslate"
	#define VERTEX_SHADER_GLSL_UNIFORM_LAYOUT_NAME "uLayout"
	#define VERTEX_SHADER_GLSL_UNIFORM_ROTATE_NAME "uRotate"
	#define VERTEX_SHADER_GLSL_UNIFORM_SCALE_NAME "uScale"

	#define FRAGMENT_SHADER_GLSL_UNIFORM_TEXTURE_SLOT_NAME "uTexture"
	#define FRAGMENT_SHADER_GLSL_UNIFORM_OPACITY_NAME "uOpacity"

	// uniform opaque, transparency = 1.0
	#define UNIFORM_OPAQUE 1.0f

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

		void use_transform(int aTexture_slot, const glm::mat4& aTranslate = ID_MAT, const glm::mat4& aRotate = ID_MAT, const glm::mat4& aScale = ID_MAT, float aOpacity = UNIFORM_OPAQUE);

		void bind_translate() const;

		void set_translate(const glm::mat4& aMat);

		void set_rotate(const glm::mat4& aMat);

		void bind_rotate() const;

		void set_scale(const glm::mat4& aMat);

		void bind_scale() const;

		void set_texture_slot(int aTex_slot) const;

		void set_opacity(float aOpacity);

		void bind_opacity() const;

	private:
		float mOpacity;

		glm::mat4 mProjection;
		glm::mat4 mView;
		glm::mat4 mTranslate;
		glm::mat4 mRotate;
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
