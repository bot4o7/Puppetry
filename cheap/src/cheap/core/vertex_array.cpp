#include "pch.h"
#include "vertex_array.h"

namespace cheap {
	/*vertex_array::vertex_array(float* aVertices, unsigned* aIndices,
		const bool aIs_these_array_need_to_be_delete_in_dtor) :
		mIs_these_array_need_to_be_delete_in_dtor(aIs_these_array_need_to_be_delete_in_dtor),
		mVertices(aVertices),
		mIndices(aIndices)
	{
		LOG();
		glGenVertexArrays(1, &mVertex_array_object_id);
		glGenBuffers(1, &mVertex_buffer_object_id);
		glGenBuffers(1, &mIndex_buffer_object_id);
	}*/

	vertex_array::vertex_array(
		const bool aIs_these_array_need_to_be_delete_in_dtor) :
		mIs_these_array_need_to_be_delete_in_dtor(aIs_these_array_need_to_be_delete_in_dtor)
		/*mVertices(),
		mIndices({})*/
	{
		LOG();
		glGenVertexArrays(1, &mVertex_array_object_id);
		glGenBuffers(1, &mVertex_buffer_object_id);
		glGenBuffers(1, &mIndex_buffer_object_id);
	}

	vertex_array::~vertex_array()
	{
		LOG();
		if (mIs_these_array_need_to_be_delete_in_dtor) {
			//delete[] mVertices;
			//delete[] mIndices;
		}
		glDeleteVertexArrays(1, &mVertex_array_object_id);
		glDeleteBuffers(1, &mVertex_buffer_object_id);
		glDeleteBuffers(1, &mIndex_buffer_object_id);
	}

	void vertex_array::bind_VAO() const
	{
		LOG();
		// bind VAO
		glBindVertexArray(mVertex_array_object_id);
	}

	void vertex_array::bind() const
	{
		LOG();
		bind_VAO();

		// bind VBO
		glBindBuffer(VBO_TARGET, mVertex_buffer_object_id);
		//glBufferData(VBO_TARGET, 20 * sizeof(float), mVertices, BUFFER_USAGE);
		glBufferData(VBO_TARGET, sizeof(mVertices), mVertices, BUFFER_USAGE);

		// bind IBO/EBO
		glBindBuffer(IBO_TARGET, mIndex_buffer_object_id);
		//glBufferData(IBO_TARGET, 6 * sizeof(unsigned int), mIndices, BUFFER_USAGE);
		glBufferData(IBO_TARGET, sizeof(mIndices), mIndices, BUFFER_USAGE);

		// position attribute
		glVertexAttribPointer(
			TEXCOORD_INDEX,
			TEXCOORD_SIZE,
			TEXCOORD_TYPE,
			TEXCOORD_NORMALIZED,
			STRIDE,
			TEXCOORD_POINTER);
		glEnableVertexAttribArray(TEXCOORD_INDEX);

		// texture coords attribute
		glVertexAttribPointer(
			TEXCOORD_INDEX,
			TEXCOORD_SIZE,
			TEXCOORD_TYPE,
			TEXCOORD_NORMALIZED,
			STRIDE,
			TEXCOORD_POINTER);
		glEnableVertexAttribArray(TEXCOORD_INDEX);
	}

	void vertex_array::unbind()
	{
		LOG();
		// 1. unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 2. unbind VAO
		glBindVertexArray(0);
		// 3. unbind IBO/EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
