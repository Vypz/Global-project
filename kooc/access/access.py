#!/usr/bin/env python3
from pyrser import grammar, meta
from pyrser.directives import ignore
import sys
from cnorm.nodes import *
from cnorm.parsing.declaration import Declaration
from cnorm.passes import to_c
import weakref

class Parser(grammar.Grammar, Declaration):
    entry = "translation_unit"
    grammar = """
    primary_expression =
    [ Declaration.primary_expression:>_
    | access:>_ ]

    access = [ __scope__:n 
    '[' id_module:m
      [
        id_variable:>n
      | [ id_function params_list ]
      ]
    ']' #access(_, m, n)
    ]

    id_module = [ id ]

    id_variable = [ '.' id:n #variable(_, n) ]

    id_function = [ id ]

    params_list = [ [ ':' assignment_expression ]* ]
    """

@meta.hook(Parser)
def access(self, _, m, n):
    if isinstance(n, Func):
        n.call_expr.value = self.value(m) + "_" + n.call_expr.value
    elif isinstance(n, Id):
        n.value = self.value(m) + "_" + n.value
    _.set(n)
#    _.set(Literal("3"))
# Car j'ai déjà mis 3 ans avant de trouver le _.set, donc ça suffit pour aujourd'hui.
    return True

@meta.hook(Parser)
def variable(self, _, n):
    _.set(Id(self.value(n)))
    return True

c = Parser()
res = c.parse_file("test.c")
if res:
#    transfo(res)
#    print(res.to_yml())
    print(res.to_c())
