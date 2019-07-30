myDictionary = {"1": "Bonjour", "2": "Test", "3": "Boss"}


print("Le Dict complet est : ", myDictionary)
print("Le premier index est : ", myDictionary["1"])
print("Le troisième index est : ", myDictionary.get("3"))

print("--------")
for value in myDictionary.items():
    print(value)
