from cnorm.parsing.declaration import Declaration
from pyrser import meta
import kooc

import sys
import subprocess
import my_pickle

from symtab.symtab import symtab

importedFiles = []

def do_import(ast, module):
    if module in importedFiles:
        return True
    importedFiles.append(module)

    subprocess.call([sys.argv[0], "-c", module])
    name_p = module.replace(".kh", ".kp")
    obj = my_pickle.load(open(name_p, "rb"))
    ast.ref.body += obj[0].body
    for it in obj[0].types.maps:
        ast.ref.types.update(it)
    symtab.update(obj[1])

@meta.hook(kooc.Kooc)
def add_import(self, ast, ident):
    module = self.value(ident)
    module = module.strip()
    module = module.replace('"', '')
    do_import(ast, module)
    return True
