# What's this?

Usage demonstration for capturing screen content with libvt

Usage:
```
# With root
ssh root@tv 'bin/capture' | ffplay -f mjpeg -framerate 60 -
# Without root
ssh root@tv 'jailer -d -t native_devmode -i com.palmdts.devmode -p /media/developer bin/capture' | ffplay -f mjpeg -framerate 60 -
```
