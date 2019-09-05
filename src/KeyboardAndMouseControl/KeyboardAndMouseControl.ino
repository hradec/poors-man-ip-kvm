/*
  KeyboardAndMouseControl

  Controls the mouse from five pushbuttons on an Arduino Leonardo, Micro or Due.

  Hardware:
  - five pushbuttons attached to D2, D3, D4, D5, D6

  The mouse movement is always relative. This sketch reads four pushbuttons, and
  uses them to set the movement of the mouse.

  WARNING: When you use the Mouse.move() command, the Arduino takes over your
  mouse! Make sure you have control before you use the mouse commands.

  created 15 Mar 2012
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl
*/

#include "HID-Project.h"
//#include "Keyboard.h"
//#include "Mouse.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

// set pin numbers for the five buttons:
const int upButton = 2;
const int downButton = 3;
const int leftButton = 4;
const int rightButton = 5;
const int mouseButton = 6;
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
char buf[10];
char cbuf = 0;
char escape_sequence_done = 0;
char x = 0;

void setup() { // initialize the buttons' inputs:
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();

  Serial1.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  //Keyboard.begin();
}

void loop() {
  // Light led if keyboard uses the boot protocol (normally while in bios)
  // Keep in mind that on a 16u2 and Arduino Micro HIGH and LOW for TX/RX Leds are inverted.
  if (BootKeyboard.getProtocol() == HID_BOOT_PROTOCOL)
    digitalWrite(pinLed, HIGH);
  else
    digitalWrite(pinLed, LOW);

  //Keyboard.wakeupHost()

  // use serial input to control the mouse:
  if (Serial1.available() > 0) {
    int inChar = Serial1.read();

    // ====================================================================
    // detect escape sequence
    // ====================================================================
    Serial1.print(inChar, HEX);
    Serial1.write("\n\r" );

    // deal with scape sequences
    if( inChar == 0x1B ){
        // detect a escape sequence
        Serial1.write("flag1\n\r" );
        cbuf = 0;
        buf[cbuf++] = inChar;
    } else
    // now that we have a escape sequence,
    // start pulling it into a buffer
    if ( cbuf > 0 ) {
        // store sequence
        if ( cbuf > 0 ) {
            Serial1.write("flagN\n\r" );
            buf[cbuf++] = inChar;
        }
    }else{
        cbuf=0;
    }

    // ====================================================================
    // crtl+alt+del
    // ====================================================================
    if ( buf[0] == 0x1B && buf[1] == 0x04  ) {
        Serial1.write("crtl+alt+del\n\r");
        BootKeyboard.press(KEY_LEFT_CTRL);
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.press(KEY_DELETE);
        delay(100);
        BootKeyboard.releaseAll();
        for (x = 0; x < 10; x++) buf[x] = 0; cbuf = 0;
    } else

    // ====================================================================
    // F1 ( shift + 1  or ! ) - special case workaround for F1
    // ====================================================================
    if ( inChar == 0x21  ){
        Serial1.write("key F1\n\r");
        BootKeyboard.write(KEY_F1);
        for(x=0;x<10;x++) buf[x]=0;cbuf=0;
    }else

    // ====================================================================
    // power on via keyboard - crtl+alt+p
    // ====================================================================
    if ( buf[0] == 0x1B && buf[1] == 0x10  ){
        Serial1.write("crtl+alt+p = power on\n\r");
        Keyboard.write(CONSUMER_POWER);
        Keyboard.write(KEY_POWER);
        Keyboard.wakeupHost();
        for (x = 0; x < 10; x++) buf[x] = 0; cbuf = 0;
    } else

        // ====================================================================
        // We try to detect if this is the end of the escape sequence
        // ====================================================================
        if ( buf[0] == 0x1B && cbuf > 0 && ( inChar == 0x7E || ( inChar >= 0x41 && inChar < 0x5B ) ) ) {
            cbuf--;
            escape_sequence_done = 0;
            Serial1.write("cbuf==0 && buf[cbuf] >= 0x41 \n\r");
            if ( buf[cbuf] == 0x7E ) {
                buf[cbuf] = 0;
                Serial1.write("buf[cbuf]==0x7E\n\r");
                switch (buf[cbuf - 2]) {
                    // F5-F8 Keys
                    case 0x31:
                        Serial1.write("buf[cbuf-2]==0x31\n\r");
                        switch (buf[cbuf - 1]) {
                            case 0x35:
                                Serial1.write("key F2\n\r");
                                BootKeyboard.write(KEY_F2); break;
                            case 0x37:
                                Serial1.write("key F6\n\r");
                                BootKeyboard.write(KEY_F6); break;
                            case 0x38:
                                Serial1.write("key F7\n\r");
                                BootKeyboard.write(KEY_F7); break;
                            case 0x39:
                                Serial1.write("key F8\n\r");
                                BootKeyboard.write(KEY_F8); break;
                        }
                        break;
                    // F9-F8 Keys
                    case 0x32:
                        Serial1.write("buf[cbuf-2]==0x32\n\r");
                        switch (buf[cbuf - 1]) {
                            case 0x30:
                                Serial1.write("key F9\n\r");
                                BootKeyboard.write(KEY_F9); break;
                            case 0x31:
                                Serial1.write("key F10\n\r");
                                BootKeyboard.write(KEY_F10); break;
                            case 0x33:
                                Serial1.write("key F11\n\r");
                                BootKeyboard.write(KEY_F11); break;
                            case 0x34:
                                Serial1.write("key F12\n\r");
                                BootKeyboard.write(KEY_F12); break;
                        }
                        break;
                    // delete, home, end, pgup, pgdown Keys
                    case 0x5B:
                        Serial1.write("buf[cbuf-2]==0x5B\n\r");
                        switch (buf[cbuf - 1]) {
                            case 0x33:
                                Serial1.write("delete\n\r");
                                BootKeyboard.write(KEY_DELETE); break;
                            case 0x31:
                                Serial1.write("key HOME\n\r");
                                BootKeyboard.write(KEY_HOME); break;
                            case 0x32:
                                Serial1.write("key INSERT\n\r");
                                BootKeyboard.write(KEY_INSERT); break;
                            case 0x34:
                                Serial1.write("key END\n\r");
                                BootKeyboard.write(KEY_END); break;
                            case 0x35:
                                Serial1.write("key PGUP\n\r");
                                BootKeyboard.write(KEY_PAGE_UP); break;
                            case 0x36:
                                Serial1.write("key PGDOWN\n\r");
                                BootKeyboard.write(KEY_PAGE_DOWN); break;
                        }
                        break;
                }
                escape_sequence_done = 1;
            } else {
                flag1 = 0;
                // ALT PRESSED
                if (buf[cbuf - 1] == 0x33) {
                  Serial1.write("key alt + ");
                  BootKeyboard.press(KEY_LEFT_ALT);
                  flag1 = 1;
                } else
                // CTRL PRESSED
                if (buf[cbuf - 1] == 0x35) {
                  Serial1.write("key ctrl + ");
                  BootKeyboard.press(KEY_LEFT_CTRL);
                  flag1 = 2;
                }
                // arrow keys and F1 to F4
                switch (buf[cbuf]) {
                    case 0x41:
                        Serial1.write("key up\n\r");
                        BootKeyboard.press(KEY_UP); break;
                        if (flag1 == 2) Mouse.move(0, -40);
                    case 0x42:
                        Serial1.write("key down\n\r");
                        BootKeyboard.press(KEY_DOWN); break;
                        if (flag1 == 2) Mouse.move(0, 40);
                    case 0x43:
                        Serial1.write("key right\n\r");
                        BootKeyboard.press(KEY_RIGHT); break;
                        if (flag1 == 2) Mouse.move(40, 0);
                    case 0x44:
                        Serial1.write("key left\n\r");
                        BootKeyboard.press(KEY_LEFT); break;
                        if (flag1 == 2) Mouse.move(-40, 0);
                    case 0x31:
                        Serial1.write("key home\n\r");
                        BootKeyboard.press(KEY_HOME); break;
                        if (flag1 == 2) Mouse.click(MOUSE_LEFT);
                    case 0x32:
                        Serial1.write("key insert\n\r");
                        BootKeyboard.press(KEY_INSERT); break;
                    case 0x33:
                        Serial1.write("key delete\n\r");
                        BootKeyboard.press(KEY_DELETE); break;
                    case 0x34:
                        Serial1.write("key end\n\r");
                        BootKeyboard.press(KEY_END); break;
                        if (flag1 == 2) Mouse.click(MOUSE_RIGHT);
                    case 0x35:
                        Serial1.write("key page up\n\r");
                        BootKeyboard.press(KEY_PAGE_UP); break;
                    case 0x36:
                        Serial1.write("key down up\n\r");
                        BootKeyboard.press(KEY_PAGE_DOWN); break;
                    case 0x50:
                        Serial1.write("f1\n\r");
                        BootKeyboard.press(KEY_F1); break;
                    case 0x51:
                        Serial1.write("f2\n\r");
                        BootKeyboard.press(KEY_F2); break;
                    case 0x52:
                        Serial1.write("f3\n\r");
                        BootKeyboard.press(KEY_F3); break;
                    case 0x53:
                        Serial1.write("f4\n\r");
                        BootKeyboard.press(KEY_F4); break;
                }
                delay(100);
                BootKeyboard.releaseAll();
                escape_sequence_done = 1;
            }
            if ( escape_sequence_done )
                for (x = 0; x < 10; x++) buf[x] = 0; cbuf = 0;
        } else
        // ====================================================================
        // if we're not in a escape sequence, just send the chars to keyboard
        // ====================================================================
        if ( cbuf == 0 ) {
            if ( inChar == 0x0D ) {
                BootKeyboard.write(KEY_ENTER);
                Serial1.write("key enter\n");
            } else if ( inChar == 0x60 ) {
                BootKeyboard.write(KEY_ESC);
                Serial1.write("key esc\n");
            } else if ( inChar == 0x03 ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('c');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + c\n");
            } else if ( inChar == 0x18 ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('x');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + x\n");
            } else if ( inChar == 0x1A ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('z');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + z\n");
            } else if ( inChar == 0x0F ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('o');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + o\n");
            } else if ( inChar == 0x01 ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('a');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + a\n");
            } else if ( inChar == 0x05 ) {
                BootKeyboard.press(KEY_LEFT_CTRL);
                BootKeyboard.press('e');
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + e\n");
            } else if ( inChar == 0x05 ) {
                BootKeyboard.press(KEY_TAB);
                delay(100);
                BootKeyboard.releaseAll();
                Serial1.write("key ctrl + e\n");
            } else
                BootKeyboard.write( inChar );
            for (x = 0; x < 10; x++) buf[x] = 0;
        }
    }
}
/*
    switch (inChar) {mlrmlrmlrmlrmlrmlrmlrmlrmlrmlrmlrmlrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
      case 'u':
        // move mouse up
        Mouse.move(0, -40);
        break;
      case 'd':
        // move mouse down
        Mouse.move(0, 40);
        break;
      case 'l':
        // move mouse left
        Mouse.move(-40, 0);
        break;
      case 'r':
        // move mouse right
        Mouse.move(40, 0);
        break;
      case 'm':
        // perform mouse left click
        Mouse.click(MOUSE_LEFT);
        break;
    }
*/
