def p1():
    with open('input.txt', 'r') as file:
        codes = [line.strip() for line in file]

    dpad_coords = {'^': (0, 1), 'A': (0, 2), '<': (1, 0), 'v': (1, 1), '>': (1, 2)}
    dpad_banned_coord = {(0, 0)}

    dir_1_dist = {}

    for origin_coord in dpad_coords:
        dist_map = {}
        for dest_coord in dpad_coords:
            dist_map[dest_coord] = abs(dpad_coords[origin_coord][0] - dpad_coords[dest_coord][0]) + abs(dpad_coords[origin_coord][1] - dpad_coords[dest_coord][1]) + 1
        dir_1_dist[origin_coord] = dist_map

    cur_dict = dir_1_dist

    for _ in range(24):
        cur_dict = create_map(dpad_coords, cur_dict, dpad_banned_coord)

    dir_2_dist = cur_dict

    keypad_coords = {'7': (0, 0), '8': (0, 1), '9': (0, 2), '4': (1, 0), '5': (1, 1), '6': (1, 2), '1': (2, 0), '2': (2, 1), '3': (2,2), '0': (3, 1), 'A': (3, 2)}
    keypad_banned_coord = {(3, 0)}

    keypad_dist = create_map(keypad_coords, dir_2_dist, keypad_banned_coord)

    sol = 0

    for code in codes:
        cur_head = 'A'
        cur_sequence = 0
        for c in code:
            cur_sequence += keypad_dist[cur_head][c]
            cur_head = c
        sol += cur_sequence * int(code[0:3])

    print(sol)


def create_map(coords, prev_map, banned_coord):
    return_map = {}

    for origin_coord in coords:
        dist_map = {}
        for dest_coord in coords:
            (origin_row, origin_col) = coords[origin_coord]
            (dest_row, dest_col) = coords[dest_coord]

            best_sol = -1

            if dest_row != origin_row:
                # move row first
                cur_row = origin_row
                cur_col = origin_col
                cur_sol = 0
                cur_head = 'A'
                valid = True
                while cur_row != dest_row:
                    if dest_row > cur_row:
                        cur_sol += prev_map[cur_head]['v']
                        cur_head = 'v'
                        cur_row += 1
                    else:
                        cur_sol += prev_map[cur_head]['^']
                        cur_head = '^'
                        cur_row -= 1

                if (cur_row, cur_col) in banned_coord:
                    valid = False

                while cur_col != dest_col:
                    if dest_col > cur_col:
                        cur_sol += prev_map[cur_head]['>']
                        cur_head = '>'
                        cur_col += 1
                    else:
                        cur_sol += prev_map[cur_head]['<']
                        cur_head = '<'
                        cur_col -= 1

                cur_sol += prev_map[cur_head]['A']
                if valid and (best_sol == -1 or cur_sol < best_sol):
                    best_sol = cur_sol

            if dest_col != origin_col:
                # move col first
                cur_row = origin_row
                cur_col = origin_col
                cur_sol = 0
                cur_head = 'A'
                valid = True
                while cur_col != dest_col:
                    if dest_col > cur_col:
                        cur_sol += prev_map[cur_head]['>']
                        cur_head = '>'
                        cur_col += 1
                    else:
                        cur_sol += prev_map[cur_head]['<']
                        cur_head = '<'
                        cur_col -= 1

                if (cur_row, cur_col) in banned_coord:
                    valid = False

                while cur_row != dest_row:
                    if dest_row > cur_row:
                        cur_sol += prev_map[cur_head]['v']
                        cur_head = 'v'
                        cur_row += 1
                    else:
                        cur_sol += prev_map[cur_head]['^']
                        cur_head = '^'
                        cur_row -= 1
                cur_sol += prev_map[cur_head]['A']

                if valid and (best_sol == -1 or cur_sol < best_sol):
                    best_sol = cur_sol
            if best_sol == -1: # case of not moving
                best_sol = 1
            dist_map[dest_coord] = best_sol
        return_map[origin_coord] = dist_map
    return return_map


p1()
