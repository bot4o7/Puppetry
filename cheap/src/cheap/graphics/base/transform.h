#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cheap {
	// glm::mat4(ID_MAT_PARaM), glm::mat4(1.0f)
	// ID_MAT_PARAM 1.0f
	// identity matrix
	#define ID_MAT glm::mat4(1.0f)

	// default camera position
	#define DEFAULT_CAM_POS glm::vec3(0.0f, 0.0f, 1.0f)
	// default camera direction
	#define DEFAULT_CAM_DIR glm::vec3(0.0f, 0.0f, 0.0f)
	// default camera world up direction
	#define DEFAULT_CAM_UP glm::vec3(0.0f, 1.0f, 0.0f)

	// orthogonal projection left
	#define DEFAULT_ORTHO_PROJ_LEFT (-1.f)
	// orthogonal projection
	#define DEFAULT_ORTHO_PROJ_RIGHT (1.f)
	// orthogonal projection
	#define DEFAULT_ORTHO_PROJ_BOTTOM (-1.f)
	// orthogonal projection
	#define DEFAULT_ORTHO_PROJ_TOP (1.f)
	// orthogonal projection
	#define DEFAULT_ORTHO_PROJ_NEAR (-1000.f)
	// orthogonal projection
	#define DEFAULT_ORTHO_PROJ_FAR (1000.f)

	class transform
	{
	public:
		~transform()
		{
			LOG();
		}
		// identity matrix
		[[nodiscard]] static glm::mat4 get_identity_matrix()
		{
			return ID_MAT;
		}
		// orthogonal projection matrix
		/*[[nodiscard]] static glm::mat4 get_orthogonal_projection(
			const float aLeft = DEFAULT_ORTHO_PROJ_LEFT,
			const float aRight = DEFAULT_ORTHO_PROJ_RIGHT,
			const float aBottom = DEFAULT_ORTHO_PROJ_BOTTOM,
			const float aTop = DEFAULT_ORTHO_PROJ_TOP,
			const float aNear = DEFAULT_ORTHO_PROJ_NEAR,
			const float aFar = DEFAULT_ORTHO_PROJ_FAR
		)
		{
			return glm::ortho(
				aLeft,
				aRight,
				aBottom,
				aTop,
				aNear,
				aFar);
		}*/
		// orthogonal projection matrix
		[[nodiscard]] static glm::mat4 get_orthogonal_projection(
			const float aLeft,
			const float aRight,
			const float aBottom,
			const float aTop,
			const float aNear,
			const float aFar
		)
		{
			return glm::ortho(
				aLeft,
				aRight,
				aBottom,
				aTop,
				aNear,
				aFar);
		}
		// orthogonal projection matrix
		[[nodiscard]] static glm::mat4 get_orthogonal_projection(
			const float aAspect
		)
		{
			return glm::ortho(
				DEFAULT_ORTHO_PROJ_LEFT * aAspect,
				DEFAULT_ORTHO_PROJ_RIGHT * aAspect,
				DEFAULT_ORTHO_PROJ_BOTTOM,
				DEFAULT_ORTHO_PROJ_TOP,
				DEFAULT_ORTHO_PROJ_NEAR,
				DEFAULT_ORTHO_PROJ_FAR);
		}
		// perspective projection matrix
		[[nodiscard]] static glm::mat4 get_perspective_projection(
			const float aFov_degree,
			const int aAspect_numerator,
			const int aAspect_denominator,
			const float aNear, const float aFar)
		{
			return glm::perspective(
				glm::radians(aFov_degree),
				static_cast<float>(aAspect_numerator) / static_cast<float>(aAspect_denominator),
				aNear,
				aFar);
		}
		// get a view transform
		[[nodiscard]] static glm::mat4 get_view(
			const glm::vec3& aCamera_pos = DEFAULT_CAM_POS, const glm::vec3& aCamera_direction = DEFAULT_CAM_DIR, const glm::vec3& aCamera_world_up = DEFAULT_CAM_UP)
		{
			return glm::lookAt(
				aCamera_pos,
				aCamera_direction,
				aCamera_world_up);
		}
		// get a view transform
		[[nodiscard]] static glm::mat4 get_view(
			const float aPos_x,
			const float aPos_y,
			const float aPos_z,
			const float aLook_x,
			const float aLook_y,
			const float aLook_z)
		{
			return glm::lookAt(
				glm::vec3(aPos_x, aPos_y, aPos_z),
				glm::vec3(aLook_x, aLook_y, aLook_z),
				DEFAULT_CAM_UP);
		}
		// get a scale transform
		[[nodiscard]] static glm::mat4 get_scale(
			const float aScale_x,
			const float aScale_y,
			const float aScale_z)
		{
			return scale(
				ID_MAT,
				glm::vec3(aScale_x, aScale_y, aScale_z));
		}
		// get a rotate transform
		[[nodiscard]] static glm::mat4 get_rotate(const float aAngle_degree, const float aAxis_x, const float aAxis_y, const float aAxis_z)
		{
			return rotate(
				ID_MAT,
				glm::radians(aAngle_degree),
				glm::vec3(aAxis_x, aAxis_y, aAxis_z));
		}
		// get a translation transform
		[[nodiscard]] static glm::mat4 get_translate(
			const float aOffset_x,
			const float aOffset_y,
			const float aOffset_z)
		{
			return translate(
				ID_MAT,
				glm::vec3(aOffset_x, aOffset_y, aOffset_z));
		}

	private:
		transform() = default;
	};
}
