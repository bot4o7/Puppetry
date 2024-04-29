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
		// identity matrix
		[[nodiscard]] static glm::mat4 get_identity_matrix();
		// orthogonal projection matrix
		[[nodiscard]] static glm::mat4 get_orthogonal_projection(
			float aLeft,
			float aRight,
			float aBottom,
			float aTop,
			float aNear,
			float aFar
		);
		// orthogonal projection matrix
		[[nodiscard]] static glm::mat4 get_orthogonal_projection(
			float aAspect
		);
		// perspective projection matrix
		[[nodiscard]] static glm::mat4 get_perspective_projection(
			float aFov_degree,
			int   aAspect_numerator,
			int   aAspect_denominator,
			float aNear, float aFar);
		// get a view transform
		[[nodiscard]] static glm::mat4 get_view(
			const glm::vec3& aCamera_pos = DEFAULT_CAM_POS,
			const glm::vec3& aCamera_direction = DEFAULT_CAM_DIR,
			const glm::vec3& aCamera_world_up = DEFAULT_CAM_UP);
		// get a view transform
		[[nodiscard]] static glm::mat4 get_view(
			float aPos_x,
			float aPos_y,
			float aPos_z,
			float aLook_x,
			float aLook_y,
			float aLook_z);
		// get a scale transform
		[[nodiscard]] static glm::mat4 get_scale(
			float aScale_x,
			float aScale_y,
			float aScale_z);
		// get a rotate transform
		[[nodiscard]] static glm::mat4 get_rotate(
			float aAngle_degree,
			float aAxis_x,
			float aAxis_y,
			float aAxis_z);
		// get a translation transform
		[[nodiscard]] static glm::mat4 get_translate(
			float aOffset_x,
			float aOffset_y,
			float aOffset_z);

	private:
		transform();
		~transform();
	};
}
