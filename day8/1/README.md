# Day 8: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d8p1 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

You come across a door implementing what you can only assume is an
implementation of two-factor authentication after a long game of
requirements telephone.

To get past the door, you first swipe a keycard (no problem; there was
one on a nearby desk). Then, it displays a code on a little screen,
and you type that code on a keypad. Then, presumably, the door
unlocks.

Unfortunately, the screen has been smashed. After a few minutes,
you've taken everything apart and figured out how it works. Now you
just have to work out what the screen would have displayed.

The magnetic strip on the card you swiped encodes a series of
instructions for the screen; these instructions are your puzzle
input. The screen is 50 pixels wide and 6 pixels tall, all of which
start off, and is capable of three somewhat peculiar operations:

rect AxB turns on all of the pixels in a rectangle at the top-left of
the screen which is A wide and B tall.  rotate row y=A by B shifts all
of the pixels in row A (0 is the top row) right by B pixels. Pixels
that would fall off the right end appear at the left end of the row.
rotate column x=A by B shifts all of the pixels in column A (0 is the
left column) down by B pixels. Pixels that would fall off the bottom
appear at the top of the column.  For example, here is a simple
sequence on a smaller screen:

+ `rect 3x2` creates a small rectangle in the top-left corner:
+ `rotate column x=1 by 1` rotates the second column down by one pixel:
+ `rotate row y=0 by 4` rotates the top row right by four pixels:
+ `rotate column x=1 by 1` again rotates the second column down by one
  pixel, causing the bottom pixel to wrap back to the top:

As you can see, this display technology is extremely powerful, and
will soon dominate the tiny-code-displaying-screen market. That's what
the advertisement on the back of the display tries to convince you,
anyway.

There seems to be an intermediate check of the voltage used by the
display: after you swipe your card, if the screen did work, how many
pixels should be lit?

Your puzzle answer was 106.

## Solution

On the surface, this problem is just about parsing some input and
updating a 2D array based on what we get. However, I found that
shifting the display actually presents an interesting problem. My
familiarity with bit shifting operations gave me the impression that
shifting the pixels would be quite straight-forward. In reality it
takes a bit of thought. We don't want to have to shuffle everything
along by 1 until the shift is satisfied. We want to move every value
from its start point to its destination. In order to do this, we need
to guarantee that we will

+ a) Visit every element of the list at least once
+ b) Not write over any value that we will need at a later point

I had to do some reading to find a decent method. Ultimately I worked
from this StackOverflow post:

<http://stackoverflow.com/a/18154984>

The general idea is that we split the row/column into sets whose
length is the greatest common denominator of both the screen
width/height and the amount by which we wish to shift. We then perform
all of our shifting operations in sequence within these subsets. This
guarantees that we will reach every element in the row/column. We will
only visit each element once and we only require a single temporary
variable to store the value of the first shift so that it can be
reintroduced for the final shift.

I implemented the function such that it can do both row and column
shifts depending on a flag. That resulted in a bit of mucking about
with pointers. It's definitely not as clean as it could be, but it's a
very cool little algorithm none-the-less.
