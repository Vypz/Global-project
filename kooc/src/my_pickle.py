import pickle
import weakref

class MyWeakref:
    def __init__(self, i:int):
        self.i = i

weakrefs = []

def is_equal(op1, op2):
    if vars(op1) != vars(op2):
        return False
    for key in vars(op1):
        if op1[key] != op2[key]:
            return False
    return True

def find_in_list(liste, elem):
    for i in range(len(liste)):
#        if is_equal(liste[i], elem):
        if liste[i].__init__ == elem.__init__:
            return i
    return -1

def remove_weakref(obj):
    if find_in_list(weakrefs, obj()) != -1:
        obj = find_in_list(weakrefs, obj())
    else:
        weakrefs.append(obj())
        obj = len(weakrefs) - 1
    return MyWeakref(obj)

def redo_weakref(obj):
    return weakref.ref(weakrefs[obj.i])

def parse(obj, func, type_):
    if isinstance(obj, type_):
        return func(obj)
    elif isinstance(obj, list):
        for i in range(len(obj)):
            obj[i] = parse(obj[i], func, type_)
    elif isinstance(obj, dict):
        for it in obj:
            obj[it] = parse(obj[it], func, type_)
    if hasattr(obj, "body"):
        obj.body = parse(obj.body, func, type_)
    if hasattr(obj, "types"):
        obj.types = parse(obj.types, func, type_)
    if hasattr(obj, "maps"):
        obj.maps = parse(obj.maps, func, type_)
    if hasattr(obj, "variables"):
        obj.variables = parse(obj.variables, func, type_)
    if hasattr(obj, "functions"):
        obj.functions = parse(obj.functions, func, type_)
    if hasattr(obj, "module"):
        obj.module = parse(obj.module, func, type_)
    return obj

def dump(objs: tuple, fd):
    # print(objs[0].to_yml())
    # print("=====================================================")
    for it in objs:
        parse(it, remove_weakref, weakref.ReferenceType)
    # print(objs[0].to_yml())
    # print("=====================================================")
    # print(weakrefs)
    pickle.dump(objs + (weakrefs,), fd)
    weakrefs.clear()

def load(fd) -> tuple:
    objs = pickle.load(fd)
    weakrefs.extend(objs[-1])
    objs = objs[:-1]
    for it in objs:
        parse(it, redo_weakref, MyWeakref)
    weakrefs.clear()
    return objs
