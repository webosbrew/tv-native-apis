# `dile_vt` capture

## Testing
```sh
mkdir build && cd build && cmake .. && make sample-dile-vt-capture
scp /opt/webos-sdk-x86_64/1.0.g/sysroots/armv7a-neon-webos-linux-gnueabi/usr/lib/libjpeg.so.62 build/samples/dile_vt/dile-vt-capture root@10.0.0.1:/tmp && ssh root@10.0.0.1 LD_PRELOAD=/usr/lib/libPmLogLib.so.3 LD_LIBRARY_PATH=/tmp /tmp/dile-vt-capture | ffplay - -fflags nobuffer -vf setpts=PTS/60
```
**Note:** `setpts` filter is important - otherwise ffplay playback is limited to <25fps and frames will be buffered in pipe
