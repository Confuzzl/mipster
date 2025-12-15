import parse

PAGE_OFFSET = 0


def parse_top_level(line) -> tuple[str, parse.Result] | None:
    if (c := parse.parse("Chapter {:d}: {}.{}. {:d}", line)) is not None:
        c: parse.Result
        return ("Chapter", c)
    if (a := parse.parse("Appendix {}: {}.{}. {:d}", line)) is not None:
        a: parse.Result
        return ("Appendix", a)
    return None


bookmarks = ""


def write_bookmark(title: str, depth: str, page: int):
    global bookmarks

    bookmarks += "BookmarkBegin\n"
    bookmarks += f"BookmarkTitle: {title}\n"
    bookmarks += f"BookmarkLevel: {depth}\n"
    bookmarks += f"BookmarkPageNumber: {page + PAGE_OFFSET}\n"


with open("vol3template.txt", "r", encoding="utf-8") as temf, \
        open("toc.txt", "r", encoding="utf-8") as tocf, \
        open("vol3out.txt", "w", encoding="utf-8") as out:

    template = temf.read()
    toc = tocf.read()

    for line in toc.splitlines()[1:]:
        if (p := parse_top_level(line)) is not None:
            pre, res = p
            write_bookmark(f"{pre} {res[0]}: {res[1]}".strip(), 1, res[3])
        else:
            if (p := parse.parse("{}: {}.{}. {:d}", line)) is not None:
                number: str = p[0]
                title: str = p[1]
                page: int = p[3]
                depth = number.count(".") + 1
                # print(number, title, page, depth)

                write_bookmark(f"{number}: {title}".strip(), depth, page)
            else:
                print("!!!", line)
