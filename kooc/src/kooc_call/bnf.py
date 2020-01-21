bnf = """
access = [ [ typed_access | untyped_access ]:>_ ]

typed_access = [ '@!(' 'int' ')' kooc_access:>_ ]

untyped_access = [ kooc_access:>_ ]

kooc_access = [ __scope__:n 
'[' id_module:m
  [
    id_variable:>n
    | [ id_function:>n params_list:p #attach_params(n, p) ]
  ]
']' #end_kooc_call(_, m, n)
]

id_module = [ id ]

id_variable = [ '.' id:n #new_variable(_, n) ]

id_function = [ id:n #new_func(_, n) ]

params_list = [ #params_list__init(_) [ ':' primary_expression:i #params_list__add(_, i) ]* ]
"""
