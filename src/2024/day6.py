
def p1():
    with open('input.txt', 'r') as file:
        matrix = [line.strip() for line in file]

    bool_matrix = []
    visited = []
    sol = 1

    cur_point = (0, 0)

    for row, line in enumerate(matrix):
        cur_line = []
        for col, c in enumerate(line):
            cur_line.append(c == '#')
            if c == '^':
                cur_point = (row, col)
        visited.append([False] * len(line))
        bool_matrix.append(cur_line)

    facing = (-1, 0)

    visited[cur_point[0]][cur_point[1]] = True

    width = len(bool_matrix[0])
    height = len(bool_matrix)

    while check_bounds(cur_point[0] + facing[0], cur_point[1] + facing[1], width, height):
        # print(cur_point)
        new_row = cur_point[0] + facing[0]
        new_col = cur_point[1] + facing[1]
        if bool_matrix[new_row][new_col]:
            facing = rotate_cw(facing)
        else:
            cur_point = (new_row, new_col)
            if not visited[new_row][new_col]:
                visited[new_row][new_col] = True
                sol += 1

    return sol + 1


def p2():
    with open('input.txt', 'r') as file:
        matrix = [line.strip() for line in file]

    bool_matrix = []
    visited = []
    sol = 0

    cur_point = (0, 0)

    for row, line in enumerate(matrix):
        cur_line = []
        visited_line = []
        for col, c in enumerate(line):
            cur_line.append(c == '#')
            if c == '^':
                cur_point = (row, col)
            visited_line.append(set())
        visited.append(visited_line)
        bool_matrix.append(cur_line)

    facing = (-1, 0)

    width = len(bool_matrix[0])
    height = len(bool_matrix)

    rocks = set()

    while check_bounds(cur_point[0] + facing[0], cur_point[1] + facing[1], width, height):
        # print(cur_point)
        new_row = cur_point[0] + facing[0]
        new_col = cur_point[1] + facing[1]
        if bool_matrix[new_row][new_col]:
            facing = rotate_cw(facing)
        else:
            temp_visited = set()
            temp_facing = rotate_cw(facing)
            temp_point = cur_point
            temp_visited.add((temp_point, temp_facing))
            # print(cur_point)
            bool_matrix[new_row][new_col] = True
            while check_bounds(temp_point[0] + temp_facing[0], temp_point[1] + temp_facing[1], width, height):
                # print(f"visited {temp_point} facing {temp_facing}")
                temp_new_row = temp_point[0] + temp_facing[0]
                temp_new_col = temp_point[1] + temp_facing[1]
                if bool_matrix[temp_new_row][temp_new_col]:
                    temp_facing = rotate_cw(temp_facing)
                else:
                    temp_point = (temp_new_row, temp_new_col)
                    if (temp_point, temp_facing) in temp_visited:
                        if (new_row, new_col) not in rocks:
                            sol += 1
                            rocks.add((new_row, new_col))
                            print((new_row, new_col))
                        break
                    else:
                        temp_visited.add((temp_point, temp_facing))
            bool_matrix[new_row][new_col] = False
            cur_point = (new_row, new_col)
            if facing not in visited[new_row][new_col]:
                visited[new_row][new_col].add(facing)

    return sol


def check_bounds(row, col, width, height):
    return 0 <= row < width and 0 <= col < height


def rotate_cw(facing):
    match facing:
        case (0, 1):
            return 1, 0
        case (1, 0):
            return 0, -1
        case (0, -1):
            return -1, 0
        case (-1, 0):
            return 0, 1


print(p2())
