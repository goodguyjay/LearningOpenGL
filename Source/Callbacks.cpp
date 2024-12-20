#include "pch.hpp"
#include "Callbacks.hpp"

void FrameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}
