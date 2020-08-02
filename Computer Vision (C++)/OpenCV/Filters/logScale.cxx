/**
********************************************************************************
*
*	@file		logScale.cxx
*
*	@brief		A program to display an image in the log scale.
*	            Care is given to convert the RGB image to greyscale,
*	            to float and to avoid log(0) which is undefined.
*
*	@version	1.0
*
*	@date		20/01/2020
*
*	@author		Franck Vidal
*
*
********************************************************************************
*/


//******************************************************************************
//	Includes
//******************************************************************************
#include <exception> // Header for catching exceptions
#include <iostream>  // Header to display text in the console
#include <opencv2/opencv.hpp> // Main OpenCV header


//******************************************************************************
//	Namespaces
//******************************************************************************
using namespace std;


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
	try
	{
		// No file to display
		// No file to save
		std::string error_message;
		if (argc != 3)
		{
			// Create an error message            
			error_message = "usage: ";
			error_message += argv[0];
			error_message += " <input_image> <output_image>";

			// Throw an error
			throw error_message;
		}

		string input_filename = argv[1];
		cv::Mat image = cv::imread(input_filename, CV_LOAD_IMAGE_COLOR);


		if (!image.data) {
			// Create an error message
			error_message = "couldn't open or find image ";
			error_message += input_filename;

			// Throw an error
			throw error_message;
		}

		string window_title;
		window_title = "Display Image ";
		window_title += input_filename;

		cv::namedWindow(window_title, cv::WINDOW_AUTOSIZE);
		cv::imshow(window_title, image);

		cv::Mat grey_image;
		cv::cvtColor(image, grey_image, CV_RGB2GRAY);

		cv::Mat float_image;
		grey_image.convertTo(float_image, CV_32FC1);

		cv::Mat log_image;
		cv::log(float_image + 1.0, log_image);
		
		cv::Mat normalised_image;
		cv::normalize(log_image, normalised_image, 0, 255, cv::NORM_MINMAX, CV_8UC1);

		window_title = "Display Log Image ";
		window_title += input_filename;
		cv::namedWindow(window_title, cv::WINDOW_AUTOSIZE);
		cv::imshow(window_title, normalised_image);

		if (!cv::imwrite(argv[2], normalised_image)) {
			error_message = "Couldn't write image ";
			error_message += argv[2];
			throw(error_message);
		}


		cv::waitKey(0);


    }
    // An error occured
    catch (const std::exception& error)
    {
        // Display an error message in the console
        cerr << error.what() << endl;
    }
    catch (const std::string& error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }
    catch (const char* error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }

	// Do not close the prompt window
#if defined(WIN32) && defined(_DEBUG)
	system("pause");
#endif

    // Exit the program
    return 0;
}

