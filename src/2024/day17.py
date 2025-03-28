from parse import parse, compile


def p1():
    with open('input.txt', 'r') as file:
        reg_a = int(file.readline().strip().split(" ")[2])
        reg_b = int(file.readline().strip().split(" ")[2])
        reg_c = int(file.readline().strip().split(" ")[2])
        file.readline()
        memory = list(map(int, file.readline().strip().split(" ")[1].split(",")))

    print(reg_a, reg_b, reg_c)
    print(memory)

    ir = 0

    while 0 <= ir < len(memory):
        match memory[ir]:
            case 0:
                reg_a = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
            case 1:
                reg_b = reg_b ^ memory[ir + 1]
            case 2:
                reg_b = get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c) % 8
            case 3:
                if reg_a != 0:
                    ir = memory[ir+1]
                    continue
            case 4:
                reg_b = reg_b ^ reg_c
            case 5:
                print(get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c) % 8, end=',')
            case 6:
                reg_b = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
            case 7:
                reg_c = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
        ir += 2


def get_combo_op(op, reg_a, reg_b, reg_c):
    if 0 <= op <= 3:
        return op
    elif op == 4:
        return reg_a
    elif op == 5:
        return reg_b
    elif op == 6:
        return reg_c
    else:
        raise Exception("Combo Op Invalid")

def p2():
    with open('input.txt', 'r') as file:
        reg_a = int(file.readline().strip().split(" ")[2])
        reg_b = int(file.readline().strip().split(" ")[2])
        reg_c = int(file.readline().strip().split(" ")[2])
        file.readline()
        memory = list(map(int, file.readline().strip().split(" ")[1].split(",")))

    print(reg_a, reg_b, reg_c)
    print(memory)

    prev_vals = [0]

    for i in range(len(memory) - 1, -1, -1):
        new_arr = []
        for prev_val in prev_vals:
            for val in range(8):
                ret = -1
                reg_a = prev_val * 8 + val
                reg_b = 0
                reg_c = 0
                ir = 0
                while 0 <= ir < len(memory):
                    match memory[ir]:
                        case 0:
                            reg_a = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
                        case 1:
                            reg_b = reg_b ^ memory[ir + 1]
                        case 2:
                            reg_b = get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c) % 8
                        case 3:
                            if reg_a != 0:
                                break
                        case 4:
                            reg_b = reg_b ^ reg_c
                        case 5:
                            ret = get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c) % 8
                            # print(get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c) % 8, end=',')
                        case 6:
                            reg_b = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
                        case 7:
                            reg_c = reg_a >> get_combo_op(memory[ir + 1], reg_a, reg_b, reg_c)
                    ir += 2
                if ret == memory[i]:
                    new_arr.append(prev_val * 8 + val)
        prev_vals = new_arr
    prev_vals.sort()
    print(prev_vals)

p1()
p2()
