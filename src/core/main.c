#include <stdio.h>
// #include "bx/bx.h"
// #include "bgfx/bgfx.h"
#include "bgfx/c99/bgfx.h"
// #include "bgfx/platform.h"
#include "GLFW/glfw3.h"
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "GLFW/glfw3native.h"
#include "core/logo.h"

#include "global/global.h"
#include "math/math_inc.h"

static bool s_showStats = false;

static void glfw_errorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfw_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
		s_showStats = !s_showStats;
}

int main(int argc, char **argv)
{
	// Create a GLFW window without an OpenGL context.
	glfwSetErrorCallback(glfw_errorCallback);
	if (!glfwInit())
		return 1;
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow *window = glfwCreateWindow(1024, 768, "bgfx_test", NULL, NULL);
	if (!window)
		return 1;
	glfwSetKeyCallback(window, glfw_keyCallback);
	// Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
	// Most graphics APIs must be used on the same thread that created the window.
	// bgfx::renderFrame();
	
  // Initialize bgfx using the native window handle and window resolution.
	bgfx_init_t init;
	bgfx_init_ctor(&init);
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	init.platformData.ndt = glfwGetX11Display();
	init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
	init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
	init.platformData.nwh = glfwGetWin32Window(window);
#endif
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	init.resolution.width = (uint32_t)width;
	init.resolution.height = (uint32_t)height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	// if (!bgfx::init(init)) { return 1; }
	bgfx_init(&init);
	uint32_t debug  = BGFX_DEBUG_TEXT;
	uint32_t reset  = BGFX_RESET_VSYNC;
	bgfx_reset(width, height, reset, init.resolution.format);
	// Enable debug text.
	bgfx_set_debug(debug);

	// // Set view 0 to the same dimensions as the window and to clear the color buffer.
	// const bgfx::ViewId kClearView = 0;
	// bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
	bgfx_set_view_clear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);
	// bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		// Handle window resize.
		int oldWidth = width, oldHeight = height;
		glfwGetWindowSize(window, &width, &height);
		if (width != oldWidth || height != oldHeight) {
			// bgfx::reset((uint32_t)width, (uint32_t)height, BGFX_RESET_VSYNC);
			// bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	    
      // bgfx_reset(width, height, reset, init.resolution.format);
	    bgfx_reset(width, height, reset, BGFX_RESET_VSYNC);
		  bgfx_set_view_rect(0, 0, 0, (uint16_t)width, (uint16_t)height);
		}
		// // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
		// bgfx::touch(kClearView);
    // This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx_encoder_t* encoder = bgfx_encoder_begin(true);
		bgfx_encoder_touch(encoder, 0);
		bgfx_encoder_end(encoder);

		// // Use debug font to print information about this example.
		// bgfx::dbgTextClear();
		// bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20, bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
		// bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
		// bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
		// bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		// bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
		// const bgfx::Stats* stats = bgfx::getStats();
		// bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.", stats->width, stats->height, stats->textWidth, stats->textHeight);
		// // Enable stats or debug text.
		// bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
		// // Advance to next frame. Process submitted rendering primitives.
		// bgfx::frame();

    // Use debug font to print information about this example.
		bgfx_dbg_text_clear(0, false);
		bgfx_dbg_text_image(
			  MAX( (uint16_t)width /2/8, 20)-20
			, MAX( (uint16_t)height/2/16, 6)-6
			, 40
			, 12
			, s_logo
			, 160
			);

		bgfx_dbg_text_printf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

		bgfx_dbg_text_printf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
		bgfx_dbg_text_printf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

		bgfx_dbg_text_printf(0, 3, 0x1f, "bgfx/examples/25-c99");
		bgfx_dbg_text_printf(0, 4, 0x3f, "Description: Initialization and debug text with C99 API.");

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx_frame(false);
	}
	// bgfx::shutdown();
	bgfx_shutdown();
	glfwTerminate();
	return 0;
}
