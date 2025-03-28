import copy


def p1():
    with open('input.txt', 'r') as file:
        input = [line.strip().split('-') for line in file]

    connections = {}

    for connection in input:
        left = connection[0]
        right = connection[1]

        if left not in connections:
            connections[left] = set()
        if right not in connections:
            connections[right] = set()

        if left < right:    # store neighbor in lower alpha node
            connections[left].add(right)
        else:
            connections[right].add(left)

    print(connections)

    sol = 0

    for node in connections:
        for neighbor in connections[node]:
            for third in connections[neighbor]:
                if third in connections[node] and (node[0] == 't' or neighbor[0] == 't' or third[0] == 't'):
                    print(f"{node}, {neighbor}, {third}")
                    sol += 1

    print(f"p1: {sol}")


def p2():
    with open('input.txt', 'r') as file:
        input = [line.strip().split('-') for line in file]

    connections = {}

    for connection in input:
        left = connection[0]
        right = connection[1]

        if left not in connections:
            connections[left] = set()
        if right not in connections:
            connections[right] = set()

        if left < right:    # store neighbor in lower alpha node
            connections[left].add(right)
        else:
            connections[right].add(left)

    print(connections)

    sol = 0
    password = ""

    for node in connections:
        (max_clique_size, cur_password) = find_clique(connections, {node})
        max_clique_size += 1
        cur_password = node + "," + cur_password
        if max_clique_size > sol:
            sol = max_clique_size
            password = cur_password

    print(f"p2: {sol}| {password}")


def find_clique(connections, cur_set):
    candidates = connections[next(iter(cur_set))]

    for node in cur_set:
        candidates = candidates.intersection(connections[node])

    sol = 0
    str = ""

    for candidate in candidates:
        new_set = copy.deepcopy(cur_set)
        new_set.add(candidate)
        (cur, ans) = find_clique(connections, new_set)
        cur += 1 # account for candidate
        ans = candidate + "," + ans
        if cur > sol:
            sol = cur
            str = ans

    return sol, str


p2()
