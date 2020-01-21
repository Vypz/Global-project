from cnorm.parsing.declaration import Declaration

from symtab.symtab import symtab
from symtab.module import Module

from status import Status

from cnorm.nodes import *

from pyrser import meta
import kooc

import weakref
import copy

import atimport.hooks

def func_to_ptr(func):
    ret = copy.deepcopy(func)
    p = PointerType()
    p._decltype = ParenType()
    p._decltype._params = ret._ctype._params
    del ret._ctype._params
    p._decltype._decltype = ret._ctype._decltype
    ret._ctype._decltype = p
    ret._ctype.__class__ = PrimaryType
    return ret


def new_primary(type_, name, decltype = None):
    primaryType = PrimaryType(type_)
    if decltype:
        primaryType._decltype = decltype
    return Decl(name, primaryType)

def new_func(type_, name, decltype = None, *params):
    node_params = []
    for it in params:
        node_params.append(it)
    funcType = FuncType(type_, node_params, decltype)
    return Decl(name, funcType)

def add_func_proto(body, module, func, isVirtual):
    symbol = module.addSymbol(func, True, isVirtual)
    func._name = symbol.mangle()
    body.append(func)
    return symbol

def inherit_module(self, parent): # this function should be a member of Module
    if type(parent) is str:
        parent = symtab[parent]
    for it in parent.variables:
        if it.isMember:
            self.variables.append(it)
    for it in parent.functions:
        if it.isMember:
            self.functions.append(it)
    self.parent = parent
    Status.parent = parent

@meta.hook(kooc.Kooc)
def class__init(self, ast, _type, i):
    module = Module(self.value(i))
    if self.value(_type) == "@class":
        if module.name != "Object" and "Object" not in symtab:
            atimport.hooks.do_import(ast, "Object.kh")
        if Status.parent != None:
            inherit_module(module, Status.parent)
        else:
            if self.value(i) != "Object":
                inherit_module(module, "Object")
            else:
                self.parent = None


        module.isClass = True
        Status.module = Status.CLASS
        if module.parent:
            module.node = Declaration().parse("typedef int " + module.parent.name + ";typedef struct{" + module.parent.name + " parent;}" + module.name + ";").body[1]
        else:
            module.node = Declaration().parse("typedef struct{void* vtable;}" + module.name + ";").body[0]
        ast.ref.body.append(module.node)
        ast.ref.types[module.name] = weakref.ref(module.node)

        add_func_proto(ast.ref.body, module, new_func(module.name, "alloc", PointerType()), False)
        add_func_proto(ast.ref.body, module,
                       new_func("void", "delete", None,
                                new_primary(module.name, "self", PointerType())), True)
        ast.ref.body.append(Raw("#define VTABLE_" + module.name +
                                "(self) ((" + module.name + "Vtable*)self)\n"))
    else:
        Status.module = Status.MODULE
    symtab[module.name] = module
    Status.moduleName = module.name
    return True


def is_in_parent(vtable, name):
    for it in vtable._ctype.fields:
        if it._name == name:
            return True
    return False

def create_vtable(module, stmt):
    if module.parent:
        vtable = copy.deepcopy(module.parent.vtable)
        vtable._name = module.name + "Vtable"
    else:
        vtable = Declaration().parse("typedef struct{char* name;}" + module.name + "Vtable;").body[0]
    for it in module.functions:
        if it.isVirtual and it.module() == module and (
                not module.parent or it.getFromParent(module.parent) == None):
            vtable._ctype.fields.append(func_to_ptr(Decl(it.getString(), it._ctype)))
    stmt.append(vtable)
    module.vtable = vtable

@meta.hook(kooc.Kooc)
def add_class(self, ast, stmt):
    for node in stmt.body:
        if isinstance(node, Decl) and node._ctype._storage == Storages.TYPEDEF:
            ast.ref.types[node._name] = weakref.ref(node)
# Refaire le truc au dessus pour chaque définition de type autorisée (struct, enum etc).

    module = symtab[Status.moduleName]
    if module.getFuncs("init") == []:
        sym = add_func_proto(stmt.body, module,
                             new_func("void", "init", None,
                                      new_primary(module.name, "self", PointerType())), False)
        sym.default_init = True
    for i in module.getFuncs("init"):
        params = ()
        for j in i._ctype._params[1:]:
            params = params + (it,)
        add_func_proto(stmt.body, module, new_func(module.name, "new", PointerType(), *params), False)

    create_vtable(module, stmt.body)

    ast.ref.body += stmt.body
    ast.ref.types[module.name + "Vtable"] = weakref.ref(module.vtable)
    Status.module = Status.NONE
    Status.parent = None
    Status.moduleName = None
    return True


@meta.hook(kooc.Kooc)
def at_member(self, ast, v):
    node = ast.ref.body[len(ast.ref.body) - 1]
# handle member blocks
    symbol = symtab[Status.moduleName].addSymbol(node, True,
                                                 True if self.value(v) == "@virtual" else False)
    if type(node._ctype) is FuncType:
        ctype = PrimaryType(Status.moduleName)
        ctype._decltype = PointerType()
        decl = Decl("self", ctype)
        node._ctype._params.insert(0, decl)
        symbol._ctype = copy.deepcopy(node._ctype)
        node._name = symbol.mangle()
    else:
        node._name = symbol.getString()
        symtab[Status.moduleName].node._ctype.fields.append(node)
        ast.ref.body.pop()
    return True


@meta.hook(kooc.Kooc)
def non_member(self, ast):
    node = ast.ref.body[len(ast.ref.body) - 1]
    symbol = symtab[Status.moduleName].addSymbol(node)
    node._name = symbol.mangle()
    if symbol._assign_expr != None:
        del node._assign_expr
    if type(node._ctype) is not FuncType:
        node._ctype._storage = Storages.EXTERN
    return True
