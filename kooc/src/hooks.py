from pyrser import meta
import kooc


@meta.hook(kooc.Kooc)
def test(self):
    print('_')
    return True

@meta.hook(kooc.Kooc)
def l(self, s):
    print(s)
    return True

@meta.hook(kooc.Kooc)
def log(self, s, n):
    print(s, self.value(n))
    return True
