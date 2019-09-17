# poor's-man-ip-kvm

[![Watch the video](https://i9.ytimg.com/vi/kl3uO3cDpzk/sddefault.jpg?sqp=COyO2ukF&rs=AOn4CLDm5XnbSou1VJ50FWhUAOMNu2Blrg&time=1563854784781)](https://www.youtube.com/watch?v=kl3uO3cDpzk)

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
        
        
        
        
        
----

When I started this project, I bought this little capture device at aliexpress: 
https://www.aliexpress.com/wholesale?ltype=wholesale&d=y&SearchText=hdmi+capture&trafficChannel=main&SortType=price_asc&groupsort=1&CatId=0&page=1

at the time I started this project, this capture card cost me $4.99... the price went up since then, and now it costs $10 bucks... not sure why.. This little board is a HDMI/USB2 capture card, and works pretty well to capture video of the bios screen and boot at XVGA resolution. It can't capture 1080p though... for that, you need to go up to around $70 bucks. 

You can use one of these as well, for $3.53 bucks: 
https://www.aliexpress.com/item/32914705857.html?spm=a2g0o.productlist.0.0.191369a8La0QYa&algo_pvid=5443d193-3663-40dd-88b6-6e5ffdcf1c60&algo_expid=5443d193-3663-40dd-88b6-6e5ffdcf1c60-4&btsid=87480e42-7b4a-4dc7-81ff-1e62a63a95bb&ws_ab_test=searchweb0_0,searchweb201602_8,searchweb201603_52

but only if your video board has a composite or svhs output, or if you use a VGA->SVHS converter. The picture quality is crappier than the other one,

Regarding arduinos, I used 2 of these leonardos($2.50 each): 
https://www.aliexpress.com/item/1804917596.html?spm=a2g0o.productlist.0.0.59fc79fbKil2L7&algo_pvid=4e62e2c3-844b-4e21-91f8-a00bc49ab8cd&algo_expid=4e62e2c3-844b-4e21-91f8-a00bc49ab8cd-11&btsid=f69a978b-f779-4ce4-8499-3dc521952b91&ws_ab_test=searchweb0_0,searchweb201602_8,searchweb201603_52

you have to solder the TX/RX between then in a crossover setup: 

TX->RX

RX->TX

So they can communicate over they own hardware serial port.

After that, you just have to upload the "multiserial" code to the one you're going to connect from the controlling computer, and the "KeyboardAndMouseControl" to the other arduino, which is going to act as a virtual keyboard plugged to the controlled computer. 

I only use Linux , so in the controlling computer I connect to the controlling arduino using "sudo screen /dev/ttyACM0", and after that, everything I type goes to the controlled computer as keyboard keystrokes (almost everything... I didn't add all the crtl+key combinations yet, neither F1 to F5 - actually, F5 is F2, and shift+1 is F1 for now - you can see all that in the "KeyboardAndMouseControl" code)

I also open the video capture on the controlling computer using VLC, so I can see what's the video board is displaying. 

thats pretty much it. 



        
