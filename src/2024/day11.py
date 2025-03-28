from collections import defaultdict

def p1():
    with open('input.txt', 'r') as file:
        arr = list(map(int, file.readline().strip().split()))

    for _ in range(25):
        new_arr = []
        for i in arr:
            if i == 0:
                new_arr.append(1)
                continue

            str_i = str(i)

            if len(str_i) % 2 == 0:
                new_arr.append(int(str_i[:len(str_i)//2]))
                new_arr.append(int(str_i[len(str_i)//2:]))
            else:
                new_arr.append(i * 2024)
        arr = new_arr
    print(len(arr))


def p2():
    with open('input.txt', 'r') as file:
        arr = list(map(int, file.readline().strip().split()))

    stone_dict = defaultdict(lambda: 0)

    for stone in arr:
        stone_dict[stone] += 1

    for _ in range(75):
        new_dict = defaultdict(lambda: 0)
        for stone in stone_dict:
            if stone == 0:
                new_dict[1] += stone_dict[0]
                continue

            str_i = str(stone)

            if len(str_i) % 2 == 0:
                new_dict[int(str_i[:len(str_i)//2])] += stone_dict[stone]
                new_dict[int(str_i[len(str_i)//2:])] += stone_dict[stone]
            else:
                new_dict[stone * 2024] += stone_dict[stone]
        stone_dict = new_dict

    sol = 0
    for stone in stone_dict:
        sol += stone_dict[stone]
    print(sol)


p1()
p2()