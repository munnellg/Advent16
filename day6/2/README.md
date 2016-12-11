# Day 6: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d6p1 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

Of course, that would be the message - if you hadn't agreed to use a
modified repetition code instead.

In this modified code, the sender instead transmits what looks like
random data, but for each character, the character they actually want
to send is slightly less likely than the others. Even after
signal-jamming noise, you can look at the letter distributions in each
column and choose the least common letter to reconstruct the original
message.

In the above example, the least common character in the first column
is a; in the second, d, and so on. Repeating this process for the
remaining characters produces the original message, advent.

Given the recording in your puzzle input and this new decoding
methodology, what is the original message that Santa is trying to
send?

## Solution

Identical solution to Part 1. Just search the resulting array for minima.
