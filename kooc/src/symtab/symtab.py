class   SymTab:
    def __init__(self):
        self.modules = {} # Ceci est un dictionnaire assosciant une String à un Module

    def __repr__(self):
        return "SymTab()"

    def __str__(self):
        return str(vars(self))

    def to_pickle():
        #Implémentation de to_pickle()
        return

    def from_pickle():
        #Implémentation de from_pickle()
        return

#symtab = SymTab()
symtab = {}
