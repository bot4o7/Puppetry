#pragma once

namespace cheap {

	// ----- vertices and indices settings --------------------
	#define VERTICES_TYPE float
	#define INDICES_TYPE unsigned int
	// ----- vertices and indices settings --------------------

	// ----- VAO, VBO, IBO/EBO   Macros definitions------------
	#define VERTICES_LENGTH 20
	#define INDICES_LENGTH 6

	#define POS_INDEX 0
	#define TEXCOORD_INDEX 1

	#define POS_SIZE 3
	#define TEXCOORD_SIZE 2

	#define POS_TYPE GL_FLOAT
	#define TEXCOORD_TYPE GL_FLOAT

	#define POS_NORMALIZED GL_FALSE
	#define TEXCOORD_NORMALIZED GL_FALSE

	#define STRIDE (5*sizeof(float))

	#define POS_POINTER (void*)0
	#define TEXCOORD_POINTER (void*)(3 * sizeof(float))

	#define VBO_TARGET GL_ARRAY_BUFFER
	#define IBO_TARGET GL_ELEMENT_ARRAY_BUFFER

	#define BUFFER_USAGE GL_DYNAMIC_DRAW
	// ----- VAO, VBO, IBO/EBO   Macros definitions------------

	// ----- vertices position --------------------------------
	// y axis position screen top border
	#define POS_TOP 1.0f
	// y axis position screen bottom border
	#define POS_BOTTOM (-1.0f)

	// x axis position screen right border
	#define POS_RIGHT 1.0f
	// x axis position screen left border
	#define POS_LEFT (-1.0f)

	// z axis position screen
	#define POS_Z 0.0f
	// ----- vertices position --------------------------------

	class vertex_array
	{
	public:

		// you need call bind() later
		vertex_array(
			float* aVertices,
			unsigned int* aIndices, const bool aIs_these_array_need_to_be_delete_in_dtor = true);

		// TODO 万一这两个数组的生命周期不属于 vertex_array，我届时需更改这里
		// delete[] mVertices;
		// delete[] mIndices;
		~vertex_array();

		// TODO 解绑以后， glDraw 之前不绑定VAO，程序直接死给你看 ^_^
		void bind_VAO() const;

		// 单纯地绘制时，只需要绑定一个 VAO 就行，VBO,IBO/EBO会跟它联系在一起
		// 但是要更新顶点数据时，除了bind_VAO，其他也要绑定
		void bind() const;

		/**
		1. unbind VBO
		2. unbind VAO
		3. unbind IBO/EBO
		 */
		static void unbind();

		// TODO 还没实现 not implemented yet
		void update()
		{

		}
	private:
		bool mIs_these_array_need_to_be_delete_in_dtor;
		float* mVertices;
		unsigned int* mIndices;

		unsigned int mVertex_array_object_id;
		unsigned int mVertex_buffer_object_id;
		unsigned int mIndex_buffer_object_id;

	};
}
