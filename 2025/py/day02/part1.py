import re
from typing import List, Tuple

# ------------------------------------------------------------
def parse_ranges(line: str) -> List[Tuple[int, int]]:
    """Convert the input line into a list of (low, high) tuples."""
    ranges = []
    for part in line.strip().split(','):
        low, high = map(int, part.split('-'))
        ranges.append((low, high))
    return ranges

# ------------------------------------------------------------
def bad_numbers_in_range(low: int, high: int, all_bad: List[int]) -> List[int]:
    """Return the list of bad numbers that fall inside [low,high]."""
    # binary search would be fine here but linear scan is tiny
    return [x for x in all_bad if low <= x <= high]

# ------------------------------------------------------------
def generate_all_bad(limit: int) -> List[int]:
    """
    Generate every number of the form x*10^k + x that does not exceed `limit`.
    limit can be as large as 10**12 (or bigger), but we only need to
    iterate over k up to 9.
    """
    bad = []
    for k in range(1, 10):          # length of the repeated block
        pow_k = 10 ** k
        start_x = 10 ** (k - 1)     # no leading zeros
        end_x   = 10 ** k           # exclusive

        for x in range(start_x, end_x):
            val = x * pow_k + x
            if val > limit:
                break          # all larger x will also be too big
            bad.append(val)
    return bad

# ------------------------------------------------------------
def main():
    # Example input from the puzzle description
    with open('input.txt', 'r') as file:
        raw_input = file.read()

    ranges = parse_ranges(raw_input)

    # The largest possible number that we will ever need to consider
    max_limit = max(high for _, high in ranges)
    all_bad = generate_all_bad(max_limit)

    total_sum = 0
    for low, high in ranges:
        bad_in_range = bad_numbers_in_range(low, high, all_bad)
        total_sum += sum(bad_in_range)

    print("Sum of all invalid IDs:", total_sum)


if __name__ == "__main__":
    main()

