#ifndef APP_UTIL_H
#define APP_UTIL_H

#include <glm/glm.hpp>

class AppUtil
{
public:
	static void set_displaySize(glm::vec2 displaySize) { m_displaySize = displaySize; }
	static glm::vec2 displaySize() { return m_displaySize; }

	static void set_clearColor(glm::vec4 clearColor) { m_clearColor = clearColor; }
	static glm::vec4 clearColor() { return m_clearColor; }

private:
	static glm::vec2 m_displaySize;
	static glm::vec4 m_clearColor;
};

#endif //APP_UTIL_H