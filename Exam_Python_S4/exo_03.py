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

bookCategorieJava = []
bookCategorieBusiness = []
bookCategorieClientServer = []
bookCategorieDotNet = []
bookCategorieSoftEngi = []
bookCategorieInternet = []
bookCategorieTheory = []
bookCategorieComputerGraph = []
bookCategorieNetworking = []
bookCategorieProgramming = []
bookCategoriePython = []
bookCategorieSOA = []
bookCategorieObjectOriented = []
bookCategorieMobileTech = []
bookCategorieAlgo = []
bookCategorieXML = []
bookCategorieWebDev = []
bookCategoriePerl = []
bookCategorieComputerGraphics = []
bookCategorieObjectTechnologyProgramming = []
bookCategorieMiscella = []
bookCategoriePowerBuilder = []
bookCategorieOpenSource = []
bookCategorieP = []
bookCategorieS = []
bookCategorieNext = []
bookCategorieMicrosoft = []

for val in dataBooks:
    print("Catégorie = ", val['categories'])
    for index in val['categories']:
        print("l'index est ", index)

        if index == "Java":
            #print("JAVA : TITRE DU LIVRE", val['title'])
            bookCategorieJava.append(val['title'])
        if index == "Business":
            #print("Catégorie Business ! ")
            bookCategorieBusiness.append(val['title'])

        if index == "Client-Server":
            #print("Catégorie Client-Server ! ")
            bookCategorieClientServer.append(val['title'])
        if index == "Microsoft .NET":
            print("Catégorie Microsoft .NET ! ")
            bookCategorieDotNet.append(val['title'])

        if index == "Software Engineering":
            print("Catégorie Software Engineering ! ")
            bookCategorieSoftEngi.append(val['title'])

        if index == "Internet":
            print("Catégorie Internet ! ")
            bookCategorieInternet.append(val['title'])

        if index == "Theory":
            print("Catégorie Theory ! ")
            bookCategorieTheory.append(val['title'])

        if index == "Computer Graph":
            print("Catégorie Computer Graph ! ")
            bookCategorieComputerGraph.append(val['title'])

        if index == "Networking":
            print("Catégorie Networking ! ")
            bookCategorieNetworking.append(val['title'])

        if index == "Programming":
            print("Catégorie Programming ! ")
            bookCategorieProgramming.append(val['title'])

        if index == "Python":
            print("Catégorie Python ! ")
            bookCategoriePython.append(val['title'])

        if index == "SOA":
            print("Catégorie SOA ! ")
            bookCategorieSOA.append(val['title'])

        if index == "Object-Oriented Programming":
            print("Catégorie Object-Oriented Programming ! ")
            bookCategorieObjectOriented.append(val['title'])

        if index == "Mobile Technology":
            print("Catégorie Mobile Technology ! ")
            bookCategorieMobileTech.append(val['title'])

        if index == "Algorithmic Art":
            print("Catégorie Algorithmic Art ! ")
            bookCategorieAlgo.append(val['title'])
        if index == "XML":
            print("Catégorie XML ! ")
            bookCategorieXML.append(val['title'])
        if index == "Web Development":
            print("Catégorie Web Development ! ")
            bookCategorieWebDev.append(val['title'])
        if index == "Perl":
            print("Catégorie Perl ! ")
            bookCategoriePerl.append(val['title'])
        if index == "Computer Graphics":
            print("Catégorie Computer Graphics ! ")
            bookCategorieComputerGraphics.append(val['title'])
        if index == "Object-Technology Programming":
            print("Catégorie Object-Technology Programming ! ")
            bookCategorieObjectTechnologyProgramming.append(val['title'])
        if index == "Miscella":
            print("Catégorie Miscella ! ")
            bookCategorieMiscella.append(val['title'])
        if index == "PowerBuilder":
            print("Catégorie PowerBuilder ! ")
            bookCategoriePowerBuilder.append(val['title'])
        if index == "Open Source":
            print("Catégorie Open Source ! ")
            bookCategorieOpenSource.append(val['title'])
        if index == "P":
            print("Catégorie P ! ")
            bookCategorieP.append(val['title'])
        if index == "S":
            print("Catégorie S ! ")
            bookCategorieS.append(val['title'])
        if index == "Next Generation Databases":
            print("Catégorie Next Generation Databases ! ")
            bookCategorieNext.append(val['title'])
        if index == "Microsoft":
            print("Catégorie Microsoft ! ")
            bookCategorieMicrosoft.append(val['title'])

print("JAVA", bookCategorieJava)
print("Business", bookCategorieBusiness)
print("ClientServer", bookCategorieClientServer)
print("DotNet", bookCategorieDotNet)
print("SoftEngi", bookCategorieSoftEngi)
print("Internet", bookCategorieInternet)
print("Theory", bookCategorieTheory)
print("ComputerGraph", bookCategorieComputerGraph)
print("Networking", bookCategorieNetworking)
print("Programming", bookCategorieProgramming)
print("Python", bookCategoriePython)
print("SOA", bookCategorieSOA)
print("ObjectOriented", bookCategorieObjectOriented)
print("MobileTech", bookCategorieMobileTech)
print("Algo", bookCategorieAlgo)
print("XML", bookCategorieXML)
print("WebDev", bookCategorieWebDev)
print("Perl", bookCategoriePerl)
print("ComputerGraphics", bookCategorieComputerGraphics)
print("ObjectTechnologyProgramming", bookCategorieObjectTechnologyProgramming)
print("Miscella", bookCategorieMiscella)
print("PowerBuilder", bookCategoriePowerBuilder)
print("OpenSource", bookCategorieOpenSource)
print("P", bookCategorieP)
print("S", bookCategorieS)
print("CategorieNext", bookCategorieNext)
print("Microsoft", bookCategorieMicrosoft)