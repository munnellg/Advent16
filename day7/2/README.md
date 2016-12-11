# Day 7: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d7p2 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

You would also like to know which IPs support SSL (super-secret
listening).

An IP supports SSL if it has an Area-Broadcast Accessor, or ABA,
anywhere in the supernet sequences (outside any square bracketed
sections), and a corresponding Byte Allocation Block, or BAB, anywhere
in the hypernet sequences. An ABA is any three-character sequence
which consists of the same character twice with a different character
between them, such as xyx or aba. A corresponding BAB is the same
characters but in reversed positions: yxy and bab, respectively.

For example:

+ *aba[bab]xyz* supports SSL (aba outside square brackets with
  corresponding bab within square brackets).
+ *xyx[xyx]xyx* does not support SSL (xyx, but no corresponding yxy).
+ *aaa[kek]eke* supports SSL (eke in supernet with corresponding kek in
  hypernet; the aaa sequence is not related, because the interior
  character must be different).
+ *zazbz[bzb]cdb* supports SSL (zaz has no corresponding aza, but zbz
  has a corresponding bzb, even though zaz and zbz overlap).

How many IPs in your puzzle input support SSL?

## Solution

As with all AoC problems, the solution to Part 2 is strongly linked to
the solution to Part 1.

We shall retain the context window (now three characters wide),
palindrome validation and states from the previous part. However,
rather incrementing a counter depending on our state, we shall instead
enter the valid palindrome under the context window into one of two
bitvectors.

For adding the strings to the bitvectors, we define two hash
functions - hash\_aba and hash\_bab. These has functions are
symmetrical, such that a string "xyx", if hashed with the hash\_aba
function will produce the same value as a string "yxy" that is hashed
with the hash\_bab function. Our choice of hash function and
detination bitvector is dependent on our current state.

When we encounter a newline character, we compute the intersection of
the two bitvectors. If the IP supports SSL then at least one entry in
the intersection set will be non-zero. If we find this to be the case,
then we increment our counter and proceed to process the next address.
