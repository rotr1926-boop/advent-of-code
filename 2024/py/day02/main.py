reports = []
with open("day2/input.txt", "r") as f:
    for x in f:
        reports.append(list(map(int, x.strip().split())))

report_sicuri = 0

def is_safe(report):
    incremento = True
    decremento = True
    
    for y in range(len(report) - 1):
        diff = abs(report[y] - report[y + 1])
        
        if diff < 1 or diff > 3: return False
        if report[y] < report[y + 1]: decremento = False
        elif report[y] > report[y + 1]: incremento = False
            
    return incremento or decremento

for report in reports:
    if is_safe(report): report_sicuri += 1
    else:
        for i in range(len(report)):
            modified_report = report[:i] + report[i+1:]  
            if is_safe(modified_report):
                report_sicuri += 1
                break

print(report_sicuri)