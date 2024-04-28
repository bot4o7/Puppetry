#pragma once

namespace cheap {

	// ----- vertices and indices settings --------------------
	#define VERTICES_TYPE float
	#define INDICES_TYPE unsigned int
	// ----- vertices and indices settings --------------------

	// ----- layout array ---------------
	#define LAYOUT_LENGTH 3

	// ----- layout array ---------------

	// 我现在设想，因为在使用 view ， projection 之类的变换之后，
	// 一个物体、一张图片的初始位置（摆放位置）会变动很多，
	// 那我或许可以把初始的位移坐标（几何中心点）也加入到顶点数组中。
	// 但是因为顶点数组中有至少4个顶点，用老套的方式（每组 stride 里包含该顶点所有数据），这个初始位移坐标就会多重复3次，因为整个物体共用一个中点的初始位移坐标。
	// 因此我可以考虑把这个坐标加入到单独的数组？
	// 或者把它放到顶点数组 vertices 中的最前面或最后面
	// 之所以能这么想，也是因为 TODO 每种顶点属性的 index, size, count, stride 都是单独设置的
	// ----- VAO, VBO, IBO/EBO   Macros definitions------------
	#define VERTICES_LENGTH 20
	#define INDICES_LENGTH 6
	#define LAYOUT_LENGTH 3

	#define POS_INDEX 0
	#define TEXCOORD_INDEX 1
	#define LAYOUT_INDEX 2


	#define POS_SIZE 3
	#define TEXCOORD_SIZE 2
	#define LAYOUT_SIZE 3

	#define POS_TYPE GL_FLOAT
	#define TEXCOORD_TYPE GL_FLOAT
	#define LAYOUT_TYPE GL_FLOAT

	#define POS_NORMALIZED GL_FALSE
	#define TEXCOORD_NORMALIZED GL_FALSE
	#define LAYOUT_NORMALIZED GL_FALSE

	#define STRIDE (5*sizeof(float))
	#define STRIDE_LAYOUT 0

	#define POS_POINTER (void*)0
	#define TEXCOORD_POINTER (void*)(3 * sizeof(float))
	#define LAYOUT_POINTER (void*)(20 * sizeof(float))

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
			unsigned int* aIndices,
			float* aLayout,
			const bool aIs_these_array_need_to_be_delete_in_dtor = true);

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
		float* mLayout;

		unsigned int mVertex_array_object_id;
		unsigned int mVertex_buffer_object_id;
		unsigned int mIndex_buffer_object_id;

	};
}
