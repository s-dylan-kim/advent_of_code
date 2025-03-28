def p1():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n\n")

    maze_input = input[0]
    directions = input[1]

    maze = list(map(list, maze_input.split("\n")))
    directions = list(directions.replace("\n", ""))

    boxes = set()
    walls = set()
    cur_row = 0
    cur_col = 0

    for row, line in enumerate(maze):
        for col, c in enumerate(line):
            if c == 'O':
                boxes.add((row, col))
            if c == '@':
                cur_row = row
                cur_col = col
            if c == '#':
                walls.add((row, col))

    direction_map = {'<': (0, -1), 'v': (1, 0), '>': (0, 1), '^':(-1, 0)}

    for direction in directions:
        (dy, dx) = direction_map[direction]

        if push(cur_row + dy, cur_col + dx, dy, dx, boxes, walls):
            cur_row += dy
            cur_col += dx

    sol = 0

    for box in boxes:
        sol += box[0] * 100 + box[1]

    print(sol)


def push(row, col, dy, dx, boxes, walls):
    if (row, col) in boxes:
        if push(row + dy, col + dx, dy, dx, boxes, walls):
            boxes.remove((row, col))
            boxes.add((row + dy, col + dx))
            return True
        return False
    if (row, col) in walls:
        return False
    return True


def p2():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n\n")

    maze_input = input[0]
    directions = input[1]

    maze = list(map(list, maze_input.split("\n")))
    directions = list(directions.replace("\n", ""))

    boxes = set()
    walls = set()
    cur_row = 0
    cur_col = 0

    for row, line in enumerate(maze):
        for col, c in enumerate(line):
            if c == 'O':
                boxes.add((row, 2 * col))
            if c == '@':
                cur_row = row
                cur_col = 2 * col
            if c == '#':
                walls.add((row, 2 * col))
                walls.add((row, 2 * col + 1))

    direction_map = {'<': (0, -1), 'v': (1, 0), '>': (0, 1), '^': (-1, 0)}

    print(boxes)

    for direction in directions:
        (dy, dx) = direction_map[direction]

        to_push = set()

        if push2(cur_row + dy, cur_col + dx, dy, dx, boxes, walls, to_push):
            cur_row += dy
            cur_col += dx

            for box in to_push:
                boxes.remove(box)
            for box in to_push:
                boxes.add((box[0] + dy, box[1] + dx))

        # print(boxes)
        # print(direction)
        # for row in range(len(maze)):
        #
        #     for col in range(len(maze[row]) * 2):
        #         if (row, col) in walls:
        #             print("#", end='')
        #         elif (row, col) in boxes:
        #             print("[", end='')
        #         elif (row, col - 1) in boxes:
        #             print("]", end='')
        #         elif row == cur_row and col == cur_col:
        #             print("@", end='')
        #         else:
        #             print('.', end='')
        #     print("")

    sol = 0

    print(boxes)

    for box in boxes:

        sol += box[0] * 100 + box[1]

    print(sol)


def push2(row, col, dy, dx, boxes, walls, to_push):
    if dy == 0:
        if dx == 1:
            if (row, col) in boxes:
                if push2(row + dy, col + dx + 1, dy, dx, boxes, walls, to_push):
                    to_push.add((row, col))
                    return True
                return False
        if dx == -1:
            if (row, col - 1) in boxes:
                if push2(row + dy, col + dx - 1, dy, dx, boxes, walls, to_push):
                    to_push.add((row, col - 1))
                    return True
                return False
    else:
        if (row, col) in boxes:
            if push2(row + dy, col + dx, dy, dx, boxes, walls, to_push) and push2(row + dy, col + dx + 1, dy, dx, boxes, walls, to_push):
                to_push.add((row, col))
                return True
            return False
        if (row, col - 1) in boxes:
            if push2(row + dy, col + dx - 1, dy, dx, boxes, walls, to_push) and push2(row + dy, col + dx, dy, dx, boxes, walls, to_push):
                to_push.add((row, col - 1))
                return True
            return False
    if (row, col) in walls:
        return False
    return True


p1()
p2()
