sol = 0

with open('input.txt', 'r') as file:
    string = file.read()
print(string)

pattern = "mul(,)"
pattern_idx = 0 # indicies of the pattern matched
digit_idx = [4, 5]
cur_num = ''
num_1 = 0

enable_pattern = "do()"
enable_idx = 0
disable_pattern = "don't()"
disable_idx = 0

enabled = True

for c in string:
    # print(c)
    # print(f"matching idx: {pattern_idx}")
    if c == enable_pattern[enable_idx]:
        enable_idx += 1
        if enable_idx == len(enable_pattern):
            enabled = True
            enable_idx = 0
    else:
        enable_idx = 0
        if c == enable_pattern[0]:
            enable_idx = 1

    if c == disable_pattern[disable_idx]:
        disable_idx += 1
        if disable_idx == len(disable_pattern):
            enabled = False
            disable_idx = 0
    else:
        disable_idx = 0
        if c == disable_pattern[0]:
            disable_idx = 1

    if pattern_idx in digit_idx:
        if pattern_idx == 4 and c == ',':
            if cur_num != '':
                num_1 = int(cur_num)
                cur_num = ""
                pattern_idx += 1
            else:
                pattern_idx = 0
        elif pattern_idx == 5 and c == ')':
            if cur_num != '':
                if enabled:
                    sol += int(cur_num) * num_1
                print(f"{num_1}, {int(cur_num)} = {int(cur_num) * num_1}")
                cur_num = ""
            pattern_idx = 0
        elif '0' <= c <= '9':
            cur_num += c
        else:
            pattern_idx = 0
            if c == 'm':
                pattern_idx = 1
            cur_num = ""
    else:
        if pattern[pattern_idx] == c:
            pattern_idx += 1
        else:
            pattern_idx = 0
            if c == 'm':
                pattern_idx = 1
            cur_num = ""
print(sol)
