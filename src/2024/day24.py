def p1():
    with open('input.txt', 'r') as file:
        input = file.read().strip().split("\n\n")

    top = input[0].strip().split("\n")
    bottom = input[1].strip().split("\n")

    values = {}

    for value in top:
        parsed = value.split(":")
        values[parsed[0].strip()] = int(parsed[1].strip())

    for equation in bottom:
        operand1 = equation[0:3]
        operand2 = equation[-10: -7]
        result = equation[-3:]
        operation = equation[4:7]
        values[result] = (operand1, operand2, operation)

    max_val = -1

    for value in values:
        if value[0] == 'z':
            if int(value[1:3]) > max_val:
                max_val = int(value[1:3])

    for i in range(max_val, -1, -1):
        suffix = ""
        if i < 10:
            suffix += "0"
        suffix += str(i)
        print(get_val(values, "z" + suffix), end='')


def get_val(values, idx):
    if type(values[idx]) is tuple:
        (operand1, operand2, operation) = values[idx]
        if operation == "AND":
            result = get_val(values, operand1) & get_val(values, operand2)
        elif operation == "XOR":
            result = get_val(values, operand1) ^ get_val(values, operand2)
        else:
            result = get_val(values, operand1) | get_val(values, operand2)
        # values[idx] = result
        return result
    else:
        return values[idx]


def p2():
    with open('input.txt', 'r') as file:
        inputs = file.read().strip().split("\n\n")

    top = inputs[0].strip().split("\n")
    bottom = inputs[1].strip().split("\n")

    values = {}

    for value in top:
        parsed = value.split(":")
        values[parsed[0].strip()] = int(parsed[1].strip())

    for equation in bottom:
        operand1 = equation[0:3]
        operand2 = equation[-10: -7]
        result = equation[-3:]
        operation = equation[4:7]
        values[result] = (operand1, operand2, operation)

    max_val = -1

    for value in values:
        if value[0] == 'z':
            if int(value[1:3]) > max_val:
                max_val = int(value[1:3])

    prev_carry_out = "mtk"
    # for i in range(1, max_val - 1):
    #     suffix = ""
    #     if i < 10:
    #         suffix += "0"
    #     suffix += str(i)
    #     code_z = "z" + suffix
    #
    #     equation = values[code_z]
    #
    #     if equation[]

    for i in range(max_val, -1, -1):
        print(i % 10, end='')
    print("")

    print(" ", end="")
    for i in range(max_val - 1, -1, -1):
        suffix = ""
        if i < 10:
            suffix += "0"
        suffix += str(i)
        print(get_val(values, "x" + suffix), end='')

    print("")
    print(" ", end="")
    for i in range(max_val - 1, -1, -1):
        suffix = ""
        if i < 10:
            suffix += "0"
        suffix += str(i)
        print(get_val(values, "y" + suffix), end='')

    print("")
    for i in range(max_val, -1, -1):
        suffix = ""
        if i < 10:
            suffix += "0"
        suffix += str(i)
        print(get_val(values, "z" + suffix), end='')

    print("")

    while True:
        code = input("enter code: ")
        print(values[code][0], values[code][2], values[code][1], sep=" ")


p2()
