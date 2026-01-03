#ifndef QBIMAGE_H
#define QBIMAGE_H

#include<string>
#include<vector>
#include<SDL2/SDL.h>

class qbImage{
    public:
        // constructor
        qbImage();

        // destructor
        ~qbImage();

        // init function
        void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);

        // function to set colour of the pixel
        void SetPixel(const int x, const int y, const double red, const double green, const double blue);

        // function to return image for display
        void Display();

        // functions to return dimensions of the image
        int GetXSize();
        int GetYSize();
        
    private:
        Uint32 ConvertColor(const double red, const double green, const double blue);
        void InitTexture();
    private:
        //arrays to store image
        std::vector<std::vector<double>> m_rChannel; 
        std::vector<std::vector<double>> m_gChannel; 
        std::vector<std::vector<double>> m_bChannel; 

        //store dimension 
        int m_xSize, m_ySize;

        // SDL2 stuff.
        SDL_Renderer *m_pRenderer;
        SDL_Texture *m_pTexture;


};

#endif