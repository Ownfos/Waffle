#include "Vector.h"
#include "Transform.h"

using namespace DirectX;

namespace waffle
{
	Vector::Vector(float x, float y, float z)
		: data(XMVectorSet(x, y, z, 0.0f))
	{
	}

	Vector::Vector(XMVECTOR data)
		: data(data)
	{
	}

	Vector Vector::operator+(const Vector& other) const
	{
		return XMVectorAdd(data, other.data);
	}

	Vector Vector::operator-(const Vector& other) const
	{
		return XMVectorSubtract(data, other.data);
	}

	float Vector::operator*(const Vector& other) const
	{
		return XMVectorGetX(XMVector3Dot(data, other.data));
	}

	Vector Vector::operator^(const Vector& other) const
	{
		return XMVector3Cross(data, other.data);
	}

	Vector Vector::operator*(const Transform& transform) const
	{
		return XMVector3TransformCoord(data, transform.Data());
	}

	XMVECTOR Vector::Data() const
	{
		return data;
	}

	float Vector::Length() const
	{
		return XMVectorGetX(XMVector3Length(data));
	}

	float Vector::LengthSquare() const
	{
		return XMVectorGetX(XMVector3LengthSq(data));
	}

	Vector Vector::Normalized() const
	{
		return XMVector3Normalize(data);
	}
}