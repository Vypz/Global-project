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

lenTitle = 0
lenIsbn = 0
lenPublished = 0
lenthumbnailUrl = 0
lenshortDescription = 0
lenlongDescription = 0
lenStatus = 0
lenAutors = 0
lenCategories = 0


for val in dataBooks:
    #print("Titre =  ", val['title'], " : ", len(val['title']))
    lenTitle += len(val['title'])
    try:
        #print("isbn = ", val['isbn'], " : ", len(val['isbn']))
        lenIsbn += len(val['isbn'])
    except KeyError as e:
        print("ERROR isbn  = ", e)

    try:
        #print("publishedDate = ", len(val['publishedDate']['$date']))
        lenPublished += len(val['publishedDate']['$date'])
    except KeyError as e:
        print("ERROR publishedDate = ", e)

    try:
        #print("thumbnailUrl : ", val['thumbnailUrl'], " : ", len(val['thumbnailUrl']))
        lenthumbnailUrl += len(val['thumbnailUrl'])
    except KeyError as e:
        print("ERROR thumbnailUrl = ", e)

    try:
        #print("shortDescription : ", val['shortDescription'], " : ", len(val['shortDescription']))
        lenshortDescription += len(val['shortDescription'])
    except KeyError as e:
        print("ERROR shortDescription = ", e)

    try:
        #print("longDescription : ", val['longDescription'], " : ", len(val['longDescription']))
        lenlongDescription += len(val['longDescription'])
    except KeyError as e:
        print("ERROR longDescription = ", e)

    #print("Status =  ", val['status'], " : ", len(val['status']))
    lenStatus += len(val['status'])
    #print("Autors =  ", val['authors'], " : ", len(val['authors']))
    lenAutors += len(val['authors'])
    #print("Categories = ", val['categories'], " : ", len(val['categories']))
    lenCategories += len(val['categories'])

TOTAL = lenTitle + lenIsbn + lenPublished + lenthumbnailUrl + lenshortDescription + lenlongDescription + lenStatus + lenAutors + lenCategories
print("Le total des caractère est de ", TOTAL)
