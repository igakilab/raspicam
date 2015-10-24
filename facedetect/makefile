facedetect_raspicam : facedetect_raspicam.cpp 
	g++ `pkg-config --cflags opencv` -o facedetect_raspicam facedetect_raspicam.cpp `pkg-config --libs opencv` -L . libraspicamcv.a -L ~/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -lmmal_util -lvcos -lbcm_host

DEPLOY_PATH = ~/facedetect/
deploy : facedetect_raspicam
	cp facedetect_raspicam $(DEPLOY_PATH)

