sample = ["a", 90, 8, "X55", "1z", 102, "asdf", 65, 10, "word", "567", 567]


sample = [str(x) if type(x) == int else x for x in sample]


sample.sort()
print("Sorted list:", sample)


sample.reverse()
print("Reversed list:", sample)


numbers_only = [x for x in sample if type(x) == int]
print("Numbers only:", numbers_only)


def build_matrix(n):
    matrix = []
    for i in range(n):
        row = [(j % n) + 1 for j in range(i, i + n)]
        matrix.append(row)
    return matrix


matrix = build_matrix(4)
print("Matrix:")
for row in matrix:
    print(row)