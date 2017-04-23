#!/usr/bin/python3
import argparse

def clean_path_slash(path):
    if path[-1] != "/":
        path += "/"
    return path

parser = argparse.ArgumentParser(description="Generate a class.")

parser.add_argument("name", metavar="NAME", nargs="?", default="",
		help="the name of the class to generate")
parser.add_argument("path", metavar="PATH", nargs="?", default="",
		help="the path of the class in the project")
parser.add_argument("group", metavar="GROUP", nargs="?", default="Kernel",
		help="the group of the class inside the project (Kernel, Boot, ...)")
parser.add_argument("-i", "--interactive", dest="interactive", action="store_true",
                help="run in interactive mode")
parser.add_argument("--include-path", dest="include_path", type=str, default="include/",
		help="path to the include directory")
parser.add_argument("--source-path", dest="source_path", type=str, default="src/",
		help="path to the source directory")

args = parser.parse_args()

name = args.name
path = args.path
group = args.group

if args.interactive:
    name = input("What is the name of the class? ")
    path = input("What is the path of the class? ")
    group = input("What is the group of the class? ")
elif name == "" or path == "":
    parser.print_help()
    exit(1)

path = clean_path_slash(path)
args.include_path = clean_path_slash(args.include_path)
args.source_path = clean_path_slash(args.source_path)

header_guard = name.upper() + "_HPP"

header_content = """\
#ifndef {h}
#define {h}

/// \\addtogroup {g}
/// \{{

class {n}
{{
        public:
                {n}();

        private:
}};

/// \}}

#endif// {h}
""".format(h = header_guard, n = name, g = group)

source_content = """\
#include <{p}{n}.hpp>

{n}::{n}()
{{
}}
""".format(p = path, n = name)

with open(args.include_path + path + name + ".hpp", "w") as file:
    file.write(header_content)

with open(args.source_path + path + name + ".cpp", "w") as file:
    file.write(source_content)

print("Don't forget to modify the corresponding CMakeLists.txt file!")

