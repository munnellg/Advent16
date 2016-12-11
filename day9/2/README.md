# Day 9: Part 2

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d9p2 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

Apparently, the file actually uses version two of the format.

In version two, the only difference is that markers within
decompressed data are decompressed. This, the documentation explains,
provides much more substantial compression capabilities, allowing
many-gigabyte files to be stored in only a few kilobytes.

For example:

+ `(3x3)XYZ` still becomes `XYZXYZXYZ`, as the decompressed section
  contains no markers.
+ `X(8x2)(3x3)ABCY` becomes `XABCABCABCABCABCABCY`, because the
  decompressed data from the (8x2) marker is then further
  decompressed, thus triggering the (3x3) marker twice for a total of
  six `ABC` sequences.
+ `(27x12)(20x12)(13x14)(7x10)(1x12)A` decompresses into a string of
  `A` repeated `241920` times.
+ `(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN` becomes
  `445` characters long.
+ Unfortunately, the computer you brought probably doesn't have enough
  memory to actually decompress the file; you'll have to come up with
  another way to get its decompressed length.

What is the decompressed length of the file using this improved format?

## Solution

Once again we can take advantage of the fact that we don't need to
render the file. We just have to compute the output file size. From
the problem description, it is fairly apparent that our solution will
need to be recursive. The challenge lies in figuring out exactly how
this recursion should be implemented.

Taking the simple case where there is no nesting, our solution remains
the same as before.

Taking the more complex case where a compression instruction contains
another compression instruction the `num_chars` argument for the
parent includes the number of characters required to represent the
child. Thefore, after we return from computing the width of the child,
two changes need to be made in the parent. We must delete the width of
characters consumed by the child from the parent's width and replace
those characters with the decompressed with of the child, i.e. the
parents new width is equal to `p_width - c\_consumed +
c\_width\*c\_repetitions\*.

We must also adjust the parent's measure of how many characters it has
consumed when it was performing its own decompression. To help ensure
that characters consumed is propagated between levels of recursion, we
use ftell and measure conmuption based on changes in position in the
stream.

Again, we keep track of spaces encountered and do not consider them as
characters consumed by the decompression process.

The result very quickly becomes a big number, so use `uint64_t` for
storing the decompressed width in all cases
