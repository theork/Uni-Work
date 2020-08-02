/**
********************************************************************************
*
*   @file       test.cpp
*
*   @brief      tests the functionality of the new methods and 
*				compares with values found in Matlab/FUJI
*
*   @version    1.0
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
#include <sstream>
#include <iostream>
#include <exception>
#include <cmath>
#include <new>       // Header file for std::bad_alloc
#include <stdexcept> // Header file for std::out_of_range
#include <random>    // To add noise to images

#include "Image.h"


//******************************************************************************
//  Function definitions
//******************************************************************************


//------------------------------------------
inline float relativeDifference(float v0,
                                float v1,
                                float range)
//------------------------------------------
{
    return (std::abs(v0 - v1) / range);
}


//--------------------------------------------
Image addSaltPepperNoise(const Image& anImage,
		                 float aMinValue,
						 float aMaxValue)
//--------------------------------------------
{
	// Copy the input image into the output image
	Image temp = anImage;

	// Initialise the pseudo-random number generator
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Use a normal distribution with mean = 0, std dev = 2
    std::normal_distribution<> d{0, 2};

    // Process every pixel of the output
	for (unsigned int j = 0; j < temp.getHeight(); ++j)
	{
		for (unsigned int i = 0; i < temp.getWidth(); ++i)
		{
			// Get a random number
			float rand_number = d(gen);

			// If it is low, replace the pixel value by pepper
			if (rand_number <= -3.5)
			{
				temp(i, j) = aMinValue;
			}
			// Else if it is high, replace the pixel value by salt
			else if (rand_number >= 3.5)
			{
				temp(i, j) = aMaxValue;
			}
			// Else keep the pixel as it is
		}
	}

	// Return the noisy image
	return (temp);
}


//-----------------------------------------
Image addPoissonNoise(const Image& anImage)
//-----------------------------------------
{
	// Copy the input image into the output image
	Image temp = anImage;

	// Initialise the pseudo-random number generator
    std::random_device rd{};
    std::mt19937 gen{rd()};

    // Process every pixel of the output
	for (unsigned int j = 0; j < temp.getHeight(); ++j)
	{
		for (unsigned int i = 0; i < temp.getWidth(); ++i)
		{
		    // Use a Poisson distribution based on the pixel's value
		    std::poisson_distribution<> d(temp(i, j));
			float rand_number = d(gen);

			// Replace the pixel value by the random number
			temp(i, j) = rand_number;
		}
	}

	// Return the noisy image
	return (temp);
}

bool isEqual(double  a, double  b, double  epsilon = 0.00001) {
	if (a == b) return true;
	double  abs_a = abs(a);
	double  abs_b = abs(b);
	double  abs_diff = abs(a - b);

	if (a == 0 || b == 0 || (abs_a + abs_b < std::numeric_limits<float>::min()))
		return abs_diff < std::numeric_limits<float>::min();
	else
		return ((abs_diff / std::min(abs_a, abs_b) < epsilon));

}


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    // Return code
    int error_code(0);

    // Catch exceptions
    try
    {
    	// Create an empty
    	Image empty_image;

        // Load an image
        Image input_1, input_2; // Create an empty image
        input_1.loadPGM("../test_image.pgm"); // Load a PGM file
		input_2.loadPGM("../lena.ascii2.pgm");
        //input_1.normalise(); // Pixels are in the range [0, 1]
        //(255 * input_1).saveBMP("test_save_image.bmp"); // Save the image in a BMP file


		double dbl_result;
		Image inputx4 = (input_1 * 4) + 15;
		Image inputnotx4 = !(input_1 * 4) + 15;
		//input_1.saveASCII("../test_image.txt");
		//inputx4.savePGM("../test_image_x4.pgm");
		//inputnotx4.savePGM("../test_image_notx4.pgm");
		//inputx4.saveASCII("../test_image_x4.txt");
		//inputnotx4.saveASCII("../test_image_notx4.txt");

		// Testing values are taken from matlab (testing.m)
        // Test SAE
		std::cout << "******TESTING SAE******" << std::endl;		
		dbl_result = input_1.computeSAE(empty_image);
		std::cout << "SAE of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, FLT_MAX, 1) ? "OK":"NOT OK") << std::endl;
		dbl_result = input_1.computeSAE(input_1);
		std::cout << "SAE of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeSAE(inputx4);
		std::cout << "SAE of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 1.5342e+09, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeSAE(inputnotx4);
		std::cout << "SAE of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, 652735270, 1) ? "OK" : "NOT OK") << std::endl;
		
        // Test MAE
		std::cout << "******TESTING MAE******" << std::endl;
		dbl_result = input_1.computeMAE(empty_image); 
		std::cout << "MAE of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, FLT_MAX, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMAE(input_1); 
		std::cout << "MAE of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMAE(inputx4);
		std::cout << "MAE of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 705.3785) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMAE(inputnotx4);
		std::cout << "MAE of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, 300.1137) ? "OK" : "NOT OK") << std::endl;

        // Test SSE
		std::cout << "******TESTING SSE******" << std::endl;
		dbl_result = input_1.computeSSE(empty_image); 
		std::cout << "SSE of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, FLT_MAX, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeSSE(input_1); 
		std::cout << "SSE of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeSSE(inputx4);
		std::cout << "SSE of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 1.1721e+12, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeSSE(inputnotx4); 
		std::cout << "SSE of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, 2.7878e+11, 1) ? "OK" : "NOT OK") << std::endl;

        // Test MSE
		std::cout << "******TESTING MSE******" << std::endl;
		dbl_result = input_1.computeMSE(empty_image);
		std::cout << "MSE of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, FLT_MAX, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMSE(input_1);
		std::cout << "MSE of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMSE(inputx4);
		std::cout << "MSE of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 5.3889e+05, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeMSE(inputnotx4);
		std::cout << "MSE of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, 1.2818e+05, 1) ? "OK" : "NOT OK") << std::endl;

        // Test RMSE
		std::cout << "******TESTING RMSE******" << std::endl;
		dbl_result = input_1.computeRMSE(empty_image);
		std::cout << "RMSE of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, FLT_MAX, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeRMSE(input_1);
		std::cout << "RMSE of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeRMSE(inputx4);
		std::cout << "RMSE of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 734.0908)  ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeRMSE(inputnotx4);
		std::cout << "RMSE of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, 358.0185) ? "OK" : "NOT OK") << std::endl;

        // Test NCC
		std::cout << "******TESTING NCC******" << std::endl;
		dbl_result = input_1.computeNCC(empty_image); // // Should be 0.0
		std::cout << "NCC of empty image: " << dbl_result << "\t" << (isEqual(dbl_result, 0) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeNCC(input_1); // Should be 1
		std::cout << "NCC of same image: " << dbl_result << "\t" << (isEqual(dbl_result, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeNCC(inputx4);  // Should be 1
		std::cout << "NCC of 4x original: " << dbl_result << "\t" << (isEqual(dbl_result, 1) ? "OK" : "NOT OK") << std::endl;
		dbl_result = input_1.computeNCC(inputnotx4); // Should be -1
		std::cout << "NCC of 4x original inverted: " << dbl_result << "\t" << (isEqual(dbl_result, -1) ? "OK" : "NOT OK") << std::endl;


        // Test threshold(float aThreshold)
		std::cout << "******TESTING THRESHOLDING******" << std::endl;
		Image im_result;
		im_result = input_1.threshold(230);
		im_result.saveASCII("../Results/threshold1.txt");
		dbl_result = im_result.getSum();
		std::cout << "Sum of threshold: " << dbl_result << "\t" << (isEqual(dbl_result, 1884416) ? "OK" : "NOT OK") << std::endl;

        // Test threshold(float aLowerThreshold, float aUpperThreshold)
		im_result = input_1.threshold(100, 200);
		im_result.saveASCII("../Results/threshold2.txt");
		dbl_result = im_result.getSum();
		std::cout << "Sum of threshold: " << dbl_result << "\t" << (isEqual(dbl_result, 93547) ? "OK" : "NOT OK") << std::endl;

		std::cout << "******TESTING AND SAVING CONVOLUTIONS******" << std::endl;
        // Test meanFilter()
		std::cout << "mean filter... ";
		im_result = input_2.meanFilter();
		im_result.saveASCII("../Results/MeanFilter.txt");

		im_result = input_2.meanFilter(9);
		im_result.saveASCII("../Results/MeanFilter9.txt");

        // Test gaussianFilter()
		std::cout << "gaussian filter... ";
		im_result = input_2.gaussianFilter();
		im_result.saveASCII("../Results/GaussianFilter.txt");

        // Test laplacianFilter()
		std::cout << "laplacian filter... ";
		im_result = input_2.laplacianFilter();
		im_result.saveASCII("../Results/LaplacianFilter.txt");

		im_result = input_2.laplacianFilter(9);
		im_result.saveASCII("../Results/LaplacianFilter9.txt");

        // Test sobelXOperator()
		std::cout << "sobel-X filter... ";
		im_result = input_2.sobelXOperator();
		im_result.saveASCII("../Results/SobelXOperator.txt");

        // Test sobelYOperator()
		std::cout << "sobel-Y filter... ";
		im_result = input_2.sobelYOperator();
		im_result.saveASCII("../Results/SobelYOperator.txt");

        // Test gradientMagnitude()
		std::cout << "gradient Magnitude... ";
		im_result = input_2.gradientMagnitude();
		im_result.saveASCII("../Results/GradientMagnitude.txt");

        // Test sharpenFilter(double alpha)
		std::cout << "sharpen filter... ";
		im_result = input_2.sharpenFilter(5);
		im_result.saveASCII("../Results/sharpenFilter.txt");

        // Do not forget to preserve the dynamic range
        // i.e. the min/max pixel values of the output MUST BE the same as the ones of the input
        // Implement the method:
        // Image Image::clamp(float aLowerThreshold, float aUpperThreshold) const
        //Image sharpened = input_1.sharpenFilter(3);
        //sharpened = sharpened.clamp(input_1.getMinValue(), input_1.getMaxValue());
        //(255 * sharpened).saveBMP("test_meanFilter.bmp"); // Save the image in a BMP file
    }
    // An error occured
    catch (const std::bad_alloc& error)
    {
        error_code = 1;
        std::cerr << "Out of Memory error: " << error.what() << std::endl;
    }
    catch (const std::out_of_range& error)
    {
        error_code = 1;
        std::cerr << "Out of Range error: " << error.what() << std::endl;
    }
    catch (const std::exception& error)
    {
        error_code = 1;
        std::cerr << error.what() << std::endl;
    }
    catch (const std::string& error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (const char* error)
    {
        error_code = 1;
        std::cerr << error << std::endl;
    }
    catch (...)
    {
        error_code = 1;
        std::cerr << "Unknown error" << std::endl;
    }

#ifdef _DEBUG
#ifdef WIN32
    system("pause");
#endif
#endif

    return (error_code);
}
