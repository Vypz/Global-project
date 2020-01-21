from pyrser import meta
import kooc


class Status:
    # Constants for module.
    NONE   = 0
    MODULE = 1
    CLASS  = 2
    IMPL   = 3

    module = NONE
    parent = None
    member = False
    moduleName = None


@meta.hook(kooc.Kooc)
def Status__module_is_MODULE(self):
    if Status.module == Status.MODULE or Status.module == Status.CLASS:
        return True
    else:
        return False


@meta.hook(kooc.Kooc)
def Status__module_is_CLASS(self):
    if Status.module == Status.CLASS:
        return True
    else:
        return False


@meta.hook(kooc.Kooc)
def Status__module_is_IMPL(self):
    if Status.module == Status.IMPL:
        return True
    else:
        return False


@meta.hook(kooc.Kooc)
def Status__module_set_IMPL(self):
    Status.module = Status.IMPL
    return True


@meta.hook(kooc.Kooc)
def Status__module_unset_IMPL(self):
    Status.module = Status.NONE
    return True


@meta.hook(kooc.Kooc)
def Status__set_module(self, s):
    if self.value(s) == "@class":
        Status.module = Status.CLASS
    else:
        Status.module = Status.MODULE
    return True


@meta.hook(kooc.Kooc)
def Status__set_parent(self, s):
    Status.parent = self.value(s)
    return True



@meta.hook(kooc.Kooc)
def Status__set_member(self):
    Status.member = True
    return True

@meta.hook(kooc.Kooc)
def Status__unset_member(self):
    Status.member = False
    return True



@meta.hook(kooc.Kooc)
def Status__set_moduleName(self, s):
    Status.moduleName = self.value(s)
    return True

