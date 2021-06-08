Demonstration of capturing with libvtcapture.
libvtcapture is a library used on modern (+2020 4k LG) TVs for capturing the displayed video

#Usage & Permission information
###Usage

With root:
`ssh root@IPtoTV 'bin/vtcapture-capture' | ffplay -f mjpeg -`


###Permission information
LG seems to started with per executeable permissions. So each service has its own permissions depending on roles, services, apis, clients and groups. They are laying under `/usr/share/luna-service2/manifests.d/`.
To get the capture with custombinarys working, we have to edit a few files and add our exe to the "trusted services". If you do not do this, you will recieve a error like this one: `LSRegisterPubPriv FAILED`
For our capture example, we have to allow it for using the capture abilities:

1. Make a new directory in your homefolder: `mkdir /home/root/roles`
2. Copy existing capture roles file: `cp /usr/share/luna-service2/roles.d/com.webos.service.capture.role.json /home/root/roles/`
3. Open file with `vi /home/root/roles/com.webos.service.capture.role.json` and press "a" to enter editmode
4. Edit "exeName" to the path containing our executeable. In our example this line has to look like `"exeName":"/home/root/bin/vtcapture-capture",`
5. Make a new directory in tmp: `mkdir /tmp/mnt/manifests`
6. Copy the original capture manifest into this tempdir `cp /usr/share/luna-service2/manifests.d/screen-capture-webos.manifest.json /tmp/mnt/manifests/`
7. Open the copied capture manifest `vi  /tmp/mnt/manifests/screen-capture-webos.manifest.json` and enter editmode with "a".
8. Add our nearly copied roles file, so the "rolesFiles"-section is looking like the following:
        "roleFiles": [
        "/usr/share/luna-service2/roles.d/com.webos.service.capture.role.json",
        "/home/root/roles/com.webos.service.capture.role.json"
	    ],
9. "Overmount" the existing original file `mount --bind /tmp/mnt/manifests/screen-capture-webos.manifest.json /usr/share/luna-service2/manifests.d/screen-capture-webos.manifest.json`
10. Refresh all services, to get our lastly made changes applied `ls-control scan-services`

Remember that your tmp dir and mount is deleted after a reboot, so you have to do these steps each time! You can also use the homebrew channels  init.d to automate this process.

