/**
********************************************************************************
*
*    @file      videoFromFile.cxx
*
*    @brief     A simple program using OpenCV to display a video and
*               perform some image processing tasks.
*
*    @version   1.0
*
*    @date      05/02/2020
*
*    @author    Franck Vidal
*
*
********************************************************************************
*/


//******************************************************************************
//    Includes
//******************************************************************************
#include <exception> // Header for catching exceptions
#include <iostream>  // Header to display text in the console
#include <sstream>   // Header to display error messages
#include <string>    // Header to manipulate strings
#include <cmath>     // Header use round()

#include <opencv2/opencv.hpp> // Main OpenCV header


//******************************************************************************
//    Namespaces
//******************************************************************************
using namespace std;


//******************************************************************************
//    Global variables
//******************************************************************************
const double EPSILON(1.0e-5);

const int g_edge = 5; // Edge around the images in the window

cv::Mat g_current_frame; // Store the current frame
cv::Mat g_edge_frame;    // Store the edges detected in the current frame
cv::Mat g_displayed_image; // The image displayed in the window

						   // The title of every window
std::string g_window_title("Video");


//******************************************************************************
//    Function declaration
//******************************************************************************
void cartoonise(int, void*);


//******************************************************************************
//    Implementation
//******************************************************************************


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
	try
	{
		/**********************************************************************/
		/* Declare some local variables                                       */
		/**********************************************************************/

		// File names
		std::string output_file_name;


		/**********************************************************************/
		/* Process the command line arguments                                 */
		/**********************************************************************/

		// No file to display
		if (argc != 3 && argc != 4)
		{
			// Create an error message
			std::string error_message;
			error_message = "Usage: ";
			error_message += argv[0];
			error_message += " <input_video>";
			error_message += " <scaling_factor>";
			error_message += " [output_video]";

			error_message += "\n\tExample: ";
			error_message += argv[0];
			error_message += " SAMPLING.AVI";
			error_message += " 0.25";
			error_message += " test.avi";

			// Throw an error
			throw error_message;
		}


		// Get the file names

		double scaling_factor = atof(argv[1]);

		if (scaling_factor < EPSILON)
		{
			std::stringstream error_message;
			error_message << "The scaling factor either negative or null (" << scaling_factor << ")";
			throw error_message.str();
		}

		// An output file name has been specified
		if (argc == 3)
		{
			output_file_name = argv[2];
		}



		/**********************************************************************/
		/* Open the video                                                     */
		/**********************************************************************/

		// Open the video file
		cv::VideoCapture video_capture(0); // !@� YOUR CODE HERE �@!

														 // The image has not been loaded
		if (!video_capture.isOpened())
		{
			std::string error_message;
			error_message = "Error, could not open video ";
		}

		// Read the frame rate of the video (does not always work)
		double fps = 15; // !@� YOUR CODE HERE �@!
		cout << "Frame per seconds : " << fps << endl;

		// Convert in seconds per frame (default 30 ms / frame)
		double seconds_per_frame(1.0 / fps);

		// Convert in milliseconds
		int milliseconds_per_frame(round(seconds_per_frame * 1000.0));

		// Get the video size
		cv::Size input_video_size(video_capture.get(CV_CAP_PROP_FRAME_WIDTH),
			video_capture.get(CV_CAP_PROP_FRAME_HEIGHT)); // !@� YOUR CODE HERE �@!

														  // Apply the scaling factor
		cv::Size scaled_video_size(input_video_size.width * scaling_factor,
			input_video_size.height * scaling_factor); // !@� YOUR CODE HERE �@!

													   // Set the size of the image displayed in the window
		cv::Size target_video_size(g_edge * 3 + 2 * scaled_video_size.width,
			g_edge * 2 + scaled_video_size.height); // !@� YOUR CODE HERE �@!

													// Create the output image
													// !@� YOUR CODE HERE �@!
		g_displayed_image = cv::Mat(target_video_size.height, target_video_size.width,
			CV_8UC3, cv::Scalar(128, 128, 128));


		/**********************************************************************/
		/* File writer                                                        */
		/**********************************************************************/
		cv::VideoWriter video_writer;

		// Open the output
		if (output_file_name.size())
		{
			// !@� YOUR CODE HERE �@!
			//int input_codec = video_capture.get(CV_CAP_PROP_FOURCC);
			//video_writer.open(output_file_name, input_codec, fps,
			//	target_video_size, true);

			//if (!video_writer.isOpened()) {
				video_writer.open(output_file_name, CV_FOURCC('M', 'J', ' P', 'G'),
					fps, target_video_size, true);
				if (!video_writer.isOpened()) {
					std::cerr << "Cannot create output video" << std::endl;
				}
			//}
		}


		/**********************************************************************/
		/* Create the window                                                 */
		/**********************************************************************/

		// Create the window
		cv::namedWindow(g_window_title, cv::WINDOW_AUTOSIZE);


		/**********************************************************************/
		/* Event loop                                                         */
		/**********************************************************************/

		// Last key pressed
		int key;
		bool input_stream_status(true);
		// Event loop
		do
		{
			// Grab the next frame if possible
			// If an error occured, throw an error
			if (!video_capture.read(g_current_frame))
			{
				// Throw an error
				throw "Could not read frames from the video.";
			}

			if (input_stream_status) {
				// Resize the input if needed
				if (input_video_size != scaled_video_size)
				{
					cv::resize(g_current_frame, g_current_frame, scaled_video_size);
				}

				// Process the image
				cartoonise(0, 0);

				// The file writer is working
				if (video_writer.isOpened())
				{
					input_stream_status = video_capture.read(g_current_frame);
					video_writer.write(g_displayed_image);
				}
			}
			// Wait for the key press event for X ms
			// (with X equal to 'milliseconds_per_frame')
			key = cv::waitKey(milliseconds_per_frame);

		}
		// Stop the loop if 'q' or 'Escape' have been pressed
		while (key != 'q' && key != 27);
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

#ifdef _DEBUG
#ifdef WIN32
	system("pause");
#endif
#endif

	// Exit the program
	return 0;
}


//-------------------------
void cartoonise(int, void*)
//-------------------------
{
	// Copy the current frame into the large image (g_displayed_image).
	// Add an edge of g_edge pixels around g_current_frame.
	// !@� YOUR CODE HERE �@!
	cv::Mat targetROI;
	targetROI = g_displayed_image(cv::Rect(g_edge, g_edge, g_current_frame.cols,
		g_current_frame.rows));
	g_current_frame.copyTo(targetROI);

	// Convert the image (g_current_frame) to greyscale.
	// Save the resulting image in greyscale_frame.
	cv::Mat greyscale_frame;
	// !@� YOUR CODE HERE �@!
	cv::cvtColor(g_current_frame, greyscale_frame, CV_RGB2GRAY);

	// Apply a median filter on greyscale_frame with a size of 7 pixels.
	// Save the resulting image in median_frame.
	cv::Mat median_frame;
	// !@� YOUR CODE HERE �@!
	cv::medianBlur(greyscale_frame, median_frame, 7);

	// Perform a Laplacian filter on median_frame
	// You must use unsigned char for the output, i.e. the depth is CV_8U
	// The kernel size is 5x5
	// Save the resulting image in edge_frame.
	cv::Mat edge_frame;
	// !@� YOUR CODE HERE �@!
	cv::Laplacian(median_frame, edge_frame, CV_8U, 5);

	// Perform an edge detection using edge_frame and the threshold function.
	// The threshold is 100, the maximum value is 255, and the thresholding type is THRES_BINARY_INV (or 1).
	// Save the resulting image in mask_frame.
	cv::Mat mask_frame;
	// !@� YOUR CODE HERE �@!
	cv::threshold(edge_frame, mask_frame, 100, 255, CV_THRESH_BINARY_INV);

	// Reduce the input image (g_current_frame) size by a factor 10 and resample using pixel area relation.
	// Save the resulting image in small_frame.
	float ds_factor = 4;
	cv::Mat small_frame;
	// !@� YOUR CODE HERE �@!
	cv::resize(g_current_frame, small_frame, cv::Size(0, 0), 1.0 / ds_factor,
		1.0 / ds_factor, cv::INTER_AREA);

	// Apply a bilateral filter 10 times. The kernel size is 5, sigma colour is 5, and sigma space is 7.
	// Save the resulting image in small_frame.
	// !@� YOUR CODE HERE �@!
	for (int i = 0; i < 10; ++i) {
		cv::Mat temp;
		cv::bilateralFilter(small_frame, temp, 5, 5, 7);
		small_frame = temp;
	}

	// Restore the of the image (small_frame) so that it is the same as the input image (g_current_frame) and resample using bi-linear interpolation.
	// Save the resulting image in output_frame.
	cv::Mat output_frame;
	// !@� YOUR CODE HERE �@!
	cv::resize(small_frame, output_frame, cv::Size(0, 0), ds_factor, ds_factor, CV_INTER_LINEAR);

	// Add a thick boundary using a boolean operator (AND).
	// Save the resulting image in cartoon_frame.
	cv::Mat cartoon_frame;
	// !@� YOUR CODE HERE �@!
	cv::bitwise_and(output_frame, output_frame, cartoon_frame, mask_frame);

	// Copy the result
	// !@� YOUR CODE HERE �@!
	targetROI = g_displayed_image(cv::Rect(g_edge * 2 + g_current_frame.cols, g_edge, cartoon_frame.cols,
		cartoon_frame.rows));
	cartoon_frame.copyTo(targetROI);

	// Display the images
	// !@� YOUR CODE HERE �@!
	cv::imshow(g_window_title, g_displayed_image);
}
