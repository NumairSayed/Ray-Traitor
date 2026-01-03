#include "scene.hpp"

// constructor
qbRT::Scene::Scene(){
    //COnfigure the camera
    m_camera.SetPosition( qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    m_camera.SetLookAt	( qbVector<double>{std::vector<double> {0.0, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(0.25);
	m_camera.SetAspect(1920/1080);
	m_camera.UpdateCameraGeometry();
}

// function for rendering
bool qbRT::Scene::Render(qbImage &outputImage){

    // get dimensions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector<double> intPoint			(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;

    for (int x=0; x<xSize; ++x)
	{
		for (int y=0; y<ySize; ++y)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test if we have a valid intersection.
			bool validInt = m_testSphere.TestIntersection(cameraRay, intPoint, localNormal, localColor);
			
			// If we have a valid intersection, change pixel color to red.
			if (validInt)
			{
				
				outputImage.SetPixel(x, y, 0.0,255.0, 0.0);
			}
			else
			{
				outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
			}
		}
	}
    // // create some colour variations
    // for(int x = 0; x < xSize; ++x){
    //     for( int y =0; y < ySize; ++y){
    //         double red = (static_cast<double>(x)/static_cast<double>(xSize))*255.0;
    //         double green = (static_cast<double>(y)/static_cast<double>(ySize))*255.0;
    //         outputImage.SetPixel(x, y, red, green, 0.0);
    //     }
    // }
return true;
}
