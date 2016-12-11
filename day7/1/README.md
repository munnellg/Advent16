# Day 7: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d7p1 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

While snooping around the local network of EBHQ, you compile a list of
IP addresses (they're IPv7, of course; IPv6 is much too
limited). You'd like to figure out which IPs support TLS
(transport-layer snooping).

An IP supports TLS if it has an Autonomous Bridge Bypass Annotation,
or ABBA. An ABBA is any four-character sequence which consists of a
pair of two different characters followed by the reverse of that pair,
such as xyyx or abba. However, the IP also must not have an ABBA
within any hypernet sequences, which are contained by square brackets.

For example:

+ *abba[mnop]qrst* supports TLS (abba outside square brackets).
+ *abcd[bddb]xyyx* does not support TLS (bddb is within square brackets,
  even though xyyx is outside square brackets).
+ *aaaa[qwer]tyui* does not support TLS (aaaa is invalid; the interior
  characters must be different).
+ *ioxxoj[asdfgh]zxcvbn* supports TLS (oxxo is outside square brackets,
  even though it's within a larger string).

How many IPs in your puzzle input support TLS?

## Solution

This problem may be solved by creating a context window, four
characters in width, which we slide across the input stream searching
for valid palindromes. Each time we encounter a valid palindrome, we
increment a counter. Validating the palindrome for required conditions
is trivial given the small size of the context window.

There are, in fact, two counters in this problem - a count of
palindromes inside brackets and a count of those outside brackets.
Hence our program will have two states - OUTSIDE\_BRACKET and
INSIDE\_BRACKET. Each time we encounter an opening [ symbol in our
context window, we flip to the INSIDE\_BRACKET state. When we encounter
a closing ], we flip back to OUTSIDE_BRACKET. Depending on our current
state, we choose which of the two counters to increment.

When we encounter a newline character in our context window, we test to
ensure that the OUTSIDE\_BRACKET counter is greater than zero and the
INSIDE\_BRACKET counter is equal to zero. If this is the case, then
the address is valid and we add it to our running total.
