# poors-man-ip-kvm

It's just ridiculous the price for an IP KVM solution. I simply can't get accept that! 

So, this is a "poor's man" IP KVM that works pretty well, and allows one to go into a remote Bios machine, setup, boot, install OS... everything!! 

For around 10$ bucks!! (if you buy the arduinos and the hdmi capture board at AliExpress! lol)

It requires some basic arduino knownledge, VLC to stream the remote computer monitor video, and some soldering to construct the serial/usb keyboard cable. (just to solder 2 wires actually!)

The basic idea is to use a computer you already have some sort of remote access (like a raspberry pi running linux with ssh access), plug the USB/HDMI capture board to it's usb toguether with the serial/USB Keyboard cable.

Then plug the HDMI to the computer you wan't to control, and the serial/USB Keyboard to the USB.

and voila... you can stream the video from the computer using VLC, and type on the virtual keyboard using ssh on the raspberry pi. 

It also requires some basic knowledge of opening ports on your router, or using upnpc if you want to do it over the internet! 

This project doesn't cover that part yet, neither has a nice frontend. 

But it works, and it works even better than some very expensive IP KVM options out there. 
