#include "stpch.h"

#include "Application.hpp"

int main() {
	Application::Instance = new Application();

	Application::Instance->Run();

	delete Application::Instance;

	return EXIT_SUCCESS;
}
