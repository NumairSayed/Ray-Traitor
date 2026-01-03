#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "./ray.hpp"
#include "../qbLinAlg/qbVector.h"

namespace qbRT{
    class ObjectBase{
        public:
            // cons and destructor
            ObjectBase();
            virtual ~ObjectBase();

            // function to test intersection
            virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

            // if two points are close enough
            bool CloseEnough(const double f1, const double f2);
        
        // public member variables
        public:
            qbVector<double> m_baseColor{3};




    };
}
#endif