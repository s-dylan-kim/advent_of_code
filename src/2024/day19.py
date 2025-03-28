def p1_failed():
    with open('input.txt', 'r') as file:
        data = file.read().split("\n\n")
        towels = data[0].replace(" ", "").split(",")
        patterns = data[1].split("\n")

    max_len = 0
    for pattern in patterns:
        if len(pattern) > max_len:
            max_len = len(pattern)

    print(max_len)

    possible_strings = [set()]
    possible_strings[0].add("")

    for i in range(1, max_len + 1):
        print(i)
        print(len(possible_strings[i-1]))
        possible_strings.append(set())
        for towel in towels:
            if len(towel) > i:
                continue

            for prefix in possible_strings[i - len(towel)]:
                possible_strings[i].add(prefix + towel)

    sol = 0

    for pattern in patterns:
        if pattern in possible_strings[len(pattern)]:
            sol += 1

    print(f"p1: {sol}")


def p1():
    with open('input.txt', 'r') as file:
        data = file.read().split("\n\n")
        towels = set(data[0].replace(" ", "").split(","))
        patterns = data[1].split("\n")

    sol = 0

    for pattern in patterns:
        dp = [False for i in range(len(pattern) + 1)] # up to index i exclusive matched
        dp[0] = True
        for i in range(1, len(pattern) + 1):
            for k in range(1, i + 1):
                if dp[i - k] and pattern[i - k: i] in towels:
                    dp[i] = True
                    break
        if dp[len(pattern)]:
            sol += 1

    print(f"p1: {sol}")


def p2():
    with open('input.txt', 'r') as file:
        data = file.read().split("\n\n")
        towels = set(data[0].replace(" ", "").split(","))
        patterns = data[1].split("\n")

    sol = 0

    for pattern in patterns:
        dp = [0 for i in range(len(pattern) + 1)] # up to index i exclusive matched
        dp[0] = 1
        for i in range(1, len(pattern) + 1):
            for k in range(1, i + 1):
                if dp[i - k] != 0 and pattern[i - k: i] in towels:
                    dp[i] += dp[i - k]
        sol += dp[len(pattern)]

    print(f"p2: {sol}")


p1()
p2()
