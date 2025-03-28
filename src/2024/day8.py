import math


def inbounds(row, col, height, width):
    return 0 <= row < height and 0 <= col < width


def p1():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    width = len(matrix[0])
    height = len(matrix)

    coords = dict()
    antinodes = set()
    sol = 0

    for row, line in enumerate(matrix):
        for col, val in enumerate(line):
            if val != '.':
                for coord in coords.get(val, set()):
                    # get 4 coords
                    row_coord = coord[0]
                    col_coord = coord[1]

                    node1 = (2 * row - row_coord, 2 * col - col_coord)
                    if inbounds(*node1, height, width):
                        if node1 not in antinodes:
                            antinodes.add(node1)
                            sol += 1

                    node2 = (2 * row_coord - row, 2 * col_coord - col)
                    if inbounds(*node2, height, width):
                        if node2 not in antinodes:
                            antinodes.add(node2)
                            sol += 1

                    if (row * 2 + row_coord) % 3 == 0 and (col * 2 + col_coord) % 3 == 0:
                        node3 = ((row * 2 + row_coord)/3, (col * 2 + col_coord)/3)
                        if inbounds(*node3, height, width):
                            if node3 not in antinodes:
                                antinodes.add(node3)
                                sol += 1

                    if (row + row_coord*2) % 3 == 0 and (col + col_coord*2) % 3 == 0:
                        node4 = ((row + row_coord*2)/3, (col + col_coord*2)/3)
                        if inbounds(*node4, height, width):
                            if node4 not in antinodes:
                                antinodes.add(node4)
                                sol += 1
                if val not in coords:
                    coords[val] = set()
                coords[val].add((row, col))
    print(sol)


def p2():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    width = len(matrix[0])
    height = len(matrix)

    coords = dict()
    antinodes = set()
    sol = 0

    for row, line in enumerate(matrix):
        for col, val in enumerate(line):
            if val != '.':
                for coord in coords.get(val, set()):
                    diff = (row - coord[0], col - coord[1])
                    div = math.gcd(diff[0], diff[1])
                    min_step = (diff[0]/div, diff[1]/div)

                    cur = (row, col)

                    # one dir
                    while inbounds(*cur, height, width):
                        if cur not in antinodes:
                            antinodes.add(cur)
                            sol += 1
                        cur = (cur[0] + min_step[0], cur[1] + min_step[1])

                    # other dir
                    cur = (row - min_step[0], col - min_step[1])
                    while inbounds(*cur, height, width):
                        if cur not in antinodes:
                            antinodes.add(cur)
                            sol += 1
                        cur = (cur[0] - min_step[0], cur[1] - min_step[1])

                if val not in coords:
                    coords[val] = set()
                coords[val].add((row, col))
    print(sol)


p1()
p2()
