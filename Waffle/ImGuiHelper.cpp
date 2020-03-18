#include "ImGuiHelper.h"

namespace waffle
{
	ImGuiHelper::ImGuiHelper(Context& context, RenderWindow& window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplWin32_Init(window.Handle());
		ImGui_ImplDX11_Init(context.Device(), context.DeviceContext());
		//ImGui::StyleColorsDark();
	}

	void ImGuiHelper::BeginFrame()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiHelper::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}