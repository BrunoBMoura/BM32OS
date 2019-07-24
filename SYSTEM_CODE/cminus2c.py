import os

path = os.getcwd()

for file in os.listdir(path):
	if file.endswith(".cminus"):
		new_file = str(file).replace("cminus","c")
		cminus_file = open(file, "r")
		text = cminus_file.read()
		c_file = open(new_file, "w")
		c_file.write(text)
		cminus_file.close()
		c_file.close()
		
