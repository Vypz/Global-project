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
    declaration =
    [ Declaration.declaration
    | at_module
    ]

    at_module = [ "@module" id:i Statement.compound_statement:stmt
    #add_module(current_block, i, stmt) ]
    """

@meta.hook(Parser)
def add_module(self, ast, idx, stmt):
    for node in stmt.body:
        if isinstance(node, Decl) and node._ctype._storage == Storages.TYPEDEF:
            ast.ref.types[node._name] = weakref.ref(node)
# Check la syntaxe (on a le droit de mettre des typedef dans un @module ? Si oui, refaire
# le truc au dessus pour chaque définition de type autorisée (struct, enum etc).
# Sinon, supprimer le bout de code au dessus.
#
# Stocker tout ce dont on a besoin quelque part pour pouvoir le charger lors d'un @import.
# Traiter l'arbre avant de le réinjecter: mangler, mettre les vars en externe. Autre chose ?
    ast.ref.body += stmt.body
    return True
# Je fais pas le @implementation car niveau BNF, c'est du même niveau.


#f = sys.argv[1]
#if f:
c = Parser()
res = c.parse_file("mon_header.kh")
if res:
    print(res.to_c())
