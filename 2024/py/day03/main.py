with open("input.txt", "r") as f:
    data = f.readlines()


import re
def part_one(data):
    result = 0

    for z in data:
        matches = re.findall(r'mul\((\d+),\s*(\d+)\)', z)
        
        for k in matches:
            x = int(k[0])
            y = int(k[1])
            result += x * y
    
    return result

def part_two(data):
    program = "".join(data)

    tokens = re.findall(r"mul\(\d+,\d+\)|do\(\)|don't\(\)", program)

    result = 0
    enabled = True

    for token in tokens:
        if token == "do()":
            enabled = True
        elif token == "don't()":
            enabled = False
        else:
            if enabled:
                x, y = map(int, re.findall(r"\d+", token))
                result += x * y

    return result

print(part_one(data))
print(part_two(data))

