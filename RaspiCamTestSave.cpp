/**
 * @author: jenselme@jujens.eu
 *
 * This program takes the number of pictures give as a parameter after
 * -n (1 by default) and saves them in the directory given after -o (the
 * current directory by default). It is useful if you don't have X on
 * your Raspberry Pi.
 */


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "RaspiCamCV.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
  int number_pictures_take = 1;
  std::string location = "";

  //Parse arguments
  if ( argc > 1 )
    {
      if( (std::string)argv[1] == "-o" )
	location = (std::string)argv[2];
      else if ( (std::string)argv[1] == "-n" )
	number_pictures_take = atoi( argv[2] );
      if ( argc > 3 )
        {
	  if( (std::string)argv[3] == "-o" )
	    location = (std::string)argv[4];
	  else if ( (std::string)argv[3] == "-n" )
	    number_pictures_take = atoi( argv[4] );
        }
    }
  // Initialize the camera
  RaspiCamCvCapture * camera = raspiCamCvCreateCameraCapture(0);

  std::string save_name = "";
  for ( int i = 0; i < number_pictures_take; i++ )
    {
      // Capture a picture
      cv::Mat image( raspiCamCvQueryFrame(camera) );
      // Save the picture
      save_name = location + "picture" + std::to_string(i) + ".jpeg";
      cv::imwrite( save_name, image );
      std::cout << "Saved: " << save_name << std::endl;
    }
  return 0;
}
