teensykey
=========

Teensy Sketch and C program to use a Teensy as a password storage device

TeensyKey/TeensyKey.ino is the Teensyduino sketch

Compiles on Linux (with libusb-dev) and OSX 10.9 (with Makefile changes)

This was based heavily on the RawHID example by PJRC (The Teensy
People).

example: ./teensykey 1
This will send 1 (one) to the Teensy, which will then respond with
password number one, stored in flash memory.

example: ./teensykey 84 | tail -n 1 | xclip -i -selection clipboard

This will grab password 84, chop off all the debug info (if any)
and put the password on the clipboard.

I'm using Vim and storing my passwords in a file. All of the passwords
are double-quoted with backslash and double-quotes within the strings
escaped. Each password has a comma after the last enclosing
double-quote. I can import this into the Teensy sketch by going to the
line "const char passwords[][64] = {" and running:

:r &lt;mypasswordfile&gt;

(No < or >)

DO NOT COMMIT YOUR PASSWORDS TO A PUBLIC REPO!
