
            ______ ______                                  
           / ____// ____/____ ___   ____   ___   ____ _
          / /_   / /_   / __ `__ \ / __ \ / _ \ / __ `/
         / __/  / __/  / / / / / // /_/ //  __// /_/ /
        /_/    /_/    /_/ /_/ /_// .___/ \___/ \__, /
                                /_/           /____/


                build: ffmpeg-4.2.1-amd64-static.tar.xz
              version: 4.2.1

                  gcc: 6.3.0
                 yasm: 1.3.0.36.ge2569
                 nasm: 2.14.02

               libaom: 1.0.0-2344-gcd14cc130
               libass: 0.14.0
               libgme: 0.6.2
               libsrt: 1.3.2
               libvpx: 1.8.1-130-g5a0242ba5
              libvmaf: 1.3.14
              libx264: 0.157.2969 d4099dd
              libx265: 3.1+5-9c5c9cef2a86
              libxvid: 1.3.4-1+b2
              libwebp: 0.5.2 
              libzimg: 2.8.0
              libzvbi: 0.2.36
             libdav1d: 0.4.0
            libgnutls: 3.6.8
            libtheora: 1.2.0alpha1+git
            libfrei0r: 1.5.0-1
           libvidstab: 1.10
          libfreetype: 2.6.3-3.2
          libharfbuzz: 2.5.3
          libopenjpeg: 2.3.1 

              libalsa: 1.1.9
              libsoxr: 0.1.3
              libopus: 1.3.1
             libspeex: 1.2
            libvorbis: 1.3.6
           libmp3lame: 3.100 
        librubberband: 1.8.2 
       libvo-amrwbenc: 0.1.3-1
    libopencore-amrnb: 0.1.3-2.1+b2
    libopencore-amrwb: 0.1.3-2.1+b2


     Notes:  A limitation of statically linking glibc is the loss of DNS resolution. Installing
             nscd through your package manager will fix this.

             The vmaf filter needs external files to work- see model/000-README.TXT


      This static build is licensed under the GNU General Public License version 3.

      
      Patreon: https://www.patreon.com/johnvansickle
      Paypal:  https://www.paypal.me/johnvansickle 
      Bitcoin: 13pZjChR1gR6wqzGMuwLAzqeVR5o9XGoCP 

      email: john.vansickle@gmail.com
      irc:   relaxed @ irc://chat.freenode.net #ffmpeg
      url:   https://johnvansickle.com/ffmpeg/
