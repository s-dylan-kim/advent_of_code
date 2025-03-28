def recursive_fill(matrix, cache, row, col):
    val = matrix[row][col]

    if val == 9:
        cache[row][col] = {(row, col)}
        return

    ret_set = set()

    if row >= 1 and matrix[row - 1][col] == val + 1:
        if cache[row - 1][col] is None:
            recursive_fill(matrix, cache, row - 1, col)
        ret_set.update(cache[row - 1][col])

    if col >= 1 and matrix[row][col - 1] == val + 1:
        if cache[row][col - 1] is None:
            recursive_fill(matrix, cache, row, col - 1)
        ret_set.update(cache[row][col - 1])

    if row < len(matrix) - 1 and matrix[row + 1][col] == val + 1:
        if cache[row + 1][col] is None:
            recursive_fill(matrix, cache, row + 1, col)
        ret_set.update(cache[row + 1][col])

    if col < len(matrix[0]) - 1 and matrix[row][col + 1] == val + 1:
        if cache[row][col + 1] is None:
            recursive_fill(matrix, cache, row, col + 1)
        ret_set.update(cache[row][col + 1])

    cache[row][col] = ret_set


def recursive_fill2(matrix, cache, row, col):
    val = matrix[row][col]

    if val == 9:
        cache[row][col] = 1
        return 1

    ret_val = 0

    if row >= 1 and matrix[row - 1][col] == val + 1:
        if cache[row - 1][col] != -1:
            ret_val += cache[row - 1][col]
        else:
            ret_val += recursive_fill2(matrix, cache, row - 1, col)

    if col >= 1 and matrix[row][col - 1] == val + 1:
        if cache[row][col - 1] != -1:
            ret_val += cache[row][col - 1]
        else:
            ret_val += recursive_fill2(matrix, cache, row, col - 1)

    if row < len(matrix) - 1 and matrix[row + 1][col] == val + 1:
        if cache[row + 1][col] != -1:
            ret_val += cache[row + 1][col]
        else:
            ret_val += recursive_fill2(matrix, cache, row + 1, col)

    if col < len(matrix[0]) - 1 and matrix[row][col + 1] == val + 1:
        if cache[row][col + 1] != -1:
            ret_val += cache[row][col + 1]
        else:
            ret_val += recursive_fill2(matrix, cache, row, col + 1)

    cache[row][col] = ret_val
    return ret_val


def p1():
    with open('input.txt', 'r') as file:
        matrix = [list(map(int, list(line.strip()))) for line in file]
    cache = [[None for _ in range(len(matrix[0]))] for _ in range(len(matrix))]

    sol = 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 0:
                recursive_fill(matrix, cache, row, col)
                sol += len(cache[row][col])
    print(f"p1 sol: {sol}")


def p2():
    with open('input.txt', 'r') as file:
        matrix = [list(map(int, list(line.strip()))) for line in file]
    cache = [ [-1 for _ in range(len(matrix[0]))] for _ in range(len(matrix))]

    sol = 0

    for row, line in enumerate(matrix):
        for col, c in enumerate(line):
            if c == 0:
                sol += recursive_fill2(matrix, cache, row, col)
    print(f"p2 sol: {sol}")


p1()
p2()
