#!/usr/bin/env python3
"""
Checker helper for PCom / HTTP client assignment (#4)

Dependencies: pexpect
"""

import sys
import shlex
import traceback
from collections import namedtuple
import argparse
import re
import textwrap

import pexpect

TEST_USERNAME = "test"
TEST_PASSWORD = "test123"
EXPECT_TIMEOUT = 1  # 1 second should be enough...
TEXT_INDENT = "    "

EXPECT_SEP = "="

RE_SUCCESS = re.compile(r"^.*((?:^|\W)succ?ess?|(?:^|\W)ok(?:$|\W)|(?:^|\W)okay).*$", re.IGNORECASE)
RE_ERROR = re.compile(r"^.*((?:^|\W)err?oa?r|(?:^|\W)fail|(?:^|\W)esuat).*$", re.IGNORECASE)
# JSON parsing using RegExp: don't do this at home!
RE_BOOK_ID = r"id[ \t\f\v]*[=:][ \t\f\v]*([0-9]+)|\"id\"\s*:\s*\"?([0-9]+)"
RE_EXTRACT_FIELD = r"%s[ \t\f\v]*[=:][ \t\f\v]*([^\r\n]+)\s*?|\"%s\"\s*:\s*(?:\"([^\"]+)|([0-9]+))"


# classes used
class CheckerException(Exception): pass

def wrap_test_output(text, indent=TEXT_INDENT):
    return textwrap.indent(text, prefix=indent)

def color_print(text, fg="white", bg=None, style="normal", stderr=False, newline=True):
    """ Forgive this mess... but it's better than extra dependencies ;) """
    COLORS = ["black", "red", "green", "yellow", "blue", "purple", "cyan", "white"]
    STYLES = ["normal", "bold", "light", "italic", "underline", "blink"]
    fg = str(30 + COLORS.index(fg.lower()))
    bg = ("" if not bg else ";" + str(40 + COLORS.index(bg.lower())))
    style = str(STYLES.index(style.lower()))
    text = '\033[{style};{fg}{bg}m{text}\033[0;0m'.format(text=text, fg=fg, bg=bg, style=style)
    if stderr:
        sys.stderr.write(text + ("\n" if newline else ""))
    else:
        sys.stdout.write(text + ("\n" if newline else ""))

class ExpectInputWrapper:
    """ Utility IO class used for prefixing the debug output. """
    def __init__(self, direction=False):
        self._dir = direction
    def write(self, s):
        prefix = "  > " if self._dir else "  < "
        color_print(wrap_test_output(s.strip(), indent=prefix),
                    fg="white", style="italic")
    def flush(self): pass

def normalize_user(xargs):
    user = xargs.get("user")
    if user and isinstance(user, str):
        user_pair = user.split(":")
        xargs["user"] = { "username": user_pair[0], "password": user_pair[1] }
    if not xargs.get("user"):
        xargs["user"] = { "username": TEST_USERNAME, "password": TEST_PASSWORD }

def expect_send_params(p, xvars):
    keys = list(xvars.keys())
    xpatterns =  [(r"(" + kw + r")[ \t\f\v]*" + EXPECT_SEP + r"[ \t\f\v]*") for kw in keys]
    xseen = set()
    while xseen != set(keys):
        idx = p.expect(xpatterns)
        p.sendline(str(xvars.get(keys[idx])))
        xseen.add(keys[idx])

def expect_flush_output(p):
    i = p.expect([pexpect.TIMEOUT, pexpect.EOF])
    buf = p.before
    if i == 0 and p.before:
        p.expect(r'.+')
    return buf

def expect_print_output(p):
    res = p.expect([RE_SUCCESS, RE_ERROR, pexpect.TIMEOUT])
    color_args = {}
    text = p.after
    if res == 0:
        color_args = {"fg": "green"}
    elif res == 1:
        color_args = {"fg": "red"}
    else:
        text = p.before or "<no output>"
        if p.before:
            p.expect(r'.+')
            
    color_print(wrap_test_output(text.strip()), **color_args)

def extract_book_ids(output):
    matches = re.findall(RE_BOOK_ID, output)
    return [val[0] or val[1] for val in matches]

def extract_book_fields(output, field):
    matches = re.findall(RE_EXTRACT_FIELD % (field, field), output)
    return [val[0] or val[1] or val[2] for val in matches]

def do_register(p, xargs):
    normalize_user(xargs)
    p.sendline("register")
    expect_send_params(p, xargs["user"])
    expect_print_output(p)

def do_login(p, xargs):
    normalize_user(xargs)
    p.sendline("login")
    expect_send_params(p, xargs["user"])
    expect_print_output(p)

def do_enter(p, xargs):
    p.sendline("enter_library")
    expect_print_output(p)

def do_get_books(p, xargs):
    p.sendline("get_books")
    buf = expect_flush_output(p)
    xargs["book_ids"] = extract_book_ids(buf)
    xargs["book_titles"] = extract_book_fields(buf, "title")
    print(wrap_test_output("Retrieved book IDs + titles: \n" +
                                 str(xargs["book_ids"]) + "\n" + str(xargs["book_titles"])))
    expect_count = xargs.get("expect_count", False)
    if type(expect_count) is int:
        if len(xargs["book_ids"]) != expect_count:
            raise CheckerException("Book count mismatch: %s != %s" % 
                                   (len(xargs["book_ids"]), expect_count))
        color_print(wrap_test_output("OKAY: count=%i" % expect_count), fg="green", style="bold")

def do_add_book(p, xargs):
    book_titles = xargs.get("book_titles", [])
    book = xargs.get("book", {})
    if book["title"] in book_titles:
        color_print(wrap_test_output("SKIP: book already added!"), fg="yellow")
        return
    p.sendline("add_book")
    book_struct = { key : book.get(key, "") for key in ("title", "author", "genre", "publisher", "page_count") }
    expect_send_params(p, book_struct)
    expect_print_output(p)

def do_get_book_id(p, xargs):
    book_ids = xargs.get("book_ids")
    idx = xargs.get("book_idx")
    if not book_ids:
        raise CheckerException("No books found!")
    if idx >= len(book_ids):
        raise CheckerException("No book index: %s" % str(idx))
    book_id = book_ids[idx]
    p.sendline("get_book")
    expect_send_params(p, {"id": book_id})
    buf = expect_flush_output(p)
    expect_book = xargs.get("expect_book", False)
    if type(expect_book) is dict:
        for field in expect_book.keys():
            values = extract_book_fields(buf, field)
            if not values:
                raise CheckerException("Cannot find book field '%s'" % field)
            if len(values) != 1:
                raise CheckerException("Multiple '%s' fields found in output: %s!" % (field, values))
            if str(values[0]) != str(expect_book[field]):
                raise CheckerException("Book field '%s' mismatch: %s != %s" % 
                                       (field, values[0], expect_book[field]))
        color_print(wrap_test_output("OKAY: fields match!"), fg="green", style="bold")

def do_delete_book(p, xargs):
    book_ids = xargs.get("book_ids")
    idx = xargs.get("book_idx")
    if not book_ids:
        raise CheckerException("No books found!")
    if idx >= len(book_ids):
        raise CheckerException("No book index: %s" % str(idx))
    book_id = book_ids[idx]
    p.sendline("delete_book")
    expect_send_params(p, {"id": book_id})
    expect_print_output(p)

def do_delete_all_books(p, xargs):
    book_ids = xargs.get("book_ids")
    if not book_ids and not xargs.get("delete_books_ignore", False):
        raise CheckerException("No books found!")
    for book_id in book_ids:
        p.sendline("delete_book")
        expect_send_params(p, {"id": book_id})
        expect_print_output(p)

def do_logout(p, xargs):
    p.sendline("logout")
    expect_print_output(p)

def do_exit(p, xargs):
    if xargs.get("dont_exit", False):
        return
    p.sendline("exit")
    p.expect(pexpect.EOF)

def interactive_shell(p, xargs):
    p.setecho(True)
    p.interact()


ACTIONS = {
    "register": do_register,
    "login": do_login,
    "enter_library": do_enter,
    "get_books": do_get_books,
    "get_book_id": do_get_book_id,
    "add_book": do_add_book,
    "delete_book": do_delete_book,
    "delete_all_books": do_delete_all_books,
    "logout": do_logout,
    "exit": do_exit,
    "shell": interactive_shell,
}

SAMPLE_BOOKS = [
    {
        "title": "Computer Networks", "author": "A. Tanenbaum et. al.",
        "genre": "Manual", "publisher": "Prentice Hall", "page_count": 950,
    },
    {
        "title": "Viata Lui Nutu Camataru: Dresor de Lei si de Fraieri",
        "author": "Codin Maticiuc", "genre": "Lifestyle", "publisher": "Scoala Vietii",
        "page_count": 200,
    },
    {
        "title": "Oracle SQL, SQL*Plus", "author": "Alexandru Boicea",
        "publisher": "Printech", "genre": "BD", "page_count": 112
    },
]
_book_test_fields = lambda idx: {key: SAMPLE_BOOKS[idx][key] for key in ("title", "author", "page_count")}

SAMPLE_BOOKS_NS = [
    {
        "title": "Computer_Networks", "author": "A._Tanenbaum_et._al.",
        "genre": "Manual", "publisher": "Prentice_Hall", "page_count": 950,
    },
    {
        "title": "Viata_Lui_Nutu_Camataru:_Dresor_de_Lei_si_de_Fraieri",
        "author": "Codin_Maticiuc", "genre": "Lifestyle", "publisher": "Scoala_Vietii",
        "page_count": 200,
    },
]

SCRIPTS = {
    "ALL": ["full", "delete_all", "add3", "read3", "delete_all",
            "invalid_user", "invalid_book_fields", "invalid_book_pages", "delete_all"],
    "full": [
        ("register", {}),  # use CLI-provided user
        ("login", {}), ("enter_library", {}),
        ("get_books", {"expect_count": False}),
        ("add_book", {"book": SAMPLE_BOOKS[0]}),
        ("add_book", {"book": SAMPLE_BOOKS[1]}),
        ("get_books", {"expect_count": 2}),
        ("get_book_id", {"book_idx": 0, "expect_book": {"title": "Computer Networks", "page_count": 950}}),
        ("delete_book", {"book_idx": 1}),
        ("logout", {}), ("exit", {}), 
    ],
    "nospace": [
        ("register", {}),  # use CLI-provided user
        ("login", {}), ("enter_library", {}),
        ("get_books", {"expect_count": False}),
        ("add_book", {"book": SAMPLE_BOOKS_NS[0]}),
        ("add_book", {"book": SAMPLE_BOOKS_NS[1]}),
        ("get_books", {"expect_count": 2}),
        ("get_book_id", {"book_idx": 0, "expect_book": {"title": "ComputerNetworks", "page_count": 950}}),
        ("delete_book", {"book_idx": 1}),
        ("logout", {}), ("exit", {}), 
    ],
    "add3": [
        ("register", {}),
        ("login", {}), ("enter_library", {}),
        ("get_books", {"expect_count": False}),
        ("add_book", {"book": SAMPLE_BOOKS[0]}),
        ("add_book", {"book": SAMPLE_BOOKS[1]}),
        ("add_book", {"book": SAMPLE_BOOKS[2]}),
        ("get_books", {"expect_count": 3}),
        ("get_book_id", {"book_idx": 2, "expect_book": _book_test_fields(2)}),
        ("get_book_id", {"book_idx": 0, "expect_book": _book_test_fields(0)}),
        ("get_book_id", {"book_idx": 1, "expect_book": _book_test_fields(1)}),
        ("logout", {}), ("exit", {}), 
    ],
    "read3": [
        ("login", {}), ("enter_library", {}),
        ("get_books", {"expect_count": 3}),
        ("get_book_id", {"book_idx": 1, "expect_book": SAMPLE_BOOKS[1]}),
        ("logout", {}), ("exit", {}), 
    ],
    "delete_all": [
        ("login", {}), ("enter_library", {}),
        ("get_books", {}), ("delete_all_books", {"delete_books_ignore": True}),
        ("get_books", {"expect_count": 0}),
        ("logout", {}), ("exit", {}), 
    ],

    # interactive shell
    "SHELL": [
        ("register", {}), ("login", {}), ("enter_library", {}),
        ("shell", {}),
        ("logout", {}), ("exit", {}), 
    ],

    # for the following ones, errors should be reported by the user program
    "invalid_user": [
        ("register", {"user": "hahah don't create this:test123"}),
        ("login", {}), ("enter_library", {}),
        ("logout", {}), ("exit", {}), 
    ],
    "invalid_book_fields": [
        ("register", {}),
        ("login", {}), ("enter_library", {}),
        ("add_book", {"book": {"title": "Something Invalid"}}),
        ("logout", {}), ("exit", {}), 
    ],
    "invalid_book_pages": [
        ("register", {}),
        ("login", {}), ("enter_library", {}),
        ("add_book", {"book": dict(SAMPLE_BOOKS[0], page_count="nope")}),
        ("logout", {}), ("exit", {}), 
    ],
}

def run_tasks(p, args):
    script_name = args.get("script")
    if not script_name:
        script_name = "full"
    if script_name not in SCRIPTS:
        raise CheckerException("Invalid script: %s" % (script_name))
    script = SCRIPTS[script_name]
    xargs = dict(args)
    for task in script:
        ignore = xargs.get("ignore", False)
        action = None
        action_name = ""
        print_style = {"fg": "cyan", "style": "bold"}
        if isinstance(task, tuple):
            action_name = task[0]
            action = ACTIONS[action_name]
            if task[1]:
                xargs.update(task[1])
            ignore = xargs.get("ignore", False)
        elif isinstance(task, str):
            action_name = "<RUN SUBTASK: %s>" % str(task)
            print_style = {"fg": "black", "bg": "purple", "style": "bold"}
            action = run_tasks
            ignore = True
            xargs = dict(args, script=task, dont_exit=True)
        if not action:
            continue
        try:
            color_print("%s: " % action_name, **print_style)
            action(p, xargs)
        except CheckerException as ex:
            ex = CheckerException("%s: %s" % (action.__name__, str(ex)))
            color_print(wrap_test_output("ERROR:"), fg="black", bg="red", stderr=True, newline=False)
            color_print(wrap_test_output(str(ex)), fg="red", stderr=True)
            if args.get("debug"):
                color_print(wrap_test_output(traceback.format_exc()), fg="red", stderr=True)
            if not ignore:
                break
    

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='checker.py',
                                     description='Python helper for PCom / HTTP Assignment')
    parser.add_argument('program')
    parser.add_argument('--script', choices=SCRIPTS.keys())
    parser.add_argument('-u', '--user', help="Override username & password " \
            "(separated by colon, e.g. `-u user:pass`")
    parser.add_argument('-d', '--debug', help="Enable debug output", action="store_true")
    parser.add_argument('-i', '--ignore', help="Ignore errors (do not break the tests)", action="store_true")
    parser.add_argument('-E', '--use-colon', help="Use ':' as field prompt separator instead of '='", action="store_true")

    args = parser.parse_args()
    p = pexpect.spawn(shlex.quote(args.program), encoding='utf-8', echo=False, timeout=EXPECT_TIMEOUT)
    if args.debug:
        p.logfile_send = ExpectInputWrapper(direction=True)
        p.logfile_read = ExpectInputWrapper(direction=False)

    if args.use_colon:
        EXPECT_SEP = ":"

    try:
        run_tasks(p, vars(args))
    except Exception as ex:
        color_print("FATAL ERROR:", fg="black", bg="red", stderr=True, newline=False)
        color_print(" " + str(ex), fg="red", stderr=True)
        if args.debug:
            color_print(traceback.format_exc(), fg="red", stderr=True)

