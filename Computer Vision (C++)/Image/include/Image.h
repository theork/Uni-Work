#ifndef __Image_h
#define __Image_h


/**
********************************************************************************
*
*   @file       Image.h
*
*   @brief      Class to handle a greyscale image.
*
*   @version    1.0
*
*   @todo       Write here anything you did not implement.
*
*   @date       22/10/2019
*
*   @author     Franck Vidal
*   @author     YOUR NAME
*
*
********************************************************************************
*/

//******************************************************************************
//  Include
//******************************************************************************
#include <string>


//******************************************************************************
//  Declare class
//******************************************************************************
class Image;


//******************************************************************************
//  Declare functions
//******************************************************************************

//------------------------------------------------------------------------------
/// Addition operator. Add aValue to every pixel of the image anImage
/**
* @param aValue: the value to add
* @param anImage: the image to transform
* @return the resulting image
*/
//------------------------------------------------------------------------------
Image operator+(float aValue, const Image& anImage);


//------------------------------------------------------------------------------
/// Multiplication operator. Multiply every pixel of the image anImage
/// by aValue
/**
* @param aValue: the value for the multiplication
* @param anImage: the image to transform
* @return the resulting image
*/
//------------------------------------------------------------------------------
Image operator*(float aValue, const Image& anImage);


//------------------------------------------------------------------------------
/// Image blending: Cross-dissolve between two images so that the pixel
/// i,j of the output image is:
/// output(i,j) = (1-alpha) * f0(i,j) + alpha * f1(i,j)
/**
* @param alpha: the blending parameter
* @param f0: the 1st image to blend
* @param f1: the 2nd image to blend
* @return the output image after image blending
*/
//------------------------------------------------------------------------------
Image blending(float alpha, const Image& f0, const Image& f1);


//------------------------------------------------------------------------------
/// Image matting and compositing.
/**
* @param aForeground: the background
* @param aBackground: the foreground
* @param aForegroundMask: the foreground mask
* @return the output image after image matting and compositing
*/
//------------------------------------------------------------------------------
Image mattingAndCompositing(const Image& aBackground,
        const Image& aForeground,
        const Image& aForegroundMask);


//==============================================================================
/**
*   @class  Image
*   @brief  Image is a class to manage a greyscale image.
*/
//==============================================================================
class Image
//------------------------------------------------------------------------------
{
//******************************************************************************
public:
    //--------------------------------------------------------------------------
    /// Default constructor.
    //--------------------------------------------------------------------------
    Image();


    //--------------------------------------------------------------------------
    /// Copy constructor.
    /**
    * @param anImage: the image to copy
    */
    //--------------------------------------------------------------------------
    Image(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Constructor from an array.
    /**
    * @param apData: the array to copy
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    */
    //--------------------------------------------------------------------------
    Image(const float* apData,
                 unsigned int aWidth,
                 unsigned int aHeight);


    //--------------------------------------------------------------------------
    /// Constructor to build a black image.
    /**
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    * @param aDefaultValue: the default pixel intensity
    */
    //--------------------------------------------------------------------------
    Image(unsigned int aWidth,
                 unsigned int aHeight,
                float aDefaultValue = 0.0);


    //--------------------------------------------------------------------------
    /// Destructor.
    //--------------------------------------------------------------------------
    ~Image();


    //--------------------------------------------------------------------------
    /// Assignment operator (also called copy operator).
    /**
    * @param anImage: the image to copy
    * @return the updated version of the current image
    */
    //--------------------------------------------------------------------------
    Image& operator=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Release the memory.
    //--------------------------------------------------------------------------
    void destroy();


    //--------------------------------------------------------------------------
    /// Compute a region of interest (ROI).
    /**
    * @param i: the position of the first pixel of the ROI along the horizontal axis
    * @param j: the position of the first pixel of the ROI along the vertical axis
    * @param aWidth: the width of the ROI (in number of pixels)
    * @param aHeight: the height of the ROI (in number of pixels)
    * @return the ROI
    */
    //--------------------------------------------------------------------------
    Image getROI(unsigned int i,
            unsigned int j,
            unsigned int aWidth,
            unsigned int aHeight) const;


    //--------------------------------------------------------------------------
    /// Set a pixel.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @param aValue: the new pixel value
    */
    //--------------------------------------------------------------------------
    void setPixel(unsigned int i, unsigned int j, float aValue);


    //--------------------------------------------------------------------------
    /// Accessor on a pixel value.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @return the pixel value
    */
    //--------------------------------------------------------------------------
    float getPixel(unsigned int i, unsigned int j) const;


    //--------------------------------------------------------------------------
    /// Accessor on a pixel value.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @return the pixel value
    */
    //--------------------------------------------------------------------------
    float& operator()(unsigned int i, unsigned int j);


    //--------------------------------------------------------------------------
    /// Accessor on a pixel value.
    /**
    * @param i: the position of the pixel along the horizontal axis
    * @param j: the position of the pixel along the vertical axis
    * @return the pixel value
    */
    //--------------------------------------------------------------------------
    const float& operator()(unsigned int i, unsigned int j) const;


    //--------------------------------------------------------------------------
    /// Addition operator. Pixel-wise addition between the two images.
    /**
    * @param anImage: the image to add
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator+(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Subtraction operator. Pixel-wise subtraction between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator-(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Multiplication operator. Pixel-wise multiplication between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator*(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Division operator. Pixel-wise division between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator/(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Addition assignment operator. Pixel-wise addition between the two images.
    /**
    * @param anImage: the image to add
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image& operator+=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Subtraction assignment operator. Pixel-wise subtraction between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image& operator-=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Multiplication assignment operator. Pixel-wise multiplication between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image& operator*=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Division assignment operator. Pixel-wise division between the two images.
    /**
    * @param anImage: the image to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image& operator/=(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Addition operator. Add aValue to every pixel of the image
    /**
    * @param aValue: the value to add
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator+(float aValue) const;


    //--------------------------------------------------------------------------
    /// Subtraction operator. Subtract aValue to every pixel of the image
    /**
    * @param aValue: the value to subtract
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator-(float aValue) const;


    //--------------------------------------------------------------------------
    /// Multiplication operator. Multiply every pixel of the image by aValue
    /**
    * @param aValue: the value for the multiplication
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator*(float aValue) const;


    //--------------------------------------------------------------------------
    /// Division operator. Divide every pixel of the image by aValue
    /**
    * @param aValue: the value for the division
    * @return the resulting image
    */
    //--------------------------------------------------------------------------
    Image operator/(float aValue) const;


    //--------------------------------------------------------------------------
    /// Addition operator. Add aValue to every pixel of the image
    /**
    * @param aValue: the value to add
    * @return the updated version of the current image
    */
    //--------------------------------------------------------------------------
    Image& operator+=(float aValue);


    //--------------------------------------------------------------------------
    /// Subtraction operator. Subtract aValue to every pixel of the image
    /**
    * @param aValue: the value to subtract
    * @return the updated version of the current image
    */
    //--------------------------------------------------------------------------
    Image& operator-=(float aValue);


    //--------------------------------------------------------------------------
    /// Multiplication operator. Multiply every pixel of the image by aValue
    /**
    * @param aValue: the value for the multiplication
    * @return the updated version of the current image
    */
    //--------------------------------------------------------------------------
    Image& operator*=(float aValue);


    //--------------------------------------------------------------------------
    /// Division operator. Divide every pixel of the image by aValue
    /**
    * @param aValue: the value for the division
    * @return the updated version of the current image
    */
    //--------------------------------------------------------------------------
    Image& operator/=(float aValue);


    //--------------------------------------------------------------------------
    /// Negation operator. Compute the negative of the current image.
    /**
    * @return the negative image
    */
    //--------------------------------------------------------------------------
    Image operator!() const;


    //--------------------------------------------------------------------------
    /// Compute the aspect ratio
    /**
    * @return the aspect ratio
    */
    //--------------------------------------------------------------------------
    double getAspectRatio() const;


    //--------------------------------------------------------------------------
    /// Number of pixels along the horizontal axis
    /**
    * @return the width
    */
    //--------------------------------------------------------------------------
    unsigned int getWidth() const;


    //--------------------------------------------------------------------------
    /// Number of pixels along the vertical axis
    /**
    * @return the height
    */
    //--------------------------------------------------------------------------
    unsigned int getHeight() const;


    //--------------------------------------------------------------------------
    /// Compute the minimum pixel value in the image
    /**
    * @return the minimum pixel
    */
    //--------------------------------------------------------------------------
    float getMinValue() const;


    //--------------------------------------------------------------------------
    /// Compute the maximum pixel value in the image
    /**
    * @return the maximum pixel
    */
    //--------------------------------------------------------------------------
    float getMaxValue() const;


    //--------------------------------------------------------------------------
    /// Compute the sum of all the pixel values of the image
    /**
    * @return the sum of all the pixel values of the image
    */
    //--------------------------------------------------------------------------
    double getSum() const;


    //--------------------------------------------------------------------------
    /// Compute the average value of all the pixels of the image
    /**
    * @return the average value of all the pixels of the image
    */
    //--------------------------------------------------------------------------
    double getAverage() const;


    //--------------------------------------------------------------------------
    /// Compute the average value of all the pixels of the image
    /**
    * @return the average value of all the pixels of the image
    */
    //--------------------------------------------------------------------------
    double getMean() const;


    //--------------------------------------------------------------------------
    /// Compute the variance of the pixel values of the image
    /**
    * @return the variance of the pixel values of the image
    */
    //--------------------------------------------------------------------------
    double getVariance() const;


    //--------------------------------------------------------------------------
    /// Compute the standard deviation of the pixel values of the image
    /**
    * @return the standard deviation of the pixel values of the image
    */
    //--------------------------------------------------------------------------
    double getStdDev() const;


    //--------------------------------------------------------------------------
    /// Add aShiftValue to every pixel, then multiply every pixel
    /// by aScaleValue
    /**
    * @param aShiftValue: the shift parameter of the filter
    * @param aScaleValue: the scale parameter of the filter
    */
    //--------------------------------------------------------------------------
    void shiftScaleFilter(float aShiftValue, float aScaleValue);


    //--------------------------------------------------------------------------
    /// Normalise the image between 0 and 1
    //--------------------------------------------------------------------------
    void normalise();


    //--------------------------------------------------------------------------
    /// Normalize the image between 0 and 1
    //--------------------------------------------------------------------------
    void normalize();


    //--------------------------------------------------------------------------
    /// Load an image from a PGM file
    /**
    * @param aFileName: the name of the file to load
    */
    //--------------------------------------------------------------------------
    void loadPGM(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Load an image from a PGM file
    /**
    * @param aFileName: the name of the file to load
    */
    //--------------------------------------------------------------------------
    void loadPGM(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Save the image in a PGM file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void savePGM(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Save the image in a PGM file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void savePGM(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Load an image from a Raw file
    /**
    * @param aFileName: the name of the file to load
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    */
    //--------------------------------------------------------------------------
    void loadRaw(const char* aFileName,
            unsigned int aWidth,
            unsigned int aHeight);


    //--------------------------------------------------------------------------
    /// Load an image from a Raw file
    /**
    * @param aFileName: the name of the file to load
    * @param aWidth: the width of the image
    * @param aHeight: the height of the image
    */
    //--------------------------------------------------------------------------
    void loadRaw(const std::string& aFileName,
            unsigned int aWidth,
            unsigned int aHeight);


    //--------------------------------------------------------------------------
    /// Save the image in a Raw file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void saveRaw(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Save the image in a Raw file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void saveRaw(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Load an image from an ASCII file
    /**
    * @param aFileName: the name of the file to load
    */
    //--------------------------------------------------------------------------
    void loadASCII(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Load an image from an ASCII file
    /**
    * @param aFileName: the name of the file to load
    */
    //--------------------------------------------------------------------------
    void loadASCII(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Save the image in an ASCII file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void saveASCII(const char* aFileName);


    //--------------------------------------------------------------------------
    /// Save the image in an ASCII file
    /**
    * @param aFileName: the name of the file to write
    */
    //--------------------------------------------------------------------------
    void saveASCII(const std::string& aFileName);


    //--------------------------------------------------------------------------
    /// Operator Equal to
    /**
    * @param anImage: the image to compare with
    * @return true if the images are similar,
    *         false if they are different
    */
    //--------------------------------------------------------------------------
    bool operator==(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Operator Not equal to
    /**
    * @param anImage: the image to compare with
    * @return true if the images are different,
    *         false if they are similar
    */
    //--------------------------------------------------------------------------
    bool operator!=(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Compute the sum of absolute errors (SAE) between two images.
    /**
     * @param anImage: the image to use in the comparison
     * @return the SAE
     */
    //--------------------------------------------------------------------------
    //double computeSAE(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Compute the mean absolute errors (MAE) between two images.
    /**
     * @param anImage: the image to use in the comparison
     * @return the MAE
     */
    //--------------------------------------------------------------------------
    //double computeMAE(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Compute the sum of squared errors (SSE) between two images.
    /**
     * @param anImage: the image to use in the comparison
     * @return the SSE
     */
    //--------------------------------------------------------------------------
    //double computeSSE(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Compute the mean squared errors (MSE) between two images.
    /**
     * @param anImage: the image to use in the comparison
     * @return the MSE
     */
    //--------------------------------------------------------------------------
    //double computeMSE(const Image& anImage) const;


    //--------------------------------------------------------------------------
    /// Compute the root mean squared errors (RMSE) between two images.
    /**
     * @param anImage: the image to use in the comparison
     * @return the RMSE
     */
    //--------------------------------------------------------------------------
    //double computeRMSE(const Image& anImage) const;


    //------------------------------------------------------------------------
    /// Compute the normalised-cross correlation (NCC) between two images.
    /**
    * @param anImage: the image to use in the comparison
    * @return the NCC
    */
    //--------------------------------------------------------------------------
    //double computeNCC(const Image& anImage) const;


//******************************************************************************
private:
    /// Number of pixel along the horizontal axis
    unsigned int m_width;


    /// Number of pixel along the vertical axis
    unsigned int m_height;


    /// The pixel data
    float* m_p_image;
};

#endif
