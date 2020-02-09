#pragma once

#include "glm.hpp"

class Camera
{

public:

	virtual void Update(float fDeltaTime) = 0;

	void SetPerspective(float fFOV, float fAspectRatio, float fNear, float fFar);
	void SetLookAt(glm::vec3 v3From, glm::vec3 v3To, glm::vec3 v3Up);
	void SetPosition(glm::vec3 v3position);

	glm::mat4 GetWorldTransform();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::mat4 GetProjectionView();

private:

	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

	void UpdateProjectionViewTransform();
};

