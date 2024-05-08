#include "pch.h"
#include "new_texture.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace cheap {
	new_texture::new_texture(
		const char* aPic_file_path,
		bool aIs_RGBA)
		:
		mId(0),
		mPic_file_path(aPic_file_path),
		mWidth(0),
		mHeight(0),
		mChannels(0),
		mIs_RGBA(aIs_RGBA)
	{
		LOG();
		glGenTextures(1,
			&mId);
		glBindTexture(TEXTURE_TARGET,
			mId);

		// set the texture wrapping parameters
		glTexParameteri(TEXTURE_TARGET,
			WRAP_S,
			WRAP_REPEAT);
		glTexParameteri(TEXTURE_TARGET,
			WRAP_T,
			WRAP_REPEAT);

		// set texture filtering parameters
		glTexParameteri(TEXTURE_TARGET,
			FILTER_MIN,
			FILTER_LINEAR);
		glTexParameteri(TEXTURE_TARGET,
			FILTER_MAG,
			FILTER_LINEAR);

		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(aPic_file_path,
			&mWidth,
			&mHeight,
			&mChannels,
			0);
		if (data) {
			glTexImage2D(TEXTURE_TARGET,
				BASE_MIPMAP_LEVEL,
				aIs_RGBA
				? FORMAT_RGBA
				: FORMAT_RGB,
				mWidth,
				mHeight,
				IMAGE_BORDER,
				aIs_RGBA
				? FORMAT_RGBA
				: FORMAT_RGB,
				TYPE_U_BYTE,
				data);
			glGenerateMipmap(TEXTURE_TARGET);
		} else { LOG_INFO("Failed to load texture"); }
		stbi_image_free(data);
	}

	new_texture::~new_texture()
	{
		LOG();
		glDeleteTextures(1, &mId);
	}

	void new_texture::bind(
		const int aTexture_slot) const
	{
		//LOG();
		if (aTexture_slot < GL_TEXTURE0
			|| GL_TEXTURE15 < aTexture_slot) {
			LOG_INFO("only 16 texture slots availiable now\n现在只支持 0-15 共 16 个 纹理 slot");
		} else {
			glActiveTexture(aTexture_slot);
			glBindTexture(TEXTURE_TARGET, mId);
		}
	}

	void new_texture::update(
		const char* aPic_file_path,
		bool aIs_RGBA)
	{
		LOG();
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(aPic_file_path, &mWidth, &mHeight, &mChannels, 0);
		if (data) {
			glTexSubImage2D(TEXTURE_TARGET, BASE_MIPMAP_LEVEL, 0, 0, mWidth, mHeight, aIs_RGBA ? FORMAT_RGBA : FORMAT_RGB, TYPE_U_BYTE, data);
			glGenerateMipmap(TEXTURE_TARGET);
		} else {
			LOG_INFO("Failed to load texture");
		}
		stbi_image_free(data);
	}

	unsigned new_texture::get_id() const
	{
		LOG();
		return mId;
	}

	float new_texture::get_aspect_ratio() const
	{
		LOG();
		return static_cast<float>(mWidth) / static_cast<float>(mHeight);
	}
}
