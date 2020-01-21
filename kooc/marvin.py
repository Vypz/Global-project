from cnorm.nodes import *
from cnorm.parsing.declaration import Declaration

def print_definie(n: Decl) -> str:
    if n._ctype._storage == Storages.EXTERN:
        return "declare! "
    else:
        return "definie! "


def print_name(n: Decl) -> str:
    return n._name + " "


def print_type_int(n:Decl) -> str:
    if n._ctype._specifier == Specifiers.SHORT:
        return "un entier court"
    elif n._ctype._specifier == Specifiers.LONG:
        return "un entier a la jack"
    elif n._ctype._specifier == Specifiers.LONGLONG:
        return "un entier a la super-jack"
    else:
        return "un entier"

def print_ptr(n:Decl) -> str:
    if type(n._ctype._decltype) is not PointerType:
        return ""
    s = "un pointeur "
    if type(n._ctype._decltype._decltype) is PointerType:
        s += "de pointeur "
    s += "sur "
    return s

def print_type(n: Decl) -> str:
    s = "est "
    s += print_ptr(n)
    if "_colon_expr" in vars(n):
        s += "un champs de bit"
    elif n._ctype._identifier == "int":
        s += print_type_int(n)
    elif n._ctype._identifier == "char":
        s += "un caractere"
    elif n._ctype._identifier == "float":
        s += "un floattant"
    elif n._ctype._identifier == "double":
        s += "un floattant double precision"
    elif n._ctype._identifier == "void":
        s += "rien"
    s += print_sign(n)
    s += print_static(n)
    s += print_qualifier(n)
    s += print_register(n)
    return s


def print_sign(n: Decl) -> str:
    if "_sign" in vars(n._ctype) and n._ctype._sign == Signs.UNSIGNED:
        return " positif ou nul"
    else:
        return ""


def print_static(n: Decl) -> str:
    if n._ctype._storage == Storages.STATIC:
        return " definie localement"
    else:
        return ""


def print_qualifier(n: Decl) -> str:
    if n._ctype._decltype == None or "_qualifier" not in vars(n._ctype._decltype):
        return ""
    if n._ctype._decltype._qualifier == Qualifiers.CONST:
        return " constant"
    elif n._ctype._decltype._qualifier == Qualifiers.VOLATILE:
        return " toujours mis a jour lorsqu'on y accede"
    else:
        return ""


def print_register(n:Decl) -> str:
    if n._ctype._storage == Storages.REGISTER:
        return " stocker dans un registre"
    else:
        return ""


def print_initialized(n:Decl) -> str:
    if "_assign_expr" in vars(n):
        return " qui est initialise a une certaine valeur mais ca me saoule"
    else:
        return ""


def print_node(n: Decl):
    s = "je "
    s += print_definie(n)
    s += print_name(n)
    s += print_type(n)
    s += print_initialized(n)
    print(n, '\n')
    return s + '\n'

def marvin(ast: Decl) -> str:
    return print_node(ast)
#    s = "[Marvin]\n"
#    for n in ast.body:
#        s += print_node(n)
#    return s
