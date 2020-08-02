/**
********************************************************************************
*
*   @file       test.cpp
*
*   @brief      Tests the Image.cpp program
*
*   @version    1.0
*
*   @date       13/11/19
*
*   @author     Theo Rook EEUB22
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

#include "Image.h"

//------------------------------------------
inline float relativeDifference(float v0,
                                float v1,
                                float range)
//------------------------------------------
{
    return (std::abs(v0 - v1) / range);
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

        // Load an image
        Image input_1; // Create an empty image
        input_1.loadPGM("../test_image.pgm"); // Load a PGM file

        // or
        //input_1.loadASCII("../test_image.txt"); // Load an ASCII file

        //input_1.savePGM("test_save_image.pgm"); // Save the image in a PGM file
        //input_1.saveASCII("test_save_image.txt"); // Save the image in an ASCII file (can be used in Matlab, Python, ImageJ and Fiji)

        // Image statistics from Fiji/Matlab
        float min_val_in_fiji          = 0;
        float max_val_in_fiji          = 255;
        float mean_val_in_fiji         = 230.126;
        float std_dev_val_in_fiji      = 67.766;
        float variance_val_in_fiji = std_dev_val_in_fiji * std_dev_val_in_fiji;
			   		
        // Image statistics from our image class
        float min_val_in_class      = input_1.getMinValue();
        float max_val_in_class      = input_1.getMaxValue();
        float range_val_in_class    = max_val_in_class - min_val_in_class;
        float mean_val_in_class     = input_1.getMean();
        float std_dev_val_in_class  = input_1.getStdDev();
        float variance_val_in_class = input_1.getVariance();

        // Relative difference between values computed with Fiji/Matlab and our image class
        // in percentage, 0 means 0%, 0.01 means 1%, and 1 means 100%
        // A difference less than 5% is good.
        float relative_difference_min  = relativeDifference(    min_val_in_fiji,      min_val_in_class, range_val_in_class);
        float relative_difference_max  = relativeDifference(    max_val_in_fiji,      max_val_in_class, range_val_in_class);
        float relative_difference_mean = relativeDifference(   mean_val_in_fiji,     mean_val_in_class, range_val_in_class);
        float relative_difference_var = relativeDifference(variance_val_in_fiji, variance_val_in_class, range_val_in_class);
        float relative_difference_std = relativeDifference( std_dev_val_in_fiji,  std_dev_val_in_class, range_val_in_class);

        // Print image statistics in the console
        std::cout << "Min: "      << min_val_in_class      << "\t" <<
            (relative_difference_min  < 0.05? "OK" : "Not OK") << std::endl;

        std::cout << "Max: "      << max_val_in_class      << "\t" <<
            (relative_difference_max  < 0.05? "OK" : "Not OK") << std::endl;

        std::cout << "Mean: "     << mean_val_in_class     << "\t" <<
            (relative_difference_mean < 0.05? "OK" : "Not OK") << std::endl;

        std::cout << "Variance: " << variance_val_in_class << "\t" <<
            (relative_difference_var  < 0.05? "OK" : "Not OK") << std::endl;

        std::cout << "Std dev: "  << std_dev_val_in_class  << "\t" <<
            ( relative_difference_std < 0.05? "OK" : "Not OK") << std::endl;

        //******************************************************
        // Add a lot more testing below to test other methods
        //******************************************************
	
		// testing get/set pixel
		float first_val = input_1.getPixel(0, 0);		
		std::cout << "Test getPixel() at (0, 0) = " << first_val << std::endl;
		input_1.setPixel(0, 0, 50.0);
		float updated_first = input_1.getPixel(0, 0);
		std::cout << "Test setPixel() at (0, 0) to 50: " << updated_first << "\t" << (relativeDifference(50.0, updated_first, range_val_in_class) < 0.05 ? "OK" : "Not Ok") << std::endl;

		//testing more image statistics
		unsigned int i1_height = input_1.getHeight();
		unsigned int i1_width = input_1.getWidth();
		std::cout << "Height: " << i1_height << std::endl;
		std::cout << "Width:  " << i1_width << std::endl;
		float actual_ratio = 1.4145;
		float calculated_ratio = input_1.getAspectRatio();
		std::cout << "Aspect Ratio: " << calculated_ratio << "\t" << (relativeDifference(actual_ratio, calculated_ratio, 2) < 0.05 ? "OK" : "Not Ok") <<  std::endl;

		//testing assignment
		std::cout << std::endl << "Testing assignment operator" << std::endl;
		Image assignment_test;
		assignment_test = input_1;
		std::cout << (assignment_test == input_1 ? "OK" : "Not OK") << std::endl;

		//testing operators by value
		std::cout << std::endl << "Testing operators by value" << std::endl;
		Image result(i1_width, i1_height, 0);		
		result = input_1 + 50;
		std::cout << "Adding 50 to all values" << std::endl;
		float addition_average = result.getAverage();
		std::cout << "Average: " << addition_average << "\t" <<
			(relativeDifference(mean_val_in_fiji + 50, addition_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		result = input_1 - 50;
		std::cout << "Taking 50 from all values" << std::endl;
		float minus_average = result.getAverage();
		std::cout << "Average: " << minus_average << "\t" <<
			(relativeDifference(mean_val_in_fiji - 50, minus_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "OK" : "Not Ok") << std::endl;

		result = input_1 * 0.5;
		std::cout << "Multiplying all values by 0.5" << std::endl;
		float multiply_average = result.getAverage();
		std::cout << "Average: " << multiply_average << "\t" << 
			(relativeDifference(mean_val_in_fiji * 0.5, multiply_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		result = input_1 / 5;
		std::cout << "Dividing all values by 5" << std::endl;
		float divide_average = result.getAverage();
		std::cout << "Average: " << divide_average << "\t" <<
			(relativeDifference(mean_val_in_fiji / 5, divide_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "OK" : "Not OK") << std::endl;

		//testing operators by image
		std::cout << std::endl << "Testing operators by image" << std::endl;
		Image operate_by(i1_width, i1_height, 100);
		result = input_1 + operate_by;
		std::cout << "Adding 100 to all values" << std::endl;
		float addition_image_average = result.getAverage();
		std::cout << "Average: " << addition_image_average << "\t" <<
			(relativeDifference(mean_val_in_fiji + 100, addition_image_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		result = input_1 - operate_by;
		std::cout << "Taking 100 to all values" << std::endl;
		float minus_image_average = result.getAverage();
		std::cout << "Average: " << minus_image_average << "\t" <<
			(relativeDifference(mean_val_in_fiji - 100, minus_image_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		result = input_1 * operate_by;
		std::cout << "Multiplying all values by 100" << std::endl;
		float multiply_image_average = result.getAverage();
		std::cout << "Average: " << multiply_image_average << "\t" <<
			(relativeDifference(mean_val_in_fiji * 100, multiply_image_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		result = input_1 / operate_by;
		std::cout << "Dividing all values by 100" << std::endl;
		float divide_image_average = result.getAverage();
		std::cout << "Average: " << divide_image_average << "\t" <<
			(relativeDifference(mean_val_in_fiji / 100, divide_image_average, result.getMaxValue() - result.getMinValue()) < 0.05 ? "Ok" : "Not Ok") << std::endl;

		//testing error checking
		std::cout << std::endl << "Checking values that should throw error" << std::endl;

		std::cout << "Dividing by 0" << std::endl;
		try {
			result = input_1 / 0;
		}
		catch (std::string& e){
			std::cout << "OK" << std::endl;
		}
		


		std::cout << "Dividing by image of 0" << std::endl;
		Image zeros(i1_width, i1_height, 0);
		result = input_1 / zeros;
		float divide_by_0_image = result.getSum();
		std::cout << "Sum: " << divide_by_0_image << "\t" << ((divide_by_0_image > -0.01) & (divide_by_0_image < 0.01) ? "Ok" : "Not Ok" ) << std::endl;

		try {
			std::cout << input_1.getPixel(-1, -1);
		}
		catch (std::string& e){
			std::cout << "OK" << std::endl;
		}

		try {
			std::cout << input_1.getPixel(i1_height, i1_width+1);
		}
		catch (std::string& e) {
			std::cout << "OK" << std::endl;
		}

		//testing other methods - see saved image for results
		std::cout << std::endl << "Saving images... may take a bit of time" << std::endl;
		result = !input_1;
		result.savePGM("../Results/negative.pgm");


		Image bright_image, dark_image;
		bright_image.loadPGM("../bright_image.pgm");
		dark_image.loadPGM("../dark_image.pgm");
		result = blending(0.5, dark_image,bright_image);
		result.savePGM("../Results/blend.pgm");

		Image ml_foreground, ml_background, ml_mask;
		ml_foreground.loadPGM("../grey_mona_lisa_foreground.pgm");
		ml_background.loadPGM("../grey_mona_lisa_background.pgm");
		ml_mask.loadPGM("../mona_lisa_foreground_mask.pgm");
		ml_mask.normalise();
		result = mattingAndCompositing(ml_background, ml_foreground, ml_mask);
		result.savePGM("../Results/matting-compositing.pgm");

		std::cout << "Saved to ../Results folder" << std::endl;

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
