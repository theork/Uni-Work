/**
********************************************************************************
*
*   @file       Image.cpp
*
*   @brief      Class to handle a greyscale image.
*
*   @version    1.0
*
*   @todo       Write here anything you did not implement.
*
*   @date       21/01/20
*
*   @author     Franck Vidal; Theo Rook
*
*
********************************************************************************
*/


//******************************************************************************
//  Include
//******************************************************************************
#include <sstream>   // Header file for stringstream
#include <fstream>   // Header file for filestream
#include <algorithm> // Header file for min/max/fill
#include <numeric>   // Header file for accumulate
#include <cmath>     // Header file for abs and pow
#include <new>       // Header file for std::bad_alloc
#include <stdexcept> // Header file for std::out_of_range
#include <vector>    // Header file for STL vectors
#include <limits>    // Header file for numeric_limits

#include "Image.h"


//--------------------------------------------------
double Image::computeSAE(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return something HUGE, e.g. FLT_MAX or std::numeric_limits<int>::max()
	if (( m_width != anImage.getWidth() ) || ( m_height != anImage.getHeight() )){
		return(FLT_MAX);
	}
		
	//(*this - anImage).getSum(); //can't abs() it...
	
	double sae = 0;
	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width ; ++i) {
			sae += abs(getPixel(i, j) - anImage.getPixel(i, j));
		}
	}
    return sae;
}


//--------------------------------------------------
double Image::computeMAE(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return something HUGE, e.g. FLT_MAX or std::numeric_limits<int>::max()
	if ((m_width != anImage.getWidth()) || (m_height != anImage.getHeight())) {
		return(FLT_MAX);
	}
    return computeSAE(anImage) / (m_width * m_height);
}


//--------------------------------------------------
double Image::computeSSE(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return something HUGE, e.g. FLT_MAX or std::numeric_limits<int>::max()
	if ((m_width != anImage.getWidth()) || (m_height != anImage.getHeight())) {
		return(FLT_MAX);
	}

	double sse = 0;

	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			sse += pow(getPixel(i, j) - anImage.getPixel(i, j), 2);
		}
	}
    return sse;
}


//--------------------------------------------------
double Image::computeMSE(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return something HUGE, e.g. FLT_MAX or std::numeric_limits<int>::max()
	if ((m_width != anImage.getWidth()) || (m_height != anImage.getHeight())) {
		return(FLT_MAX);
	}
    return computeSSE(anImage) / (m_height * m_width);
}


//--------------------------------------------------
double Image::computeRMSE(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return something HUGE, e.g. FLT_MAX or std::numeric_limits<int>::max()
	if ((m_width != anImage.getWidth()) || (m_height != anImage.getHeight())) {
		return(FLT_MAX);
	}
    return sqrt(computeMSE(anImage));
}


//--------------------------------------------------
double Image::computeNCC(const Image& anImage) const
//--------------------------------------------------
{
    // Handle errors: if the images have a different size,
    // return 0
	if ((m_width != anImage.getWidth()) || (m_height != anImage.getHeight())) {
		return(0);
	}

	double ncc = 0,	im1_avg = getAverage(), im2_avg = anImage.getAverage(), 
		im1_std = getStdDev(), im2_std = anImage.getStdDev();
	
	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			ncc += ((getPixel(i, j) - im1_avg) * (anImage.getPixel(i, j) - im2_avg)) / (im1_std * im2_std);
		}
	}

    return 1.0 / (m_width * m_height) * ncc;
}


//--------------------------------------------------------------------
Image Image::clamp(float aLowerThreshold, float aUpperThreshold) const
//--------------------------------------------------------------------
{
	//will swap the upper and lower if they are entered the wrong way around
	if (aUpperThreshold < aLowerThreshold) {
		float swap = aLowerThreshold;
		aLowerThreshold = aUpperThreshold;
		aUpperThreshold = swap;
	}

	Image temp = *this;
	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			float currPix = getPixel(i, j);
			if (currPix < aLowerThreshold)
				temp.setPixel(i, j, aLowerThreshold);
			else if (currPix > aUpperThreshold)
				temp.setPixel(i, j, aUpperThreshold);
		}
	}
	return temp;

}


//-------------------------------------------
Image Image::threshold(float aThreshold) const
//-------------------------------------------
{
    // The simplest thresholding methods replace each pixel in an image with
    // - a black pixel if the image intensity I(i ,j) is less than some fixed constant T
    // - a white pixel if the image intensity I(i ,j) is greater than or equal to T
    // Black is 0
    // White is 1

	Image temp(m_width, m_height);

	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			// assigns pixel to the logical statement - 0 = false, 1 = true
			temp(i, j) = (getPixel(i, j) >= aThreshold);
		}
	}

    return temp;
}


//-------------------------------------------------
Image Image::threshold(float aLowerThreshold,
                       float aUpperThreshold) const
//-------------------------------------------------
{
    // This thresholding method replace each pixel in an image with
    // - a black pixel if the image intensity I(i ,j) is less than aMinThreshold or greater than aMaxThreshold
    // - a white pixel otherwise
    // Black is 0
    // White is 1

	Image temp(m_width, m_height, 1);

	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			// assigns pixel to the logical statement - 0 = false, 1 = true
			temp(i, j) = ((getPixel(i, j) >= aLowerThreshold) & (getPixel(i, j) <= aUpperThreshold));
		}
	}

	return temp;
}


//-----------------------------------------------
Image Image::convolution(float* apKernel,
                         int aKernelWidth,
                         int aKernelHeight) const
//-----------------------------------------------
{
	Image newImage(m_width, m_height);

	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {

			float sum = 0;
			for (unsigned int l = 0; l < aKernelHeight; ++l) {
				for (unsigned int k = 0; k < aKernelWidth; ++k) {
					try {
						 sum += getPixel(i - aKernelWidth / 2 + k, j - aKernelHeight / 2 + l) * apKernel[l * aKernelWidth + k]; // converts 2d index into 1d for apKernel
					}
					catch (const std::out_of_range& e) {
						newImage.setPixel(i, j, 0);
					}
				}
			}
			newImage.setPixel(i, j, sum);
		}
	}
	return newImage;
}

//-----------------------------
Image Image::meanFilter(unsigned int size) const
//-----------------------------
{
	if (size > m_width | size > m_height | size == 0) {
		std::stringstream error_message;
		error_message << size << " is an invalid kernel size" << std::endl;
		throw(error_message.str());
	}

	unsigned int total_size = size * size;
	float* kernel = 0;
	kernel = new float[total_size];
	float val = 1.0 / total_size;

	for (unsigned int i = 0; i < (total_size); ++i) {
		kernel[i] = val;
	}

    //float kernel[] = {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    //        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
    //        1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0};
    return convolution(kernel, size, size);
}


//----------------------------
Image Image::boxFilter(unsigned int size) const
//----------------------------
{
    // Box filter is the same as mean filter
    return meanFilter(size);
}


//--------------------------------
Image Image::averageFilter(unsigned int size) const
//--------------------------------
{
    // Average filter is the same as mean filter
    return meanFilter(size);
}


//---------------------------------
Image Image::gaussianFilter() const
//---------------------------------
{
	float kernel[] = {1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0, 
					2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0, 
					1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0};
	return convolution(kernel, 3, 3);
}


//----------------------------------
Image Image::laplacianFilter(unsigned int size) const
//----------------------------------
{
	if (size > m_width | size > m_height | size == 0 | size % 2 == 0) {
		std::stringstream error_message;
		error_message << size << " is an invalid kernel size (needs to be odd)" << std::endl;
		throw(error_message.str());
	}

	unsigned int total_size = size * size;
	float* kernel;
	kernel = new float[total_size];
	for (unsigned int i = 0; i < total_size; ++i) {
		kernel[i] = -1;
	}
	kernel[((total_size + 2) - 1) / 2] = total_size - 1; // assigns midpoint

	//float kernel[] = {-1, -1, -1, -1, -1,
	//				-1, -1, -1, -1, -1,
	//				-1, -1, 24, -1, -1, 
	//				-1, -1, -1, -1, -1, 
	//				-1, -1, -1, -1, -1 };
	return convolution(kernel, size, size);
}


//---------------------------------
Image Image::sobelXOperator() const
//---------------------------------
{

	float kernel[] = { -1, 0, 1,
				-2, 0, 2,
				-1, 0, 1 };
	return convolution(kernel, 3, 3);
}


//---------------------------------
Image Image::sobelYOperator() const
//---------------------------------
{
	float kernel[] = { 1, 2, 1,
			0, 0, 0,
			-1, -2, -1 };
	return convolution(kernel, 3, 3);
}


//------------------------------------
Image Image::gradientMagnitude() const
//------------------------------------
{
    // Uses a Sobel edge detector to highlight sharp changes in intensity in
    // the image. Two 3x3 convolution kernels are used to generate vertical and
    // horizontal derivatives. The final image is produced by combining
    // the two derivatives using the square root of the sum of the squares.

	Image sobelX = sobelXOperator();
	Image sobelY = sobelYOperator();
	Image temp(m_width, m_height);

	for (unsigned int j = 0; j < m_height; ++j) {
		for (unsigned int i = 0; i < m_width; ++i) {
			temp.setPixel(i, j, sqrt(pow(sobelX.getPixel(i, j), 2) + pow(sobelY.getPixel(i, j), 2)));
		}
	}

	return temp;
}


//--------------------------------------------
Image Image::sharpenFilter(double alpha) const
//--------------------------------------------
{
	/// Sharpen an image. The amount of sharpening is controled with alpha:
///    output(i, j) = input(i,j) + alpha * (input(i,j) - gaussian(input)(i,j))
///    Pixel values in the output are clamped beween the min/max pixel values of the input.

	//Image output(m_width, m_height);
	//for (unsigned int j = 0; j < m_height; ++j) {
	//	for (unsigned int i = 0; i < m_width; ++i) {
	//		output.setPixel(i, j, getPixel(i, j) + alpha * (getPixel(i, j) - gaussian.getPixel(i, j)));
	//	}
	//}
    //return output.clamp(getMinValue(), getMaxValue());

	// found a more elegant way...
	return (*this + alpha * (*this - gaussianFilter())).clamp(getMinValue(), getMaxValue());
}




// DO NOT MODIFY THE CODE BELOW THIS LINE


//-----------------------------------------------
void Image::saveBMP(const std::string& aFileName)
//-----------------------------------------------
{
    saveBMP(aFileName.c_str());
}


//----------------------------------------
void Image::saveBMP(const char* aFileName)
//----------------------------------------
{
    // Open the file in binary
    std::ofstream output_file (aFileName, std::ifstream::binary);

    // The file is not open
    if (!output_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") cannot be created";

        throw error_message;
    }

    int file_size = 54 + 3 * m_width * m_height;
    unsigned char* p_bgr_data = new unsigned char[3 * m_width * m_height];

    for(int i = 0; i < m_width; ++i)
    {
        for(int j = 0; j < m_height; ++j)
        {
            unsigned int x = i;
            unsigned int y = (m_height-1) - j;

            float luminance = m_p_image[j * m_width + i];
            unsigned char pixel;

            if (luminance < 0.0) pixel = 0;
            else if (luminance > 255) pixel = 255;
            else pixel = luminance;

            p_bgr_data[(x + y * m_width) * 3 + 2] = luminance;
            p_bgr_data[(x + y * m_width) * 3 + 1] = luminance;
            p_bgr_data[(x + y * m_width) * 3 + 0] = luminance;
        }
    }

    unsigned char bmp_file_header[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmp_info_header[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmp_pad[3] = {0,0,0};

    bmp_file_header[ 2] = (unsigned char)(file_size    );
    bmp_file_header[ 3] = (unsigned char)(file_size>> 8);
    bmp_file_header[ 4] = (unsigned char)(file_size>>16);
    bmp_file_header[ 5] = (unsigned char)(file_size>>24);

    bmp_info_header[ 4] = (unsigned char)(       m_width    );
    bmp_info_header[ 5] = (unsigned char)(       m_width>> 8);
    bmp_info_header[ 6] = (unsigned char)(       m_width>>16);
    bmp_info_header[ 7] = (unsigned char)(       m_width>>24);
    bmp_info_header[ 8] = (unsigned char)(       m_height    );
    bmp_info_header[ 9] = (unsigned char)(       m_height>> 8);
    bmp_info_header[10] = (unsigned char)(       m_height>>16);
    bmp_info_header[11] = (unsigned char)(       m_height>>24);

    output_file.write(reinterpret_cast<char*>(bmp_file_header), 14 * sizeof(char));
    output_file.write(reinterpret_cast<char*>(bmp_info_header), 40 * sizeof(char));

    for(int j = 0; j < m_height; ++j)
    {
        output_file.write(reinterpret_cast<char*>(&p_bgr_data[j * 3 * m_width]), 3 * m_width * sizeof(char));
        output_file.write(reinterpret_cast<char*>(bmp_pad), (4-(m_width*3)%4)%4 * sizeof(char));
    }

    // Release memory
    delete [] p_bgr_data;
}





//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//
// Definitions of the functions/methods required in Assignment 1:
//
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------
//---------------------------------------------------------------


//-----------------------------------------------------------
Image blending(float alpha, const Image& f0, const Image& f1)
//-----------------------------------------------------------
{
    /// Image blending: Cross-dissolve between two images so that the pixel
    /// i,j of the output image is:
    /// output(i,j) = (1-alpha) * f0(i,j) + alpha * f1(i,j)

    return (1.0 - alpha) * f0 + alpha * f1;
}


//-------------------------------------------------------
Image mattingAndCompositing(const Image& aBackground,
                            const Image& aForeground,
                            const Image& aForegroundMask)
//-------------------------------------------------------
{
    // Make sure the pixel values are between 0 and 1 in the mask
    Image foreground_mask = aForegroundMask;
    foreground_mask.normalise();

    // The background mask is the negative of the foreground mask
    Image background_mask = !foreground_mask;

    // Perform the matting and compositing
    return aForeground * foreground_mask + aBackground * background_mask;
}


//----------------------------------------------------------------
void Image::setPixel(unsigned int i, unsigned int j, float aValue)
//----------------------------------------------------------------
{
    // Very similar to operator()(unsigned int i, unsigned int j)

    // Invalid index
    if (i >= m_width || j >= m_height)
    {
        // Create an error message
        std::stringstream error_message;
        error_message << "Index " << i << "/" << j << " is invalid in " << __FUNCTION__ << ". The image size is " << m_width << "x" << m_height;

        throw std::out_of_range(error_message.str());
    }

    // Set the pixel value
    m_p_image[j * m_width + i] = aValue;
}


//---------------------------------------------------------
float Image::getPixel(unsigned int i, unsigned int j) const
//---------------------------------------------------------
{
    // Very similar to operator()(unsigned int i, unsigned int j)

    // Invalid index
    if (i >= m_width || j >= m_height)
    {
        // Create an error message
        std::stringstream error_message;
        error_message << "Index " << i << "/" << j << " is invalid in " << __FUNCTION__ << ". The image size is " << m_width << "x" << m_height;

        throw std::out_of_range(error_message.str());
    }

    // Return the pixel value
    return (m_p_image[j * m_width + i]);
}


//-------------------------------------------
Image& Image::operator=(const Image& anImage)
//-------------------------------------------
{
    // Same as copy constructor

    // Prevent self-instantiation
    if (&anImage != this)
    {
        // Release memory if needed (to prevent possible memory leaks)
        destroy();

        // Record the image size
        m_width   = anImage.m_width;
        m_height  = anImage.m_height;

        // Allocate the memory
        m_p_image = new float[m_width * m_height];

        // Copy the data
        std::copy(anImage.m_p_image, anImage.m_p_image + m_width * m_height, m_p_image);
    }

    // Return the instance
    return (*this);
}


//------------------------------------------------
Image Image::operator+(const Image& anImage) const
//------------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));

    // Create an image of the right size
    Image temp(min_width, min_height);

    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.setPixel(i, j, getPixel(i, j) + anImage.getPixel(i, j));
        }
    }

    // Return the result
    return (temp);
}


//------------------------------------------------
Image Image::operator-(const Image& anImage) const
//------------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));

    // Copy the instance into a temporary variable
    Image temp(getROI(0, 0, min_width, min_height));

    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.m_p_image[j * temp.m_width + i] -= anImage.m_p_image[j * anImage.m_width + i];
        }
    }

    // Return the result
    return (temp);
}


//------------------------------------------------
Image Image::operator*(const Image& anImage) const
//------------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));

    // Copy the instance into a temporary variable
    Image temp(getROI(0, 0, min_width, min_height));

    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.m_p_image[j * temp.m_width + i] *= anImage.m_p_image[j * anImage.m_width + i];
        }
    }

    // Return the result
    return (temp);
}


//------------------------------------------------
Image Image::operator/(const Image& anImage) const
//------------------------------------------------
{
    // Deal with images of different sizes
    unsigned int min_width(std::min(m_width, anImage.m_width));
    unsigned int min_height(std::min(m_height, anImage.m_height));

    // Copy the instance into a temporary variable
    Image temp(getROI(0, 0, min_width, min_height));

    // Copy the data
    for (unsigned int j(0); j < min_height; ++j)
    {
        for (unsigned int i(0); i < min_width; ++i)
        {
            temp.m_p_image[j * temp.m_width + i] /= anImage.m_p_image[j * anImage.m_width + i];
        }
    }

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator+(float aValue) const
//----------------------------------------
{
    // Copy the instance into a temporary variable
    Image temp = *this;

    // Add aValue to every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        temp.m_p_image[i] += aValue;
    }

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator-(float aValue) const
//----------------------------------------
{
    // Copy the instance into a temporary variable
    Image temp = *this;

    // Subtract aValue to every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        temp.m_p_image[i] -= aValue;
    }

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator*(float aValue) const
//----------------------------------------
{
    // Copy the instance into a temporary variable
    Image temp = *this;

    // Subtract aValue to every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        temp.m_p_image[i] *= aValue;
    }

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator/(float aValue) const
//----------------------------------------
{
    // The C++ standard state that a division by 0.0 is undefined

    // Handle division by 0.0
    if (abs(aValue) < 1e-20)
    {
        throw std::runtime_error("Math error: Attempted to divide by Zero");
    }

    // Copy the instance into a temporary variable
    Image temp = *this;

    // Subtract aValue to every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        temp.m_p_image[i] /= aValue;
    }

    // Return the result
    return (temp);
}


//----------------------------
Image Image::operator!() const
//----------------------------
{
    // Create an image of the right size
    Image temp(m_width, m_height);

    // Record min/max values
    float min_value = getMinValue();
    float max_value = getMaxValue();

    // Process every pixel
    // Make sure the dynamic range is preserved
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        temp.m_p_image[i] = max_value - m_p_image[i] + min_value;
    }

    // Return the result
    return (temp);
}


//----------------------------------
double Image::getAspectRatio() const
//----------------------------------
{
    return (double(m_width) / double(m_height));
}


//----------------------------------
unsigned int Image::getWidth() const
//----------------------------------
{
    return (m_width);
}


//-----------------------------------
unsigned int Image::getHeight() const
//-----------------------------------
{
    return (m_height);
}


//------------------------------
float Image::getMinValue() const
//------------------------------
{
    return (*std::min_element(m_p_image, m_p_image + m_width * m_height));
}


//------------------------------
float Image::getMaxValue() const
//------------------------------
{
    return (*std::max_element(m_p_image, m_p_image + m_width * m_height));
}


//--------------------------
double Image::getSum() const
//--------------------------
{
    return (std::accumulate(m_p_image, m_p_image + m_width * m_height, 0.0));
}


//------------------------------
double Image::getAverage() const
//------------------------------
{
    // Handle division by 0
    if (m_width * m_height == 0)
    {
        throw std::runtime_error("Math error: Attempted to divide by Zero");
    }

    return (getSum() / (m_width * m_height));
}


//-------------------------------
double Image::getVariance() const
//-------------------------------
{
    double sum = 0;

    // Cache the average pixel value
    double mean = getAverage();

    // Process every pixel
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        sum += std::pow(m_p_image[i] - mean, 2);
    }

    // Return the result
    return (sum) / (m_width * m_height);
}


//-----------------------------
double Image::getStdDev() const
//-----------------------------
{
    return (sqrt(getVariance()));
}







// DO NOT MODIFY THE CODE BELOW THIS LINE









//-------------------------------------------------
Image operator+(float aValue, const Image& anImage)
//-------------------------------------------------
{
    return anImage + aValue;
}


//-------------------------------------------------
Image operator*(float aValue, const Image& anImage)
//-------------------------------------------------
{
    return anImage * aValue;
}



//------------------
Image::Image():
//------------------
        m_width(0),
        m_height(0),
        m_p_image(0)
//------------------
{}


//----------------------------------------------
Image::Image(const Image& anImage):
//----------------------------------------------
        m_width(anImage.m_width),
        m_height(anImage.m_height),
        m_p_image(new float[m_width * m_height])
//----------------------------------------------
{
    // Copy the data
    std::copy(anImage.m_p_image, anImage.m_p_image + m_width * m_height, m_p_image);
}


//-----------------------------------------------------
Image::Image(const float* apData,
             unsigned int aWidth,
             unsigned int aHeight):
//-----------------------------------------------------
        m_width(aWidth),
        m_height(aHeight),
        m_p_image(new float[m_width * m_height])
//-----------------------------------------------------
{
    // Copy the data
    std::copy(apData, apData + m_width * m_height, m_p_image);
}


//----------------------------------------------
Image::Image(unsigned int aWidth,
             unsigned int aHeight,
             float aDefaultValue):
//----------------------------------------------
        m_width(aWidth),
        m_height(aHeight),
        m_p_image(new float[m_width * m_height])
//----------------------------------------------
{
    // Initialise all the elements of the array
    for (size_t i = 0; i < m_width * m_height; ++i)
    {
        m_p_image[i] = aDefaultValue;
    }
}


//-------------
Image::~Image()
//-------------
{
    // Release memory
    destroy();
}


//-------------------
void Image::destroy()
//-------------------
{
    // Memory has been dynamically allocated
    delete [] m_p_image;

    // There is no pixel in the image
    m_width  = 0;
    m_height = 0;
}


//---------------------------------------------
Image Image::getROI(unsigned int i,
                    unsigned int j,
                    unsigned int aWidth,
                    unsigned int aHeight) const
//---------------------------------------------
{
    // Create a black image
    Image roi(aWidth, aHeight);

    // Process every row of the ROI
    for (unsigned y(0); y < aHeight; ++y)
    {
        // Process every column of the ROI
        for (unsigned x(0); x < aWidth; ++x)
        {
            unsigned int index_i(x + i);
            unsigned int index_j(y +j);

            // The pixel index is valid
            if ((index_i < m_width) && (index_j < m_height))
            {
                // Set the pixel of the ROI
                roi(x, y) = getPixel(index_i, index_j);
            }
        }
    }

    return (roi);
}


//------------------------------------------------------
float& Image::operator()(unsigned int i, unsigned int j)
//------------------------------------------------------
{
    float temp;

    // Invalid index
    if (i >= m_width || j >= m_height)
    {
        // Create an error message
        std::stringstream error_message;
        error_message << "Index " << i << "/" << j << " is invalid in " << __FUNCTION__ << ". The image size is " << m_width << "x" << m_height;

        throw std::out_of_range(error_message.str());
    }

    // Return the result
    return (m_p_image[j * m_width + i]);
}


//------------------------------------------------------------------
const float& Image::operator()(unsigned int i, unsigned int j) const
//------------------------------------------------------------------
{
    float temp;

    // Invalid index
    if (i >= m_width || j >= m_height)
    {
        // Create an error message
        std::stringstream error_message;
        error_message << "Index " << i << "/" << j << " is invalid in " << __FUNCTION__ << ". The image size is " << m_width << "x" << m_height;

        throw std::out_of_range(error_message.str());
    }

    // Return the result
    return (m_p_image[j * m_width + i]);
}


//--------------------------------------------
Image& Image::operator+=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator+
    *this = *this + anImage;

    // Return the result
    return (*this);
}


//--------------------------------------------
Image& Image::operator-=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator-
    *this = *this - anImage;

    // Return the result
    return (*this);
}


//--------------------------------------------
Image& Image::operator*=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator+
    *this = *this * anImage;

    // Return the result
    return (*this);
}


//--------------------------------------------
Image& Image::operator/=(const Image& anImage)
//--------------------------------------------
{
    // Re-use operator-
    *this = *this / anImage;

    // Return the result
    return (*this);
}


//-----------------------------------
Image& Image::operator+=(float aValue)
//-----------------------------------
{
    // Re-use operator+
    *this = *this + aValue;

    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator-=(float aValue)
//------------------------------------
{
    // Re-use operator-
    *this = *this - aValue;

    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator*=(float aValue)
//------------------------------------
{
    // Re-use operator*
    *this = *this * aValue;

    // Return the result
    return (*this);
}


//------------------------------------
Image& Image::operator/=(float aValue)
//------------------------------------
{
    // Re-use operator/
    *this = *this / aValue;

    // Return the result
    return (*this);
}


//---------------------------
double Image::getMean() const
//---------------------------
{
    // Return the result
    return (getAverage());
}


//----------------------------------------------------------------
void Image::shiftScaleFilter(float aShiftValue, float aScaleValue)
//----------------------------------------------------------------
{
    // Process every pixel of the image
    for (unsigned int i = 0; i < m_width * m_height; ++i)
    {
        // Apply the shilft/scale filter
        m_p_image[i] = (m_p_image[i] + aShiftValue) * aScaleValue;
    }


    // Or
    // *this += aShiftValue;
    // *this *= aScaleValue

    // Or
    // *this = (*this + aShiftValue) * aScaleValue;
}


//---------------------
void Image::normalise()
//---------------------
{
    float min_value = getMinValue();
    shiftScaleFilter(-min_value, 1.0 / (getMaxValue() - min_value));
}


//----------------------------------------
void Image::loadPGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ifstream input_file(aFileName, std::ifstream::binary);

    // The file does not exist
    if (!input_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot open the file \"" << aFileName << "\". It does not exist";

        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Release the memory if necessary
        destroy();

        // Variable to store a line
        std::string line;

        // Get the first line
        std::getline(input_file, line);

        // Get the image type
        std::string image_type(line);

        // Valid ASCII format
        if (image_type == "P2")
        {
            // Variable to save the max value
            int max_value(-1);

            // There is data to read
            unsigned int pixel_count(0);
            while (input_file.good())
            {
                // Get the new line
                std::getline(input_file, line);

                // It is not a comment
                if (line[0] != '#')
                {
                    // Store the line in a stream
                    std::stringstream stream_line;
                    stream_line << std::string(line);

                    // The memory is not allocated
                    if (!m_p_image && !m_width && !m_height)
                    {
                        // Load the image size
                        stream_line >> m_width >> m_height;

                        // Alocate the memory
                        m_p_image = new float[m_width * m_height];
                    }
                    // The max value is not set
                    else if (max_value < 0)
                    {
                        // Get the max value;
                        stream_line >> max_value;
                    }
                    // Read the pixel data
                    else
                    {
                        // Process all the pixels of the line
                        while (stream_line.good())
                        {
                            // Get the pixel value
                            int pixel_value(-1);
                            stream_line >> pixel_value;
                            // The pixel exists
                            if (pixel_count < m_width * m_height)
                            {
                                m_p_image[pixel_count++] = pixel_value;
                            }
                        }
                    }
                }
            }
        }
        // Valid binary format
        else if (image_type == "P5")
        {
            // Variable to save the max value
            int max_value(-1);

            // There is data to read
            unsigned int pixel_count(0);
            while (input_file.good() && !pixel_count)
            {
                // Process as an ASCII file
                if (!m_width || !m_height || max_value < 0)
                {
                    // Get the new line
                    std::getline(input_file, line);

                    // It is not a comment
                    if (line[0] != '#')
                    {
                        // Store the line in a stream
                        std::stringstream stream_line;
                        stream_line << std::string(line);

                        // The memory is not allocated
                        if (!m_p_image && !m_width && !m_height)
                        {
                            // Load the image size
                            stream_line >> m_width >> m_height;

                            // Alocate the memory
                            m_p_image = new float[m_width * m_height];
                        }
                        // The max value is not set
                        else
                        {
                            // Get the max value;
                            stream_line >> max_value;
                        }
                    }
                }
                // Read the pixel data
                else
                {
                    unsigned char* p_temp(new unsigned char[m_width * m_height]);

                    // Out of memory
                    if (!p_temp)
                    {
                        throw ("Out of memory");
                    }

                    input_file.read(reinterpret_cast<char*>(p_temp), m_width * m_height);

                    for (unsigned int i(0); i < m_width * m_height; ++i)
                    {
                        m_p_image[i] = p_temp[i];
                        ++pixel_count;
                    }
                    delete [] p_temp;
                }
            }
        }
        // Invalid format
        else
        {
            // Build the error message
            std::stringstream error_message;
            error_message << "Invalid file (\"" << aFileName << "\")";

            // Throw an error
            throw (error_message.str());
        }
    }
}


//-----------------------------------------------
void Image::loadPGM(const std::string& aFileName)
//-----------------------------------------------
{
    loadPGM(aFileName.data());
}


//----------------------------------------
void Image::savePGM(const char* aFileName)
//----------------------------------------
{
    // Open the file
    std::ofstream output_file(aFileName);

    // The file does not exist
    if (!output_file.is_open())
    {
        // Build the error message
        std::stringstream error_message;
        error_message << "Cannot create the file \"" << aFileName << "\"";

        // Throw an error
        throw (error_message.str());
    }
    // The file is open
    else
    {
        // Set the image type
        output_file << "P2" << std::endl;

        // Print a comment
        output_file << "# ICP3038 -- Assignment 1 -- 2018/2019" << std::endl;

        // The image size
        output_file << m_width << " " << m_height << std::endl;

        // The get the max value
        //output_file << std::min(255, std::max(0, int(getMaxValue()))) << std::endl;
        //output_file << std::max(255, int(getMaxValue())) << std::endl;

        // Process every line
        for (unsigned int j = 0; j < m_height; ++j)
        {
            // Process every column
            for (unsigned int i = 0; i < m_width; ++i)
            {
                // Process the pixel
                int pixel_value(m_p_image[j * m_width + i]);
                pixel_value = std::max(0, pixel_value);
                pixel_value = std::min(255, pixel_value);

                output_file << pixel_value;

                // It is not the last pixel of the line
                if (i < (m_width - 1))
                {
                    output_file << " ";
                }
            }

            // It is not the last line of the image
            if (j < (m_height - 1))
            {
                output_file << std::endl;
            }
        }
    }
}


//-----------------------------------------------
void Image::savePGM(const std::string& aFileName)
//-----------------------------------------------
{
    savePGM(aFileName.data());
}


//----------------------------------------
void Image::loadRaw(const char* aFileName,
                    unsigned int aWidth,
                    unsigned int aHeight)
//----------------------------------------
{
    // Open the file in binary
    std::ifstream input_file (aFileName, std::ifstream::binary);

    // The file is not open
    if (!input_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") does not exist";

        throw error_message;
    }

    // Get size of file
    input_file.seekg(0, input_file.end);
    unsigned int size(input_file.tellg());

    // The size is not correct
    if (aWidth * aHeight * sizeof(float) != size)
    {
        std::stringstream error_message;
        error_message << "The size of " << aFileName << " is not " <<
                aWidth << "x" << aHeight;

        throw error_message.str();
    }

    // Rewind the file
    input_file.seekg (0);

    // Release the memory
    destroy();

    // Allocate memory for file content
    m_width = aWidth;
    m_height = aHeight;
    m_p_image = new float[m_width * m_height];

    // Read content of input_file
    input_file.read(reinterpret_cast<char*>(&m_p_image[0]), size);
}


//-----------------------------------------------
void Image::loadRaw(const std::string& aFileName,
                    unsigned int aWidth,
                    unsigned int aHeight)
//-----------------------------------------------
{
    loadRaw(aFileName.data(), aWidth, aHeight);
}


//----------------------------------------
void Image::saveRaw(const char* aFileName)
//----------------------------------------
{
    // Open the file in binary
    std::ofstream output_file (aFileName, std::ifstream::binary);

    // The file is not open
    if (!output_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") cannot be created";

        throw error_message;
    }

    // Write content to file
    output_file.write(reinterpret_cast<char*>(&m_p_image[0]), m_width * m_height * sizeof(float));
}


//-----------------------------------------------
void Image::saveRaw(const std::string& aFileName)
//-----------------------------------------------
{
    saveRaw(aFileName.data());
}


//------------------------------------------
void Image::loadASCII(const char* aFileName)
//------------------------------------------
{
    // Release the memory
    destroy();

    // Open the file
    std::ifstream input_file (aFileName);

    // The file is not open
    if (!input_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") does not exist";

        throw error_message;
    }

    // Load the data into a vector
    std::string line;
    int number_of_rows(0);
    int number_of_columns(0);
    std::vector<float> p_image;

    // Read evely line
    while (std::getline(input_file, line))
    {
        number_of_columns = 0;
        float intensity;
        std::stringstream line_parser;
        line_parser << line;
        while (line_parser >> intensity)
        {
            p_image.push_back(intensity);
            ++number_of_columns;
        }
        ++number_of_rows;
    }

    // Wrong number of pixels
    if (number_of_rows * number_of_columns != p_image.size())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") is invalid";

        throw error_message;
    }

    // Create the image from the raw data

    // Use line below if assignment operator implemented
    //*this = Image(&p_image[0], number_of_columns, number_of_rows);

    // Or
    m_p_image = new float[number_of_columns * number_of_rows];
    m_width   = number_of_columns;
    m_height  = number_of_rows;

    // Copy the data
    std::copy(&p_image[0], &p_image[0] + m_width * m_height, m_p_image);
}


//-------------------------------------------------
void Image::loadASCII(const std::string& aFileName)
//-------------------------------------------------
{
    loadASCII(aFileName.data());
}


//------------------------------------------
void Image::saveASCII(const char* aFileName)
//------------------------------------------
{
    // Open the file
    std::ofstream output_file (aFileName);

    // The file is not open
    if (!output_file.is_open())
    {
        std::string error_message("The file (");
        error_message += aFileName;
        error_message += ") cannot be created";

        throw error_message;
    }

    // Write content to file
    float* p_data(&m_p_image[0]);
    for (unsigned int j(0); j < m_height; ++j)
    {
        for (unsigned int i(0); i < m_width; ++i)
        {
            output_file << *p_data++;

            // This is not the last pixel of the line
            if (i < m_width - 1)
            {
                output_file << " ";
            }
        }

        // This is not the last line
        if (j < m_height - 1)
        {
            output_file << std::endl;
        }
    }
}


//------------------------------------------------
void Image::saveASCII(const std::string& aFileName)
//------------------------------------------------
{
    saveASCII(aFileName.data());
}


//------------------------------------------------
bool Image::operator==(const Image& anImage) const
//------------------------------------------------
{
    // The width of the two images is different
    if (m_width != anImage.m_width)
    {
        return (false);
    }

    // The height of the two images is different
    if (m_height != anImage.m_height)
    {
        return (false);
    }

    // Get the image range for both images
    float range1 = getMaxValue() - getMinValue();
    float range2 = anImage.getMaxValue() - anImage.getMinValue();

    // Set an iterator per image
    const float* ite1 = m_p_image;
    const float* ite2 = anImage.m_p_image;

    // If relative absolute difference is greater than 1%,
    // Then consider the pixel to be different
    float temp;
    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        // Absolute difference
        temp = std::abs(*ite1++ - *ite2++);

        // Check if the relative differences are more than 1%
        // If it is the case, then the images are different
        if ((temp / range1) > 0.01 || (temp / range2) > 0.01)
        {
            return (false);
        }
    }

    // No difference detected, the images are the same
    return (true);
}


//------------------------------------------------
bool Image::operator!=(const Image& anImage) const
//------------------------------------------------
{
    // Re-use operator== using a negation
    return (!(operator==(anImage)));
}
