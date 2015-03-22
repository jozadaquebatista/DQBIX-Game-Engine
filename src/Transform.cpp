#include "..\include\Transform.h"

Transform::Transform()
{
	m_rotation = quat(1.0f, 0.0f, 0.0f, 0.0f);
	m_translation = vec3(0.0f);
	m_scale = vec3(1.0f, 1.0f, 1.0f);
	m_parentMat = mat4(1.0f);
	m_initOld = false;
	m_parent = 0;

}

void Transform::rotate_transform(float x, float y, float z)
{
	m_rotation = rotate(m_rotation, x, vec3(1.0f, 0.0f, 0.0f));
	m_rotation = rotate(m_rotation, y, vec3(0.0f, 1.0f, 0.0f));
	m_rotation = rotate(m_rotation, z, vec3(0.0f, 0.0f, 1.0f));
}

void Transform::move(float x, float y, float z)
{
	m_translation += vec3(x, y, z);
}

void Transform::scale_transform(float x, float y, float z)
{
	m_scale += vec3(x, y, z);
}

glm::mat4 Transform::getTransformation()
{
	mat4 trans = translate(mat4(1.0f), m_translation);
	mat4 scal = scale(mat4(1.0f), m_scale);
	mat4 rot = mat4_cast(m_rotation);

	return getParentMatrix() * (trans * rot * scal);
}

glm::mat4 Transform::getParentMatrix()
{
	if (m_parent != 0)
		m_parentMat = m_parent->getTransformation();
	return m_parentMat;
}

bool Transform::changed()
{
	if (m_parent != 0 && m_parent->changed())
		return true;

	if (m_translation != m_oldTranslation)
		return true;

	if (m_rotation != m_oldRotation)
		return true;

	if (m_scale != m_oldScale)
		return true;

	return false;
}

void Transform::update()
{
	if (m_initOld)
	{
		m_oldTranslation = m_translation;
		m_oldRotation = m_rotation;
		m_oldScale = m_scale;
	}
	else
	{
		m_oldTranslation = m_translation + vec3(1, 1, 1);
		m_oldRotation = m_oldRotation * 0.5f;
		m_oldScale = m_scale + 1.0f;
		m_initOld = true;
	}
}
