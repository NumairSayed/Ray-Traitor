#ifndef SCENE_H
#define SCENE_H
#include "qbImage.hpp"
#include "camera.hpp"
#include "objsphere.hpp"

namespace qbRT{
class Scene{
    public:
        // default constructor
        Scene();

        // function to perform rendering
        bool Render(qbImage &outputImage);
    private:
        // camera that we will use
        qbRT::Camera m_camera;

        // unit spehere on origin for testin

        qbRT::ObjSphere m_testSphere;
        

};
}

#endif