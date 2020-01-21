bnf = """
    at_implementation =
    [
      "@implementation" id:i #at_implementation__init(current_block, i)
      '{'
        Declaration.declaration*
      '}'
      #Status__module_unset_IMPL
    ]

    impl_c_decl = [
        #Status__module_is_IMPL
        __scope__:local_specifier
        #create_ctype(local_specifier)
        [ "@member" #Status__set_member ]?
        declaration_specifier*:dsp
        init_declarator:decl
        #not_empty(current_block, dsp, decl)
        #end_decl(current_block, decl)
        [
            impl_compound_statement:b
            #add_body(decl, b)
        ]
        #Status__unset_member
    ]

impl_compound_statement =
    [
      #Status__module_unset_IMPL
      [ Statement.compound_statement:>_ | [ #Status__module_set_IMPL #false ] ]
      #Status__module_set_IMPL
      #at_implementation__line(current_block)
    ]
"""
