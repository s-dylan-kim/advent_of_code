def p1():
    with open('input.txt', 'r') as file:
        input = file.readline().strip()

    sol = 0

    cur_id = 0
    idx = 0
    blocks = []

    block_next = True

    for c in input:
        block_size = int(c)
        if block_next:
            blocks.append((cur_id, idx, block_size))
            cur_id += 1
        else:
            blocks.append((-1, idx, block_size))
        idx += block_size
        block_next = not block_next

    front_ptr = 0

    while front_ptr < len(blocks):
        if blocks[front_ptr][0] != -1:
            (block_id, block_idx, block_size) = blocks[front_ptr]
            coef = (2 * block_idx + block_size - 1) * block_size // 2
            sol += coef * block_id
        else:

            (block_id, block_idx, block_size) = blocks[front_ptr]

            while block_size > 0 and front_ptr < len(blocks): # second part is here so that we dont backtrack into stuff already used
                (last_block_id, last_block_idx, last_block_size) = blocks[len(blocks) - 1]

                if last_block_size > block_size:
                    blocks[len(blocks) - 1] = (last_block_id, last_block_idx, last_block_size - block_size)
                    coef = (2 * block_idx + block_size - 1) * block_size // 2
                    sol += coef * last_block_id
                    block_size -= block_size
                    block_idx += block_size

                else:
                    del blocks[-2:]
                    coef = (2 * block_idx + last_block_size - 1) * last_block_size // 2
                    sol += coef * last_block_id
                    block_size -= last_block_size
                    block_idx += last_block_size

        front_ptr += 1

    print(f"p1: {sol}")


def p2():
    with open('input.txt', 'r') as file:
        input = file.readline().strip()

    sol = 0

    idx = 0
    blocks = []
    empty_blocks = []

    block_next = True

    for c in input:
        block_size = int(c)
        if block_next:
            blocks.append((idx, block_size))
        else:
            empty_blocks.append((idx, block_size))
        idx += block_size
        block_next = not block_next

    for block_id in range(len(blocks) - 1, -1, -1):
        (block_idx, block_size) = blocks[block_id]
        for empty_blocks_idx, (empty_block_idx, empty_block_size) in enumerate(empty_blocks):
            if empty_block_idx > block_idx:
                break
            if block_size <= empty_block_size:
                blocks[block_id] = (empty_block_idx, block_size)
                if block_size == empty_block_size:
                    del empty_blocks[empty_blocks_idx]
                else:
                    empty_blocks[empty_blocks_idx] = (empty_block_idx + block_size, empty_block_size - block_size)
                break

    for block_id, (block_idx, block_size) in enumerate(blocks):
        coef = (2 * block_idx + block_size - 1) * block_size // 2
        sol += coef * block_id

    print(f"p2: {sol}")


p1()
p2()