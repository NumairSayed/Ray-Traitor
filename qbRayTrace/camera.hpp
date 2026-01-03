#ifndef CAMERA_H
#define CAMERA_H
#include "../qbLinAlg/qbVector.h"
#include "ray.hpp"

namespace qbRT{
    class Camera{
        public:
            Camera();
            void SetPosition(const qbVector<double> &newPosition);
            void SetLookAt(const qbVector<double> &newLookAt);
            void SetUp(const qbVector<double> &upVector);
            void SetLength(double newLength);
            void SetAspect(double newAspect);
            void SetHorzSize(double newHorzSize);
            
        // functipons to get camera parameters
            qbVector<double> GetPosition();
            qbVector<double> GetLookAt();
            qbVector<double> GetUp();
            qbVector<double> GetV();
            qbVector<double> GetU();
            qbVector<double> GetScreenCentre();
            double           GetLength();
            double           GetHorzSize();
            double           GetAspect();

        // function to generate ray
        // This function generates ray for a particular x,y tuple i.e the projection screen. Originally it would be pixel pposition but in our 3d system of ensemble, it will have an x,y direction             
            bool GenerateRay(float proScreenX, float proScreenY, qbRT::Ray &cameraRay);

        // function to update camera geometry
            void UpdateCameraGeometry();

        // private
        private:
            qbVector<double> m_cameraPosition{3};
            qbVector<double> m_cameraLookAt{3}; // if a single undivergent ray is extended from the pinhole camera, this is where it would hit the scene at.
            qbVector<double> m_cameraUp{3};
            double m_cameraLength; // how far away is the camera from the projection screen
            double m_cameraHorzSize;
            double m_cameraAspectRatio;

            qbVector<double> m_alignmentVector{3};
            qbVector<double> m_projectionScreenU{3}; // conveniently, U will represent the horizontal pixel location
            qbVector<double> m_projectionScreenV{3}; // likewise, V will represent vertical pixel location
            qbVector<double> m_projectionScreenCentre{3};
            
    };
}
#endif