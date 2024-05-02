#pragma once

#ifdef CP_OPENGL_API
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

#define FREE_TYPE_FONT
#ifdef FREE_TYPE_FONT
#  include <ft2build.h>
#  include FT_FREETYPE_H
#endif
