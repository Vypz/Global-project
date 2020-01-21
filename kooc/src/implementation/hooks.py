import sys

from cnorm.parsing.declaration import Declaration

from symtab.symtab import symtab
from symtab.symbol import Symbol

from status import Status

from cnorm.nodes import *

from pyrser import meta
import kooc

from module.hooks import new_func
from module.hooks import new_primary

def get_init_func(module, new):
    for it in module.getFuncs("init"):
        if it._ctype._params[1:] == new._ctype._params:
            return it
    return None

def add_funcs(ast, module):
    ast.ref.body.append(new_func("void", "malloc", PointerType(), new_primary("unsigned long", "size")))
    ast.ref.body.append(new_func("void", "free", None, new_primary("void", "ptr", PointerType())))
    for it in module.functions:
        if it.module() == module and it._name in ("alloc", "delete", "init", "new"):
            decl = Decl(it.mangle(), it._ctype)
            if it._name == "alloc":
                decl.body = Declaration().parse("{return malloc(sizeof(" + module.name + "));}").body[0].body
                ast.ref.body.append(decl)
            elif it._name == "delete":
                func = "{"
                func_clean = module.getFuncs("clean")
                if len(func_clean) == 1:
                    func += func_clean[0].mangle() + "(self);"
                elif len(func_clean) > 1:
                    sys.exit("Module " + module._name + "has more than 1 function clean.");
                func += "free(self);}"
                decl.body = Declaration().parse(func).body[0].body
                ast.ref.body.append(decl)
            elif it._name == "init" and hasattr(it, "default_init"):
                decl.body = BlockStmt([])
                ast.ref.body.append(decl)
            elif it._name == "new":
                init = get_init_func(module, it);
                func = """\
{
  """ + module.name + """ * inst;
  inst = """ + module.getFuncs("alloc")[0].mangle() + """();
  """ + init.mangle() + """();
  return inst;
}"""
                decl.body = Declaration().parse(func).body[0].body
                for var in init._ctype.params:
                    decl.body.body[2].expr.params.append(Id(var._name))
                decl.body.body[2].expr.params[0].value = "inst"
                ast.ref.body.append(decl)

def get_name(module):
    if module.parent:
        return get_name(module.parent) + "." + module.name
    else:
        return module.name

def implement_vtable(ast, module):
    vtable = Declaration().parse("vtable_for_" + module.name + "={};").body[0]
    vtable._ctype._identifier = module.name + "Vtable"
    vtable._assign_expr.body.append(Literal('"' + get_name(module) + '"'))
    for it in module.functions:
        if it.isVirtual:
            vtable._assign_expr.body.append(Literal(it.mangle()))
    ast.ref.body.append(vtable)


@meta.hook(kooc.Kooc)
def at_implementation__init(self, ast, i):
    Status.module = Status.IMPL
    Status.moduleName = self.value(i)
    module = symtab[Status.moduleName]

    if module.isClass:
        implement_vtable(ast, module)

    for it in module.variables:
        if it.isMember == False:
            decl = Decl(it.mangle(), it._ctype)
            if it._assign_expr != None:
                decl._assign_expr = it._assign_expr
            ast.ref.body.append(decl)

    if module.isClass:
        add_funcs(ast, module)
    return True


@meta.hook(kooc.Kooc)
def at_implementation__line(self, ast):
    node = ast.ref.body[len(ast.ref.body) - 1]
#    symbol = symtab.[Status.moduleName].functions[node._name]############################
    if Status.member == True:
        ctype = PrimaryType(Status.moduleName)
        ctype._decltype = PointerType()
        decl = Decl("self", ctype)
        node._ctype._params.insert(0, decl)
#    node._name = symbol.mangle()
    node._name = Symbol(node, symtab[Status.moduleName], Status.member).mangle()
    return True
