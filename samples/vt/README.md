# What's this?

Usage demonstration for capturing screen content with libvt

Usage:
```
ssh root@tv-ip 'XDG_RUNTIME_DIR=/tmp/xdg bin/capture' | ffplay -f mjpeg -framerate 60 -
```