from collections import deque
DIMENSION_SIZE = 71
BYTE_COUNT = 12


def p1():
    with open('input.txt', 'r') as file:
        lines = [list(map(int, line.split(","))) for line in file]

    print(lines)

    walls = set()
    for i in range(BYTE_COUNT):
        walls.add((lines[i][1], lines[i][0]))

    visited = set()
    queue = deque()
    queue.append((0, 0, 0))

    directions = [(-1, 0), (1, 0), (0, 1), (0, -1)]

    while len(queue) > 0:
        (row, col, distance) = queue[0]
        queue.popleft()

        if (row, col) in visited:
            continue

        visited.add((row, col))

        if row == DIMENSION_SIZE - 1 and col == DIMENSION_SIZE - 1:
            print(distance)
            return True

        for (dy, dx) in directions:
            if in_bounds(row + dy, col + dx, DIMENSION_SIZE, DIMENSION_SIZE):
                if (row + dy, col + dx) not in walls:
                    queue.append((row + dy, col + dx, distance + 1))


def in_bounds(row, col, height, width):
    return 0 <= row < height and 0 <= col < width


def p2():
    with open('input.txt', 'r') as file:
        lines = [list(map(int, line.split(","))) for line in file]

    rightmost_unincluded_wall = 0
    lower_bound = 0
    upper_bound = len(lines) - 1

    walls = set()

    while lower_bound < upper_bound:
        print(lower_bound, upper_bound)

        attempt = (lower_bound + upper_bound + 1) // 2

        if attempt > rightmost_unincluded_wall:
            for i in range(rightmost_unincluded_wall, attempt):
                walls.add((lines[i][1], lines[i][0]))
        else:
            for i in range(attempt, rightmost_unincluded_wall):
                walls.remove((lines[i][1], lines[i][0]))
        rightmost_unincluded_wall = attempt

        print(attempt, len(walls))

        if p1_modified(walls):
            print(True)
            lower_bound = attempt
        else:
            print(False)
            upper_bound = attempt - 1

    print(lower_bound)
    print(lines[lower_bound])


def p1_modified(walls):
    visited = set()
    queue = deque()
    queue.append((0, 0, 0))

    directions = [(-1, 0), (1, 0), (0, 1), (0, -1)]

    while len(queue) > 0:
        (row, col, distance) = queue[0]
        queue.popleft()

        if (row, col) in visited:
            continue

        visited.add((row, col))

        if row == DIMENSION_SIZE - 1 and col == DIMENSION_SIZE - 1:
            return True

        for (dy, dx) in directions:
            if in_bounds(row + dy, col + dx, DIMENSION_SIZE, DIMENSION_SIZE):
                if (row + dy, col + dx) not in walls:
                    queue.append((row + dy, col + dx, distance + 1))


p1()
p2()
