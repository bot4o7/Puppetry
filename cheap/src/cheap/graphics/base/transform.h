#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cheap {
	class transform
	{
	public:

		transform()
			:
			mMatrix(glm::mat4(1.0f))
		{

			LOG();
		}
		~transform()
		{
			LOG();
		}

		[[nodiscard]] glm::mat4 get() const
		{
			return mMatrix;
		}

		[[nodiscard]] glm::mat4 get_translate(const float aOffset_x, const float aOffset_y, const float aOffset_z) const
		{
			return glm::translate(mMatrix, glm::vec3(aOffset_x, aOffset_y, aOffset_z));
		}

		// 
		[[nodiscard]] glm::mat4 get_rotate(const float aAngle_degree, const float aAxis_x, const float aAxis_y, const float aAxis_z) const
		{
			return glm::rotate(mMatrix, glm::radians(aAngle_degree), glm::vec3(aAxis_x, aAxis_y, aAxis_z));
		}

	private:
		glm::mat4 mMatrix;
	};
}
