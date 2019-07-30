import json

f = open("books.json", "r")

books = json.load(f)

categories = {}

for book in books:
    for categorie in book["categories"]:
        if not categorie in categories:
            categories[categorie] = []
            categories[categorie].append(book)
        else:
            categories[categorie].append(book)

    for categorie, books in categories.items():
        print("Livre de la catégorie : ", categorie)
    for book in books:
        print(book["title"])
f.close()

recupInput = input("* Lister les catégories existantes ( List ). * Afficher les livres. ( Show )" \
                   "* Afficher les livres de la catégorie listé par l’utilisateur. ( Show C ) ")
print("Hello", recupInput)

if recupInput == "List":
    print("List")
    for val in categories:
        print(val)

if recupInput == "Show":
    print("Show")
if recupInput == "Show C":
    print("Show C")
