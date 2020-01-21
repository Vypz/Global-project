#!/usr/bin/env python3
from pyrser import grammar, meta
from pyrser.directives import ignore
import sys
from cnorm.nodes import *
from cnorm.parsing.declaration import Declaration
from cnorm.parsing.statement import Statement
from cnorm.passes import to_c
import weakref

class Parser(grammar.Grammar, Declaration):
    entry = "translation_unit"
    grammar = """
    declaration =
    [ Declaration.declaration
    | at_class
    ]

    at_class = [ "@class" id:i Statement.compound_statement:stmt
    #add_class(current_block, i, stmt) ]

    line_of_code =
    [ Declaration.line_of_code
    | [ "@member" Declaration.line_of_code #at_member(current_block) ]
    ]
    """
#    | [ "@method" Statement.single_statement:>_ ]

@meta.hook(Parser)
def to_yml(self, _):
    print(_.ref.to_yml())
    return True

@meta.hook(Parser)
def at_member(self, ast):
    node = ast.ref.body[len(ast.ref.body) - 1]
# handle member blocks
    node._name = "member_" + node._name
    return True

@meta.hook(Parser)
def test(self):
    print("_")
    return True

@meta.hook(Parser)
def add_class(self, ast, idx, stmt):
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
