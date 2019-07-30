import json
import sys


def isJson():

    with open('ffexample.json') as json_data:
        try:
            data_dict = json.load(json_data)        # Fichier
            data_str = json.dumps(data_dict)
            data_dict_02 = json.loads(data_str)     #Strings
            json_data.close()                       # Fermer le fichier
            return data_dict_02
        except ValueError as e:
            print(e)
            sys.exit(1)


dataFF = isJson()
print("Le fichier en dur : ", type(dataFF))
print("Test = ", dataFF[0]['name'])
print("----------")

persoList = []

for value in dataFF:
    persoList.append(value['name'] + " " + value['origin'])

print(persoList)

