#include "pch.h"
#include "transform.h"

namespace cheap {
	transform::~transform() = default;

	glm::mat4 transform::get_identity_matrix()
	{
		return ID_MAT;
	}

	glm::mat4 transform::get_orthogonal_projection(
		const float aLeft, const float aRight,
		const float aBottom, const float aTop,
		const float aNear, const float aFar)
	{
		return glm::ortho(
			aLeft,
			aRight,
			aBottom,
			aTop,
			aNear,
			aFar);
	}

	glm::mat4 transform::get_orthogonal_projection(const float aAspect)
	{
		return glm::ortho(
			DEFAULT_ORTHO_PROJ_LEFT * aAspect,
			DEFAULT_ORTHO_PROJ_RIGHT * aAspect,
			DEFAULT_ORTHO_PROJ_BOTTOM,
			DEFAULT_ORTHO_PROJ_TOP,
			DEFAULT_ORTHO_PROJ_NEAR,
			DEFAULT_ORTHO_PROJ_FAR);
	}

	glm::mat4 transform::get_perspective_projection(
		const float aFov_degree,
		const int aAspect_numerator, const int aAspect_denominator,
		const float aNear, const float aFar)
	{
		return glm::perspective(
			glm::radians(aFov_degree),
			static_cast<float>(aAspect_numerator) / static_cast<float>(aAspect_denominator),
			aNear,
			aFar);
	}

	glm::mat4 transform::get_view(
		const glm::vec3& aCamera_pos,
		const glm::vec3& aCamera_direction,
		const glm::vec3& aCamera_world_up)
	{
		return glm::lookAt(
			aCamera_pos,
			aCamera_direction,
			aCamera_world_up);
	}

	glm::mat4 transform::get_view(
		const float aPos_x, const float aPos_y, const float aPos_z,
		const float aLook_x, const float aLook_y, const float aLook_z)
	{
		return glm::lookAt(
			glm::vec3(aPos_x, aPos_y, aPos_z),
			glm::vec3(aLook_x, aLook_y, aLook_z),
			DEFAULT_CAM_UP);
	}

	glm::mat4 transform::get_scale(
		const float aScale_x, const float aScale_y, const float aScale_z)
	{
		return scale(
			ID_MAT,
			glm::vec3(aScale_x, aScale_y, aScale_z));
	}

	glm::mat4 transform::get_rotate(
		const float aAngle_degree,
		const float aAxis_x, const float aAxis_y, const float aAxis_z)
	{
		return rotate(
			ID_MAT,
			glm::radians(aAngle_degree),
			glm::vec3(aAxis_x, aAxis_y, aAxis_z));
	}

	glm::mat4 transform::get_translate(
		const float aOffset_x, const float aOffset_y, const float aOffset_z)
	{
		return translate(
			ID_MAT,
			glm::vec3(aOffset_x, aOffset_y, aOffset_z));
	}

	transform::transform() = default;
}
