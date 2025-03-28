def recursive_calc (target, operands, prev_val, idx):
    add_val = prev_val + operands[idx]
    mult_val = prev_val * operands[idx]
    concat_val = int(str(prev_val) + str(operands[idx]))

    if idx == len(operands) - 1:
        return mult_val == target or add_val == target or concat_val == target

    if add_val <= target:
        if recursive_calc(target, operands, add_val, idx + 1):
            return True
    if mult_val <= target:
        if recursive_calc(target, operands, mult_val, idx + 1):
            return True
    if concat_val <= target:
        if recursive_calc(target, operands, concat_val, idx + 1):
            return True

    return False


def p1():
    with open('input.txt', 'r') as file:
        data = [line.strip().split(':') for line in file]
        targets = [int(line[0]) for line in data]
        operands = [list(map(int, line[1].strip().split(' '))) for line in data]

    sol = 0

    for idx, target in enumerate(targets):
        # print(f"{target}: ")
        if recursive_calc(target, operands[idx], operands[idx][0], 1):
            sol += target
            # print(True)

    print(sol)

p1()
