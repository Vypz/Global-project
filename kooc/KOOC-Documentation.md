Documentation "KOOC"
=========
**"Kind Of Objective C"**

Voici la classe globale __Status__. Elle sert à stocker des informations sur ce qui est parsé à un moment donné, et facilite ainsi le contrôle des syntaxes.

```
Class Status:
	module = MODULE | CLASS | IMPL | 0
	parent = (référence ves le parent) | NONE
	member = True | False
	moduleName = String | NONE
```

###@import
####Organisation des données en mémoire:
Les données sont organisées en mémoire sous la forme d'un tableau de modules, avec pour chaque module un tableau de variables et un tableau de fonctions.
```
class SymTab:
	__init__(self):
	    self.modules = {} # Ceci est un dictionnaire assosciant une String à un Module
	to_pickle():
	    #Implémentation de to_pickle()
	from_pickle():
	    #Implémentation de from_pickle()
	    
class Module:
	__init__(self, name: string, isClass: bool = false, parent: Module = None):
	    self.variables = {}
	    self.functions = {}
	    # Ces 2 dictionnaires assoscient une string à un Symbol.
	    self.name = name # Nom du module
	    self.isClass = isClass
	    self.Parent = parent

```
####Définition des symboles:
En mémoire, les symboles ont la forme d'une classe de données, contenant:
- *Une copie du noeud correspondant*, avec les informations du type.
- *Le nom du symbole.*
- *Un booléen indiquant si le symbole est virtuel ou non.*
- *Dans le cas où le symbole est virtuel, un booléen indiquant s'il a été redéfini.*
- *Une méthode de récupération du symbole manglé*.

Cette classe de données se présente de la forme suivante:
```
class Symbol:
	__init__(self, name: string, type: Node, module: Module, isVirtual: bool = False, isRedefined: bool = False):
	    self.type = type
	    self.name = name
	    self.module = weakref.ref(module)
	    self.isVirtual = isVirtual
	    self.isRedefined = False
	getString(): #retourne une str identifiant le symbole (unique)
	    #Implémentation de getString()
	mangle():
    	return self.module().name + self.getString() # On devrait mangler self.module ?
	getMangledNode(): # copie le node et mangle le nom
```

A la compilation d'un fichier __.kh__ se génère donc un fichier __.kho__ contenant sous forme binaire les données mémoire évoquées plus haut.

Une vérification du timestamp de ces 2 fichiers (kh, kho) est effectuée afin de ne compiler le .kh que s'il est __plus récent__ que le .kho.
	Au moment du __@import__, ce .kho sera donc chargé et ajouté à la structure de données.

####Déroulement:
```sh
./kooc fichier.kh
# Si l'extension est un .kh ET
# si le timestamp du .kho est plus récent que celui du .kh, exit.
# Lancement d'un ast.parse() sur fichier.kh
# (on procède de la même façon que pour un .kc).
# Lancement d'un pickle.pack sur l'AST afin de générer le .kho.
```
1. Extraction des données du .kho à l'aide de pickle.
2. Concaténation de la liste de symboles du .kho avec la liste de symboles existante.
3. Ajout de deux noeuds de type __Raw__ contenant par exemple:
```
#ifndef FILENAME_KH_
#define FILENAME_KH_
```

4. Ajout de l'AST se trouvant dans le .kho à la fin de l'AST de l'unité de compilation courante.
5. Ajout d'un noeud de type __Raw__ contenant:
```
#endif
```

###@module, @class
Le __@module__ et le __@class__ s'appuient sur la BNF suivante:

```
declaration =
[ Declaration.declaration
| at_class ]

at_class = [
    [ "@module" | "@class" ]
    id [ ':' id ]?
    Statement.compound_statement:stmt ]
/*
** Exemple de syntaxe détectée par at_class :
** @class  ClassName : ParentName
** {
**     ...
** }
*/

line_of_code =
[ Declaration.line_of_code
| at_member
]

at_member = [ [ "@member" | "@virtual" ] Declaration.line_of_code ]
```

Ajout de l'entrée correspondant à ce module dans le tableau de Modules. S'il s'agit d'une classe héritant d'une classe parent, cette entrée est une copie de l'entrée correspondant au module parent.

S'il s'agit d'un __@class__:
- On donne la valeur True à la variable __isClass__ de __Module__.
- Si la classe n'hérite pas d'une autre classe, alors elle hérite de la classe __Object__ (disponible en annexe).
- On déclare une structure décrivant la *vtable* (la *vtable* étant un élément contenant l'ensemble des fonctions virtuelles d'un objet).
Cette structure est une copie de la structure décrivant la *vtable Parent*.
- On génère à la fin de l'AST une structure qui est une copie la structure décrivant la classe parent.
    - On change le type de pointeur sur la *vtable*.
- On ajoute une référence vers cette structure dans *ast.ref.types*.

Pour chaque *at_member* de la BNF: 
- Avant la Declaration.line_of_code:
        Initialisation de la variable member dans Status à True

- Après la Declaration.line_of_code:

        Si la line_of_code est une fonction membre
            Rajout de self en premier paramètre
        Si elle est une fonction virtuelle
            Si elle n existe pas encore dans la vtable de la classe
                Ajout de sa définition à la vtable de la classe
            Sinon
                Dans la structure Membre créée plus haut, recherche de son Symbole correspondant, et initialisation de sa
                variable isRedefined à True.
        Si elle n est pas une fonction virtuelle, elle est ajoutée à la structure Member créée plus haut
        Réinitialisation de la variable member dans Status à False

- Pour chaque line_of_code:
        Si le member de Status vaut True
            Meme traitement qu après la Declaration.line_of_code

####Déroulement:

Pour chaque entrée dans stmt :
- S'il s'agit d'une *déclaration*, elle est ajoutée au tableau de symboles correspondant au Module courant; ajout au current_block de l'AST la variable passée en extern amputée de l''éventuel opérateur "=" à sa droite.
- __const__ est géré comme une déclaration standard.
- Lorsqu'un __static__ est rencontré, le symbole est push dans le current_block.
- Lorsqu'un __inline__ est rencontré, un message d'erreur est affiché et l'unité de compilation est quittée avec le code __1__ car un __inline__ ne peut se trouver dans un __@module__.
- Enfin, dans le cas des définitions de types (__typedef__, __struct__, __union__, __enum__), un weakref est ajouté dans ast.ref.types, puis le node inchangé est push dans le current_block.

*Exemple avec __typedef__:*

```
if isinstance(node, Decl) and node._ctype._storage == Storages.TYPEDEF:
    ast.ref.types[node._name] = weakref.ref(node)
```

###@implementation
Chaque __@module__/__@class__ a son __@implementation__ associée, qui s'appuie sur la BNF suivante:

```
declaration =
[ Declaration.declaration
| at_implementation
]

at_implementation = [
    "@implementation" id
    Statement.compound_statement ]

line_of_code =
[ Declaration.line_of_code
| at_member
]

at_member = [ [ "@member" | "@virtual" ] Declaration.line_of_code ]
```


On commence par définir les variables déclarées dans le __@module__/__@class__ en leur
assosciant une valeur si nécéssaire.

On prend ensuite chaque fonction dans le __@implementation__, et grâce à la structure de données on l'assoscie à *un symbole manglé*.

####Déroulement:

1. Le block est parsé comme un block standard
2. Pour chaque fonction
    - On effectue un mangling sur le nom
        - Si le nom n'est pas dans la liste des symboles
            Le programme quitte avec une erreur de code __1__.
    - On vérifie s'il n'y a pas de déclarations multiples

En surcouche de ce __@implementation__, il existe 4 fonctions: __alloc__, __new__, __delete__ et __init_vtable__.

- __alloc__ va allouer la mémoire nécéssaire à l'objet sur le tas.
```
T*  T_alloc()
{
    return(malloc(sizeof(T)));
}
```

- __new__ est créée pour chaque fonction __init__ définie par l'utilisateur.
```
T*  new(int p1)
{
    T* self = [T alloc];
    [self init :p1];
    return (self);
}
```

- __delete__ appelle la fonction de nettoyage de l'instance si elle existe, puis libère la mémoire.
```
void    T_delete(T* self)
{
    /* si clean existe */
        T_clean(self);
    free(self);
}
```

- __init_vtable__ réalloue (alloue pour __Object__) la vtable et initialise l'ensemble de ses membres.

Au début de chaque fonction __init__, on appellera la fonction __init__ du Parent, puis la fonction __init_vtable__.

###Opérateurs [ ]
Les opérateurs [ ] marquent des appels KOOC. On les traite à l'aide de la BNF suivante:
```
primary_expression =
[ Declaration.primary_expression
| brackets ]

brackets = [ id:Mod [ " " | "." ] id [ ':' id ]* ]
```

Lorsque Cnorm rencontre ces opérateurs, les opérations se déroulent en 3 étapes:
1. Les opérateurs [ ] sont remplacés par des noeuds de type __Id | Func__. S'il s'agit du traitement d'une variable, l'__Id__ sera créé à l'aide du contenu de "var". Sinon, on initialise la variable __name__ du noeud créé à "var".
2. Dans le cas d'une fonction, tous les paramètres définis avec le "__[ ':' id ]*__" de la BNF sont placés dans une liste dans le noeud.
3. Dans le noeud, on créé une variable __module__, de type __Id__ ou __Expr__ dans laquelle on stocke le __Mod__ de la BNF.

Lorsque le parsing de Cnorm est terminé, nous relançons un nouveau parsing sur l'ensemble de l'AST à la recherche d'un noeud ayant une variable appelée __module__.
Lorsqu'un noeud est trouvé, l'expression à laquelle il appartient se voit soumise à un algoritme de résolution de types. Si le type est différent d'un __Module__ alors on cherche à résoudre le type de l'expression stockeé dans __module__. Si ce type ne correspond à aucune classe, une erreur est affichée et le programme quitte. Sinon, on insère notre __module__ à la première position du tableau de paramètres du noeud et on stocke dans __module__ une référence vers le __Module__ concerné. Si le noeud représente un appel vers une fonction virtuelle, on remplace cet appel de fonction par un appel depuis la vtable de l'objet spécifié en premier paramètre de la fonction.

Enfin, tous les appels KOOC de l'expression sont manglés afin d'éviter les collisions dans le code C généré.

###Annexe
Partie 1
========

Module.kh :
```
@module	Module
{
  int		v = 3;
  char		v = 7;

  void		func();
  void		func(int);
  int		func();
};
```
Module.h :
```
extern int	int_Module_v;
extern char	char_Module_v;

void	void_Module_func();
void	void_Module_func_int(int);
int	int_Module_func();
```

main.kc :
```
@import "Module.kh"

int	main()
{
  int	var;

  [a func];
  [a func :7];
  void_a_func_int(7);
  var = [a func];
  @!(int)[a func]
  var = [a.v];

  return (0);
}
```

Module.kc :
```
@import "Module.kh"

@implementation	Module
{
  void	func()
  {
    printf("Quelque chose\n");
  }

  void	func(int d)
  {
    printf("%d\n", d);
  }

  int	func()
  {
    return (printf("Quelque chose d'autre\n"));
  }
}
```

Module.c :
```
#ifndef MODULE_KH_
#define MODULE_KH_
#include "Module.h"
#endif

int	int_Module_v = 3;
char	char_Module_v = 7;

void	void_Module_func()
{
  printf("Quelque chose\n");
}

int	int_Module_func_int(int d)
{
  printf("%d\n", d);
}

int	int_Module_func()
{
  return (printf("Quelque chose d'autre\n"));
}
```

main.c :
```
#ifndef MODULE_KH_
#define MODULE_KH_
#include "Module.h"
#endif

int	main()
{
  int	var;

  void_a_func();
  void_a_func_int(7);
  void_a_func_int(7);
  var = int_a_func();
  int_a_func();
  var = int_a_v;

  return (0);
}
```


Partie 2
========

Class.kh :
```
@class	Class
{
  int	var;
  void	func();

  @member
    {
      int	member_var;
      void	member_func();

      void	init();
      void	init(int);

      void	clean();
    }
}
```

Class.h :
```
Class*	pClass_Class_alloc();
void	void_Class_delete_pClass(Class* self);

typedef struct
{
  int	int_member_var;
}	Class;

extern int	int_Class_var;
void	void_Class_func();
void	void_Class_member_func_pClass(Class* self);
void	void_Class_init_pClass(Class* self);
Class*	pClass_Class_new();
void	void_Class_init_pClass_int(Class* self, int);
Class*	pClass_Class_new_int(int n);
void	void_Class_clean_pClass(Class* self);
```

Class.kc :
```
@import "Class.kh"

@implement	Class
{
  void	func()
  {
    printf("Non-member func\n");
  }

  @member void	member_func()
  {
    printf("Member func : self=%p\n", self);
  }

  @member void	init()
  {}

  @member void	init(int n)
  {
    self->member_var = n;
  }
}
```

Class.c :
```
#include	<stdlib.h>
#ifndef CLASS_KH_
#define CLASS_KH_
#include "Class.h"
#endif

int	int_Class_var;

Class*	pClass_Class_alloc()
{
  return malloc(sizeof(Class));
}

void	void_Class_delete_pClass(Class* self)
{
  void_Class_clean_pClass(self);
  free(self);
}

void	void_Class_func()
{
  printf("Non-member func\n");
}

void	void_Class_member_func_pClass(Class* self)
{
  printf("Member func : self=%p\n", self);
}


void	void_Class_init_pClass(Class* self)
{}

Class*	pClass_Class_new()
{
  Class*	inst;

  inst = pClass_Class_alloc();
  void_Class_init_pClass(inst);
  return inst;
}

void	void_Class_init_pClass_int(Class* self, int n)
{
  self->member_var = n;
};

Class*	pClass_Class_new_int(int n)
{
  Class*	inst;

  inst = pClass_Class_alloc();
  void_Class_init_pClass_int(inst, n);
  return inst;
}

void	void_Class_clean_pClass(Class* self)
{
  printf("Cleaning class...\n");
}
```

EmptyClass.kh :
```
// Cette exemple de classe sert notamment à montrer le comportement lorsqu'aucune fonction
// init ou clean n'est déclarée.
@class	EmptyClass
{}
```

EmptyClass.h :
```
EmptyClass*	pEmptyClass_EmptyClass_alloc();
void	void_EmptyClass_delete_pEmptyClass(Class* self);

typedef struct
{
}	EmptyClass;

void		void_EmptyClass_init_pEmptyClass(EmptyClass* self);
EmptyClass*	pEmptyClass_EmptyClass_new();
```

EmptyClass.kc :
```
@import "EmptyClass.kh"

@implement	EmptyClass
{}
```

EmptyClass.c :
```
#include	<stdlib.h>
#ifndef EMPTYCLASS_KH_
#define EMPTYCLASS_KH_
#include "EmptyClass.h"
#endif

EmptyClass*	pEmptyClass_EmptyClass_alloc()
{
  return malloc(sizeof(EmptyClass));
}

void	void_EmptyClass_delete_pEmptyClass(EmptyClass* self)
{
  free(self);
}

void		void_EmptyClass_init_pEmptyClass(EmptyClass* self)
{}

EmptyClass*	pEmptyClass_EmptyClass_new()
{
  EmptyClass*	inst;

  inst = pEmptyClass_EmptyClass_alloc();
  void_EmptyClass_init_pEmptyClass(inst);
  return inst;
}
```

main.kc :
```
@import "Class.kh"
@import "EmptyClass.kh"

int		main()
{
  Class		class_inst;
  EmptyClass*	emptyClass_inst;
  int		n;

  [&class_inst init :3];
  n = [Class.var];
  n = [inst.member_var];
  [Class func];
  [Class member_func &inst];
  [&inst member_func];
  [&inst clean];

  emptyClass_inst = [EmptyClass new];
  [emptyClass delete];

  return 0;
}
```

main.c :
```
#ifndef CLASS_KH_
#define CLASS_KH_
#include "Class.h"
#endif
#ifndef EMPTYCLASS_KH_
#define EMPTYCLASS_KH_
#include "EmptyClass.h"
#endif

int		main()
{
  Class		class_inst;
  EmptyClass*	emptyClass_inst;
  int		n;

  void_Class_init_pClass_int(&class_inst, 3);
  n = int_Class_var;
  n = inst.int_member_var;
  void_Class_func();
  void_Class_member_func_pClass(&inst);
  void_Class_member_func_pClass(&inst);
  void_Class_clean_pClass(&inst);

  emptyClass_inst = pEmptyClass_EmptyClass_new();
  void_EmptyClass_delete_pEmptyClass(emptyClass);

  return 0;
}
```

Partie 3
========

Object.kh :
```
@class	Object
{
  @member int	isInstanceOf(Object* other);
  @member int	isInstanceOf(const char* otherClassName);
  @member int	isKindOf(Object* other);
  @member int	isKindOf(const char* otherClassName);
}
```

Object.h :
```
Class*	pObject_Object_alloc();
void	void_Object_delete_pObject(Object* self);

typedef struct
{
  char*	type;
  void	(*void_delete_pObject)(Object*);
}	ObjectVtable;

typedef struct
{
  ObjectVtable*	__vtable;
}		Object;

void	void_Object_init_pObject(Object* self);
Object*	pObject_Object_new();

int	int_Object_isInstanceOf_pObject_pObject(Object* self, Object* other);
int	int_Object_isInstanceOf_pObject_pchar(Object* self, const char* otherClassName);
int	int_Object_isKindOf_pObject_pObject(Object* self, Object* other);
int	int_Object_isKindOf_pObject_pchar(Object* self, const char* otherClassName);
```

Object.kc :
```
@import "Object.kh"

@implementation	Object
{
  @member int	isInstanceOf(Object* other)
  {
    if (strcmp(self->__vtable->type, other->__vtable->type) == 0)
      return 1;
    else
      return 0;
  }

  @member int	isInstanceOf(const char* otherClassName)
  {
    const char*	selfClassName;

    selfClassName = self->__vtable->type;
    if (strrchr(selfClassName, '.'))
      selfClassName = strrchr(selfClassName, '.') + 1;
    if (strcmp(selfClassName, otherClassName) == 0)
      return 1;
    else
      return 0;
  }

  @member int	isKindOf(Object* other)
  {
    if (strncmp(self->__vtable->type, other->__vtable->type, strlen(other->__vtable->type)) == 0 &&
	(self->__vtable->type[strlen(other->__vtable->type)] == '.' ||
	 self->__vtable->type[strlen(other->__vtable->type)] == '\0'))
      return 1;
    else
      return 0;
  }

  @member int	isKindOf(const char* otherClassName)
  {
    const char*	selfClassName = self->__vtable->type;

    while ((selfClassName = strstr(selfClassName, otherClassName)) != NULL)
      if ((selfClassName == self.__vtable[0] || selfClassName[-1] == '.') &&
	  (selfClassName[strlen(otherClassName)] == '.' ||
	   selfClassName[strlen(otherClassName)] == '\0'))
	return 1;
    return 0;
  }
}
```

Object.c :
```
#include	<stdlib.h>
#ifndef OBJECT_KH_
#define OBJECT_KH_
#include "Object.h"
#endif

Object*	pObject_Object_alloc()
{
  return malloc(sizeof(Object));
}

void	void_Object_init_vtable_pObject(Object* self)
{
  self->__vtable = malloc(sizeof(Object_Vtable));
  self->__vtable->type = "Object";
  self->__vtable->void_delete_pObject = void_Object_delete_pObject;
}

void	void_Object_delete_pObject(Object* self)
{
  free(self);
}

void		void_Object_init_pObject(Object* self)
{
  void_Object_init_vtable_pObject(self);
}

Object*	pObject_Object_new()
{
  Object*	inst;

  inst = pObject_Object_alloc();
  void_Object_init_pObject(inst);
  return inst;
}


int	int_Object_isInstanceOf_pObject_pObject(Object* self, Object* other)
{
  if (strcmp(self->__vtable->type, other->__vtable->type) == 0)
    return 1;
  else
    return 0;
}

int	int_Object_isInstanceOf_pObject_pchar(Object* self, const char* otherClassName)
{
  const char*	selfClassName;

  selfClassName = self->__vtable->type;
  if (strrchr(selfClassName, '.'))
    selfClassName = strrchr(selfClassName, '.') + 1;
  if (strcmp(selfClassName, otherClassName) == 0)
    return 1;
  else
    return 0;
}

int	int_Object_isKindOf_pObject_pObject(Object* self, Object* other)
{
  if (strncmp(self->__vtable->type, other->__vtable->type, strlen(other->__vtable->type)) == 0 &&
      (self->__vtable->type[strlen(other->__vtable->type)] == '.' ||
       self->__vtable->type[strlen(other->__vtable->type)] == '\0'))
    return 1;
  else
    return 0;
}

int	int_Object_isKindOf_pObject_pchar(Object* self, const char* otherClassName)
{
  const char*	selfClassName = self->__vtable->type;

  while ((selfClassName = strstr(selfClassName, otherClassName)) != NULL)
    if ((selfClassName == self.__vtable[0] || selfClassName[-1] == '.') &&
	(selfClassName[strlen(otherClassName)] == '.' ||
	 selfClassName[strlen(otherClassName)] == '\0'))
      return 1;
  return 0;
}
```

Parent.kh :
```
@class	Parent
{
  @member int	member_var;
  @member void	func();
  @virtual void	virtual_func();
}
```

Parent.h :
```
Class*	pParent_Parent_alloc();
void	void_Parent_delete_pParent(Parent* self);

typedef struct
{
  char*	type;
  void	(*void_delete_pObject)(Object*);
  void	(*void_virtual_func_pParent)(Parent*); // /!\ Ici, Parent n'est pas encore défini.
  // Note de mangling : pour le nom de type dans le nom de fonction, on prendra le plus haut ayant cette function. Ou simplement Objet.
}	ParentVtable;

typedef struct
{
  ParentVtable*	__vtable;
  int		int_member_var;
}		Parent;

void	void_Parent_init_pParent(Parent* self);
Parent*	pParent_Parent_new();

void	void_Parent_func_pParent(Parent* self);
void	void_Parent_virtual_func_pParent(Parent* self);
```

Parent.kc :
```
@import "Parent.kh"

@implement	Parent
{
  @member void	func()
  {}

  @virtual void	virtual_func()
  {
    printf("Virtual function called from Parent");
  }
}
```

Parent.c :
```
#ifndef OBJECT_KH_
#define OBJECT_KH_
#include "Object.h"
#endif
#include	<stdlib.h>
#ifndef PARENT_KH_
#define PARENT_KH_
#include "Parent.h"
#endif

Parent*	pParent_Parent_alloc()
{
  return malloc(sizeof(Parent));
}

void	void_Parent_init_vtable_pParent(Parent* self)
{
  self.__vtable = realloc(self.__vtable, sizeof(Parent_Vtable));
  self->__vtable->type = "Object.Parent";
  self->__vtable->void_delete_pObject = void_Parent_delete_pParent;
  self->__vtable->void_virtual_func_pParent = void_Parent_virtual_func_pParent;
}

void	void_Parent_delete_pParent(Parent* self)
{
  free(self);
}

void		void_Parent_init_pParent(Parent* self)
{
  void_Object_init_pObject(self);
  void_Parent_init_vtable_pParent(self);
}

Parent*	pParent_Parent_new()
{
  Parent*	inst;

  inst = pParent_Parent_alloc();
  void_Parent_init_pParent(inst);
  return inst;
}

void	void_Parent_func_pParent(Parent* self)
{}

void	void_Parent_virtual_func_pParent(Parent* self)
{
  printf("Virtual function called from Parent");
}
```

Class.kh :
```
@import	Parent

@class	Class : Parent
{
  @member int	member_var_in_class;
  @member void	func_in_class();
  @virtual void	virtual_func();
  @virtual void	other_virtual();
}
```

Class.h :
```
#ifndef PARENT_KH_
#define PARENT_KH_
#include "Parent.h"
#endif

Class*	pClass_Class_alloc();
void	void_Class_delete_pClass(Class* self);

typedef struct
{
  char*	type;
  void	(*void_delete_pObject)(Object*);
  void	(*void_virtual_func_pParent)(Parent*);
  void	(*void_other_virtual_pClass)(Class*);
}	ClassVtable;

typedef struct
{
  ClassVtable*	__vtable;
  int		int_member_var;
  int		int_member_var_in_class;
}		Class;

void	void_Class_init_pClass(Class* self);
Class*	pClass_Class_new();

void	void_Class_func_in_class_pClass(Class* self);
void	void_Class_virtual_func_pClass(Class* self);
void	void_Class_other_virtual_pClass(Class* self);
```

Class.kc :
```
@import "Class.kh"

@implement	Class
{
  @member void	func_in_class()
  {}

  @virtual void	virtual_func()
  {
    printf("Virtual function called from Class");
  }

  @virtual void	other_virtual()
  {}
}
```

Class.c :
```
#include	<stdlib.h>
#ifndef CLASS_KH_
#define CLASS_KH_
#include "Class.h"
#endif

Class*	pClass_Class_alloc()
{
  return malloc(sizeof(Class));
}

void	void_Class_init_vtable_pClass(Class* self)
{
  self.__vtable = realloc(self.__vtable, sizeof(Class_Vtable));
  self->__vtable->type = "Object.Parent.Class";
  self->__vtable->void_delete_pObject = void_Class_delete_pClass;
  self->__vtable->void_virtual_func_pParent = void_Class_virtual_func_pClass;
  self->__vtable->void_other_virtual_pClass = void_Class_other_virtual_pClass;
}

void	void_Class_delete_pClass(Class* self)
{
  free(self);
}

void	void_Class_init_pClass(Class* self)
{
  void_Parent_init_pParent(self);
  void_Class_init_vtable_pClass(self);
}

Class*	pClass_Class_new()
{
  Class*	inst;

  inst = pClass_Class_alloc();
  void_Class_init_pClass(inst);
  return inst;
}

void	void_Class_func()
{
  printf("Non-member func\n");
}

void	void_Class_member_func_pClass(Class* self)
{
  printf("Member func : self=%p\n", self);
}


void	void_Class_func_in_class_pClass(Class* self)
{}

void	void_Class_virtual_func_pClass(Class* self)
{
  printf("Virtual function called from Class");
}

void	void_Class_other_virtual_pClass(Class* self)
{}
```

main.kc :
```
@import "Class.kh"

int		main()
{
  Class*	class;
  Parent*	parent;

  class = [Class new];
  parent = class;

  [parent virtual_func];
  [class virtual_func];
  [Parent virtual_func :class];

  [parent delete]

  return 0;
}
```

main.c :
```
#ifndef CLASS_KH_
#define CLASS_KH_
#include "Class.h"
#endif

int		main()
{
  Class*	class;
  Parent*	parent;

  class = pClass_Class_new();
  parent = class;

  parent->__vtable->void_virtual_func_pParent(parent);
  class->__vtable->void_virtual_func_pParent(class);
  void_Parent_virtual_func_pParent(class);

  parent->__vtable->void_Object_delete_pObject(parent);

  return 0;
}
```
