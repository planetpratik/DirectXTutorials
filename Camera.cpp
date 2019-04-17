#include "Camera.h"
#include "Windows.h"
#include <stdio.h>

using namespace DirectX;

Camera::Camera() : 
	camera_position(XMFLOAT3(0.0f, 0.0f, -1.0f)), 
	camera_forward_direction(XMFLOAT3(0.0f, 0.0f, 1.0f)),
	relativeInput(XMFLOAT3(0.0f, 0.0f,-1.0f)),
	x_axis_rotation(0.0f),
	y_axis_rotation(0.0f)
{
}

Camera::~Camera()
{
}

void Camera::update(const float t_deltaTime)
{
	
	relativeInput.x = 0.0f;
	relativeInput.y = 0.0f;
	relativeInput.z = 0.0f;
	if (GetAsyncKeyState('W') & 0x80000)
	{
		relativeInput.z += 1.0f;
	}

	if (GetAsyncKeyState('S') & 0x80000)
	{
		relativeInput.z -= 1.0f;
	}

	if (GetAsyncKeyState('A') & 0x80000)
	{
		relativeInput.x -= 1.0f;
	}

	if (GetAsyncKeyState('D') & 0x80000)
	{
		relativeInput.x += 1.0f;
	}

	// Moving up and down (Absolute)
	if (GetAsyncKeyState('X') & 0x80000)
	{
		relativeInput.y -= 1.f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x80000)
	{
		relativeInput.y += 1.f;
	}

	relativeInput.x *= t_deltaTime;
	relativeInput.y *= t_deltaTime;
	relativeInput.z *= t_deltaTime;
	camera_position.y += relativeInput.y;
	updateViewMatrix(t_deltaTime);

}

const float Camera::getXAxisRotation() const
{
	return x_axis_rotation;
}

const float Camera::getYAxisRotation() const
{
	return y_axis_rotation;
}

const DirectX::XMFLOAT3 Camera::getCameraPosition() const
{
	return camera_position;
}

const DirectX::XMFLOAT3 Camera::getCameraForwardDirection() const
{
	return camera_forward_direction;
}

const DirectX::XMFLOAT4X4 Camera::getViewMatrix() const
{
	return view_matrix;
}

const DirectX::XMFLOAT4X4 Camera::getProjectionMatrix() const
{
	return projection_matrix;
}

const float Camera::getHorizontalRotationSpeed() const
{
	return horizontal_rotation_speed;
}

const float Camera::getVerticalRotationSpeed() const
{
	return vertical_rotation_speed;
}

void Camera::updateProjectionMatrix(const unsigned int t_width, const unsigned int t_height)
{
	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//   the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)t_width / t_height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projection_matrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

void Camera::updateMouseInput(const float t_DeltaMouseX, const float t_DeltaMouseY)
{
	x_axis_rotation += t_DeltaMouseX * horizontal_rotation_speed;
	if (x_axis_rotation < -90)
	{
		x_axis_rotation = -90;
	}
	else if (x_axis_rotation > -85)
	{
		x_axis_rotation = -85;
	}

	y_axis_rotation += t_DeltaMouseY * vertical_rotation_speed;
	if (y_axis_rotation < -90)
	{
		y_axis_rotation = -90;
	}
	else if (y_axis_rotation > -85)
	{
		y_axis_rotation = -85;
	}
	printf("Rot Values:\tX: %f Y: %f\n", x_axis_rotation, y_axis_rotation);
}

void Camera::updateViewMatrix(const float t_delta_time)
{
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space

	XMVECTOR position = XMVectorSet(camera_position.x, camera_position.y, camera_position.z, 0);
	XMVECTOR rotation = isUsingInvertAxis ?
		XMQuaternionRotationRollPitchYaw(x_axis_rotation, y_axis_rotation, 0.0f) :
		XMQuaternionRotationRollPitchYaw(y_axis_rotation, x_axis_rotation, 0.0f);

	XMVECTOR forward_direction = XMVectorSet(0, 0, 1, 0);
	XMVECTOR camera_direction_for_view_matrix = XMVector3Rotate(forward_direction, rotation);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR left = XMVector3Cross(camera_direction_for_view_matrix, up);
	position += camera_direction_for_view_matrix * relativeInput.z;
	position -= left * relativeInput.x;
	XMMATRIX V = XMMatrixLookToLH(
		position,     // The position of the "camera"
		camera_direction_for_view_matrix,
		up);     // "Up" direction in 3D space (prevents roll)

	XMStoreFloat4x4(&view_matrix, XMMatrixTranspose(V)); // Transpose for HLSL!
	XMStoreFloat3(&camera_position, position);
}