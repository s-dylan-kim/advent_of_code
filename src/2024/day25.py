def p1():
    with open('input.txt', 'r') as file:
        schematics = file.read().strip().split("\n\n")

    keys = []
    locks = []

    for schematic in schematics:
        schematic = schematic.strip().split("\n")
        values = []
        for i in range(len(schematic[0])):
            for j in range(1, len(schematic)):
                if schematic[j][i] != schematic[0][0]:
                    values.append(j)
                    break

        if schematic[0][0] == '.':
            keys.append(values)
        else:
            locks.append(values)

    sol = 0

    for key in keys:
        for lock in locks:
            works = True
            for idx in range(len(key)):
                if key[idx] < lock[idx]:
                    works = False
                    break

            if works:
                sol += 1

    print(sol)


p1()
