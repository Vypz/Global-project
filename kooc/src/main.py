#!/usr/bin/env python3
# notes de bruno :
# - gérer le timestamp lors de la compil d'un .kh
from cnorm.passes import to_c
import subprocess
import sys
import kooc
import os
from symtab.symtab import symtab
import my_pickle

def compile_file(name_in):
    name_E = name_in + ".ke"
    subprocess.call(["gcc", "-E", "-x", "c", name_in, "-o", name_E])

    cparse = kooc.Kooc()
    ast = cparse.parse_file(name_E)
    os.remove(name_E)
    # cas d'un .kc
    if name_in.find(".kc") != -1:
        name_c = name_in.replace(".kc", ".c")
        with open(name_c, 'w') as outputFile:
            outputFile.write(str(ast.to_c()))
    # cas d'un .kh
    elif name_in.find(".kh") != -1:
        name_h = name_in.replace(".kh", ".h")
        with open(name_h, 'w') as outputFile:
            outputFile.write(str(ast.to_c()))
        name_p = name_in.replace(".kh", ".kp")
        my_pickle.dump((ast, symtab), open(name_p, "wb"))

# cas de plusieurs .kc
if "-c" not in sys.argv:
    sys.argv.append("Object.kc")
    objects = []
    for v in sys.argv[1:]:
        subprocess.call([sys.argv[0], "-c", v])
        temp_name = v.replace(".kc", ".c")
        subprocess.call(["gcc", "-c", temp_name])
        objects.append(v.replace(".kc", ".o"))
    subprocess.call(["gcc"] + objects)

if "-c" in sys.argv:
    for s in sys.argv[1:]:
        if s != "-c":
            compile_file(s)
