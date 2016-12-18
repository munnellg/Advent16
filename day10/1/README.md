# Day 10: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d10p1 FILE NUM1 NUM2` where `FILE`
is one of the input files found in the data directory and `NUM1` and
`NUM2` are two values which should appear at the same node in the graph
described by the input.

For source code, see `main.c` in the `src` directory.

## Problem

You come upon a factory in which many robots are zooming around
handing small microchips to each other.

Upon closer examination, you notice that each bot only proceeds when
it has two microchips, and once it does, it gives each one to a
different bot or puts it in a marked "output" bin. Sometimes, bots
take microchips from "input" bins, too.

Inspecting one of the microchips, it seems like they each contain a
single number; the bots must use some logic to decide what to do with
each chip. You access the local control computer and download the
bots' instructions (your puzzle input).

Some of the instructions specify that a specific-valued microchip
should be given to a specific bot; the rest of the instructions
indicate what a given bot should do with its lower-value or
higher-value chip.

For example, consider the following instructions:

+ `value 5 goes to bot 2`
+ `bot 2 gives low to bot 1 and high to bot 0`
+ `value 3 goes to bot 1`
+ `bot 1 gives low to output 1 and high to bot 0`
+ `bot 0 gives low to output 2 and high to output 0`
+ `value 2 goes to bot 2`

1. Initially, bot 1 starts with a value-3 chip, and bot 2 starts with
   a value-2 chip and a value-5 chip.
2. Because bot 2 has two microchips, it gives its lower one (2) to bot
   1 and its higher one (5) to bot 0.
3. Then, bot 1 has two microchips; it puts the value-2 chip in output
   1 and gives the value-3 chip to bot 0.
4. Finally, bot 0 has two microchips; it puts the 3 in output 2 and
   the 5 in output 0.

In the end, output bin 0 contains a value-5 microchip, output bin 1
contains a value-2 microchip, and output bin 2 contains a value-3
microchip. In this configuration, bot number 2 is responsible for
comparing value-5 microchips with value-2 microchips.

Based on your instructions, what is the number of the bot that is
responsible for comparing value-61 microchips with value-17
microchips?

## Solution

This is really just a graph problem. The inputs describe nodes, edges
and initial states. Each node has two edges - hi and lo - and some
nodes receive values on initialization due to the "value X goes to bot
Y" instruction

I have basically loaded the bots into an array where the id of a bot
is its index in the list. The program initializes the graph from the
file and then loops across the array, updating each node until the
graph is stable i.e. no more changes take place.

If it encounters a node with the two values we are interested in, it
prints a message to let us know that the node of interest has been
found.

I discard values that are sent to outputs. They're not needed.

A better way to load the bots would be to use a hash map or a tree
structure. In its current form, the application does not scale
well. Many of the nodes in the array are not actually connected to
anything in the graph. I used an array because it was easier than
taking the time to write the code necessary to build a tree.

Bear in mind that my solution does not handle loops in the graph and
will crash due to infinite recursion if it encounters one.
