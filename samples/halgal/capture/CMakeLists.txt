find_package(PkgConfig REQUIRED)

add_executable(sample-halgal-capture capture.c)
set_target_properties(sample-halgal-capture PROPERTIES OUTPUT_NAME halgal-captureWithoutVideo)
target_link_libraries(sample-halgal-capture halgal)

add_executable(sample-halgal-captureWithVideo capture_withVideo.c)
target_include_directories(sample-halgal-captureWithVideo PRIVATE /home/opencv-3.2.0/build/install/include)
set_target_properties(sample-halgal-captureWithVideo PROPERTIES OUTPUT_NAME halgal-capture)
target_link_libraries(sample-halgal-captureWithVideo halgal vtcapture /home/opencv-3.2.0/build/install/lib/libopencv_core.so /home/opencv-3.2.0/build/install/lib/libopencv_imgproc.so /home/opencv-3.2.0/build/install/lib/libopencv_imgcodecs.so /home/opencv-3.2.0/build/install/lib/libopencv_photo.so /home/opencv-3.2.0/build/install/lib/libopencv_shape.so /home/opencv-3.2.0/build/install/lib/libopencv_stitching.so /home/opencv-3.2.0/build/install/lib/libopencv_superres.so /home/opencv-3.2.0/build/install/lib/libopencv_video.so /home/opencv-3.2.0/build/install/lib/libopencv_videoio.so /home/opencv-3.2.0/build/install/lib/libopencv_videostab.so /home/opencv-3.2.0/build/install/lib/libopencv_calib3d.so /home/opencv-3.2.0/build/install/lib/libopencv_features2d.so /home/opencv-3.2.0/build/install/lib/libopencv_flann.so /home/opencv-3.2.0/build/install/lib/libopencv_highgui.so /home/opencv-3.2.0/build/install/lib/libopencv_ml.so /home/opencv-3.2.0/build/install/lib/libopencv_objdetect.so)