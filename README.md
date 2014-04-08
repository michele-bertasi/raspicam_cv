RaspiCamCV
===========
Clone from https://github.com/erget/robidouille which was forked from:
https://github.com/robidouille/robidouille.

More info about the original RaspiCamCV:
* Website: http://www.robidouille.com
* Google+: https://www.google.com/+Robidouille

I modify it to fit my needs:
* Modify compilation flags so it compiles on Archarm
* Add another test program to test the camera without X
* Modify the way the camera's properties are handled

# To compile

## First make sure you have cmake and git installed

`sudo apt-get install cmake git`

You might also need gcc/g++ in case it's not already installed, along with some other libraries:
`sudo apt-get install gcc g++ libx11-dev libxt-dev libxext-dev libgraphicsmagick1-dev libcv-dev libhighgui-dev`


## You need the raspberry pi userland libraries:

```shell
mkdir -p ~/git/raspberrypi
cd ~/git/raspberrypi
git clone https://github.com/raspberrypi/userland.git
cd userland
./buildme
```


## To build the raspicam library
```shell
mkdir -p ~/git
cd ~/git
git clone https://github.com/robidouille/robidouille.git
cd robidouille/raspicam_cv
mkdir objs
make
```

This will create:
* libraspicamcv.a: the raspberry cam library which provides an opencv like interface
* raspicamtest: a small test app which uses the library


## To use it in your own project:

Fellow the steps below:

1. add the include path: `-I$(HOME)/git/robidouille/raspicam_cv`
2. link with the raspicamcv library: `-L$(HOME)/git/robidouille/raspicam_cv -lraspicamcv`
3. link with the userland libraries: `-L$(HOME)/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host`

In your code add a `#include "RaspiCamCV.h"`, and replace:
* cvCreateCameraCapture -> raspiCamCvCreateCameraCapture (function is analog to
cvCreateCameraCapture and delivers pictures in 640x480 resolution)
* cvQueryFrame -> raspiCamCvQueryFrame
* CvCapture -> RaspiCamCvCapture

If you want to set the capture's resolution manually, use
raspiCamCvSetCaptureProperty. Otherwise the querying the frame will return an
image in the camera's native resolution (2592x1944 px).

# Credits
RaspiCamCV.c/h is the library source.
It's converted from camcv_vid0.c from Pierre Raufast.
https://thinkrpi.wordpress.com/2013/05/22/opencv-and-camera-board-csi/
https://thinkrpi.wordpress.com/
