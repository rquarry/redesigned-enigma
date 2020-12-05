inFile = open("app_flag.txt")

flag = inFile.read()

#print(flag)

test = flag.split()

print(test)

flag_string = ""

for i in test:
	#print(i)
	flag_int = int(i,16)
	flag_string += chr(flag_int-40)
	#print(flag_int)
	#flag_char -= 28
	#print(chr(flag_char))

print(flag_string)