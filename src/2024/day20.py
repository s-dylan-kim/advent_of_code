from collections import deque

def p1():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    start_row, start_col, end_row, end_col = 0, 0, 0, 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 'S':
                start_row = row
                start_col = col
            elif c == 'E':
                end_row = row
                end_col = col

    start_dist = bfs(matrix, start_row, start_col)
    orig_time = start_dist[end_row][end_col]
    end_time = bfs(matrix, end_row, end_col)

    sol = 0

    skip_locations = [(-2, 0), (-1, -1), (-1, 1), (0, 2), (0, -2), (1, -1), (1, 1), (2, 0)]

    for row, line in enumerate(start_dist):
        for col, orig_distance in enumerate(line):
            if orig_distance != -1:
                for (dy, dx) in skip_locations:
                    if 0 <= row + dy < len(matrix) and 0 <= col + dx < len(matrix[row + dy]):
                        if end_time[row + dy][col + dx] != -1:
                            if orig_distance + end_time[row + dy][col + dx] + 2 <= orig_time - 100:
                                sol += 1
    print(f"p1: {sol}")
    return sol


def bfs(matrix, origin_row, origin_col):
    queue = deque()

    queue.append((origin_row, origin_col, 0))
    directions = [(-1, 0), (1, 0), (0, 1), (0, -1)]

    ret_matrix = [[-1] * len(matrix[i]) for i in range(len(matrix))]

    while len(queue) > 0:
        (row, col, distance) = queue[0]
        queue.popleft()

        if ret_matrix[row][col] != -1:
            continue

        ret_matrix[row][col] = distance

        for (dy, dx) in directions:
            if 0 <= row + dy < len(matrix) and 0 <= col + dx < len(matrix[row + dy]):
                if matrix[row + dy][col + dx] != '#':
                    queue.append((row + dy, col + dx, distance + 1))

    return ret_matrix


def p2():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    start_row, start_col, end_row, end_col = 0, 0, 0, 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 'S':
                start_row = row
                start_col = col
            elif c == 'E':
                end_row = row
                end_col = col

    start_dist = bfs(matrix, start_row, start_col)
    orig_time = start_dist[end_row][end_col]
    end_time = bfs(matrix, end_row, end_col)

    sol = 0

    for row, line in enumerate(start_dist):
        for col, orig_distance in enumerate(line):
            if orig_distance != -1:
                for dy in range(-20, 21):
                    for dx in range(-20 + abs(dy), 21 - abs(dy)):
                        if 0 <= row + dy < len(matrix) and 0 <= col + dx < len(matrix[row + dy]):
                            if end_time[row + dy][col + dx] != -1:
                                if orig_distance + end_time[row + dy][col + dx] + abs(dy) + abs(dx) <= orig_time - 100:
                                    sol += 1
    print(f"p2: {sol}")
    return sol


p1()
p2()
