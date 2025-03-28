from parse import parse, compile


def p1():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n\n")

    p = compile("Button A: X+{:d}, Y+{:d}\nButton B: X+{:d}, Y+{:d}\nPrize: X={:d}, Y={:d}")

    parsed_input = []
    sol = 0

    for line in input:
        match = p.parse(line).fixed
        parsed_input.append((match[0:2], match[2:4], match[4:6]))

    for idx, line in enumerate(parsed_input):
        x_target = line[2][0]
        y_target = line[2][1]

        a_x = line[0][0]
        a_y = line[0][1]
        b_x = line[1][0]
        b_y = line[1][1]

        a_count = 0
        b_count = 0

        x_total = 0
        y_total = 0

        min_coins = None

        while x_total < x_target and y_total < y_target:
            x_total += a_x
            y_total += a_y
            a_count += 1

        while a_count > 0 or x_total <= x_target and y_total <= y_target:
            if x_total > x_target or y_total > y_target:
                x_total -= a_x
                y_total -= a_y
                a_count -= 1
            if x_total == x_target and y_total == y_target:
                if min_coins is None or min_coins > (3*a_count + b_count):
                    min_coins = 3*a_count + b_count
                x_total -= a_x
                y_total -= a_y
                a_count -= 1
            if x_total <= x_target and y_total <= y_target:
                x_total += b_x
                y_total += b_y
                b_count += 1

        if min_coins is not None:
            sol += min_coins
            print(f"idx: {idx} val: {min_coins}")

    print(sol)


def p2():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n\n")

    p = compile("Button A: X+{:d}, Y+{:d}\nButton B: X+{:d}, Y+{:d}\nPrize: X={:d}, Y={:d}")

    parsed_input = []
    sol = 0

    for line in input:
        match = p.parse(line).fixed
        parsed_input.append((match[0:2], match[2:4], match[4:6]))

    for idx, line in enumerate(parsed_input):
        x_target = line[2][0] + 10000000000000
        y_target = line[2][1] + 10000000000000

        a_x = line[0][0]
        a_y = line[0][1]
        b_x = line[1][0]
        b_y = line[1][1]

        det = a_x * b_y - a_y * b_x

        if det == 0:
            print("HELP")

        a_count = (b_y * x_target - b_x * y_target)
        b_count = (a_x * y_target - a_y * x_target)

        if a_count % det != 0 or b_count % det != 0:
            continue
        else:
            sol += (a_count//det)*3 + (b_count//det)

    print(sol)


p2()
