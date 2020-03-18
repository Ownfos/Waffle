#include "Window.h"

#define CLASS_NAME L"class"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace waffle
{
    std::unordered_map<HWND, Window*> Window::windows;

    Window::Window(std::wstring title, Rectangle size, WindowType type)
		: input(*this), size(size), type(type)
    {
		try
		{
			if (static bool classRegistered = false; !classRegistered)
			{
				classRegistered = true;

				WNDCLASSEX wcex = {};
				{
					wcex.cbSize = sizeof(WNDCLASSEX);
					wcex.lpfnWndProc = WindowProcedure;
					wcex.lpszClassName = CLASS_NAME;
					wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
					wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
				}

				if (FAILED(RegisterClassEx(&wcex)))
					throw std::exception("Failed to register class");
			}

			auto adjustedSize = AdjustedSize(size, type);

			handle = CreateWindowEx(
				NULL, CLASS_NAME,
				title.c_str(),
				static_cast<int>(type),
				CW_USEDEFAULT, CW_USEDEFAULT,
				adjustedSize.width,
				adjustedSize.height,
				NULL, NULL, NULL, NULL
			);
			if (!handle)
				throw std::exception("Failed to create a window");

			windows[handle] = this;

			ShowWindow(handle, SW_SHOW);
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Window::Window()"));
		}
    }

	Window::~Window()
	{
		if (handle)
			DestroyWindow(handle);
	}

	void Window::Resize(Rectangle size)
	{
		try
		{
			auto adjustedSize = AdjustedSize(size, type);

			RECT currentPosition;
			GetWindowRect(handle, &currentPosition);
			SetWindowPos(
				handle,
				HWND_TOP,
				currentPosition.left,
				currentPosition.top,
				adjustedSize.width,
				adjustedSize.height,
				NULL
			);
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Window::Resize()"));
		}
	}

	Rectangle Window::Size() const
	{
		return size;
	}

    HWND Window::Handle() const
    {
        return handle;
    }

    float Window::AspectRatio() const
    {
        return static_cast<float>(size.width) / size.height;
    }

	std::optional<int> Window::ProcessMessage()
	{
		try
		{
			MSG msg;
			while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					return static_cast<int>(msg.wParam);

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		catch (...)
		{
			std::throw_with_nested(std::exception("Window::ProcessMessage()"));
		}

		return {};
	}

    void Window::Quit()
    {
		PostQuitMessage(0);
    }

	Rectangle Window::AdjustedSize(Rectangle size, WindowType type)
	{
		RECT adjusted = { 0, 0, size.width, size.height };
		AdjustWindowRect(&adjusted, static_cast<int>(type), NULL);
		auto width = adjusted.right - adjusted.left;
		auto height = adjusted.bottom - adjusted.top;

		return { width, height };
	}

	LRESULT WINAPI Window::WindowProcedure(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
			return true;

		switch (message)
		{
			case WM_DESTROY:
			{
				windows.erase(handle);
				if (windows.empty())
					PostQuitMessage(0);
				return 0;
			}
			case WM_SIZE:
			{
				if (wParam != SIZE_MINIMIZED)
				{
					windows[handle]->size = { LOWORD(lParam), HIWORD(lParam) };
					windows[handle]->resizeEvent.Signal(windows[handle]->size);
				}
				return 0;
			}
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_CHAR:
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MOUSEMOVE:
			case WM_MOUSEWHEEL:
			{
				windows[handle]->inputEvent.Signal(MSG{ handle, message, wParam, lParam });
				return 0;
			}
			default:
			{
				return DefWindowProc(handle, message, wParam, lParam);
			}
		}
	}

}