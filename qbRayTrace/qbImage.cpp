#include "qbImage.hpp"

// default constructor
qbImage::qbImage(){
    m_xSize = 0;
    m_ySize  = 0;
    m_pTexture = NULL;
}

//destructor

qbImage::~qbImage(){
    if (m_pTexture != NULL){
        SDL_DestroyTexture(m_pTexture);
    }

}

//initialize
void qbImage::Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer){

    //resizing 
m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

// storing dimensions
m_xSize = xSize;
m_ySize = ySize;

// storing pointer to the renderer
m_pRenderer = pRenderer;

// initialize the texture.
InitTexture(); 
}

// function to set pixels
void qbImage::SetPixel(const int x, const int y, const double red, const double green, const double blue){
    m_rChannel.at(x).at(y) = red;
    m_gChannel.at(x).at(y) = green;
    m_bChannel.at(x).at(y) = blue;
    
}

// function to generate display
void qbImage::Display(){
    //allocate memory for a pixel buffer
    Uint32 *tempPixels = new Uint32[m_xSize*m_ySize];

    //clear the pixel buffer
    memset(tempPixels, 0, m_xSize * m_ySize *sizeof(Uint32));
    for(int x=0; x<m_xSize; ++x){
        for(int y=0; y<m_ySize; ++y){
            tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
        }

    }
    // update the texture with pixel buffer.
    SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize*(sizeof(Uint32)));

    // delete the buffer
    delete[] tempPixels;

    // copy the texture to renderer
    SDL_Rect srcRect, bounds;
srcRect.x = 0;
srcRect.y = 0;
srcRect.w = m_xSize;
srcRect.h = m_ySize;

bounds.x = 0;
bounds.y = 0;
bounds.w = m_xSize;
bounds.h = m_ySize;

SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
    if (SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds) != 0) {
    SDL_Log("qbImage::Display - SDL_RenderCopy failed: %s", SDL_GetError());
}

}

// function to return image dimensions
int qbImage::GetXSize(){
    return m_xSize;
}

int qbImage::GetYSize(){
    return m_ySize;
}

// Function to return the image as an SDL2 texture.
void qbImage::InitTexture()
{
	// Initialise the texture.
	Uint32 rmask, gmask, bmask, amask;
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN

    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	
    #endif
	
	// Delete any previously created texture before we create a new one.
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
	
	// Create the texture that will store the image.
	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);	
}

// Function to convert color to Uint32
Uint32 qbImage::ConvertColor(const double red, const double green, const double blue)
{
    // Clamp and convert colours to unsigned char.
    auto clamp = [](double v)->unsigned char {
        if (v < 0.0) return 0;
        if (v > 255.0) return 255;
        return static_cast<unsigned char>(v + 0.5); // round
    };
    unsigned char r = clamp(red);
    unsigned char g = clamp(green);
    unsigned char b = clamp(blue);
    unsigned char a = 255;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        // For big endian packing (r,g,b,a)
        Uint32 pixelColor = (r << 24) | (g << 16) | (b << 8) | a;
    #else
        // For little endian we created surface with masks:
        // rmask=0x000000ff, gmask=0x0000ff00, bmask=0x00ff0000, amask=0xff000000
        // That means the 32-bit pixel should be: (a<<24)|(b<<16)|(g<<8)|r
        Uint32 pixelColor = (a << 24) | (b << 16) | (g << 8) | r;
    #endif

    return pixelColor;
}

