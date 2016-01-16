#pragma once

#include <directxmath.h>
using namespace DirectX;

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void setPosition(float, float, float);
	void setRotation(float, float, float);

	XMFLOAT3 getPosition();
	XMFLOAT3 getRotation();

	void render();
	void getViewMatrix(XMMATRIX&);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	XMMATRIX m_viewMatrix;
};
