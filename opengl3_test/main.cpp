#pragma once
#include "Shader.h"

#include <GLFW/glfw3.h>


#define Println(x) std::cout << x << std::endl
#define Println2(x, y) std::cout << x << y << std::endl

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const std::string ShaderPath = "graphics/shaders/";

const std::string vertexShaderSource = ShaderPath + "vertex";
const std::string fragmentShaderSource = ShaderPath + "fragment";

int main()
{
	// 1.GLFW 初始化
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 2.GLFW 创建窗口
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		Println("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 3.设置 GLAD
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Println("Failed to initialize GLAD");
		return -1;
	}

	// 4.构建、编译 着色器 程序
	// ------------------------------------
	Shader ourShader1(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	Shader ourShader2(vertexShaderSource.c_str(), fragmentShaderSource.c_str());

	// 5.设置顶点的数据（和缓存区），并且设置顶点的属性
	// ------------------------------
	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};
	float vertices[] = {
		-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形
		0, 1, 2, // 第一个三角形
		//0, 1, 2 // 第一个三角形
		2, 3, 4  // 第二个三角形
	};
	unsigned int indices2[] = {
		2, 3, 4
	};


	unsigned int VBO, VAO, EBO, EBO2;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &EBO2);

	// 6.先绑定顶点数组对象、再绑定顶点缓冲、最后设置顶点的属性
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	// 注意，这是允许的，对glVertexAttribPointer的调用将VBO注册为顶点属性的绑定顶点缓冲区对象，这样之后我们就可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	//之后可以解除VAO的绑定，这样其他VAO调用就不会意外修改此VAO，但这种情况很少发生。无论如何，修改其他VAO都需要调用glBindVertexArray，因此在不直接需要时，我们通常不会解除VAO（或VBO）的绑定。
	glBindVertexArray(0);


	//取消注释此调用以在线框多边形中绘制。线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	Println2("Maximum nr of vertex attributes supported: ", nrAttributes);
	// 7.渲染循环
	// -----------
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		float time = glfwGetTime();

		ourShader1.use();

		ourShader1.setVec4f("offset", sin(time), 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		//鉴于我们只有一个VAO，没有必要每次都绑定它，但我们这样做是为了让事情更有条理
		// 画两个

		// 这里是为了用另一个 fragment shader 来渲染右边的三角形
		// 我看参考答案中,VAO, VBO, EBO 都用了两个， 我这里只用了一个大的 vertex数组装下 2个三角形， 然后在 glDrawArrays中指定 0, 3 （从第0个顶点开始的3个点  和 2, 3 （从第2个顶点开始的3个点）    两个三角形只有 5 个点， vertex[2] 这个点是公共点。
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		time = glfwGetTime();
		ourShader2.use();
		ourShader2.setVec4f("offset", sin(time), 0.0f, 0.0f, 0.0f);

		glDrawArrays(GL_TRIANGLES, 2, 3);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		//无需每次都解除绑定



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// ------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// --------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// -----------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ----------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// -----------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}