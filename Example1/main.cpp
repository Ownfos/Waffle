// Description:
// - This example project shows how to use ImGui with this library
// - There are some steps you need to follow in order to use ImGui
//   1) Create waffle::ImGuiHelper instance (requires waffle::Context and waffle::RenderWindow)
//   2) Call RenderWindow::Clear() and RenderWindow::Set() at the beginning of each frame
//   3) Call ImGuiHelper::BeginFrame() with the instance you've created
//   4) Use ImGui (ImGui::Begin, ImGui::Button, ...)
//   5) Call ImGuiHelper::EndFrame()
//   6) Call RenderWindow::Present()
//
// Required project settings:
// - C++ 17 as language standard
// - Waffle as project reference (for correct build order)
// - Additional include directories
//   1) ../libraries/boost_1_72_0
//   2) ../libraries/imgui
//   3) ../Waffle
//
//   * The external libraries I used is not modified at all.
//     Just download, unzip if neccessary, and everything's good to go.
//     If you have those libraries in different folder, then change
//     additional include directories to fit yours.
//
//   * I assume that you are creating a project in this solution (the same one where Waffle is in),
//     so there will be no problem in locating required lib file

#include "Waffle.h"

using namespace waffle;

int main()
{
	try
	{
		auto context = Context();
		auto window = RenderWindow(context, L"title", { 600, 400 });
		auto ui = ImGuiHelper(context, window);

		return Window::MessageLoop([&]
			{
				// Handle input
				if (window.input.RawState(KeyCode::Esc))
					Window::Quit();

				// Draw anything you want
				window.Clear(1, 1, 1, 0);
				window.Set();
				{
					ui.BeginFrame();
					{
						static bool check = false;

						ImGui::Begin("Test");
						ImGui::Button("Button");
						ImGui::Checkbox("Check box", &check);
						ImGui::End();
					}
					ui.EndFrame();
				}
				window.Present();
			});
	}
	catch (const std::exception & e)
	{
		PrintNestedException(e);
		return -1;
	}
}