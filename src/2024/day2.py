sol = 0

with open('input.txt', 'r') as file:
    vals = [list(map(int, line.split())) for line in file]
# print(vals)

for line in vals:
    ascending = line[1] > line[0]
    works = True
    for i in range(0, len(line) - 1):
        if abs(line[i] - line[i + 1]) > 3 or line[i] == line[i+1] or (ascending != (line[i + 1] > line[i])):
            works = False
            break
    if works:
        sol += 1

print(sol)


sol = 0

with open('input.txt', 'r') as file:
    vals = [list(map(int, line.split())) for line in file]
# print(vals)

for line in vals:
    dp = [[-1] * 2 for i in range(len(line))]
    ascending = [[False] * 2 for i in range(len(line))]
    dp[0][0] = True
    dp[0][1] = True
    for i in range(1, len(dp)):
        if abs(line[i] - line[i - 1]) <= 3 and line[i] != line[i-1] and ((ascending[i - 1][0] == (line[i] > line[i-1])) or i == 1):
            dp[i][0] = dp[i-1][0]
        else:
            dp[i][0] = False

        if abs(line[i] - line[i - 1]) <= 3 and line[i] != line[i-1] and ((ascending[i - 1][1] == (line[i] > line[i-1])) or i == 1):
            dp[i][1] = dp[i-1][1]
        else:
            dp[i][1] = False

        ascending[i][0] = line[i] > line[i - 1]
        ascending[i][1] = line[i] > line[i - 1]

        if i >= 2 and abs(line[i] - line[i - 2]) <= 3 and line[i] != line[i-2] and ((ascending[i-2][0] == (line[i] > line[i-2])) or i == 2):
            if not dp[i][1]:
                dp[i][1] = dp[i-2][0]
                ascending[i][1] = line[i] > line[i-2]
    print("dp")
    print(dp)
    print("ascending")
    print(ascending)
    if dp[len(dp) - 2][0] or dp[len(dp) - 1][1]:
        print("works")
        sol += 1

print(sol)

