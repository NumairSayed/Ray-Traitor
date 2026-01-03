#ifndef OBJESPHERE_H
#define OBJESPHERE_H
#include "objectbase.hpp"

namespace qbRT{
    class ObjSphere : public ObjectBase{
      public:

        // default constructor
        // this will define a unit sphere at the origin
        ObjSphere();
        
        // override the destructor
        virtual ~ObjSphere();

        // override the funtions to test ofr intersection because every shape will have different gemoetry
        virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);

      private:
    
    };
}

#endif