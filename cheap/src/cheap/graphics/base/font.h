#pragma once

#include "ft2build.h"
#include "freetype/freetype.h"

namespace cheap {
	struct glyph
	{
		float width;        // width in pixels
		float height;       // height in pixels
		float bearing_x;     // distance from origin to left side
		float bearing_y;     // distance from origin to top side
		float advance_x;     // distance from origin to next glyph's origin
		float atlas_coords_x;  // x coordinate in the atlas
	};

	class font
	{
	public:
		font(const std::string& path, const std::string& name, unsigned int size = 24);
		~font();

		/* Accessors for data used to differentiate between various fonts */
		std::string  get_name() const;
		std::string  get_path() const;
		unsigned int get_size() const;
		/* Accessors for base font data */
		unsigned int get_atlas_width() const;
		unsigned int get_atlas_height() const;
		const FT_Face& get_font_face() const;
		const std::unordered_map<char, glyph*>& get_glyphs() const;

	private:
		std::string m_path_;
		std::string m_name_;
		unsigned int m_size_;
		FT_Library m_freetype_;
		FT_Face m_face_;
		std::unordered_map<char, glyph*> m_characters_;
		unsigned int m_atlas_width_;
		unsigned int m_atlas_height_;

		void init_free_type();
		void load_font_data();
		void create_glyph(const float x_pos, const int character, const FT_GlyphSlot& glyph_slot);
		void clear_free_type() const;
	};
}
