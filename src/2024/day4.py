import re

sol = 0
with open('input.txt', 'r') as file:
    matrix = [list(line.split()[0]) for line in file]

stringToTest = ""
height = len(matrix)
width = len(matrix[0])

print("rows")
# test rows
for row in matrix:
    for c in row:
        stringToTest += c
    # print(f"testing: {stringToTest}")
    sol += len(re.findall("XMAS", stringToTest))
    sol += len(re.findall("SAMX", stringToTest))
    stringToTest = ""

print("cols")
# test cols
for c in range(width):
    for row in matrix:
        stringToTest += row[c]
    # print(f"testing: {stringToTest}")
    sol += len(re.findall("XMAS", stringToTest))
    sol += len(re.findall("SAMX", stringToTest))
    stringToTest = ""

print("diag")
# test up right
dim_sum = width + height
for total in range(dim_sum - 1):
    for r in range(0, min(total + 1, height)):
        c = total - r
        if 0 <= c < width:
            stringToTest += matrix[r][c]
    # print(f"testing: {stringToTest}")
    sol += len(re.findall("XMAS", stringToTest))
    sol += len(re.findall("SAMX", stringToTest))
    stringToTest = ""

# test down right
# test up right
dim_sum = width + height
for total in range(dim_sum - 1):
    for r in range(0, min(total + 1, height)):
        c = total - r
        if 0 <= c < width:
            stringToTest += matrix[r][width - 1 - c]
    # print(f"testing: {stringToTest}")
    sol += len(re.findall("XMAS", stringToTest))
    sol += len(re.findall("SAMX", stringToTest))
    stringToTest = ""

print(sol)

# p2

sol = 0
with open('input.txt', 'r') as file:
    matrix = [list(line.split()[0]) for line in file]

stringToTest = ""
height = len(matrix)
width = len(matrix[0])

matches = []

# print("rows")
# # test rows
# for idx, row in enumerate(matrix):
#     for c in row:
#         stringToTest += c
#     # print(f"testing: {stringToTest}")
#     itr = re.finditer("MAS", stringToTest)
#     for match in itr:
#         matches.append((idx, match.start() + 1))
#
#     itr = re.finditer("SAM", stringToTest)
#     for match in itr:
#         matches.append((idx, match.start() + 1))
#     stringToTest = ""
#
# print("cols")
# # test cols
# for c in range(width):
#     for row in matrix:
#         stringToTest += row[c]
#     # print(f"testing: {stringToTest}")
#     itr = re.finditer("MAS", stringToTest)
#     for match in itr:
#         if (match.start() + 1, c) in matches:
#             sol += 1
#
#     itr = re.finditer("SAM", stringToTest)
#     for match in itr:
#         if (match.start() + 1, c) in matches:
#             sol += 1
#     stringToTest = ""

matches = []


print("diag")
# test up right
dim_sum = width + height
for total in range(dim_sum - 1):
    for r in range(0, min(total + 1, height)):
        c = total - r
        if 0 <= c < width:
            stringToTest += matrix[r][c]
        else:
            stringToTest += '-'
    # print(f"testing: {stringToTest}")
    itr = re.finditer("MAS", stringToTest)
    for match in itr:
        matches.append((match.start() + 1, total - match.start() - 1))

    itr = re.finditer("SAM", stringToTest)
    for match in itr:
        matches.append((match.start() + 1, total - match.start() - 1))
    stringToTest = ""

print(matches)

# test up right
dim_sum = width + height
for total in range(dim_sum - 1):
    for r in range(0, min(total + 1, height)):
        c = total - r
        if 0 <= c < width:
            stringToTest += matrix[r][width - 1 - c]
        else:
            stringToTest += '-'
    # print(f"testing: {stringToTest}")
    itr = re.finditer("MAS", stringToTest)
    for match in itr:
        if (match.start() + 1, width - total + match.start()) in matches:
            sol += 1

    itr = re.finditer("SAM", stringToTest)
    for match in itr:
        if (match.start() + 1, width - total + match.start()) in matches:
            sol += 1
    stringToTest = ""

print(sol)


