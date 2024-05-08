#pragma once

namespace cheap {

	#define TEXTURE_TARGET GL_TEXTURE_2D
	// ------------ Wrapping Param -----------------------
	// wrap param name 
	#define WRAP_S GL_TEXTURE_WRAP_S
	// wrap param name 
	#define WRAP_T GL_TEXTURE_WRAP_T
	// param, wrap mode
	#define WRAP_REPEAT GL_REPEAT
	// ------------ Wrapping Param -----------------------

	// ------------ Filtering Param ----------------------
	// filter param name
	#define FILTER_MIN GL_TEXTURE_MIN_FILTER
	// filter param name
	#define FILTER_MAG GL_TEXTURE_MAG_FILTER
	// param, filter mode
	#define FILTER_LINEAR GL_LINEAR
	// ------------ Filtering Param ----------------------

	// ------------ image --------------------------------
	// COLOR FORMAT
	#define FORMAT_RGB GL_RGB
	// COLOR FORMAT
	#define FORMAT_RGBA GL_RGBA

	#define BASE_MIPMAP_LEVEL 0

	#define IMAGE_BORDER 0
	#define OFFSET_X_UPDATE 0
	#define OFFSET_Y_UPDATE 0
	// image data type
	#define TYPE_U_BYTE GL_UNSIGNED_BYTE
	// ------------ image --------------------------------

	// ------------ texture coords -----------------------
	// texture U begin
	#define TEX_S_BEGIN 0.0f
	// texture V begin
	#define TEX_T_BEGIN 0.0f

	// texture U end
	#define TEX_S_END 1.0f
	// texture V end
	#define TEX_T_END 1.0f
	// ------------ texture coords -----------------------

	class new_texture
	{
	public:
		unsigned int mId;
		std::string mPic_file_path;
		int mWidth, mHeight, mChannels;
		bool mIs_RGBA;


		new_texture(const char* aPic_file_path, bool aIs_RGBA);

		~new_texture();

		void bind(const int aTexture_slot) const;

		void update(const char* aPic_file_path, bool aIs_RGBA);

		unsigned get_id() const;

		float get_aspect_ratio() const;
	};

}
