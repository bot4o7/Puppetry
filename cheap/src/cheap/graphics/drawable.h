#pragma once

#include "base/base.h"
#include "base/transform.h"
#include "base/color.h"

namespace cheap {


	enum class layout_position
	{
		left, mid_left, mid_x, mid_right, right, // horizontal
		bottom, mid_bottom, mid_y, mid_top, top  // vertical
	};

	struct parent_layout_pos
	{
		layout_position horizontal;
		layout_position vertical;
	};

	struct parent_layout_coords
	{
		float x;
		float y;
	};

	class drawable
	{
	public:
		virtual             ~drawable() = default;
		static unsigned int get_index_count();

		/* Transform operations */
		[[nodiscard]] transform* get_transform() const;
		[[nodiscard]] const transform* get_parent_transform() const;
		void                           set_parent_transform(transform* transform);
		void                           set_parent_layout_pos(layout_position horizontal, layout_position vertical);
		void                           set_parent_layout_coords(float x, float y);
		/* Operations used for rendering */
		[[nodiscard]] virtual unsigned int get_item_count() const = 0;
		[[nodiscard]] virtual unsigned int get_buffer_size() const = 0;
		virtual const std::vector<vertex>& get_vertex_data() = 0;
		[[nodiscard]] virtual unsigned int get_tex_id() const { return 0; };
		virtual void                       set_texture_slot(int slot) { };
		[[nodiscard]] virtual color        get_color() const { return { 255, 255, 255, 0 }; };
		virtual void                       set_color(color color) { };

	protected:
		static const unsigned int s_index_count;
		std::unique_ptr<transform> m_transform_;
		transform* m_parent_transform_;

		drawable();
		void update_transform() const;

	private:
		std::unique_ptr<parent_layout_pos> m_parent_layout_pos_;
		std::unique_ptr<parent_layout_coords> m_parent_layout_coords_;

		[[nodiscard]] float find_horizontal_pos() const;
		[[nodiscard]] float find_vertical_pos() const;
	};
}
