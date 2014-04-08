#ifndef __RaspiCamCV__
#define __RaspiCamCV__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _RASPIVID_STATE RASPIVID_STATE;

typedef struct {
	RASPIVID_STATE * pState;
} RaspiCamCvCapture;

typedef struct _IplImage IplImage;

enum
{
	RPI_CAP_PROP_FRAME_WIDTH  = 0,
	RPI_CAP_PROP_FRAME_HEIGHT = 1,
	RPI_CAP_PROP_FPS          = 2
};

RaspiCamCvCapture * raspiCamCvCreateCameraCapture(int index);
void raspiCamCvReleaseCapture(RaspiCamCvCapture ** capture);
IplImage * raspiCamCvQueryFrame(RaspiCamCvCapture * capture);

/**
 * Set a property in the RaspiCamCvCapture.
 *
 * capture - Pointer to the capture to modify
 * property_id - Property to change. Possible property ids:
 * 	RPI_CAP_PROP_FRAME_WIDTH - Width of the frames in the stream.
 * 	RPI_CAP_PROP_FRAME_HEIGHT - Height of the frames in the stream.
 * value - Value to set the property to
 */
void raspiCamCvSetCaptureProperty(RaspiCamCvCapture * capture, int property_id,
		double value);

/**
 * Take the width and modify the capture resolution (heigth is change automatically).
 * If the width is not supported, nothing is changed.
 *
 * @param capture  the pointer to the camera
 * @param width  the new width
 */
void raspiCamCvSetCapturePropertyWidth(RaspiCamCvCapture * capture, int width);

/**
 * Take the height and modify the capture resolution (width is change automatically).
 * If the height is not supported, nothing is changed.
 *
 * @param capture  the pointer to the camera
 * @param height  the new height
 */
void raspiCamCvSetCapturePropertyHeight(RaspiCamCvCapture * capture, int height);

#ifdef __cplusplus
}
#endif

#endif
