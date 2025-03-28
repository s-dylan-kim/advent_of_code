from collections import defaultdict


def p1():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    locs = defaultdict(set)
    sol = 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            locs[c].add((row, col))

    for c in locs:
        unseen = locs[c]
        while len(unseen) != 0:
            seen = set()
            start = unseen.pop()
            unseen.add(start)
            floodfill(matrix, *start, seen, unseen)

            perim = 0
            for location in seen:
                perim += addval(*location, seen)
            sol += perim * len(seen)

    print(sol)


def addval(row, col, seen):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    ret_val = 0

    for (dy, dx) in directions:
        if (dy + row, dx + col) not in seen:
            ret_val += 1

    return ret_val


def inbounds(row, col, height, width):
    return 0 <= row < height and 0 <= col < width


def floodfill(matrix, row, col, seen, unseen):
    if (row, col) in seen:
        return
    seen.add((row, col))
    unseen.remove((row, col))

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    width = len(matrix[0])
    height = len(matrix)

    for (dy, dx) in directions:
        if inbounds(row + dy, col + dx, height, width):
            if matrix[row][col] == matrix[row + dy][col + dx]:
                floodfill(matrix, row + dy, col + dx, seen, unseen)


def p2():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    locs = defaultdict(set)
    sol = 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            locs[c].add((row, col))

    for c in locs:
        unseen = locs[c]
        while len(unseen) != 0:
            seen = set()
            start = unseen.pop()
            unseen.add(start)
            floodfill(matrix, *start, seen, unseen)

            edges = set()
            for location in seen:
                get_edges(*location, seen, edges)

            # floodfill on edges
            edge_count = 0
            while len(edges) != 0:
                edge_count += 1
                edge_start = edges.pop()
                edges.add(edge_start)
                edge_floodfill(*edge_start, edges)

            sol += edge_count * len(seen)

    print(sol)


def edge_floodfill(row, col, direction, edges):
    row_directions = [(-1, 0), (1, 0)]
    col_directions = [(0, -1), (0, 1)]

    edges.remove((row, col, direction))

    if direction in row_directions:
        for (dy, dx) in col_directions:
            if (dy + row, dx + col, direction) in edges:
                edge_floodfill(row + dy, col + dx, direction, edges)
    else:
        for (dy, dx) in row_directions:
            if (dy + row, dx + col, direction) in edges:
                edge_floodfill(row + dy, col + dx, direction, edges)


def get_edges(row, col, seen, edges):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    for (dy, dx) in directions:
        if (dy + row, dx + col) not in seen:
            edges.add((row, col, (dy, dx)))


p1()
p2()
