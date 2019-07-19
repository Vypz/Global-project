userReply = input("would you like to buy stamps, an envelope, or make a copy ? ")

if userReply == "stamps":
	print("We have plenty of stamps")
elif userReply == "envelope":
	print("We have have many envelope")
elif userReply == "copy":
	copies = input("would you like to buy stamps, an envelope, or make a copy ? ")
	print("here are {} copie".format(copies))
else:
	print("thanks you, please come again")
