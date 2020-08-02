/**
********************************************************************************
*
*   @file       Image.cpp
*
*   @brief      Class to handle a greyscale image.
*
*   @version    1.0
*
*   @date       13/11/19
*
*   @author     Franck Vidal; Theo Rook EEUB22
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

#include "Image.h"

//-----------------------------------------------------------
Image blending(float alpha, const Image& f0, const Image& f1)
//-----------------------------------------------------------
{
    //******************************************************
    // Modify this method to write your own function
    //******************************************************

	//unsigned int w = f0.getWidth();
	//unsigned int h = f0.getHeight();
	//Image output(f0);
	////finds the smaller width/height
	//if (w > f1.getWidth()) {
	//	w = f1.getWidth();
	//}
	//if (h > f1.getHeight()) {
	//	h = f1.getHeight();
	//}
	//
	//for (int i = 0; i < w; i++) {
	//	for (int j = 0; j < h; j++) {
	//		output.setPixel(i, j, (1 - alpha) * f0.getPixel(i, j) + alpha * f1.getPixel(i, j));
	//	}
	//}
    return (1 - alpha) * f0 + alpha * f1;
}


//-------------------------------------------------------
Image mattingAndCompositing(const Image& aBackground,
                            const Image& aForeground,
                            const Image& aForegroundMask)
//-------------------------------------------------------
{
    //******************************************************
    // Modify this method to write your own function
    //******************************************************


//	Image output;


	//Image output(aBackground);
	//unsigned int w = aBackground.getWidth();
	//unsigned int h = aBackground.getHeight();
	//for (int i = 0; i < w; i++) {
	//	for (int j = 0; j < h; j++) {
	//		float currentPix = aForegroundMask.getPixel(i, j);
	//		output.setPixel(i, j, aForegroundMask.getPixel(i,j) * aForeground.getPixel(i, j) + (1 - aForegroundMask.getPixel(i, j)) * aBackground.getPixel(i, j));
	//	}
	//}

    return aForegroundMask * aForeground + !aForegroundMask * aBackground;
}


//----------------------------------------------------------------
void Image::setPixel(unsigned int i, unsigned int j, float aValue)
//----------------------------------------------------------------
{
    //******************************************************
    // Modify this method to write your own setter
    //******************************************************
	if ((i >= 0 & i <= m_width) & (j >= 0 & j <= m_height)) {
		m_p_image[i + m_width * j] = aValue;
	}
	else {
		std::stringstream error_message;
		error_message << "error, setPixel(() out of range";
		throw (error_message.str());
	}	
}

//---------------------------------------------------------
float Image::getPixel(unsigned int i, unsigned int j) const
//---------------------------------------------------------
{
    //******************************************************
    // Modify this method to write your own getter
    //******************************************************

    // Return the result
	if ((i >= 0 & i <= m_width) & (j >= 0 & j <= m_height)) {
		return (m_p_image[i + m_width * j]);
	}
	std::stringstream error_message;
	error_message << "error, getPixel() out of range with values i = " << i << " & j = " << j;
	throw (error_message.str());
}


//-------------------------------------------
Image& Image::operator=(const Image& anImage)
//-------------------------------------------
{
    //*********************************************************
    // Modify this method to write your own assignment operator
    //*********************************************************

    // Prevent self-instantiation
    if (&anImage != this)
    {

		m_width = anImage.m_width;
		m_height = anImage.m_height;
		m_p_image = new float[m_width * m_height];
		std::copy(anImage.m_p_image, anImage.m_p_image + m_width * m_height, m_p_image);
	}

    // Return the instance
    return (*this);
}


//------------------------------------------------
Image Image::operator+(const Image& anImage) const
//------------------------------------------------
{
    //******************************************************
    // Modify this method to write your operator+
    //******************************************************    
	Image temp(m_width, m_height, 0);
	// WILL STOP METHOD RUNNING IF DIMENSIONS DONT MATCH
	//if (anImage.m_height != m_height || anImage.m_width != m_width) {
	//	std::stringstream error_message;
	//	error_message << "Error adding images - dimensions don't match";
	//	throw (error_message.str());
	//}

	//Finds smallest width/height - will continue if dimensions don't match
	int width = m_width;
	int height = m_height;
	if (anImage.m_height < m_height) {
		height = anImage.m_height;		
	}
	if (anImage.m_width < m_width) {
		width = anImage.m_width;
	}

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
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
    //******************************************************
    // Modify this method to write your operator-
    //******************************************************
    Image temp(m_width, m_height, 0);

	//Finds smallest width/height - will continue if dimensions don't match
	int width = m_width;
	int height = m_height;
	if (anImage.m_height < m_height) {
		height = anImage.m_height;
	}
	if (anImage.m_width < m_width) {
		width = anImage.m_width;
	}

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			temp.setPixel(i, j, getPixel(i, j) - anImage.getPixel(i, j));
		}
	}

    // Return the result
    return (temp);
}


//------------------------------------------------
Image Image::operator*(const Image& anImage) const
//------------------------------------------------
{
    //******************************************************
    // Modify this method to write your operator+
    //******************************************************
    Image temp(m_width, m_height, 0);

	//Finds smallest width/height - will continue if dimensions don't match
	int width = m_width;
	int height = m_height;
	if (anImage.m_height < m_height) {
		width = anImage.m_width;
	}
	if (anImage.m_width < m_width) {
		height = anImage.m_height;
	}

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			temp.setPixel(i, j, getPixel(i, j) * anImage.getPixel(i, j));
		}
	}


    // Return the result
    return (temp);
}


//------------------------------------------------
Image Image::operator/(const Image& anImage) const
//------------------------------------------------
{
    //******************************************************
    // Modify this method to write your operator-
    //******************************************************
    Image temp(m_width, m_height, 0);

	//Finds smallest width/height - will continue if dimensions don't match
	int width = m_width;
	int height = m_height;
	if (anImage.m_height < m_height) {
		width = anImage.m_width;
	}
	if (anImage.m_width < m_width) {
		height = anImage.m_height;
	}

	for (unsigned int i = 0; i < width; i++) {
		for (unsigned int j = 0; j < height; j++) {
			//if dividing by zero, give zero as a result
			float pix = anImage.getPixel(i, j);
			if (pix < -0.001 | pix > 0.001){ //cant use exact number for floats pix!=0
				temp.setPixel(i, j, getPixel(i, j) / pix);
			}
		}
	}

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator+(float aValue) const
//----------------------------------------
{
    //******************************************************
    // Modify this method to write your operator+
    //******************************************************
    Image temp(m_width, m_height, 0);
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			temp.setPixel(i, j, getPixel(i, j) + aValue);
		}
	}

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator-(float aValue) const
//----------------------------------------
{
    //******************************************************
    // Modify this method to write your operator-
    //******************************************************
    Image temp(m_width, m_height, 0);
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			temp.setPixel(i, j, getPixel(i, j) - aValue);
		}
	}

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator*(float aValue) const
//----------------------------------------
{
    //******************************************************
    // Modify this method to write your operator*
    //******************************************************
    Image temp(m_width, m_height, 0);
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			temp.setPixel(i, j, getPixel(i, j) * aValue);
		}
	}

    // Return the result
    return (temp);
}


//----------------------------------------
Image Image::operator/(float aValue) const
//----------------------------------------
{
    //******************************************************
    // Modify this method to write your operator/
    //******************************************************
    Image temp(m_width, m_height, 0);
	if (aValue > -0.001 & aValue < 0.001) {
		std::stringstream error_message;
		error_message << "Divide by zero error - try inputting a non-zero number";
		throw (error_message.str());
	}
	else {
		for (unsigned int i = 0; i < m_width; i++) {
			for (unsigned int j = 0; j < m_height; j++) {
				temp.setPixel(i, j, getPixel(i, j) / aValue);
			}
		}
	}
    // Return the result
    return (temp);
}


//----------------------------
Image Image::operator!() const
//----------------------------
{
    //******************************************************
    // Modify this method to write your operator!
    //******************************************************
    Image temp(m_width, m_height, 0);
	float max = getMaxValue();
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			temp.setPixel(i, j, max - getPixel(i, j));
		}
	}

    // Return the result
    return (temp);
}


//----------------------------------
double Image::getAspectRatio() const
//----------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
    double temp;
	if (m_height != 0) {
		temp = double(m_width) / double(m_height);
	}
	else {
		std::stringstream error_message;
		error_message << "Divide by zero error - couldn't work out aspect ratio as height = 0";
		throw (error_message.str());
	}

    // Return the result
    return (temp);
}


//----------------------------------
unsigned int Image::getWidth() const
//----------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************

    // Return the result
    return (m_width);
}


//-----------------------------------
unsigned int Image::getHeight() const
//-----------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************

    // Return the result
    return (m_height);
}


//------------------------------
float Image::getMinValue() const
//------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
	float temp = getPixel(0, 0); // gets first value as starting point to compare
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			if (getPixel(i, j) < temp) {
				temp = getPixel(i, j);
			}
		}
	}

    // Return the result
    return (temp);
}


//------------------------------
float Image::getMaxValue() const
//------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
    float temp = getPixel(0, 0); // gets first value as starting point to compare
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			if (getPixel(i, j) > temp) {
				temp = getPixel(i, j);
			}
		}
	}

    // Return the result
    return (temp);
}


//--------------------------
double Image::getSum() const
//--------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
    double temp = 0;
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			temp = temp + getPixel(i, j);
		}
	}

    // Return the result
    return (temp);
}


//------------------------------
double Image::getAverage() const
//------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
	double temp = 0;
	if (m_height * m_width > 0) {
		temp = getSum() / (m_height * m_width);
	}

    // Return the result
    return (temp);
}


//-------------------------------
double Image::getVariance() const
//-------------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
    
	double avg = getAverage();
	double total_diff = 0;
	for (unsigned int i = 0; i < m_width; i++) {
		for (unsigned int j = 0; j < m_height; j++) {
			total_diff = total_diff + pow(getPixel(i, j) - avg, 2);
		}
	}
	double temp = total_diff / (m_width * m_height);
    // Return the result
    return (temp);
}


//-----------------------------
double Image::getStdDev() const
//-----------------------------
{
    //******************************************************
    // Modify this method to write your code
    //******************************************************
    

    // Return the result
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
        output_file << std::max(255, int(getMaxValue())) << std::endl;

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
