# Day 5: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d5p1`

No input files for this problem. Program will prompt you for
input. Sample inputs/outputs below:

`IN: abc      OUT: 18f47a30`

`IN: ugkcyxxp OUT: d4cd2ee1`

For source code, see `main.c` in the `src` directory.

## Problem

You are faced with a security door designed by Easter Bunny engineers
that seem to have acquired most of their security knowledge by
watching hacking movies.

The eight-character password for the door is generated one character
at a time by finding the MD5 hash of some Door ID (your puzzle input)
and an increasing integer index (starting with 0).

A hash indicates the next character in the password if its hexadecimal
representation starts with five zeroes. If it does, the sixth
character in the hash is the next character of the password.

For example, if the Door ID is abc:

+ The first index which produces a hash that starts with five zeroes
  is 3231929, which we find by hashing abc3231929; the sixth character
  of the hash, and thus the first character of the password, is 1.
+ 5017308 produces the next interesting hash, which starts with
  000008f82..., so the second character of the password is 8.
+ The third time a hash starts with five zeroes is for abc5278568,
  discovering the character f.

In this example, after continuing this search a total of eight times,
the password is 18f47a30.

Given the actual Door ID, what is the password?

## Solution

Get input password from the user and store in a buffer. Start a loop
runs indefinitely, appending ever increasing numbers to the input. The
the resulting string is hashed using the MD5 hash function. Hashes
which meet the criteria specified in the problem should have their
sixth hexadecimal digit printed. Process continues until eight
characters have been printed.

Validating the hash can be done by shifting the first three bytes of the
hash into an integer. If the value of the integer is less than 16, then
it should be printed and the count of found digits incremented.

For this program, the openssl implementation of MD5 was used.
