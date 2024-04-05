#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Full screen windows 全屏窗口
	// To create a full screen window, you need to specify which monitor the window should use.In most cases, the user's primary monitor is a good choice. For more information about retrieving monitors, see Retrieving monitors.
	// 要创建全屏窗口，您需要指定窗口应使用哪个监视器。在大多数情况下，用户的主显示器是一个不错的选择。有关检索监视器的更多信息，请参阅检索监视器。
	//
	// Windowed mode windows can be made full screen by setting a monitor with glfwSetWindowMonitor, and full screen ones can be made windowed by unsetting it with the same function.
	// 窗口模式窗口可以通过使用 glfwSetWindowMonitor 设置监视器来设置为全屏，并且可以通过使用相同的函数取消设置来设置全屏窗口。
	//
	// Each field of the GLFWvidmode structure corresponds to a function parameter or window hint and combine to form the desired video mode for that window.The supported video mode most closely matching the desired video mode will be set for the chosen monitor as long as the window has input focus.For more information about retrieving video modes, see Video modes.
	// GLFWvidmode 结构的每个字段对应于一个函数参数或窗口提示，并组合起来形成该窗口所需的视频模式。只要窗口具有输入焦点，就会为所选显示器设置与所需视频模式最匹配的支持视频模式。有关检索视频模式的更多信息，请参阅视频模式。
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Window", glfwGetPrimaryMonitor(), NULL);
	// Not full screen window
	//GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Window", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	//gladLoadGL(glfwGetProcAddress);
	// 方案一:
	//gladLoadGL(); 
	// 方案二:
	//gladLoadGLloader((GLADloadproc) glfwGetProcAdderess);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// NOTE: OpenGL error checks have been omitted for brevity

	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}

//! [code]
