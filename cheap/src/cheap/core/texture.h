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

	class texture
	{
	public:
		explicit texture(const char* aPic_file_path, bool aIs_RGBA = false);
		//When you're done using the texture, delete it. This will set texname to 0 and
		//delete all of the graphics card memory associated with the texture. If you
		//don't call this method, the texture will stay in graphics card memory until you
		//close the application.
		~texture();

		void bind(const int aTexture_slot) const;

		// TODO 你应确保两个材质的图片宽高一样。这里使用了 glTexSubImage2D
		void update(const char* aPic_file_path, bool aIs_RGBA = false);

		[[nodiscard]] unsigned int get_id() const;

	private:
		unsigned int mId;
		// load image, create texture and generate mipmaps
		int mWidth, mHeight, mChannels;
	};
}
