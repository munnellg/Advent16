# Day 1: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d1p1 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

Santa's sleigh uses a very high-precision clock to guide its
movements, and the clock's oscillator is regulated by
stars. Unfortunately, the stars have been stolen... by the Easter
Bunny. To save Christmas, Santa needs you to retrieve all fifty stars
by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available
on each day in the advent calendar; the second puzzle is unlocked when
you complete the first. Each puzzle grants one star. Good luck!

You're airdropped near Easter Bunny Headquarters in a city
somewhere. "Near", unfortunately, is as close as you can get - the
instructions on the Easter Bunny Recruiting Document the Elves
intercepted start here, and nobody had time to work them out further.

The Document indicates that you should start at the given coordinates
(where you just landed) and face North. Then, follow the provided
sequence: either turn left (L) or right (R) 90 degrees, then walk
forward the given number of blocks, ending at a new intersection.

There's no time to follow such ridiculous instructions on foot,
though, so you take a moment and work out the destination. Given that
you can only walk on the street grid of the city, how far is the
shortest path to the destination?

For example:

+ Following R2, L3 leaves you 2 blocks East and 3 blocks North, or 5
  blocks away.
+ R2, R2, R2 leaves you 2 blocks due South of your starting position,
  which is 2 blocks away.
+ R5, L5, R5, R3 leaves you 12 blocks away.

## Solution

Maintain four variables throughout - `x`, `y`, `delta\_x` and
`delta\_y`. Init as follows:

+ `x = 0`
+ `y = 0`
+ `delta_x = 0`
+ `delta_y = 1`

Parse input stream in blocks splitting on spaces. First char
encountered is direction followed by integer argument which is
displacement. Update `delta\_x` and `delta\_y` values based on
displacement. It is useful to note that updating really only involves
swapping `delta\_x` and `delta\_y`, occasionally with negation
(depending on the direction of rotation). Hence we can implement
rotation as:

		/* Rotate */
        dy = dy * ( 1 - 2*( r==TURN_LEFT ) );
		dx = dx * ( 1 - 2*( r==TURN_RIGHT) );
		
		/* Swap */
		dy ^= dx;
		dx ^= dy;
		dy ^= dx;

Displacement is `x += delta_x*displacement; y += delta_y*displacement`

When `EOF` is reached, answer is `abs(x)+abs(y)` which is the
Manhattan distance from the origin
