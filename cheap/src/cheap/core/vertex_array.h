#pragma once

namespace cheap {

	// TODO 似乎可以根据 C++ 中，对象地址、对象属性内存分布，之类的知识，可以直接传入一个对象，而不是一个数组，但是有点难

// TODO 注意，vertex 属性跟你的 shader 的 GLSL 文件怎么写的，有关。 比如 pos, color, texture coords，\
		// TODO 搭配上 location=0    location=1 之类的 GLSL语句
		// TODO 再搭配上 glVertexAttribPointer(index:1, size:3, type:GL_FLOAT, normalized:GL_FALSE, stride:8*sizeof(float), 1st_attribute_location:(void*)(6*sizeof(float));  的 GL 代码
		// TODO 就可以配置一组顶点的很多东西

		// 以一个矩形图片为例
		/**
		 *
		 *  float vertices[] = {
			// positions          // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
		};
		*
		*unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		* 位置坐标 pos 有 3 个 float
		* 4 个位置坐标， 4 * 3 = 12 个 float
		*
		* texture 坐标有 2 个 float
		* 4 个 texture 坐标， 4 * 2 = 8 个 float
		*
		* index 有 6 个 int
		 */

		 // 以绑定为例
		 // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		 // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		 // glVertexAttribPointer(
		 /** index / location in GLSL shader,
		  * size,
		  * type,
		  * normalized,
		  * stride,
		  * pointer (position of the first attribute (a pointer) )
		  * );
		  */

		  // ----- VAO, VBO, IBO/EBO   Macros definitions------------
	#define VERTICES_LENGTH 20
	#define INDICES_LENGTH 6

	#define TEXCOORD_INDEX 0
	#define TEXCOORD_INDEX 1

	#define TEXCOORD_SIZE 3
	#define TEXCOORD_SIZE 2

	#define TEXCOORD_TYPE GL_FLOAT
	#define TEXCOORD_TYPE GL_FLOAT

	#define TEXCOORD_NORMALIZED GL_FALSE
	#define TEXCOORD_NORMALIZED GL_FALSE

	#define STRIDE (5*sizeof(float))

	#define TEXCOORD_POINTER (void*)0
	#define TEXCOORD_POINTER (void*)(3 * sizeof(float))

	#define VBO_TARGET GL_ARRAY_BUFFER
	#define IBO_TARGET GL_ELEMENT_ARRAY_BUFFER

	#define BUFFER_USAGE GL_DYNAMIC_DRAW
	// ----- VAO, VBO, IBO/EBO   Macros definitions------------




	class vertex_array
	{
	public:

		// you need call bind() later
		vertex_array(
			float* aVertices,
			unsigned int* aIndices, const bool aIs_these_array_need_to_be_delete_in_dtor = true)
			:
			mVertices(aVertices),
			mIndices(aIndices),
			mIs_these_array_need_to_be_delete_in_dtor(aIs_these_array_need_to_be_delete_in_dtor)
		{
			glGenVertexArrays(1, &mVertex_array_object_id);
			glGenBuffers(1, &mVertex_buffer_object_id);
			glGenBuffers(1, &mIndex_buffer_object_id);
		}

		// TODO 万一这两个数组的生命周期不属于 vertex_array，我届时需更改这里
		// delete[] mVertices;
		// delete[] mIndices;
		~vertex_array()
		{
			if (mIs_these_array_need_to_be_delete_in_dtor) {

				delete[] mVertices;
				delete[] mIndices;
			}
		}

		// also called on every frame rendering? after setting Shader's Uniform, and before glDrawElements()?
		// "seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized"
		// TODO 解绑以后， glDraw 之前不绑定VAO，程序直接死给你看 ^_^
		void bind_VAO() const
		{
			// bind VAO
			glBindVertexArray(mVertex_array_object_id);
		}


		// 单纯地绘制时，只需要绑定一个 VAO 就行，VBO,IBO/EBO会跟它联系在一起
		// 但是要更新顶点数据时，除了bind_VAO，其他也要绑定
		void bind() const
		{

			bind_VAO();

			// bind VBO
			glBindBuffer(VBO_TARGET, mVertex_buffer_object_id);
			glBufferData(VBO_TARGET, sizeof(mVertices), mVertices, BUFFER_USAGE);

			// bind IBO/EBO
			glBindBuffer(IBO_TARGET, mIndex_buffer_object_id);
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


			// unbind
			unbind();
		}

		/**
		*
		1. unbind VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		2. unbind VAO
			glBindVertexArray(0);
		3. unbind IBO/EBO
			 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		 */
		static void unbind()
		{
			// 1. unbind VBO
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// 2. unbind VAO
			glBindVertexArray(0);
			// 3. unbind IBO/EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
