from cnorm.nodes import *
import weakref
import copy
import symtab.module

def len03d(i: int) -> str:
    # renvoyer une erreur si len(i) > 999
    return "%03d" % len(i)

def mangleName(name: str) -> str:
    return '_' + len03d(name) + name

def manglePointer(self) -> str:
    s = ""
    _type = self._ctype._decltype
    while type(_type) is PointerType:
        s += 'p'
        _type = _type._decltype
    if type(_type) is ParenType:
        s += 'f' + str(len(_type._params))
        s += mangleParams(_type)
    return s

def mangleType(self) -> str:
    s = self._ctype._identifier
    if self._ctype._identifier not in ["int", "void", "char", "float", "double"]:
        s = len03d(self._ctype._identifier) + s
    elif self._ctype._specifier == Specifiers.SHORT:
        s = 's' + s
    elif self._ctype._specifier == Specifiers.LONG:
        s = 'l' + s
    elif self._ctype._specifier == Specifiers.LONGLONG:
        s = 'll' + s
    s = '_' + s
    return manglePointer(self) + s

def mangleParams(self) -> str:
    s = ""
    for i in self._params:
        s += mangleType(i)
    return s





# def compare_2_params(p1, p2):
#     p1 = p1._ctype._identifier
#     p2 = p2._ctype._identifier
#     if p1 == p2:
#         return True
#     if p1 == "Object" and p2 == "Classe":
#         return True
#     return False

# def compare_params(sym1, sym2):
#     if len(sym1._ctype.params) != len(sym2._ctype.params):
#         return False
#     for i in range(len(sym1._ctype.params)):
#         p1 = sym1._ctype.params[i]
#         p2 = sym2._ctype.params[i]
#         if compare_2_params(p1, p2) == False:
#             return False
#     return True






class   Symbol:
    def __init__(self, decl_symbol: Decl, module, isMember: bool = False, isVirtual: bool = False):
        self._name = decl_symbol._name
        self._ctype = copy.deepcopy(decl_symbol._ctype)
        if hasattr(decl_symbol, "_assign_expr"):
            self._assign_expr = decl_symbol._assign_expr
        else:
            self._assign_expr = None
        self.module = weakref.ref(module) # module est le dernier module ayant défini la variable.
        self.isMember = isMember
        self.isVirtual = isVirtual

    def __repr__(self):
        return "Symbol()"

    def __str__(self):
        return str(vars(self))

    def getString(self) -> str:
        s = mangleType(self) + mangleName(self._name)
        if type(self._ctype) is FuncType:
            s += mangleParams(self._ctype)
        return s

    def mangle(self) -> str:
        return mangleName(self.module().name) + self.getString()

    def getFromParent(self, parent):
        if self.isVirtual == False:
            return None
        for it in parent.getFuncs(self._name):
            if self._ctype._identifier == it._ctype._identifier and symtab.module.compare_params(it, self, self.module()):
                    return True
        return None
