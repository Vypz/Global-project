#!/usr/bin/env python3
from pyrser import grammar, meta
from pyrser.directives import ignore
import sys
from cnorm.nodes import *
from cnorm.parsing.declaration import Declaration
from cnorm.passes import to_c
import weakref
import copy

class AspectC(grammar.Grammar, Declaration):
    entry = "translation_unit"
    grammar = """
    declaration =
    [ Declaration.declaration
    | at_begin | at_end | at_callback
    ]

    at_begin =
    [ "@begin" '(' id:i ')' Statement.compound_statement:stmt
    #add_begin(current_block, i, stmt)
    ]

    at_end =
    [ "@end" '(' id:i ')' Statement.compound_statement:stmt
    #add_end(current_block, i, stmt)
    ]

    at_callback =
    [ "@callback" '(' id:i ')' ';':stmt
    #add_cb(current_block, i, stmt)
    ]
    """

# Statement.compound_statement == truc entre accollades


@meta.hook(AspectC)
def add_begin(self, ast, idx, stmt):
    beg = AtBegin(ast.ref, self.value(idx), stmt, len(ast.ref.body))
    ast.ref.body.append(beg)
    return True


class AtBegin:
    def __init__(self, ast, func_name, stmt, idx):
        self.here = weakref.ref(ast)
        self.func_name = func_name
        self.stmt = stmt
        self.idx = idx

    def doTrans(self):
        for it in self.here().declfuncs(self.func_name):
            if hasattr(it, 'body'):
                it.body.body.insert(0, self.stmt)
        return self.idx


@meta.hook(AspectC)
def add_end(self, ast, idx, stmt):
    end = AtEnd(ast.ref, self.value(idx), stmt, len(ast.ref.body))
    ast.ref.body.append(end)
    return True


@meta.add_method(BlockStmt)
def found_return(self, collect, listblock = None, idx = -1):
    if type(self) is Return:
        collect.append({"list":listblock, "idx":idx})
    elif type(self) is list:
        i = 0
        for it in self:
            found_return(it, collect, self, i)
            i += 1
    else:
        if hasattr(self, "body"):
            found_return(self.body, collect)
        if hasattr(self, "thencond"):
            found_return(self.thencond, collect)
        if hasattr(self, "elsecond"):
            found_return(self.elsecond, collect)

class AtEnd:
    def __init__(self, ast, func_name, stmt, idx):
        self.here = weakref.ref(ast)
        self.func_name = func_name
        self.stmt = stmt
        self.idx = idx

    def doTrans(self):
        for declfunc in self.here().declfuncs(self.func_name):
            if hasattr(declfunc, 'body'):
                collect = []
                revmap = {}
                declfunc.body.found_return(collect)
                for it in collect:
                    uid = id(it['list'])
                    if uid not in revmap:
                        revmap[uid] = []
                    revmap[uid].append(it)
                for modif in revmap.values():
                    for p in reversed(modif):
                        p['list'].insert(p['idx'], self.stmt)
                declfunc.body.body.append(self.stmt) # rajouté par moi pour ajotuer un return à la fin
        return self.idx


@meta.hook(AspectC)
def add_cb(self, ast, idx, stmt):
    cb = AtCb(ast.ref, self.value(idx), stmt, len(ast.ref.body))
    ast.ref.body.append(cb)
    ast.ref.types["callback_" + self.value(idx)] = None # or cb
    return True

class AtCb:
    def __init__(self, ast, func_name, stmt, idx):
        self.here = weakref.ref(ast)
        self.func_name = func_name
        self.stmt = stmt
        self.idx = idx

    def doTrans(self):
        decl = copy.deepcopy(self.here().func(self.func_name))
        if hasattr(decl, "body"):
            del decl.body
        decl._name = "callback_" + decl._name
        decl._ctype._storage = Storages.TYPEDEF
        p = ParenType()
        decl._ctype.push(p)
        decl._ctype.push(PointerType())
        p._params = decl._ctype._params
        del decl._ctype._params
        decl._ctype.__class__ = PrimaryType
        self.here().body[self.idx] = decl

#        s = decl.to_c()
#        # Traitement
#        self.here().body[self.idx] = self.parse(s)
#        return -1


def transfo(ast):
    poplist = []
    for it in ast.body:
        mustdrop = -1
        if isinstance(it, AtBegin) or isinstance(it, AtEnd) or isinstance(it, AtCb):
            mustdrop = it.doTrans()
        if mustdrop != -1:
            poplist.append(mustdrop)
    for d in reversed(poplist):
        ast.body.pop(d)

f = sys.argv[1]
if f:
    c = AspectC()
    res = c.parse_file(f)
    if res:
        transfo(res)
        print(res.to_c())
