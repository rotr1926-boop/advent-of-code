left_column = []
right_column = []

with open("day1/input.txt", "r") as f:
    for x in f:
        left_id, right_id = map(int, x.split())
        left_column.append(left_id)
        right_column.append(right_id)

left_column.sort()
right_column.sort()
    
total_distance = sum(abs(l - r) for l, r in zip(left_column, right_column))
    
print(total_distance)


r = 0
for x in left_column:
    for y in right_column:
        if x == y:
            r += y
        
print(r)