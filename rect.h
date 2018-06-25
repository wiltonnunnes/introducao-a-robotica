#include "point.h"

class Rect {
	private:
		int m_left, m_top, m_right, m_bottom;
		
	public:
		Rect(int left, int top, int right, int bottom) {
			m_left = left;
			m_top = top;
			m_right = right;
			m_bottom = bottom;
		}
		
		Point getCentroid() {
			return Point(0, 0);
		}
};
