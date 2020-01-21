from symtab.symtab import symtab

from cnorm.nodes import *

from pyrser import meta
import kooc

import sys

@meta.hook(kooc.Kooc)
def end_kooc_call(self, _, m, n):
    module = self.value(m)
    if module in symtab:
        n.module = symtab[module]
    else:
        n.module = Id(module)
    _.set(n)
    return True

@meta.hook(kooc.Kooc)
def new_variable(self, _, n):
    _.set(Id(self.value(n)))
    return True

@meta.hook(kooc.Kooc)
def new_func(self, _, n):
    _.set(Func(Id(self.value(n)), []))
    return True

@meta.hook(kooc.Kooc)
def attach_params(self, n, p):
#    n.params = p.params
    n._ctype._params = p.params
    return True


@meta.hook(kooc.Kooc)
def params_list__init(self, _):
    _.params = []
    return True

@meta.hook(kooc.Kooc)
def params_list__add(self, _, i):
    _.params.append(i)
    return True
