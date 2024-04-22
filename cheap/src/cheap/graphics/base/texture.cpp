#include "pch.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace cheap {
	texture::texture() : m_image_path_(""), m_tex_slot_(0), m_width_(1),
		m_height_(1), m_bytes_per_pixel_(4), m_color_format_(color_format::rgba), m_image_data_(nullptr)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &m_id_);
		bind(m_tex_slot_);

		config_texture();
		load_white_texture();
	}

	texture::texture(const std::string& image_path) : m_image_path_(image_path), m_tex_slot_(1), m_width_(1),
		m_height_(1), m_bytes_per_pixel_(4), m_color_format_(color_format::rgba), m_image_data_(nullptr)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &m_id_);
		bind(m_tex_slot_);

		config_texture();
		//FindColorFormat(); // not reliable
		load_sprite_gfx_texture();
	}

	texture::texture(const font& font) : m_image_path_(""), m_tex_slot_(1), m_width_(font.get_atlas_width()), m_height_(font.get_atlas_height()),
		m_bytes_per_pixel_(1), m_color_format_(color_format::red), m_image_data_(nullptr)
	{
		// Allocate space and bind a 2D texture
		glGenTextures(1, &m_id_);
		bind(m_tex_slot_);

		config_texture();
		load_font_texture(font);
	}

	texture::~texture()
	{
		if (m_image_data_ && m_image_path_ != "")
			stbi_image_free(m_image_data_);
		glDeleteTextures(1, &m_id_);
	}

	unsigned texture::get_id() const { return m_id_; }

	unsigned texture::get_tex_slot() const { return m_tex_slot_; }

	int texture::get_width() const { return m_width_; }

	int texture::get_height() const { return m_height_; }

	void texture::set_color_format(const color_format format) { m_color_format_ = format; }

	void texture::bind(const unsigned slot)
	{
		m_tex_slot_ = slot;
		// Assign a slot to the texture and bind it
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_id_);
	}

	void texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void texture::config_texture()
	{
		// Set how the texture will be processed when it needs to be scaled up or down
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // smaller
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // larger
		// Set how (and if) the texture will be repeated if its coords exceed the [0 1] range
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // x axis
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // y axis
	}

	void texture::load_white_texture() const
	{
		constexpr unsigned char white_texture[] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width_, m_height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, white_texture);
	}

	void texture::load_sprite_gfx_texture()
	{
		const int opengl_format = (m_color_format_ == color_format::rgb) ? GL_RGB : GL_RGBA;

		// Flip the image vertically so that it's compatible with OpenGL
		stbi_set_flip_vertically_on_load(1);
		// Load the image and fill in its parameters
		m_image_data_ = stbi_load(m_image_path_.c_str(), &m_width_, &m_height_, &m_bytes_per_pixel_, static_cast<int>(m_color_format_));

		glTexImage2D(GL_TEXTURE_2D,
			0, opengl_format, m_width_, m_height_, 0, opengl_format, GL_UNSIGNED_BYTE, m_image_data_);
	}

	void texture::load_font_texture(const font& font)
	{
		// Use 1 color channer per pixel
		int opengl_format = GL_RED;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Reserve memory for the individual glyph bitmaps in the atlas
		glTexImage2D(GL_TEXTURE_2D,
			0, GL_RED, font.get_atlas_width(), font.get_atlas_height(), 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

		int x_pos = 0;
		// Add all the glyph bitmaps into the same texture
		const FT_GlyphSlot glyph = font.get_font_face()->glyph;
		for (int c = 32; c < 128; c++) {
			if (FT_Load_Char(font.get_font_face(), c, FT_LOAD_RENDER))
				continue;

			glTexSubImage2D(GL_TEXTURE_2D, 0, x_pos, 0,
				glyph->bitmap.width, glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

			x_pos += glyph->bitmap.width;
		}
	}

	void texture::find_color_format()
	{
		// Get the image format from the given path
		const unsigned int pos = m_image_path_.find_last_of('.');

		// Return the appropriate color format according to the extension
		if (const std::string image_type = m_image_path_.substr(pos + 1); cheap::utils::to_lower(image_type) == "png")
			m_color_format_ = color_format::rgba;
		else // default format
			m_color_format_ = color_format::rgb;
	}
}
