#include <cstdio>

int main()
{
	bool is_GameRunning = false;

	// A typical game-like application taking advantage of GPU rendering would run in a loop:
	while (is_GameRunning) {
		// Poll events
		// Update application/game state
		// Render contents into a framebuffer
		// Swap/Present framebuffer to the screen
		// Wait some time (e.g. 1/60 of a second)
	}

	return 0;
}