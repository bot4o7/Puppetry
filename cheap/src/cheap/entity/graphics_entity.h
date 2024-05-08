#pragma once
#include "entity.h"
#include "new_texture.h"
#include "../graphics/graphics_rectangle.h"
#include "../graphics/base/transform.h"

namespace cheap {
	class animation;

	class graphics_entity : public  cheap::entity
	{
	public:
		enum class type
		{
			UI,
			OBJ,
			BG
		};


		struct color
		{
			float mR, mG, mB;
			color(
				const float aR,
				const float aG,
				const float aB) :
				mR(aR), mG(aG), mB(aB)
			{

			}
		};
		struct vertex_layout
		{
			// ----- vertices and indices settings --------------------
			#define VERTICES_TYPE float
			#define INDICES_TYPE unsigned int
			// ----- vertices and indices settings --------------------

			// ----- VAO, VBO, IBO/EBO   Macros definitions------------
			#define VERTICES_LENGTH 20
			#define INDICES_LENGTH 6
			#define LAYOUT_LENGTH 12

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
			#define STRIDE_LAYOUT (3*sizeof(float))

			#define POS_POINTER (void*)0
			#define TEXCOORD_POINTER (void*)(3 * sizeof(float))
			#define LAYOUT_POINTER (void*)(20 * sizeof(float))

			#define VBO_TARGET GL_ARRAY_BUFFER
			#define IBO_TARGET GL_ELEMENT_ARRAY_BUFFER

			#define BUFFER_USAGE GL_DYNAMIC_DRAW


			#define INDICES_TOP_RIGHT 0
			#define INDICES_BOTTOM_RIGHT 1
			#define INDICES_BOTTOM_LEFT 2
			#define INDICES_TOP_LEFT 3

		// top right
			#define VERTICES_TR_X mVertices[0]
			#define VERTICES_TR_Y mVertices[1]
			#define VERTICES_TR_Z mVertices[2]
			#define VERTICES_TR_S mVertices[3]
			#define VERTICES_TR_T mVertices[4]
		// bottom right
			#define VERTICES_BR_X mVertices[5]
			#define VERTICES_BR_Y mVertices[6]
			#define VERTICES_BR_Z mVertices[7]
			#define VERTICES_BR_S mVertices[8]
			#define VERTICES_BR_T mVertices[9]
		// bottom left
			#define VERTICES_BL_X mVertices[10]
			#define VERTICES_BL_Y mVertices[11]
			#define VERTICES_BL_Z mVertices[12]
			#define VERTICES_BL_S mVertices[13]
			#define VERTICES_BL_T mVertices[14]
		// top left
			#define VERTICES_TL_X mVertices[15]
			#define VERTICES_TL_Y mVertices[16]
			#define VERTICES_TL_Z mVertices[17]
			#define VERTICES_TL_S mVertices[18]
			#define VERTICES_TL_T mVertices[19]


			// ----- VAO, VBO, IBO/EBO   Macros definitions------------

			// ----- vertices position --------------------------------
			// y-axis position screen top border
			#define POS_TOP 1.0f
			// y-axis position screen bottom border
			#define POS_BOTTOM (-1.0f)

			// x-axis position screen right border
			#define POS_RIGHT 1.0f
			// x-axis position screen left border
			#define POS_LEFT (-1.0f)

			// z-axis position screen
			#define POS_Z 0.0f
			// ----- vertices position --------------------------------
			#define VERTICES_LAYOUT_X mVertices[20]
			#define VERTICES_LAYOUT_Y mVertices[21]
			#define VERTICES_LAYOUT_Z mVertices[22]

			#define INDEX_OF_WIDTH_IN_VERTICES 0
			#define INDEX_OF_HEIGHT_IN_VERTICES 1

			#define VERTICES_RIGHT_BOUND mVertices[0]
			#define VERTICES_TOP_BOUND mVertices[1]
			#define VERTICES_LEFT_BOUND mVertices[10]
			#define VERTICES_BOTTOM_BOUND mVertices[11]


			float mVertices[VERTICES_LENGTH + LAYOUT_LENGTH];
			unsigned int mIndices[INDICES_LENGTH];

			unsigned int mVertex_array_object_id;
			unsigned int mVertex_buffer_object_id;
			unsigned int mIndex_buffer_object_id;


			// TODO
			void update_translation(
				const float aX_offset,
				const float aY_offset,
				const float aZ_offset)
			{
				LOG();

				mVertices[20] += aX_offset;
				mVertices[21] += aY_offset;
				mVertices[22] += aZ_offset;

				mVertices[23] += aX_offset;
				mVertices[24] += aY_offset;
				mVertices[25] += aZ_offset;

				mVertices[26] += aX_offset;
				mVertices[27] += aY_offset;
				mVertices[28] += aZ_offset;

				mVertices[29] += aX_offset;
				mVertices[30] += aY_offset;
				mVertices[31] += aZ_offset;

				update_vbo();
			}
			// TODO 暂时真不想做旋转的更新，等会
			void update_rotation(
				float   aX,
				float            aY,
				float aZ,
				bool   aPlaceholder_width,
				float        aHeight)
			{
			}
			void update_scale(
				const float aX_scale,
				const float aY_scale,
				const float aZ_scale)
			{
				LOG();

				// top right
				VERTICES_TR_X *= aX_scale;
				VERTICES_TR_Y *= aY_scale;
				VERTICES_TR_Z *= aZ_scale;

				// bottom right
				VERTICES_BR_X *= aX_scale;
				VERTICES_BR_Y *= aY_scale;
				VERTICES_BR_Z *= aZ_scale;
				// bottom left
				VERTICES_BL_X *= aX_scale;
				VERTICES_BL_Y *= aY_scale;
				VERTICES_BL_Z *= aZ_scale;
				// top left
				VERTICES_TL_X *= aX_scale;
				VERTICES_TL_Y *= aY_scale;
				VERTICES_TL_Z *= aZ_scale;

				update_vbo();
			}


			[[nodiscard]] bool is_pos_in_area_2d(const double aX, const double aY) const
			{
				if (aX > VERTICES_RIGHT_BOUND) return false;
				if (aX < VERTICES_LEFT_BOUND) return false;
				if (aY > VERTICES_TOP_BOUND) return false;
				if (aY < VERTICES_BOTTOM_BOUND) return false;

				return true;
			}

			[[nodiscard]] float get_x() const
			{
				return VERTICES_LAYOUT_X;
			}

			[[nodiscard]] float get_y() const
			{
				return VERTICES_LAYOUT_Y;
			}

			[[nodiscard]] float get_z() const
			{
				return VERTICES_LAYOUT_Z;
			}

			[[nodiscard]] float get_width() const
			{
				return INDEX_OF_WIDTH_IN_VERTICES;
			}

			[[nodiscard]] float get_height() const
			{
				return INDEX_OF_HEIGHT_IN_VERTICES;
			}

			vertex_layout(
				const float aWidth, const float aHeight,
				const float aX,
				const float aY,
				const float aZ
			)
				:
				mVertices{
					// top right
					aWidth,
					aHeight,
					POS_Z,
					TEX_S_END,
					TEX_T_END,
					// bottom right
					aWidth,
					-aHeight,
					POS_Z,
					TEX_S_END,
					TEX_T_BEGIN,
					// bottom left
					-aWidth,
					-aHeight,
					POS_Z,
					TEX_S_BEGIN,
					TEX_T_BEGIN,
					// top left
					-aWidth,
					aHeight,
					POS_Z,
					TEX_S_BEGIN,
					TEX_T_END,

					// layout
					aX,
					aY,
					aZ,
					aX,
					aY,
					aZ,
					aX,
					aY,
					aZ,
					aX,
					aY,
					aZ
				},
				mIndices{
					// first triangle
					INDICES_TOP_RIGHT,
					INDICES_BOTTOM_RIGHT,
					INDICES_TOP_LEFT,
					// second triangle
					INDICES_BOTTOM_RIGHT,
					INDICES_BOTTOM_LEFT,
					INDICES_TOP_LEFT,
				},
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

			~vertex_layout()
			{
				LOG();
				glDeleteVertexArrays(1, &mVertex_array_object_id);
				glDeleteBuffers(1, &mVertex_buffer_object_id);
				glDeleteBuffers(1, &mIndex_buffer_object_id);
			}

			void bind_vao() const
			{
				glBindVertexArray(mVertex_array_object_id);
			}
			void update_vbo() const
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

			void bind() const
			{
				LOG();
				bind_vao();
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

			static void unbind()
			{
				LOG();
				// 1. unbind VBO
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				// 2. unbind VAO
				glBindVertexArray(0);
				// 3. unbind IBO/EBO
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		};

		// no Projection and View
		struct uniform
		{
			unsigned int mTexture_slot;
			glm::mat4 mTranslation;
			glm::mat4 mScale;
			glm::mat4 mRotation;
			// plus to texture
			glm::vec4 mColor;
			float mOpacity;

			uniform(
				const unsigned int aTexture_slot,
				const float        aOpacity = 1.f)
				:
				mTexture_slot(aTexture_slot),
				mTranslation(ID_MAT),
				mScale(ID_MAT),
				mRotation(ID_MAT),
				mColor(glm::vec4()),
				mOpacity(aOpacity)
			{
				LOG();
			}
		};


		type mType;
		new_texture mTexture;
		vertex_layout mVertex_layout;
		uniform mUniform;
		//std::vector<animation*> mAnimation_list;
		bool mIs_visible;
		bool mIs_block_mouse;
		bool mIs_receive_mouse;
		bool mIs_receive_keyboard;



		// data
		// on_event_list
		// animation

		// use width and height
		graphics_entity(
			const unsigned int aId,
			const type         aType,
			const float        aX,
			const float        aY,
			const float        aZ,
			const float        aWidth,
			const float        aHeight,
			const char* aPic_file_path,
			const bool         aIs_RGBA,
			const bool         aIs_visible,
			const bool         aIs_block_mouse,
			const bool         aIs_receive_mouse,
			const bool         aIs_receive_keyboard,
			const float        aOpacity = 1.f
		)
			:
			entity(aId),
			mType(aType),
			mTexture(aPic_file_path, aIs_RGBA),
			mVertex_layout(aWidth, aHeight, aX, aY, aZ),
			mUniform(aOpacity),
			//mAnimation_list(std::vector<animation*>()),
			mIs_visible(aIs_visible),
			mIs_block_mouse(aIs_block_mouse),
			mIs_receive_mouse(aIs_receive_mouse),
			mIs_receive_keyboard(aIs_receive_keyboard)
		{
			LOG();
		}
		// use height to calculate width
		graphics_entity(
			const unsigned int aId,
			const type         aType,
			const float        aX,
			const float        aY,
			const float        aZ,
			const float        aHeight,
			const char* aPic_file_path,
			const bool         aIs_RGBA,
			const bool         aIs_visible,
			const bool         aIs_block_mouse,
			const bool         aIs_receive_mouse,
			const bool         aIs_receive_keyboard,
			const float        aColor_r = 0.f,
			const float        aColor_g = 0.f,
			const float        aColor_b = 0.f,
			const float        aOpacity = 1.f
		)
			:
			entity(aId),
			mType(aType),
			mTexture(aPic_file_path, aIs_RGBA),
			mVertex_layout(aHeight* mTexture.get_aspect_ratio(), aHeight, aX, aY, aZ),
			mUniform(mTexture.mId, aOpacity),
			//mAnimation_list(std::vector<animation*>()),
			mIs_visible(aIs_visible),
			mIs_block_mouse(aIs_block_mouse),
			mIs_receive_mouse(aIs_receive_mouse),
			mIs_receive_keyboard(aIs_receive_keyboard)
		{
			LOG();
		}


		~graphics_entity() override
			= default;



		/*void add_animation(animation* aAnimation)
		{
			mAnimation_list.emplace_back(aAnimation);
		}*/


		void before_draw(const int aTexture_slot) const
		{
			mTexture.bind(aTexture_slot);
			mVertex_layout.bind_vao();

		}

		[[nodiscard]] category get_category() const override
		{
			LOG();
			return category::GRAPHICS;
		}

		[[nodiscard]] bool is_pos_in_area_2d(const double aPos_x, const double aPos_y) const
		{
			return mVertex_layout.is_pos_in_area_2d(aPos_x, aPos_y);
		}

		[[nodiscard]] bool is_category(const category aCategory) const override
		{
			LOG();
			return aCategory == category::GRAPHICS;
		}
	};
}
