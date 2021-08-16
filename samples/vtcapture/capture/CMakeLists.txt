
find_package(PkgConfig REQUIRED)

pkg_check_modules(JPEG REQUIRED IMPORTED_TARGET libjpeg)


#set(OpenCV_DIR /usr/share/OpenCV)
#find_package( OpenCV REQUIRED imgproc)

add_executable(sample-vtcapture-capture capture.c)
target_include_directories(sample-vtcapture-capture PRIVATE /home/opencv-3.2.0/build/install/include)
set_target_properties(sample-vtcapture-capture PROPERTIES OUTPUT_NAME vtcapture-capture)
#target_link_libraries(sample-vtcapture-capture vtcapture PkgConfig::JPEG /home/opencv-3.2.0/build/install/lib/libopencv_core.so /home/opencv-3.2.0/build/install/lib/libopencv_imgproc.so /home/opencv-3.2.0/build/install/lib/libopencv_imgcodecs.so)
target_link_libraries(sample-vtcapture-capture vtcapture PkgConfig::JPEG /home/opencv-3.2.0/build/install/lib/libopencv_core.so /home/opencv-3.2.0/build/install/lib/libopencv_imgproc.so /home/opencv-3.2.0/build/install/lib/libopencv_imgcodecs.so /home/opencv-3.2.0/build/install/lib/libopencv_photo.so /home/opencv-3.2.0/build/install/lib/libopencv_shape.so /home/opencv-3.2.0/build/install/lib/libopencv_stitching.so /home/opencv-3.2.0/build/install/lib/libopencv_superres.so /home/opencv-3.2.0/build/install/lib/libopencv_video.so /home/opencv-3.2.0/build/install/lib/libopencv_videoio.so /home/opencv-3.2.0/build/install/lib/libopencv_videostab.so /home/opencv-3.2.0/build/install/lib/libopencv_calib3d.so /home/opencv-3.2.0/build/install/lib/libopencv_features2d.so /home/opencv-3.2.0/build/install/lib/libopencv_flann.so /home/opencv-3.2.0/build/install/lib/libopencv_highgui.so /home/opencv-3.2.0/build/install/lib/libopencv_ml.so /home/opencv-3.2.0/build/install/lib/libopencv_objdetect.so)
