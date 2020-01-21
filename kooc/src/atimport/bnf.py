bnf = """
    at_import = [ "@import" Declaration.preproc_directive:i #add_import(current_block, i) ]
"""
