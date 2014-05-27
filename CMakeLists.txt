CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("RaspiCamCV" C)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CROSS_COMPILE true)
else()
    set(CROSS_COMPILE false)
endif()

# userland
set(USERLAND_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../userland CACHE PATH "The userland directory")

set(USERLAND_INCLUDE_DIRS
    ${USERLAND_DIR}
    ${USERLAND_DIR}/host_applications/linux/libs/bcm_host/include
	${USERLAND_DIR}/host_applications/linux/apps/raspicam
	${USERLAND_DIR}/interface/vcos/pthreads
	${USERLAND_DIR}/interface/vmcs_host/linux
	${USERLAND_DIR}/interface/mmal
	${USERLAND_DIR}/build/inc
	${USERLAND_DIR}/build/inc/interface/vcos)

set(USERLAND_LIBRARY_DIRS ${USERLAND_DIR}/build/lib)
set(USERLAND_LIBRARIES mmal_core mmal mmal_util vcos bcm_host)

# opencv
set(OpenCV_LIBS
    opencv_core opencv_legacy opencv_video opencv_features2d
    opencv_calib3d opencv_imgproc)

# others
set(X11_LIBS X11 Xext)
set(CRT_LIBS rt pthread m)

link_directories(${USERLAND_LIBRARY_DIRS})
include_directories(. ${USERLAND_INCLUDE_DIRS})

add_library(raspicamcv STATIC RaspiCamCV.c)
target_link_libraries(raspicamcv
    ${USERLAND_LIBRARIES} ${OpenCV_LIBS} ${X11_LIBS} ${CRT_LIBS})
