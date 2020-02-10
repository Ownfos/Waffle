#include "RenderWindow.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "Transform.h"
#include "Mesh.h"
#include "Color.h"
#include "RenderSurface.h"
#include "Sampler.h"
#include <iostream>

#define PI 3.141592f

using namespace waffle;

int main()
{
	try
	{
		auto context = Context();
		auto window = RenderWindow(context, L"title", { 600, 400 });

		// Prepare shader
		auto inputLayout = std::vector<InputElement>{
			{"POSITION", InputFormat::Float3},
			{"TEXCOORD", InputFormat::Float2}
		};

		auto firstPassVS = VertexShader(context, {L"FirstPassVS.cso"}, inputLayout);
		auto firstPassPS = PixelShader(context, {L"FirstPassPS.cso"});

		auto secondPassVS = VertexShader(context, {L"SecondPassVS.cso"}, inputLayout);
		auto secondPassPS = PixelShader(context, {L"SecondPassPS.cso"});

		// Create rectangle mesh
		auto vertices = std::vector<Vertex>{
			{{-1, -1, 0}, {0, 1}},
			{{-1, 1, 0}, {0, 0}},
			{{1, 1, 0}, {1, 0}},
			{{1, -1, 0}, {1, 1}}
		};
		auto indices = std::vector{
			0U, 1U, 2U,
			2U, 3U, 0U
		};
		auto mesh = Mesh(context, std::move(vertices), std::move(indices));


		// Transform matrices
		auto world =
			Transform::Scale({ 0.5, 0.5, 1 }) *
			Transform::Rotate({ 0, 0, PI / 4 }) *
			Transform::Translate({ 0, 0, 0 });
		auto view = Transform::LookAt({ 0,0,-1.5 }, { 0,0,0 });
		auto projection = Transform::Perspective(PI / 2, window.AspectRatio(), 1.0f, 100.0f);
		auto wvp = world * view * projection;

		// Create constant buffers
		auto transform = ConstantBuffer(context, wvp.Transposed());
		auto color = ConstantBuffer(context, Color{ 0xffffffff });

		// Texture resource for off-screen rendering (first pass)
		auto surface = std::make_unique<RenderSurface>(context, window.Size());
		auto sampler = Sampler(context);

		(void)window.resizeEvent.AddHandler([&](auto size) {
			// Synchronize texture size
			surface = std::make_unique<RenderSurface>(context, size);

			// Update projection matrix
			projection = Transform::Perspective(PI / 2, window.AspectRatio(), 1.0f, 100.0f);
			wvp = world * view * projection;
			transform.Update(wvp.Transposed());
		});

		// Bind constant buffers and sampler
		color.SetPS(0);
		transform.SetVS(0);
		sampler.SetPS(0);

		return Window::MessageLoop([&]
		{
			if (window.input.RawState(KeyCode::Esc))
				Window::Quit();

			// Update color constant buffer
			if (window.input.RawState(KeyCode::R)) color.Update(0xff0000ff);
			if (window.input.RawState(KeyCode::G)) color.Update(0x00ff00ff);
			if (window.input.RawState(KeyCode::B)) color.Update(0x0000ffff);

			// Render to texture
			surface->Clear(0, 0, 0, 0);
			{
				firstPassVS.Set();
				firstPassPS.Set();

				// Prevent debug error messages complaining about
				// setting shader resource to render target before unbinding...
				context.UnbindPSResource(0);

				surface->SetRT();
				mesh.Draw();
			}

			// Render texture to window
			window.Clear(1, 1, 1, 0);
			{
				secondPassVS.Set();
				secondPassPS.Set();

				window.Set();
				surface->SetPS(0);
				mesh.Draw();
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