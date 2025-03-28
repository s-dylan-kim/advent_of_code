from heapq import heappush, heappop
from queue import Queue
from collections import defaultdict

def p1():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    start_row, start_col, end_row, end_col = 0, 0, 0, 0

    print(matrix)

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 'S':
                start_row = row
                start_col = col
                matrix[row][col] = '.'
            if c == 'E':
                end_row = row
                end_col = col
                # matrix[row][col] = '.'

    to_visit = []
    visited = set()

    heappush(to_visit, (0, start_row, start_col, (0, 1)))

    max_dist = -1

    while True:
        (dist, row, col, (dy, dx)) = heappop(to_visit)
        if ((row, col), (dy, dx)) in visited:
            continue
        visited.add(((row, col), (dy, dx)))
        # print(f"({row}, {col})")

        if matrix[row][col] == 'E':
            print(f"part 1: {dist}")
            return dist

        if matrix[row + dy][col + dx] != '#':
            heappush(to_visit, (dist + 1, row + dy, col + dx, (dy, dx)))

        if dy == 0:
            if matrix[row + 1][col] != '#':
                heappush(to_visit, (dist + 1001, row + 1, col, (1, 0)))
            if matrix[row - 1][col] != '#':
                heappush(to_visit, (dist + 1001, row - 1, col, (-1, 0)))
        else:
            if matrix[row][col + 1] != '#':
                heappush(to_visit, (dist + 1001, row, col + 1, (0, 1)))
            if matrix[row][col - 1] != '#':
                heappush(to_visit, (dist + 1001, row, col - 1, (0, -1)))


def p2():
    with open('input.txt', 'r') as file:
        matrix = [list(line.strip()) for line in file]

    start_row, start_col, end_row, end_col = 0, 0, 0, 0

    print(matrix)

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 'S':
                start_row = row
                start_col = col
                matrix[row][col] = '.'
            if c == 'E':
                end_row = row
                end_col = col
                # matrix[row][col] = '.'

    to_visit = []
    visited = {}

    heappush(to_visit, (0, start_row, start_col, (0, 1)))

    max_dist = -1

    while True:
        (dist, row, col, (dy, dx)) = heappop(to_visit)

        if ((row, col), (dy, dx)) in visited:
            continue

        if max_dist != -1 and max_dist < dist:
            break

        min_dist = dist
        if ((row, col), (dy, dx)) in visited:
            min_dist = min(dist, visited[((row, col), (dy, dx))])
        visited[((row, col), (dy, dx))] = min_dist
        # print(f"({row}, {col})")

        if matrix[row][col] == 'E':
            max_dist = dist
            continue

        if matrix[row + dy][col + dx] != '#':
            heappush(to_visit, (dist + 1, row + dy, col + dx, (dy, dx)))

        if dy == 0:
            if matrix[row + 1][col] != '#':
                heappush(to_visit, (dist + 1001, row + 1, col, (1, 0)))
            if matrix[row - 1][col] != '#':
                heappush(to_visit, (dist + 1001, row - 1, col, (-1, 0)))
        else:
            if matrix[row][col + 1] != '#':
                heappush(to_visit, (dist + 1001, row, col + 1, (0, 1)))
            if matrix[row][col - 1] != '#':
                heappush(to_visit, (dist + 1001, row, col - 1, (0, -1)))

    # bfs from end
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    queue = Queue()

    for direction in directions:
        if ((end_row, end_col), direction) in visited:
            queue.put((max_dist, (end_row, end_col), direction))

    # print(queue.qsize())

    # print(visited)

    sol_set = defaultdict(set)
    while not queue.empty():
        dist, (row, col), direction = queue.get()
        (dy, dx) = direction
        # print(f"{dist}, ({row}, {col}), ({dy}, {dx})")

        if (row, col) in sol_set and sol_set[(row, col)] == direction:
            continue

        sol_set[(row, col)].add(direction)

        if ((row - dy, col - dx), direction) in visited and visited[((row - dy, col - dx), direction)] == dist - 1:
            queue.put((dist - 1, (row - dy, col - dx), direction))

        if dy == 0:
            if ((row - dy, col - dx), (-1, 0)) in visited and visited[((row - dy, col - dx), (-1, 0))] == dist - 1001:
                queue.put((dist - 1001, (row - dy, col - dx), (-1, 0)))
            if ((row - dy, col - dx), (1, 0)) in visited and visited[((row - dy, col - dx), (1, 0))] == dist - 1001:
                queue.put((dist - 1001, (row - dy, col - dx), (1, 0)))
        else:
            if ((row - dy, col - dx), (0, -1)) in visited and visited[((row - dy, col - dx), (0, -1))] == dist - 1001:
                queue.put((dist - 1001, (row - dy, col - dx), (0, -1)))

            # print(((row, col - 1), (0, 1)) in visited)
            # if ((row, col - 1), (0, 1)) in visited:
            #     print(visited[((row, col - 1), (0, 1))] == dist - 1001)

            if ((row - dy, col - dx), (0, 1)) in visited and visited[((row - dy, col - dx), (0, 1))] == dist - 1001:
                queue.put((dist - 1001, (row - dy, col - dx), (0, 1)))

    print(f"p2: {len(sol_set)}")


p1()
p2()
