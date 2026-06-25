#!/usr/bin/env python3
# ------------------------------------------------------------
#  Advent of Code – Part Two: “repeated pattern” IDs
# ------------------------------------------------------------

import math
from bisect import bisect_left, bisect_right


def read_input() -> list[tuple[int, int]]:
    """Parse the single‑line input file into a list of (low, high) tuples."""
    with open("input.txt") as f:
        raw = f.read().strip()

    ranges = []
    for part in raw.split(","):
        low, high = map(int, part.split("-"))
        ranges.append((low, high))
    return ranges


def generate_repeated_numbers(max_value: int) -> list[int]:
    """
    Return a sorted list of all integers <= max_value that are made by
    repeating some decimal pattern at least twice.
    The implementation uses string concatenation only once per candidate,
    keeping trailing zeros intact.
    """
    # Powers of ten up to the length of max_value
    max_len = len(str(max_value))
    pow10 = [1] * (max_len + 1)
    for i in range(1, max_len + 1):
        pow10[i] = pow10[i - 1] * 10

    numbers = set()

    # Pattern length l can be at most half of the final number's digit count
    for l in range(1, max_len // 2 + 1):
        start_pat = pow10[l - 1]
        end_pat   = pow10[l]

        for pat in range(start_pat, end_pat):
            # Build the first *two* copies as a string – keeps zeros.
            s = f"{pat}{pat}"
            val = int(s)
            if val > max_value:
                continue
            numbers.add(val)

            # Now keep appending the pattern until we exceed max_value
            while True:
                s += str(pat)          # one more repetition
                val = int(s)
                if val > max_value:
                    break
                numbers.add(val)

    return sorted(numbers)


def sum_invalid_ids(ranges, invalids):
    """Sum all invalid IDs that fall inside each (low, high) range."""
    total = 0
    for low, high in ranges:
        left = bisect_left(invalids, low)
        right = bisect_right(invalids, high)
        total += sum(invalids[left:right])
    return total


def main() -> None:
    ranges = read_input()
    max_high = max(high for _, high in ranges)

    invalid_numbers = generate_repeated_numbers(max_high)

    answer = sum_invalid_ids(ranges, invalid_numbers)
    print(answer)


if __name__ == "__main__":
    main()

