import json


def isJson():

    with open('books.json') as json_data:
        try:
            data_dict = json.load(json_data)
            data_str = json.dumps(data_dict)
            data_dict_02 = json.loads(data_str)
            json_data.close()
            return data_dict_02
        except ValueError as e:
            print(e)
            exit(1)


dataBooks = isJson()

for val in dataBooks:
    print(val['title'], " ", val['authors'])
