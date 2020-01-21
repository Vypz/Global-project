bnf = """
at_class =
[
  [ "@module" | "@class" ]:_type id:i
  [ ":" id:s #Status__set_parent(s) ]?
  #class__init(current_block, _type, i)
  Statement.compound_statement:stmt
  #add_class(current_block, stmt)
]

member_line_of_code =
[
  #Status__module_is_CLASS
/*  [
    [ #Status__check_member(True) ]
    |
  ]*/
  [ "@member" | "@virtual" ]:v Declaration.line_of_code #at_member(current_block, v)
]

non_member_line_of_code =
[
  #Status__module_is_MODULE
  Declaration.line_of_code #non_member(current_block)
]
"""
