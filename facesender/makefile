facedetect_raspicam : facedetect_raspicam.cpp sendhr.c sendhr.h
	g++ `pkg-config --cflags opencv` -o facedetect_raspicam facedetect_raspicam.cpp sendhr.c `pkg-config --libs opencv` -L . libraspicamcv.a -L /opt/vc/lib -lmmal_core -lmmal -lmmal_util -lvcos -lbcm_host -lpthread

DEPLOY_PATH = ~/facedetect/
deploy : facedetect_raspicam
	cp facedetect_raspicam $(DEPLOY_PATH)

