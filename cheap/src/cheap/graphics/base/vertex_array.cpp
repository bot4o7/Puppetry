#include "pch.h"
#include "vertex_array.h"

namespace cheap {
	vertex_array::vertex_array(
		float* aVertices,
		unsigned int* aIndices,
		const bool aIs_these_array_need_to_be_delete_in_dtor)
		:
		mIs_these_array_need_to_be_delete_in_dtor(aIs_these_array_need_to_be_delete_in_dtor),
		mVertices(aVertices),
		mIndices(aIndices),
		mVertex_array_object_id(0),
		mVertex_buffer_object_id(0),
		mIndex_buffer_object_id(0)
	{
		LOG();
		glGenVertexArrays(1, &mVertex_array_object_id);
		glGenBuffers(1, &mVertex_buffer_object_id);
		glGenBuffers(1, &mIndex_buffer_object_id);

		bind();
		unbind();
	}

	vertex_array::~vertex_array()
	{
		LOG();
		if (mIs_these_array_need_to_be_delete_in_dtor) {
			delete[] mVertices;
			delete[] mIndices;
		}
		glDeleteVertexArrays(1, &mVertex_array_object_id);
		glDeleteBuffers(1, &mVertex_buffer_object_id);
		glDeleteBuffers(1, &mIndex_buffer_object_id);
	}

	void vertex_array::bind_VAO() const
	{
		glBindVertexArray(mVertex_array_object_id);
	}

	void vertex_array::update_vbo() const
	{
		LOG();
		// bind VBO
		glBindBuffer(VBO_TARGET,
			mVertex_buffer_object_id);
		// TODO 因为我这里的 mVertices 是指针，不是显式数组，需要指定数量，否则 sizeof(mVertices)只是一个指针的大小
		glBufferData(
			VBO_TARGET,
			(VERTICES_LENGTH + LAYOUT_LENGTH) * sizeof(VERTICES_TYPE),
			mVertices,
			BUFFER_USAGE);
		glBindBuffer(VBO_TARGET,
			0);
	}

	void vertex_array::bind() const
	{
		LOG();
		bind_VAO();
		// bind VBO
		glBindBuffer(VBO_TARGET,
			mVertex_buffer_object_id);
		// TODO 因为我这里的 mVertices 是指针，不是显式数组，需要指定数量，否则 sizeof(mVertices)只是一个指针的大小
		glBufferData(
			VBO_TARGET,
			(VERTICES_LENGTH + LAYOUT_LENGTH) * sizeof(VERTICES_TYPE),
			mVertices,
			BUFFER_USAGE);

		// bind IBO/EBO
		glBindBuffer(
			IBO_TARGET,
			mIndex_buffer_object_id);
		// TODO 与上面的 mVertices 同理
		glBufferData(
			IBO_TARGET,
			INDICES_LENGTH * sizeof(INDICES_TYPE),
			mIndices,
			BUFFER_USAGE);

		// position attribute
		glVertexAttribPointer(
			POS_INDEX,
			POS_SIZE,
			POS_TYPE,
			POS_NORMALIZED,
			STRIDE,
			POS_POINTER);
		glEnableVertexAttribArray(POS_INDEX);

		// texture coords attribute
		glVertexAttribPointer(
			TEXCOORD_INDEX,
			TEXCOORD_SIZE,
			TEXCOORD_TYPE,
			TEXCOORD_NORMALIZED,
			STRIDE,
			TEXCOORD_POINTER);
		glEnableVertexAttribArray(TEXCOORD_INDEX);

		// layout coords attribute
		glVertexAttribPointer(
			LAYOUT_INDEX,
			LAYOUT_SIZE,
			LAYOUT_TYPE,
			LAYOUT_NORMALIZED,
			STRIDE_LAYOUT,
			LAYOUT_POINTER);
		glEnableVertexAttribArray(LAYOUT_INDEX);
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
