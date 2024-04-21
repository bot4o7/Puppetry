#include "pch.h"
#include "Font.h"

namespace cheap {
	font::font(const std::string& path, const std::string& name, const unsigned int size)
		: m_path_(path), m_name_(name), m_size_(size), m_freetype_(nullptr), m_face_(nullptr),
		m_atlas_width_(0), m_atlas_height_(0)
	{
		init_free_type();
		load_font_data();
	}

	font::~font()
	{
		// Repeat for each glyph in the font
		for (int c = 32; c < 128; c++)
			delete m_characters_.at(c);	// delete glyph data

		clear_free_type();
	}

	std::string  font::get_name() const { return m_name_; }
	std::string  font::get_path() const { return m_path_; }
	unsigned int font::get_size() const { return m_size_; }

	unsigned int font::get_atlas_width() const { return m_atlas_width_; }
	unsigned int font::get_atlas_height() const { return m_atlas_height_; }
	const FT_Face& font::get_font_face() const { return m_face_; }
	const std::unordered_map<char, glyph*>& font::get_glyphs() const { return m_characters_; }

	// Initialize FreeType resources
	void font::init_free_type()
	{
		// Initialize FreeType library
		if (FT_Init_FreeType(&m_freetype_))
			LOG_INFO("Font", "FreeType: Failed to initialize FreeType library.\n");
		// Load the given font
		if (FT_New_Face(m_freetype_, m_path_.c_str(), 0, &m_face_))
			LOG_INFO("Font", "FreeType: Failed to load font.\n");
		FT_Set_Pixel_Sizes(m_face_, 0, m_size_);
	}

	// Load the glyph data from the font and create an atlas
	void font::load_font_data()
	{
		const FT_GlyphSlot glyph_slot = m_face_->glyph;
		float x_pos = 0.0f;
		for (int c = 32; c < 128; c++) {
			// Load a specific ASCII character from the font
			if (FT_Load_Char(m_face_, c, FT_LOAD_RENDER)) {
				LOG_INFO("Font", "FreeType: Failed to load character " + (char)c + std::string("\n"));
				continue;
			}

			// Create a new glyph and add it to the unordered map
			create_glyph(x_pos, c, glyph_slot);
			// Move the x position for the next glyph in the atlas
			x_pos += glyph_slot->bitmap.width;

			// Add the glyph's width to the atlas width
			m_atlas_width_ += glyph_slot->bitmap.width;
			// Store the height of the tallest glyph
			m_atlas_height_ = std::max(static_cast<int>(m_atlas_height_), static_cast<int>(glyph_slot->bitmap.rows));
		}
	}

	// Create a new glyph and add it to the unordered map
	void font::create_glyph(const float x_pos, const int character, const FT_GlyphSlot& glyph_slot)
	{
		// Allocate memory for the glyph
		auto new_glyph = new glyph;
		new_glyph->width = glyph_slot->bitmap.width;
		new_glyph->height = glyph_slot->bitmap.rows;
		new_glyph->bearing_x = glyph_slot->bitmap_left;
		new_glyph->bearing_y = glyph_slot->bitmap_top;
		new_glyph->advance_x = glyph_slot->advance.x / 64;
		new_glyph->atlas_coords_x = x_pos;
		m_characters_.insert(std::pair<char, glyph*>(character, new_glyph));
	}

	// Clear FreeType resources
	void font::clear_free_type() const
	{
		FT_Done_Face(m_face_);
		FT_Done_FreeType(m_freetype_);
	}
}
