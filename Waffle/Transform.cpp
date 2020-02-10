#include "Transform.h"

using namespace DirectX;

namespace waffle
{
	Transform::Transform()
		: data(XMMatrixIdentity())
	{}
	Transform::Transform(DirectX::XMMATRIX data)
		: data(data)
	{}

	Transform Transform::Translate(const Vector& offset)
	{
		return XMMatrixTranslationFromVector(offset.Data());
	}
	Transform Transform::Rotate(const Vector& angle)
	{
		return XMMatrixRotationRollPitchYawFromVector(angle.Data());
	}
	Transform Transform::Scale(const Vector& scale)
	{
		return XMMatrixScalingFromVector(scale.Data());
	}
	Transform Transform::LookAt(const Vector& eye, const Vector& focus, const Vector& up)
	{
		return XMMatrixLookAtLH(eye.Data(), focus.Data(), up.Data());
	}
	Transform Transform::LookTo(const Vector& eye, const Vector& direction, const Vector& up)
	{
		return XMMatrixLookToLH(eye.Data(), direction.Data(), up.Data());
	}
	Transform Transform::Perspective(float fovy, float aspectRatio, float nearZ, float farZ)
	{
		return XMMatrixPerspectiveFovLH(fovy, aspectRatio, nearZ, farZ);
	}
	Transform Transform::Orthographic(float viewWidth, float viewHeight, float nearZ, float farZ)
	{
		return XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
	}

	Transform Transform::Inverse(const Transform& transform)
	{
		return XMMatrixInverse(nullptr, transform.data);
	}

	Transform& Transform::operator*=(const Transform& other)
	{
		data *= other.data;

		return *this;
	}

	Transform Transform::operator*(const Transform& other) const
	{
		return data * other.data;
	}

	XMMATRIX Transform::Data() const
	{
		return data;
	}

	XMMATRIX Transform::Transposed() const
	{
		return XMMatrixTranspose(data);
	}
}