with open("input.txt") as f:
    rotations = f.read().strip().split()

start = 50
count_zero = 0

for r in rotations:
    direction = r[0]
    value = int(r[1:])

    if direction == "L":
        start = (start - value) % 100
    elif direction == "R":
        start = (start + value) % 100

    if start == 0:
        count_zero += 1

print("Password:", count_zero)


start = 50
count_zero = 0

for r in rotations:
    direction = r[0]
    value = int(r[1:])

    # Simula ogni click
    for _ in range(value):
        if direction == "L":
            start = (start - 1) % 100
        else:  # R
            start = (start + 1) % 100

        if start == 0:
            count_zero += 1

print("Password Part 2:", count_zero)
