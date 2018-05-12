# AudioFreeze Teensy based Eurorack module
## What is AudioFreeze?
AudioFreeze is a Eurorack module which uses a Teensy board, and the Teensy audio shield. It allows you to 'freeze' a section of incoming audio and manipulate it with the pots. There is a potentiometer on the rear of the board to attenuate input voltage.

[See here for a video which demonstrates the AudioFreeze in action](https://www.youtube.com/watch?v=Is2dHl0MkUs)

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Is2dHl0MkUs
" target="_blank"><img src="http://img.youtube.com/vi/Is2dHl0MkUs/0.jpg" 
alt="AudioFreeze Eurorack module" width="240" height="180" border="10" /></a>

## Disclaimer
This module should be seen as a prototype. IT HAS NO POWER FILTERING OR SHORT CIRCUIT PREVENTION, if you plug the ribbon cable in the wrong way you may damage the board and potentially your other modules.  Also your case must supply 5V power (some don't). As this was my first PCB I wanted to make it as simple as possible. I'm merely making it available as a resource for people who want to make their own boards. If you do build your own I'd love to see it. Please tweet me @scolar any pictures or videos!

## BOM

* 1 AudioFreeze PCB using the attached Gerber files
* 1 Teensy board
* 1 teensy Audio Shield
* Various 2.54mm header, depending on how you want to attach Teensy to the PCB, long leg header useful
* 4 50k linear Alpha 9mm vertical pots [From Thonk](https://www.thonk.co.uk/shop/alpha-9mm-pots/)
* 3 3mm LEDs
* 3 220 Ohm resistors
* 2 Thonkiconn Jacks (PJ301M-12) [From Thonk](https://www.thonk.co.uk/shop/3-5mm-jacks/)
* 2 C&K Tactile switches [From Thonk](https://www.thonk.co.uk/shop/radio-music-switch/)
* 1 50k trimmer pot
* Some hook-up wire to connect the audio in and out to the audio shield
