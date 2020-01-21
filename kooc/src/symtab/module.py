from cnorm.nodes import *

from symtab import symbol

def is_parent(p1, module):
    while module.name != "Object":
        if p1 == module.name:
            return True
        module = module.parent
    if p1 == module.name:
        return True
    return False

def compare_2_params(p1, p2, module = None): # module est le module de p2
    p1 = p1._ctype._identifier
    p2 = p2._ctype._identifier
    if p1 == p2:
        return True
    if module and is_parent(p1, module):
        return True
#    if p1 == "Object" and p2 == "Classe":
#        return True
    return False

def compare_params(sym1, sym2, module = None): # module est le module de sym2
    if len(sym1._ctype.params) != len(sym2._ctype.params):
        return False
    for i in range(len(sym1._ctype.params)):
        p1 = sym1._ctype.params[i]
        p2 = sym2._ctype.params[i]
        if compare_2_params(p1, p2, module) == False:
            return False
    return True

class   Module:
    def __init__(self, name: str, isClass: bool = False, parent = None):
        self.variables = []
        self.functions = []
        self.name = name # Nom du module
        self.isClass = isClass
        self.parent = parent

    def __repr__(self):
        return "Module()"

    def __str__(self):
        return str(vars(self))

    def addSymbol(self, decl_symbol: Decl, isMember: bool = False, isVirtual: bool = False):
        symbol_ = symbol.Symbol(decl_symbol, self, isMember, isVirtual) # put some more params here ?
        if type(decl_symbol._ctype) is FuncType:
            if isVirtual:
                for i in range(len(self.functions)):
#                    if self.functions[i]._name == symbol_._name and self.functions[i]._ctype._params == symbol_._ctype._params:
                    if self.functions[i]._name == symbol_._name and compare_params(self.functions[i], symbol_, self):
                        self.functions[i] = symbol_
                        return symbol_
            self.functions.append(symbol_)
        else:
            self.variables.append(symbol_)
        return symbol_

    def getVars(self, name: str):
        liste = []
        for it in self.variables:
            if it._name == name:
                liste.append(it)
        return liste

    def getFuncs(self, name: str):
        liste = []
        for it in self.functions:
            if it._name == name:
                liste.append(it)
        return liste
