#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	// Default Constructor for Camera class.
	Camera();

	// Destructor for Camera class.
	~Camera();

	// Update Method for Camera.
	void update(const float t_deltaTime);

	// Get Camera's rotation around X-Axis.
	const float getXAxisRotation() const;

	// Get Camera's rotation around Y-Axis.
	const float getYAxisRotation() const;

	// Get Camera's current position.
	const DirectX::XMFLOAT3 getCameraPosition() const;

	// Get Camera's current Direction.
	const DirectX::XMFLOAT3 getCameraForwardDirection() const;

	// Get Camera's current View Matrix.
	const DirectX::XMFLOAT4X4 getViewMatrix() const;
	
	// Get Camera's current Projection Matrix.
	const DirectX::XMFLOAT4X4 getProjectionMatrix() const;

	// Get Camera's horizontal Rotation Speed.
	const float getHorizontalRotationSpeed() const;

	// Get Camera's Vertical Rotation Speed
	const float getVerticalRotationSpeed() const;

	// Updates Camera's Projection Matrix based on Aspect ratio.
	void updateProjectionMatrix(const unsigned int t_width, const unsigned int t_height);

	void updateMouseInput(const float t_DeltaMouseX, const float t_DeltaMouseY);

	// Set if camera should be rotating.
	void setDoRotation(bool t_do_rotation);

	// Returns whether camera is doing rotation or not.
	const bool getDoRotation() const;

private:
	void updateViewMatrix(const float t_delta_time);
	float x_axis_rotation = 0.0f;
	float y_axis_rotation = 0.0f;
	DirectX::XMFLOAT3 camera_position;
	DirectX::XMFLOAT3 camera_forward_direction;
	DirectX::XMFLOAT4X4 world_matrix;
	DirectX::XMFLOAT4X4 view_matrix;
	DirectX::XMFLOAT4X4 projection_matrix;
	const float horizontal_rotation_speed = 0.005f;
	const float vertical_rotation_speed = 0.005f;
	bool isUsingInvertAxis = false;
	DirectX::XMFLOAT3 relativeInput;
	bool doRotation = false;
};