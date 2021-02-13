# Cat Annoyer
Arduino-based cat toy.

[![Cat Annoyer](https://img.youtube.com/vi/FwHjwoEb1Nw/0.jpg)](https://www.youtube.com/watch?v=FwHjwoEb1Nw)

The Cat Annoyer is a simple system using inexpensive components to roughly mimic the behaviour of a small rodent. It has a proximity sensor to detect cat interactions and can be triggered using a TV remote control.

It really is easy to build. A breadboard prototype took me about an hour (most of that time was taken by me trying to figure out non-existent problems, I'd installed the libraries for the wrong Arduino Nano version). 

[![Breadboard version](https://img.youtube.com/vi/ekWHGxoxt0Y/0.jpg)](https://www.youtube.com/watch?v=ekWHGxoxt0Y)

A more solid version, with more interesting behaviour took about another hour. Making the pom-pom probably took most time.

![Pom-pom](https://github.com/danja/cat-toy/blob/main/cat-toy/media/pom-pom.jpeg)

## Hardware

![Parts](https://github.com/danja/cat-toy/blob/main/cat-toy/media/parts.jpeg)

* Arduino microcontroller module (I used a Nano) + USB cable
* 'Avoidance Sensor' - IR proximity detector module
* SG90 Servo 
* Circuit board - breadboard is fine, stripboard or whatever is convenient for permanent mounting
* Pom-pom & wooden skewer
* Misc. hardware - I mounted mine on a plywood offcut with scraps of aluminium for the power input/switch and servo, a hose clamp for the battery and plastic PCB standoffs for the circuit board

The electronic components are available from many sources at very low cost.

![Built thing](https://github.com/danja/cat-toy/blob/main/cat-toy/media/board1.jpeg)

I already had some Arduino Nanos and recently bought a
[Geekcreit UNOR3 Basic Starter Kits No Battery Version for Arduino Carton Box Packaging](https://www.banggood.com/Geekcreit-UNOR3-Basic-Starter-Kits-No-Battery-Version-for-Arduino-Carton-Box-Packaging-p-1133595.html) (which as well as lots of other things contains a breadboard, Arduino Uno and a servo) and a [Geekcreit 37 In 1 Sensor Module Board Set Starter Kits SENSOR KIT For Arduino Plastic Bag Package](https://www.banggood.com/Geekcreit-37-In-1-Sensor-Module-Board-Set-Starter-Kits-SENSOR-KIT-For-Arduino-Plastic-Bag-Package-p-1137051.html) which includes an 'Avoidance Sensor'. These packs are very good value for money and lots of fun.

## Construction

The circuit is very simple, I didn't bother drawing it. 

The Arduino USB connection to a computer can supply the power, alternately a battery or power pack (7-12v DC) can be attached to Vin and GND.

The sensor and servo take power from the Arduino, GND and +5v (**not** the battery voltage). The sensor has a data out line, the servo a data in, which should be connected to data D3 and D2 respectively on the Arduino.

![Built thing2](https://github.com/danja/cat-toy/blob/main/cat-toy/media/board2.jpeg)

A pom-pom can be easily made with a bit of wool and a couple of cardboard circles.

**Proximity Sensor**
```
Brown       GND
Red         +5v
Orange      D3
Yellow      n/c
```

**Servo**
```
Brown    GND
Red      +5v
Orange   D2
```

## Software

As well as the appropriate libraries needed for the board you use, the only other dependency is the [Servo library](https://www.arduino.cc/reference/en/libraries/servo/). All the code for the Cat Annoyer is in [main.cpp](https://github.com/danja/cat-toy/blob/main/cat-toy/src/main.cpp).

I used PlatformIO on VSCode on Ubuntu for writing the code and uploading to the Arduino, but the same code should work just fine copy & pasted into an empty Arduino IDE project. The Servo library is maintained by the Arduino folks, can be installed through the library manager of the IDE you use.
*While the Arduino IDE is fine for little projects like this, if you are planning anything more ambitious I'd strongly recommend using PlatformIO, it makes multi-file projects much more manageable.* 

## Behaviour

After compiling and uploading to the Arduino (or power on/reset) there will be a delay of 5 seconds before the servo will sweep backwards and forwards (with a little twitch), ```wave()``` in the code.

Whenever the proximity detector sees an obstacle (or changes from seeing an obstacle to not seeing an obstacle) it will twitch a random distance in a given direction. When it reaches that extreme it will switch direction.

If there's no change in the sensor's status for 10 minutes it will do another slow sweep.

The LED on the Arduino is lit whenever the proximity detector reports an obstacle. Ths sensor has two screwdriver-adjustable conrols. One adjusts the frequency of IR pulses (I believe in the region of 35kHz), should make no difference to behaviour. The other controls the sensitivity, ie. distance.   

**PS.** On trying it out with my friend's cat for the first time, realised the inactivity delay of 10 mins I'd set was too long to keep the cat's attention. *But*, out of curiosity I tried a TV remote control, without doing anything esle, and that triggered twitching. Serendipity! I'm guessing the mod freq sensor preset might need tweaking for some remotes, but it work out of the box for my friends. 

## Possible Improvements

With the same hardware it might be interesting to record the sensor input over time and use this to determine the movement of the servo - ie. learn what annoys the cat the most.

There are plenty of other I/O lines available on the Arduino. Simple additions could include sending a mousy squeak to a loudspeaker or other servos for more complex behaviours. Cheap motors & drivers are available, a mobile cat-annoying bot would be straightforward. Other sensors could be added: eg. the cheap ultrasonic sensor modules have quite a large (variable) oject-detection distance, could be used to offer behaviour to attract a distant animal.

With suitable code changes, the same hardware could be set up to make an automatic cat feeder. Not as much fun as annoying them.
