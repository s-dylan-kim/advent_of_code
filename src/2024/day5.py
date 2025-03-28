with open('input.txt', 'r') as file:
    groups = file.read().split("\n\n")

rules = groups[0].split("\n")
updates = groups[1].split("\n")

parsed_rules = [list(map(int, rule.split("|"))) for rule in rules]
parsed_updates = [list(map(int, update.split(","))) for update in updates]


def part1():
    sol = 0
    dependencies = dict()

    for rule in parsed_rules:
        if rule[1] not in dependencies:
            dependencies[rule[1]] = {rule[0]}
        else:
            dependencies[rule[1]].add(rule[0])

    for update in parsed_updates:
        banned_pages = set()
        passed = True
        for page in update:
            if page in banned_pages:
                passed = False
                break
            if page in dependencies:
                banned_pages.update(dependencies[page])
        if passed:
            sol += update[len(update)//2]
    return sol


def part2():
    sol = 0
    dependencies = dict()

    for rule in parsed_rules:
        if rule[1] not in dependencies:
            dependencies[rule[1]] = {rule[0]}
        else:
            dependencies[rule[1]].add(rule[0])

    dependency_count = {key: len(dependencies[key]) for key in dependencies}
    print(dependency_count)

    for update in parsed_updates:
        banned_pages = set()
        passed = True
        for page in update:
            if page in banned_pages:
                passed = False
                break
            if page in dependencies:
                banned_pages.update(dependencies[page])
            else:
                dependencies[page] = set()
                dependency_count[page] = 0
        if passed:
            pass
            # sol += update[len(update)//2]
        else:
            fixed_order = []
            while len(update) > 0:
                for page in update:
                    if len(dependencies[page].intersection(update)) == 0:
                        fixed_order.append(page)
                        update.remove(page)
                        break
            sol += fixed_order[len(fixed_order) // 2]
            # fix it
            # dependency_count_list = [(page, dependency_count[page]) for page in update]
            # dependency_count_list.sort(key=lambda x: x[1])
            # print(dependency_count_list)
            # for page in upd
    return sol


print(part2())
