#!/usr/bin/env python3
from cnorm.passes import to_c
from cnorm.nodes import *
import kooc

def solveBlock(block, types = {}):
    if hasattr(block, "body"):
        solveBlock(block.body, types)
    else:
        for it in block:
            solveNode(it, types)



def solveNode(node, types={}):
    if isinstance(node, Decl):
        #if hasattr(node, "_assign_expr"):
            #typage(node, types)
        types[node._name] = node._ctype
    #if isinstance(node, ExprStmt):
        #typage(node, types)
# Gérer Paren ?         while ((i = 5));
    if isinstance(node, If):
        solveNode(node.condition, types)
        solveNode(node.thencond, types)
        solveNode(node.elsecond, types)
    if isinstance(node, For):
        solveNode(node.init, types)
        solveNode(node.condition, types)
        solveNode(node.increment, types)
        # Note : le body du For est traité au niveau du hasattr plus bas. Pareil pour les While / Switch
    if isinstance(node, While):
        solveNode(node.condition, types)
    if isinstance(node, Switch):
        solveNode(node.condition, types)
    if hasattr(node, "body"):
        solveBlock(node, types.copy())



cparse = kooc.Kooc()
#ast = cparse.parse_file("stmt_test.c")
ast = cparse.parse_file("test.c")

#solveBlock(ast);
print(ast.to_c())


from symtab.symtab import symtab
