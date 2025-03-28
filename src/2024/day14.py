from parse import parse, compile
import matplotlib.pyplot as plt


def p1():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n")

    p = compile("p={:d},{:d} v={:d},{:d}")
    parsed_input = []

    for line in input:
        match = p.parse(line).fixed
        parsed_input.append((match[:2], match[2:]))

    quad_count = [0, 0, 0, 0]

    for ((x_pos, y_pos), (x_vel, y_vel)) in parsed_input:
        quad = 0

        final_x = (x_pos + 100 * x_vel) % 101

        if final_x == 50:
            continue

        if final_x > 50:
            quad += 2

        final_y = (y_pos + 100 * y_vel) % 103

        if final_y == 51:
            continue

        if final_y > 51:
            quad += 1

        quad_count[quad] += 1

    sol = 1

    for val in quad_count:
        sol *= val

    print(f"p1: {sol}")


def p2():
    with open('input.txt', 'r') as file:
        input = file.read().split("\n")

    p = compile("p={:d},{:d} v={:d},{:d}")
    parsed_input = []

    for line in input:
        match = p.parse(line).fixed
        parsed_input.append((match[:2], match[2:]))

    for t in range(14, 10000, 101):
        img = [[0] * 101 for _ in range(103)]
        for ((x_pos, y_pos), (x_vel, y_vel)) in parsed_input:
            final_x = (x_pos + t * x_vel) % 101
            final_y = (y_pos + t * y_vel) % 103
            img[final_y][final_x] = 1
        plt.imshow(img)
        plt.savefig(f"./tree_image/{t}.png")


p1()
p2()
