#include "./objsphere.hpp"
#include <cmath>

// default constructor

qbRT::ObjSphere::ObjSphere(){

}

qbRT::ObjSphere::~ObjSphere(){

}

// function to test for intersections
bool qbRT::ObjSphere::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor){
    // solving a quadratic we know from closed form
    // Compute the values of a, b and c.
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    /* Note that a is equal to the squared magnitude of the
       direction of the cast ray. As this will be a unit vector,
       we can conclude that the value of 'a' will always be 1. */
    // a = 1.0;

    // Calculate b.
    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

    // Calculate c.
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    // Test whether we actually have an intersection.
    double intTest = (b*b) - 4.0 * c;

    if (intTest > 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
