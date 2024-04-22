#pragma once
#include "../../utils/utils.h"

#ifdef CP_OPENGL_API
#include "base.h"
#include "font.h"

namespace cheap {

	class texture final : public base
	{
	public:

		enum class color_format
		{
			red = 1, rgb = 3, rgba
		};

		/********************** CONSTRUCTORS *************************/
	// Constructor for rectangles
		texture();

		// Constructor for images
		explicit texture(const std::string& image_path);

		// Constructor for fonts
		explicit texture(const font& font);

		~texture() override;

		/******************** ACCESSORS/MUTATORS *********************/

		[[nodiscard]] unsigned int get_id() const;

		[[nodiscard]] unsigned int get_tex_slot() const;

		[[nodiscard]] int get_width() const;

		[[nodiscard]] int get_height() const;

		void set_color_format(const color_format format);

		/********************* TEXTURE METHODS **********************/
		void bind(const unsigned int slot);

		static void unbind();

	private:
		std::string m_image_path_;
		// texture_slot
		unsigned int m_tex_slot_;
		int m_width_;
		int m_height_;
		int m_bytes_per_pixel_;
		color_format m_color_format_;
		unsigned char* m_image_data_;

		static void config_texture();

		void load_white_texture() const;

		void load_sprite_gfx_texture();

		static void load_font_texture(const font& font);


		// Get the pixel data format according to the image extension
		void find_color_format();
	};
}
#endif
