from pyrser import grammar
from cnorm.parsing.declaration import Declaration
import pyrser.hooks.predicate

import module.bnf
import implementation.bnf
import kooc_call.bnf
import atimport.bnf

class   Kooc(grammar.Grammar, Declaration):
    entry = "translation_unit"
    grammar = """
    declaration =
    [
      Declaration.declaration
      | at_class
      | at_implementation
      | at_import
    ]

    line_of_code =
    [
      member_line_of_code
      | non_member_line_of_code
      | Declaration.line_of_code
    ]

    c_decl =
    [
      impl_c_decl
      | Declaration.c_decl
    ]

    primary_expression =
    [
      Declaration.primary_expression:>_
      | access:>_
    ]
    """ + module.bnf.bnf + implementation.bnf.bnf + kooc_call.bnf.bnf + atimport.bnf.bnf

import hooks
import status
import module.hooks
import implementation.hooks
import kooc_call.hooks
import atimport.hooks
