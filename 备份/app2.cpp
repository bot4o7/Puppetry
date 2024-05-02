#include "pch.h"
#include "app.h"

#include "../events/event.h"
#include "../graphics/renderer.h"

#ifdef CP_OPENGL_API
namespace cheap {
	app::app(unsigned int aWidth, unsigned int aHeight)
		:
		mWindow(
			std::make_shared<window>(
				DEFAULT_TITLE,
				aWidth,
				aHeight,
				[this](event* aEvent) {this->on_event(aEvent); },
				[this]() {this->update(); })), mLayer_manager(std::make_shared<layer_manager>()),
		mRenderer(std::make_shared<renderer>(mWindow, mLayer_manager)),
		mInput_system(std::make_shared<input_system>(mWindow->get_raw_window())
		),
		mEvent_system(std::make_shared <event_system>(mWindow, mLayer_manager, mRenderer, mInput_system))
	{
		LOG();
	}
	app::~app()
	{
		LOG();
	}

	const int WIDTH = 1184;
	const int HEIGHT = 666;

	/* origin is the upper left corner */
	unsigned char image[HEIGHT][WIDTH];
	/* Replace this function with something useful. */

	void
		draw_bitmap(FT_Bitmap* bitmap,
			FT_Int      x,
			FT_Int      y)
	{
		FT_Int  i, j, p, q;
		FT_Int  x_max = x + bitmap->width;
		FT_Int  y_max = y + bitmap->rows;


		/* for simplicity, we assume that `bitmap->pixel_mode' */
		/* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

		for (i = x, p = 0; i < x_max; i++, p++) {
			for (j = y, q = 0; j < y_max; j++, q++) {
				if (i < 0 || j < 0 ||
					i >= WIDTH || j >= HEIGHT)
					continue;

				image[j][i] |= bitmap->buffer[q * bitmap->width + p];
			}
		}
	}


	void
		show_image(void)
	{
		int  i, j;


		for (i = 0; i < HEIGHT; i++) {
			for (j = 0; j < WIDTH; j++)
				putchar(image[i][j] == 0 ? ' '
					: image[i][j] < 128 ? '+'
					: '*');
			putchar('\n');
		}
	}

	void app::run()
	{
		LOG();

		//const renderer                      my_renderer(mWindow, mLayer_manager);
		//const float                   begin_frame = static_cast<float>(glfwGetTime());
		//float     last_frame = begin_frame;


		//graphics_entity task(
		//	1,
		//	graphics_entity::type::OBJ,
		//	0.5f, 0.0f, -0.1f,
		//	0.f, 1.0f,
		//	"data/images/ys.png",
		//	true,
		//	true,
		//	false,
		//	true,
		//	true);
		//graphics_entity task2(
		//	2,
		//	graphics_entity::type::OBJ,
		//	-0.2f, 0.0f, 0.1f,
		//	0.f, 1.0f,
		//	"data/images/friends.png",
		//	true,
		//	true,
		//	false,
		//	true,
		//	true);

		//mRenderer->add_new_task(&task);
		//mRenderer->add_new_task(&task2);
		FT_Library    library;
		FT_Face       face;

		FT_GlyphSlot  slot;
		FT_Matrix     matrix;                 /* transformation matrix */
		FT_Vector     pen;                    /* untransformed origin  */
		FT_Error      error;

		/*char* filename;
		char* text;*/

		double        angle;
		int           target_height;
		int           n, num_chars;


		/*if (argc != 3) {
			fprintf(stderr, "usage: %s font sample-text\n", argv[0]);
			exit(1);
		}*/

		const char* filename = "data/fonts/arial.ttf";                           /* first argument     */
		//filename = argv[1];                           /* first argument     */
		//text = argv[2];                           /* second argument    */
		const char* text = "hello world";                           /* second argument    */
		num_chars = strlen(text);
		angle = (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */
		target_height = HEIGHT;

		error = FT_Init_FreeType(&library);              /* initialize library */
		/* error handling omitted */

		error = FT_New_Face(library, filename, 0, &face);/* create face object */
		/* error handling omitted */

		/* use 50pt at 100dpi */
		error = FT_Set_Char_Size(face, 50 * 64, 0,
			100, 0);                /* set character size */
		/* error handling omitted */

		/* cmap selection omitted;                                        */
		/* for simplicity we assume that the font contains a Unicode cmap */

		slot = face->glyph;

		/* set up matrix */
		matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
		matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
		matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
		matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

		/* the pen position in 26.6 cartesian space coordinates; */
		/* start at (300,200) relative to the upper left corner  */
		pen.x = 300 * 64;
		pen.y = (target_height - 200) * 64;

		for (n = 0; n < num_chars; n++) {
			/* set transformation */
			FT_Set_Transform(face, &matrix, &pen);

			/* load glyph image into the slot (erase previous one) */
			error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
			if (error)
				continue;                 /* ignore errors */

			/* now, draw to our target surface (convert position) */
			draw_bitmap(&slot->bitmap,
				slot->bitmap_left,
				target_height - slot->bitmap_top);

			/* increment pen position */
			pen.x += slot->advance.x;
			pen.y += slot->advance.y;
		}

		show_image();

		FT_Done_Face(face);
		FT_Done_FreeType(library);

		return;
		while (app::is_running()) {
			/*if (const float current_frame = static_cast<float>(glfwGetTime()); current_frame - last_frame > 2.0f) {
				constexpr float       pace = 0.1f;
				const float delta_frame = current_frame - begin_frame;

				last_frame = current_frame;
			}*/
			/*mRenderer->clear();
			mRenderer->draw();
			mRenderer->update();*/

			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);


			// Swap the buffers
			glfwSwapBuffers(mWindow->get_raw_window());
			glfwPollEvents();
		}
	}
	void app::clear() const
	{
		LOG();
		// Clear past events
		//m_event_system_->clear();
		// Clear old graphics and poll events
		mWindow->clear();
	}
	void app::update() const
	{
		LOG();
		// Set the active entities to be processed in this frame
		//m_event_system_->SetEntities(mEntityManager->GetEntities());
		// Render all graphics visible in this frame
		//m_renderer_->submit(mEntityManager->GetEntities());
		//m_renderer_->submit();
		// Update the graphics in the window
		mWindow->update();
	}
	bool app::is_running() const
	{
		//LOG();
		return !mWindow->is_closed();
	}
	void app::exit()
	{
		LOG();
		mWindow->close();
	}

	void app::on_event(event* aNew_event)
	{
		LOG();
		mEvent_system->handle(aNew_event);
	}

	// input* get_input() const;
	window* app::get_window() const
	{
		//LOG();
		return mWindow.get();
	}
	// cursor_system* get();
	// entity_system* get();
	// state_system* get();
	// font_system* get();
	// audio_system get();
	// file_system get();
}
#endif
