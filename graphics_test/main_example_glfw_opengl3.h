#pragma once

// 未来，程序编译时使用 "OpenGL3", 还是 "DirectX11" 之类的， 将会根据编译标记决定 “def", "ifdef", "else", "endif"

#include <cstdio>

// We will here use stb_image.h to load images from disk.
// 我们将在这里使用 stb_image.h 从磁盘加载图像。
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h> // Will drag system OpenGL headers
//#include "GLFW/glfw3.h"



int my_image_width;
int my_image_height;
GLuint my_image_texture;
bool ret;

// Simple helper function to load an image into a OpenGL texture with common settings
bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
	#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}


// 未来，这个 AppGLFW_GL3 应该 继承 / 实现 某个 抽象类 / 接口
class AppGLFW_GL3
{
public:
	static int Run_Example()
	{
		if (before_loop() != 0)
			return 1;

		loop();

		after_loop();
	};

	static AppGLFW_GL3& Get()
	{
		static AppGLFW_GL3 instance;
		return instance;
	}


private:
	AppGLFW_GL3(const AppGLFW_GL3&) = delete;
	AppGLFW_GL3() { };
	~AppGLFW_GL3();

	// Our state
	static bool show_demo_window;
	static bool show_another_window;
	static ImVec4 clear_color;
	static GLFWwindow* window;
	const char* glsl_version = "#version 130";
	static ImGuiIO* io;

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	};


	// 如果 glfwInit() 的返回值不是0，则返回1，也就是glfw失败时，该函数返回1
	static int before_loop(int window_width = 1280, int window_height = 720,
		const char* window_title = "Dear ImGui GLFW+OpenGL3 example",
		GLFWmonitor* moniter_ptr = nullptr, GLFWwindow* share_window_ptr = nullptr)
		//static int before_loop()
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
			return 1;

		// HEY! LOOK AT HERE
		// 项目的附加依赖项，可以用 glfw3.lib，也可以用 glfw3_mt.lib 吗？ 
		// mt 是 multi thread 多线程的意思， 不知道用了会不会有性能提升，或其他缺点        依赖项中的 opengl32.lib 好像是系统自带？反正 imgui 自己给的项目和 example 中没有

		// GL 3.3.8 + GLSL 130
		//const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // .3.8
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only


		//Add to Initialization:
		// Create window with graphics context
		window = glfwCreateWindow(window_width, window_height, window_title, moniter_ptr, share_window_ptr);
		if (window == nullptr)
			return 1;
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = &ImGui::GetIO();
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();
		//ImGui_ImplOpenGL3_Init(glsl_version);

		// Load Fonts
		// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
		// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
		// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
		// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
		// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
		// - Read 'docs/FONTS.md' for more instructions and details.
		// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
		// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
		//io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != nullptr);



		// 这里初始化的值，以后可以改为函数传递的参数
		show_demo_window = true;
		show_another_window = false;
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



		// Load our texture after initializing OpenGL loader (for example after glewInit()):
		// 初始化 OpenGL 加载器后加载纹理（例如在 glewInit() 之后）：
		my_image_width = 0;
		my_image_height = 0;
		my_image_texture = 0;
		ret = LoadTextureFromFile("data/Meursault.png", &my_image_texture, &my_image_width, &my_image_height);
		my_image_height /= 2;
		my_image_width /= 2;
		IM_ASSERT(ret);
		// In the snippet of code above, we added an assert IM_ASSERT(ret) to check if the image file was loaded correctly.You may also use your Debugger and confirm that my_image_texture is not zero and that my_image_width my_image_width are correct.
		// 在上面的代码片段中，我们添加了一个断言 IM_ASSERT(ret) 来检查图像文件是否已正确加载。您还可以使用调试器并确认 my_image_texture 不为零并且 my_image_width my_image_width 正确。
		// Now that we have an OpenGL texture and its dimensions, we can display it in our main loop :
		// 现在我们有了 OpenGL 纹理及其尺寸，我们可以在主循环中显示它：
		return 0;
	};

	static void loop()
	{
		while (!glfwWindowShouldClose(window)) {

			// Poll events  and handle events (inputs, window resize, etc.)
					// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
					// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
					// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
					// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			// Update application/game state
			// Render contents into a framebuffer
			// Swap/Present framebuffer to the screen
			// Wait some time (e.g. 1/60 of a second)



			// Add to start of main loop:
			// (Your code calls glfwPollEvents())
			// ...
			glfwPollEvents();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// bool ImGui::ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)



			//const char* filename = "graphics_test\\data\\Meursault.png";
			// Now that we have an OpenGL texture and its dimensions, we can display it in our main loop :
			// 现在我们有了 OpenGL 纹理及其尺寸，我们可以在主循环中显示它：

			// 下面这些窗口基本属性设置的参考——如有无菜单栏、有无标题栏
			// Demonstrate the various window flags. Typically you would just use the default!
			//static bool no_titlebar = false;
			//static bool no_scrollbar = false;
			//static bool no_menu = false;
			//static bool no_move = false;
			//static bool no_resize = false;
			//static bool no_collapse = false;
			//static bool no_close = false;
			//static bool no_nav = false;
			//static bool no_background = false;
			//static bool no_bring_to_front = false;
			//static bool unsaved_document = false;

			//ImGuiWindowFlags window_flags = 0;
			//if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
			//if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
			//if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
			//if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
			//if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
			//if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
			//if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
			//if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
			//if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
			//if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
			//if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

			//// We specify a default position/size in case there's no data in the .ini file.
			//// We only do it to make the demo applications a little more welcoming, but typically this isn't required.
			//const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
			//ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
			//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

			//// Main body of the Demo window starts here.
			//if (!ImGui::Begin("Dear ImGui Demo", p_open, window_flags)) {
			//	// Early out if the window is collapsed, as an optimization.
			//	ImGui::End();
			//	return;
			//}

			static bool no_titlebar = true;
			static bool no_scrollbar = true;
			static bool no_menu = true;
			static bool no_move = false;
			static bool no_resize = false;
			static bool no_collapse = true;
			static bool no_close = false;
			static bool no_nav = true;
			static bool no_background = false;
			static bool no_bring_to_front = false;
			static bool unsaved_document = false;

			ImGuiWindowFlags window_flags = 0;
			if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
			if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
			if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
			if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
			if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
			if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
			if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
			if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
			if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
			if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
			static bool flag_true = true;
			static bool* p_open = &flag_true; // void ImGui::ShowDemoWindow(bool* p_open);
			if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

			// We specify a default position/size in case there's no data in the .ini file.
			// We only do it to make the demo applications a little more welcoming, but typically this isn't required.
			/*const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);*/

			// Main body of the Demo window starts here.
			//if (!ImGui::Begin("OpenGL Texture", p_open, window_flags)) {
			ImGui::Begin("OpenGL Texture", p_open, window_flags);
			// Early out if the window is collapsed, as an optimization.
			ImGui::Text("pointer = %x", my_image_texture);
			ImGui::Text("size = %d x %d", my_image_width, my_image_height);
			ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
			ImGui::End();
			//return;
		//}
		//ImGui::Begin("OpenGL Texture Text");
		//ImGui::Text("pointer = %x", my_image_texture);
		//ImGui::Text("size = %d x %d", my_image_width, my_image_height);
		//ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		//ImGui::End();



		//ImGui::ImageButton(texture, w, h, padding, color, alpha, bordercolor, borderalpha);
		//ImGui::Text("This is some useless text.");

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
			//ImGui::ShowDemoWindow(); // Show demo window! :)

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
				ImGui::End();
			}

			// 3. Show another simple window.
			if (show_another_window) {
				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
					show_another_window = false;
				ImGui::End();
			}

			// Add to the end of main loop:
			// Rendering
			// (Your code clears your framebuffer, renders your other stuff etc.)
			ImGui::Render();

			int display_w, display_h;
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// (Your code calls glfwSwapBuffers() etc.)
			glfwSwapBuffers(window);
		}
	};

	static void after_loop()
	{
		// Shut down:
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	};

};

// Our state
//bool AppGLFW_GL3::show_demo_window = true;
//bool AppGLFW_GL3::show_another_window = false;
//ImVec4 AppGLFW_GL3::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool AppGLFW_GL3::show_demo_window;
bool AppGLFW_GL3::show_another_window;
ImVec4 AppGLFW_GL3::clear_color;
ImGuiIO* AppGLFW_GL3::io;
GLFWwindow* AppGLFW_GL3::window;

