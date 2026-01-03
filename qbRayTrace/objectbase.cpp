#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f

// default constructor
qbRT::ObjectBase::ObjectBase(){
}

qbRT::ObjectBase::~ObjectBase(){
}

// function to test for intersection
bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor){
    // for now
    return false;
    
}

bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2){
    return fabs(f1-f2)<= EPSILON;
}



