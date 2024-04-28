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

	class transform
	{
	public:
		// identity matrix
		/*transform()
			:
			mMatrix(ID_MAT_PARAM)
		{
			LOG();
		}*/
		// ortho projection matrix
		/*transform(
			const float aLeft,
			const float aRight,
			const float aBottom,
			const float aTop,
			const float aNear,
			const float aFar
		)
			:
			mMatrix(
				glm::ortho(
					aLeft,
					aRight,
					aBottom,
					aTop,
					aNear,
					aFar))
		{
			LOG();
		}*/
		// perspective projection matrix
		/*transform(bool aFov_placeholder, const float aFov_degree, const int aAspect_numerator, const int aAspect_denominator, const float aNear, const float aFar)
			:
			mMatrix(
				glm::perspective(
					glm::radians(aFov_degree),
					static_cast<float>(aAspect_numerator) / static_cast<float>(aAspect_denominator),
					aNear,
					aFar))
		{
			LOG();
		}*/
		// view / camera matrix
		// glm::mat4 view;
		// view = glm::lookAt(cameraPos, cameraDirection, cameraUp)
		/*explicit transform(
			const glm::vec3& aCamera_pos = DEFAULT_CAM_POS, const glm::vec3& aCamera_direction = DEFAULT_CAM_DIR, const glm::vec3& aCamera_world_up = DEFAULT_CAM_UP)
			:
			mMatrix(glm::lookAt(
				aCamera_pos,
				aCamera_direction,
				aCamera_world_up))
		{
			LOG();
		}*/
		// view / camera matrix
		// glm::mat4 view;
		// view = glm::lookAt(cameraPos, cameraDirection, cameraUp)
		/*transform(
			const float aPos_x,
			const float aPos_y,
			const float aPos_z,
			const float aLook_x,
			const float aLook_y,
			const float aLook_z,
			bool aPlaceholder_camera_world_up
		)
			:
			mMatrix(glm::lookAt(
				glm::vec3(aPos_x, aPos_y, aPos_z),
				glm::vec3(aLook_x, aLook_y, aLook_z),
				DEFAULT_CAM_UP))
		{
			LOG();
		}*/
		// scale
		/*transform(const float aScale_x, const float aScale_y, const float aScale_z, bool aPlaceholder_rotate)
			:
			mMatrix(get_scale(aScale_x, aScale_y, aScale_z))
		{
			LOG();
		}*/
		// rotate
		/*transform(const float aAngle_degree, const float aAxis_x, const float aAxis_y, const float aAxis_z)
			:
			mMatrix(get_rotate(aAngle_degree, aAxis_x, aAxis_y, aAxis_z))
		{
			LOG();
		}*/
		// translate
		/*transform(const float aOffset_x, const float aOffset_y, const float aOffset_z)
			:
			mMatrix(get_translate(aOffset_x, aOffset_y, aOffset_z))
		{
			LOG();
		}*/

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
	};
}
