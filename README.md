PongWithLasers
==============
PONG is back!
The great classic of old to enjoy at home with a friend!
But this time, blast him to get extra points!
A hit with a laser gives one(1) point.
If the ball touches the side, you get 10 points!

Controls:

	p1 (left part of screen)
		Arrow up:	Go up.
		Arrow down:	Go down.
		Arrow right: FIRE!

	p2 (right part of screen)
		k:			Go up.
		j:			Go down.
		q:			FIRE!

	To exit - Press ESC.


Compilation instructions:
You will need SDL1.2 to compile it.

	% g++ -c *.cpp && g++ -o PongWithLasers *.o -lSDL -lSDL_ttf -lSDL_image

Or if you want to type it all out:

	% g++ -c Image.cpp Label.cpp main.cpp Object.cpp Rectangle.cpp Screen.cpp Timer.cpp
	% g++ -o PongWithLasers Image.o Label.o main.o Object.o Rectangle.o Screen.o Timer.o -lSDL -lSDL_ttf -lSDL_image


Have fun!

(Also, the code is bad as this is my first go at c++)
