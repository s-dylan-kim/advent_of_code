from collections import deque


def p1():
    with open('input.txt', 'r') as file:
        codes = [int(line.strip()) for line in file]

    for _ in range(2000):
        for idx, code in enumerate(codes):
            cur = code

            cur = ((cur << 6) ^ cur) % 16777216
            cur = ((cur >> 5) ^ cur) % 16777216
            cur = ((cur << 11) ^ cur) % 16777216

            codes[idx] = cur

    print(sum(codes))


def p2():
    with open('input.txt', 'r') as file:
        codes = [int(line.strip()) for line in file]

    prices = [[0] * 2001 for _ in codes]

    for idx, code in enumerate(codes):
        prices[idx][0] = code

    for idx, _ in enumerate(codes):
        for i in range(1, 2001):
            cur = prices[idx][i - 1]
            cur = ((cur << 6) ^ cur) % 16777216
            cur = ((cur >> 5) ^ cur) % 16777216
            cur = ((cur << 11) ^ cur) % 16777216
            prices[idx][i] = cur

    diffs_list = [[0] * 2000 for _ in codes]
    val_list = [[0] * 2000 for _ in codes]

    for idx, _ in enumerate(codes):
        for i in range(2000):
            diffs_list[idx][i] = (prices[idx][i + 1] % 10) - (prices[idx][i] % 10)
            val_list[idx][i] = prices[idx][i + 1] % 10

    master_list = {}
    for code_idx, diffs in enumerate(diffs_list):
        cur_queue = deque()
        cur_dict = {}
        for idx, diff in enumerate(diffs):
            cur_queue.append(diff)
            if len(cur_queue) > 4:
                cur_queue.popleft()
            if len(cur_queue) == 4:
                cur_seq = ' '.join(str(queue_val) for queue_val in cur_queue)
                if cur_seq not in cur_dict:
                    cur_dict[cur_seq] = val_list[code_idx][idx]

        for sequence in cur_dict:
            if sequence not in master_list:
                master_list[sequence] = 0
            master_list[sequence] += cur_dict[sequence]
            # print(master_list)

    sol = -1
    for sequence in master_list:
        if master_list[sequence] > sol:
            sol = master_list[sequence]
    print(f"p2: {sol}")


p1()
p2()
