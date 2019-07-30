import json


def isJson():

    with open('Film.JSON') as json_data:
        try:
            data_dict = json.load(json_data)
            data_str = json.dumps(data_dict)
            data_dict_02 = json.loads(data_str)
            json_data.close()
            return data_dict_02
        except ValueError as e:
            print(e)
            exit(1)


data_dict_02 = isJson()

serieList = []
filmList = []

for value in data_dict_02:
    if value['Type'] == 'movie':
        filmList.append(value['Title'])
    if value['Type'] == 'series':
        serieList.append(value['Title'])


print("La liste des films est :  ", filmList)
print("Le nombre de film est : ", len(filmList))
print("La liste des séries est : ", serieList)
print("Le nomde de série est : ", len(serieList))


