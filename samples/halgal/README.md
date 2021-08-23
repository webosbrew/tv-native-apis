# What's this?

Usage demonstration for capturing UI content with halgal(Graphic) and vtcapture(Video)

ssh root@TV 'bin/halgal-capture' | "ffplay" -f mjpeg - #halgal + vtcapture 
ssh root@TV 'bin/halgal-captureWithoutVideo' -> File /tmp/myfile.bin #Halgal screenshot
