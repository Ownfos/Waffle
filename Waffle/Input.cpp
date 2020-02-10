#include "Input.h"
#include "Window.h"
#include <windowsx.h>

namespace waffle
{
	Input::Input(Window& window)
	{
		(void)window.inputEvent.AddHandler(
			[input = this](auto message) { 
				input->HandleMessage(message);
			}
		);
	}

	void Input::UpdateFrameState()
	{
		for (int i = 0; i < 256 + 3; i++)
		{
			if (rawState[i])
			{
				switch (frameState[i])
				{
					case InputState::Released:
					case InputState::ReleasingNow:
					{
						frameState[i] = InputState::PressedNow;
						break;
					}
					case InputState::Pressing:
					case InputState::PressedNow:
					{
						frameState[i] = InputState::Pressing;
						break;
					}
				}
			}
			else
			{
				switch (frameState[i])
				{
					case InputState::Pressing:
					case InputState::PressedNow:
					{
						frameState[i] = InputState::ReleasingNow;
						break;
					}
					case InputState::Released:
					case InputState::ReleasingNow:
					{
						frameState[i] = InputState::Released;
						break;
					}
				}
			}
		}
	}

	bool Input::RawState(KeyCode keyCode) const
	{
		return rawState[static_cast<int>(keyCode)];
	}

	InputState Input::FrameState(KeyCode keyCode) const
	{
		return frameState[static_cast<int>(keyCode)];
	}

	int Input::MouseX() const
	{
		return mouseX;
	}
	
	int Input::MouseY() const
	{
		return mouseY;
	}

	void Input::HandleMessage(MSG message)
	{
		switch (message.message)
		{
			// keyboard
			case WM_KEYDOWN:
			{
				rawState[message.wParam] = true;
				break;
			}
			case WM_KEYUP:
			{
				rawState[message.wParam] = false;
				break;
			}

			// mouse
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			{
				rawState[static_cast<int>(KeyCode::MouseLeft)] = message.message == WM_LBUTTONDOWN;
				break;
			}
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			{
				rawState[static_cast<int>(KeyCode::MouseRight)] = message.message == WM_RBUTTONDOWN;
				break;
			}
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			{
				rawState[static_cast<int>(KeyCode::MouseMiddle)] = message.message == WM_MBUTTONDOWN;
				break;
			}
			case WM_MOUSEMOVE:
			{
				mouseX = GET_X_LPARAM(message.lParam);
				mouseY = GET_Y_LPARAM(message.lParam);
				break;
			}
			case WM_MOUSEWHEEL:
				break;
		}
	}
}
