# Day 1: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d1p2 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

Then, you notice the instructions continue on the back of the
Recruiting Document. Easter Bunny HQ is actually at the first location
you visit twice.

For example, if your instructions are R8, R4, R4, R8, the first
location you visit twice is 4 blocks away, due East.

How many blocks away is the first location you visit twice?

## Solution

Code largely stays the same except we need to maintain some record of
where we have been and test all new positions for intersections. Just
hash x,y coordinates of all visited locations and store boolean in an
array of suitable size. Messy, lazy, but it works.
