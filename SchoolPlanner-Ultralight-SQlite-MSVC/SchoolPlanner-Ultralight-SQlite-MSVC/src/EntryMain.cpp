#include "sc_pch.hpp"
#include "Application.hpp"

int main() {
	Log::init();

	SC_INFO("Application Info");

	Application* app = new Application();
	app->start();
	app->run();

	SC_INFO("Application Termination");
	delete app;

	return 0;
}