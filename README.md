# poor's-man-ip-kvm
![](arduino/.poors-man-ip-kvm.mp4)

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

___

## arduino: 
  contains 2 arduino sketches: 
  
    - MultiSerial:
        This goes into the arduino that will be connect to the bridge computer. 
        It will receive characters from the remote machine via a serial connection 
        to /dev/ttyACM0 (one can use `screen` or even the arduino ide serial monitor)
        
    - KeyboardAndMouseControl:
        This goes into the arduino connected to the remote computer we want to control. 
        This sketch receives the characters from the other arduino, and stream then as
        keyboard keystrokes to the controlled computer. 
        The controlled computer actually "thinks" it's a real keyboard!
        
        
