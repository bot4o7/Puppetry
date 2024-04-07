#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define Println(x) std::cout << x << std::endl
#define Println2(x, y) std::cout << x << y << std::endl

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// 设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

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
	// 4.1.顶点着色器
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// 4.1.2.检查编译是否出错
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Println2("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}
	// 4.2.片段着色器
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// 4.2.2.检查编译是否通过
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Println2("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
	}
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	// 4.2.2.检查编译是否通过
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		Println2("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
	}
	// 4.3.链接 着色器 程序
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// 4.3.2.检查编译是否通过
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Println2("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
	}
	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	// 4.3.2.检查编译是否通过
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		Println2("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	// 5.设置顶点的数据（和缓存区），并且设置顶点的属性
	// ------------------------------
	//float vertices[] = {
	//0.5f, 0.5f, 0.0f,   // 右上角
	//0.5f, -0.5f, 0.0f,  // 右下角
	//-0.5f, -0.5f, 0.0f, // 左下角
	//-0.5f, 0.5f, 0.0f   // 左上角
	//};
	float vertices[] = {
		-0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 注意，这是允许的，对glVertexAttribPointer的调用将VBO注册为顶点属性的绑定顶点缓冲区对象，这样之后我们就可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	//之后可以解除VAO的绑定，这样其他VAO调用就不会意外修改此VAO，但这种情况很少发生。无论如何，修改其他VAO都需要调用glBindVertexArray，因此在不直接需要时，我们通常不会解除VAO（或VBO）的绑定。
	glBindVertexArray(0);


	//取消注释此调用以在线框多边形中绘制。线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//鉴于我们只有一个VAO，没有必要每次都绑定它，但我们这样做是为了让事情更有条理
		// 画两个

		// 这里是为了用另一个 fragment shader 来渲染右边的三角形
		// 我看参考答案中,VAO, VBO, EBO 都用了两个， 我这里只用了一个大的 vertex数组装下 2个三角形， 然后在 glDrawArrays中指定 0, 3 （从第0个顶点开始的3个点  和 2, 3 （从第2个顶点开始的3个点）    两个三角形只有 5 个点， vertex[2] 这个点是公共点。
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram2);
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
	glDeleteProgram(shaderProgram);

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