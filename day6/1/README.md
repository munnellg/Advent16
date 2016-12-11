# Day 6: Part 1

## Building and Running

Compile the program by running `make`

Run the resulting executable with `./d6p1 FILE` where `FILE` is one of
the input files found in the data directory.

For source code, see `main.c` in the `src` directory.

## Problem

Something is jamming your communications with Santa. Fortunately, your
signal is only partially jammed, and protocol in situations like this
is to switch to a simple repetition code to get the message through.

In this model, the same message is sent repeatedly. You've recorded
the repeating message signal (your puzzle input), but the data seems
quite corrupted - almost too badly to recover. Almost.

All you need to do is figure out which character is most frequent for
each position. For example, suppose you had recorded the following
messages:

`eedadn`<br />
`drvtee`<br />
`eandsr`<br />
`raavrd`<br />
`atevrs`<br />
`tsrnev`<br />
`sdttsa`<br />
`rasrtv`<br />
`nssdts`<br />
`ntnada`<br />
`svetve`<br />
`tesnvt`<br />
`vntsnd`<br />
`vrdear`<br />
`dvrsen`<br />
`enarar`

The most common character in the first column is e; in the second, a;
in the third, s, and so on. Combining these characters returns the
error-corrected message, easter.

Given the recording in your puzzle input, what is the error-corrected
version of the message being sent?

## Solution

Nothing particularly clever about this solution. Create a 2D array
where rows represent an individual character in the output string and
columns are frequency counts for each character seen in that position.

Scan the input stream and aggregate counts for each character at each
position. When the EOF is found, find the ordinance of the column with
the greatest value for each position. Output the resulting text.
