# Day 10: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d10p2 FILE` where `FILE`
is one of the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

What do you get if you multiply together the values of one chip in
each of outputs 0, 1, and 2?

## Solution

Just added a new array to keep track of stuff going into the
outputs. Multiplied together the values in the first three elements at
the end and printed the result
