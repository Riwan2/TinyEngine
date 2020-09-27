#include "application/app.h"

int main(int argc, char *argv[])
{
	App app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}