#include "camera.hpp"
#include "ray.hpp"
#include <math.h>
#include "camera.hpp"

qbRT::Camera::Camera(){

    //default constructor
    m_cameraPosition = qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}};
    m_cameraLookAt = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
    m_cameraUp = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};
    m_cameraLength = 1.0;
    m_cameraHorzSize = 1.0;
    m_cameraAspectRatio = 1.0;

}

void qbRT::Camera::SetPosition(const qbVector<double> &newPosition)
{
	m_cameraPosition = newPosition;
}

void qbRT::Camera::SetLookAt(const qbVector<double> &newLookAt)
{
	m_cameraLookAt = newLookAt;
}

void qbRT::Camera::SetUp(const qbVector<double> &upVector)
{
	m_cameraUp = upVector;
}

void qbRT::Camera::SetLength(double newLength)
{
	m_cameraLength = newLength;
}

void qbRT::Camera::SetHorzSize(double newHorzSize)
{
	m_cameraHorzSize = newHorzSize;
}

void qbRT::Camera::SetAspect(double newAspect)
{
	m_cameraAspectRatio = newAspect;
}

// Method to return the position of the camera.
qbVector<double> qbRT::Camera::GetPosition()
{
    return m_cameraPosition;
}

// Method to return the look at of the camera.
qbVector<double> qbRT::Camera::GetLookAt()
{
    return m_cameraLookAt;
}

// Method to return the up vector of the camera.
qbVector<double> qbRT::Camera::GetUp()
{
    return m_cameraUp;
}

// Method to return the length of the camera.
double qbRT::Camera::GetLength()
{
    return m_cameraLength;
}

double qbRT::Camera::GetHorzSize()
{
	return m_cameraHorzSize;
}

double qbRT::Camera::GetAspect()
{
	return m_cameraAspectRatio;
}

qbVector<double> qbRT::Camera::GetU()
{
	return m_projectionScreenU;
}

qbVector<double> qbRT::Camera::GetV()
{
	return m_projectionScreenV;
}

qbVector<double> qbRT::Camera::GetScreenCentre()
{
	return m_projectionScreenCentre;
}

void qbRT::Camera::UpdateCameraGeometry(){

    // first compute vector from camera location to lookat (this will be known as alignment vector)
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // Compute U and V vectors using the parallel planes extension in the diagram we drew
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();
    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    // compute the position of the centre point on projection screen
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength*m_alignmentVector);

    // since directions of U and V are obtained, we need to modify them according to the aspect ratio and size of the projection screen
    m_projectionScreenU = m_projectionScreenU * m_cameraHorzSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorzSize / m_cameraAspectRatio);
}

bool qbRT::Camera::GenerateRay(float proScreenX, float proScreenY, qbRT::Ray &cameraRay){
    qbVector<double> screenWorldCoordinate = m_projectionScreenCentre + (m_projectionScreenU*proScreenX) + (m_projectionScreenV*proScreenY);
    cameraRay.m_point1 = m_cameraPosition;
    cameraRay.m_point2 = screenWorldCoordinate;
    cameraRay.m_lab = screenWorldCoordinate - m_cameraPosition;
    return true;

}