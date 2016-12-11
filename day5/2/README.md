# Day 5: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d5p1`

No input files for this problem. Program will prompt you for
input. Sample inputs/outputs below:

`IN: abc      OUT: 05ace8e3`

`IN: ugkcyxxp OUT: f2c730e5`

For source code, see `main.c` in the `src` directory.

## Problem

As the door slides open, you are presented with a second door that
uses a slightly more inspired security mechanism. Clearly unimpressed
by the last version (in what movie is the password decrypted in
order?!), the Easter Bunny engineers have worked out a better
solution.

Instead of simply filling in the password from left to right, the hash
now also indicates the position within the password to fill. You still
look for hashes that begin with five zeroes; however, now, the sixth
character represents the position (0-7), and the seventh character is
the character to put in that position.

A hash result of 000001f means that f is the second character in the
password. Use only the first result for each position, and ignore
invalid positions.

For example, if the Door ID is abc:

+ The first interesting hash is from abc3231929, which produces
  0000015...; so, 5 goes in position 1: \_5\_\_\_\_\__.
+ In the previous method, 5017308 produced an interesting hash;
  however, it is ignored, because it specifies an invalid position
  (8).
+ The second interesting hash is at index 5357525, which produces
  000004e...; so, e goes in position 4: \_5\_\_e\_\_\_.

You almost choke on your popcorn as the final character falls into
place, producing the password 05ace8e3.

Given the actual Door ID and this new method, what is the password? Be
extra proud of your solution if it uses a cinematic "decrypting"
animation.

## Solution

In principle this works the same as the previous solution except we
will now store the password in a buffer which is initialized to
negative values.

Again, we shift the first three bytes of the hash into an integer. If
the value of that integer is less than the length of our password,
then we examine the array index to which it corresponds. If the array
index has a negative value, then we add the seventh nibble of the hash
to the array at that index and increment our count of found digits.

When our counter of found digits reaches the desired value, we print
the password array.
