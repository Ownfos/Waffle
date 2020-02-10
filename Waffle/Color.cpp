#include "Color.h"
#include <algorithm>

namespace waffle
{
	Color::Color(float red, float green, float blue, float alpha)
		: red(std::clamp(red, 0.0f, 1.0f)),
		green(std::clamp(green, 0.0f, 1.0f)),
		blue(std::clamp(blue, 0.0f, 1.0f)),
		alpha(std::clamp(alpha, 0.0f, 1.0f))
	{
	}

	Color::Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
		: red(red / 255.0f), 
		green(green / 255.0f), 
		blue(blue / 255.0f), 
		alpha(alpha / 255.0f)
	{}

	Color::Color(unsigned int hexCode)
		: Color(
			(hexCode & 0xff000000) >> 24, 
			(hexCode & 0x00ff0000) >> 16, 
			(hexCode & 0x0000ff00) >> 8, 
			hexCode & 0x000000ff
		)
	{}

	float Color::Red()
	{
		return red;
	}

	float Color::Green()
	{
		return green;
	}

	float Color::Blue()
	{
		return blue;
	}

	float Color::Alpha()
	{
		return alpha;
	}

	Color Color::Interpolate(Color left, Color right, float ratio)
	{
		return Color(
			left.red * ratio + right.red * (1.0f - ratio),
			left.green * ratio + right.green * (1.0f - ratio),
			left.blue * ratio + right.blue * (1.0f - ratio),
			left.alpha * ratio + right.alpha * (1.0f - ratio)
		);
	}
}