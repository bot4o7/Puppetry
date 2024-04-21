#pragma once

namespace cheap {
	class base
	{
	public:
		[[nodiscard]] unsigned int get_id() const { return m_id_; }
		void                       set_id(const unsigned int id) { m_id_ = id; }

		base() = default;
		virtual ~base() = default;
	protected:
		unsigned int m_id_;
	};

}