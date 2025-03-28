sol = 0
with open('input.txt', 'r') as file:
    vals = [line.split() for line in file]

list1 = [int(val[0]) for val in vals]
list2 = [int(val[1]) for val in vals]

list1.sort()
list2.sort()

print(sum([abs(element1 - element2) for element1, element2 in zip(list1, list2)]))

# p2

list1 = [int(val[0]) for val in vals]
list2 = [int(val[1]) for val in vals]

counts = dict()

for i in list2:
    counts[i] = counts.get(i, 0) + 1

print(sum([element * counts.get(element, 0) for element in list1]))
