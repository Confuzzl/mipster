import parse

with open("text.txt", "r", encoding="utf-8") as f:
    lines = f.readlines()
    for line in lines:
        if not line.startswith("BookmarkTitle:"):
            continue
        print(parse.parse("BookmarkTitle: {}\n", line)[0])
        # print(p[0], p[2])
