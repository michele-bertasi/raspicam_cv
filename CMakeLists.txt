CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT("RaspiCamCV" C)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CROSS_COMPILE true)
else()
    set(CROSS_COMPILE false)
endif()

macro(ADD_PREFIX LIST_NAME PREFIX)
    set(${LIST_NAME}_RESULT)
    foreach(ELEMENT ${${LIST_NAME}})
        list(APPEND ${LIST_NAME}_RESULT ${PREFIX}${ELEMENT})
    endforeach()
    set(${LIST_NAME} "${${LIST_NAME}_RESULT}")
    unset(${LIST_NAME}_RESULT})
endmacro()

# userland
set(USERLAND_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../userland CACHE PATH "The userland directory")

set(USERLAND_INCLUDE_DIRS
    ${USERLAND_DIR}
    ${USERLAND_DIR}/host_applications/linux/libs/bcm_host/include
	${USERLAND_DIR}/host_applications/linux/apps/raspicam
	${USERLAND_DIR}/interface/vcos/pthreads
	${USERLAND_DIR}/interface/vmcs_host/linux
	${USERLAND_DIR}/interface/mmal)

set(USERLAND_LIBRARY_DIRS ${USERLAND_DIR}/build/lib)
set(USERLAND_LIBRARIES mmal_core mmal mmal_util vcos bcm_host)

set(USERLAND_RASPICAM_SRC RaspiCamControl.c
    RaspiCLI.c RaspiPreview.c
    RaspiStillYUV.c RaspiVid.c tga.c)
ADD_PREFIX(USERLAND_RASPICAM_SRC ${USERLAND_DIR}/host_applications/linux/apps/raspicam/)

# opencv
set(OpenCV_LIBS opencv_core opencv_imgproc)

link_directories(${USERLAND_LIBRARY_DIRS})
include_directories(. ${USERLAND_INCLUDE_DIRS})

add_library(raspicamcv STATIC RaspiCamCV.c ${USERLAND_RASPICAM_SRC})
target_link_libraries(raspicamcv ${USERLAND_LIBRARIES} ${OpenCV_LIBS})
