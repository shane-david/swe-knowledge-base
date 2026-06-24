# Shane David
# CS3080 Assignment 1
# 6/24/2026

import os
import json
import csv

"""
File Utils Class will contain static methods for working with files
"""
class FileUtils:

    @staticmethod
    def path_exists(filename):
        return os.path.exists(filename)
    
    @staticmethod
    def write_text_file(filename, content):

        # set mode to a (append) if the file exists or to w (write) if it does not
        mode = 'a' if FileUtils.path_exists(filename) else 'w'

        # open the file at the specified mode 
        with open(filename, mode, encoding='utf-8') as f:

            match content:

                # check if the content is a list or a tuple of strings 
                case list() | tuple() if all(isinstance(item,str) for item in content):

                    # write content to a text file
                    f.writelines(content)

                # check if the content is a list or a tuple NOT of strings
                case list() | tuple() if not all(isinstance(item,str) for item in content):

                    # use a list comprehension to create a new list with all non string items casted to string and write them
                    f.writelines([str(item) +'\n' for item in content])

                # check if the content is just a string
                case str():
                    
                    # write the string to the file appending a newling character to the end
                    f.write(content + '\n')

                # check if the content is a dictionary 
                case dict():

                    # write the content of the dictionary in lines of key value pairs
                    for key, value in content.items():
                        f.write(f"{key}: {value}\n")

                case _:

                    # cast any other object passed in to a string and write it
                    f.write(str(content) + '\n')

    @staticmethod
    def read_text_file(filename, to="list_string"):

        # check if the file exists, raise an error if it does not 
        if not FileUtils.path_exists(filename):
            raise FileNotFoundError(f"The file {filename} does not exist.")
        
        # open the file for reading
        with open(filename, 'r', encoding='utf-8') as f:

            if to == "list_string":
                return f.read().split() 
            elif to == "list_int":
                return [int(x) for x in f.read().split()]
            elif to == "list_float":
                return [float(x) for x in f.read().split()]
            elif to == "raw_dictionary":
                return {i: line.strip() for i, line in enumerate(f.readlines())}
            elif to == "formatted_dictionary":
                return {line.split(':')[0].strip(): line.split(':')[1].strip() for line in f.readlines() if ':' in line}

    @staticmethod
    def write_csv_file(filename, data):

        # set mode to a (append) if the file exists or to w (write) if it does not
        mode = 'a' if FileUtils.path_exists(filename) else 'w'

        # open the file at the specified mode 
        with open(filename, mode, newline='', encoding='utf-8') as f:

            # if the data is a dictionary
            if isinstance(data, dict):

                # get the keys of the dictionary to represent the headers
                fieldnames = data.keys()

                writer = csv.DictWriter(f, fieldnames=fieldnames)

                # only write the header if it is the first time opening the file
                if  mode == "w":
                    writer.writeheader()

                writer.writerow(data)

            # if the data is a list or a tuple
            elif isinstance(data, (list,tuple)):

                writer = csv.writer(f)
                writer.writerow(data)

    @staticmethod
    def read_csv_file(filename, to="list_string"):

        # check if the file exists, raise an error if it does not 
        if not FileUtils.path_exists(filename):
            raise FileNotFoundError(f"The file {filename} does not exist.")
        
        # open the file for reading 
        with open(filename, 'r', encoding='utf-8') as f:

            if to == "dictionary":
                reader = csv.DictReader(f)
                return [row for row in reader]
            
            reader = csv.reader(f)

            if to == "list_string":
                return [row for row in reader]
            elif to == "list_int":
                return [[int(item) for item in row] for row in reader]
            elif to == "list_float":
                return [[float(item) for item in row] for row in reader]
            elif to == "raw_dictionary":
                return [{i:item for i,item in enumerate(row)} for row in reader]
            
    @staticmethod
    def write_json_file(filename, data):
        
        # if the file exists, open it to append
        if FileUtils.path_exists(filename):

            with open(filename, 'r', encoding='utf-8') as f:

                # read existing data from json file
                existing = json.load(f)

                # if the existing json content is a list
                if isinstance(existing, list):

                    # append the passed in data to the list
                    existing.append(data)

                # otherwise it is not a list
                else:
                    
                    existing = [existing, data]

        # otherwise the file does not exist and we need ot create a new one
        else:
            existing = data

        # open the file for writing and dump into json
        with open(filename, 'w', encoding='utf-8') as f:
            json.dump(existing, f, indent=4)

    @staticmethod
    def read_json_file(filename):
        with open(filename, 'r', encoding='utf-8') as f:
            return json.load(f)

"""
Demo Utils Class for learning
"""
class DemoUtils:

    # class attributes
    filename = "demo"
    demo_number = 0
    filename = f"{filename}_{demo_number}"

    @classmethod
    def change_filename(cls, name):
        cls.filename = f"{name}_{cls.filename.split('_')[1]}"

    @classmethod
    def update_demo_number(cls):
        cls.filename = f"{cls.filename.split('_')[0]}_{cls.demo_number}"

    def __init__(self, folder="current"):

        # set the path
        self.path = folder

        # if path is not current join it to the working directory
        if (self.path != "current"):
            self.path = os.path.join(os.getcwd(), self.path)

            # if it does not exist make the folder 
            if not os.path.exists(self.path):
                os.makedirs(self.path)
    
    def update_filepath(self):

        # if the file path is not the current directory, append it before the filename
        if self.path != "current":

            self.filepath = os.path.join(self.path, DemoUtils.filename) 

        # otherwise the filename is sufficient
        else:
            self.filepath = DemoUtils.filename

    def new_demo(self):

        DemoUtils.demo_number += 1
        DemoUtils.update_demo_number()
        self.update_filepath()
        
        self.text_path = self.filepath + ".txt"
        self.cvs_path = self.filepath + ".csv"
        self.json_path = self.filepath + ".json"
        print(f"\nRunning demo {DemoUtils.demo_number} with new filename: {DemoUtils.filename}")


    def demo(self, name="demo"):
        
        # if name is not demo change the filenmae
        if name != "demo":
            DemoUtils.change_filename(name)

        # running first demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, ["List String Line 1\n", "List String Line 2\n", "List String Line 3\n"])
        demo_list = FileUtils.read_text_file(self.text_path, "list_string")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        print("Demo List after list of strings:", demo_list)
        print("Demo Raw Dictionary after list of strings:", demo_dict)

        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, ("Tuple String Line 1\n", "Tuple String Line 2\n", "Tuple String Line 3\n"))
        demo_list = FileUtils.read_text_file(self.text_path, "list_string")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        print("Demo List after Tuple:", demo_list)
        print("Demo Raw Dictionary after Tuple:", demo_dict)

        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, [1, 2, 3])
        demo_list = FileUtils.read_text_file(self.text_path, "list_int")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        demo_list_string = FileUtils.read_text_file(self.text_path, "list_string")
        print("Demo List after List Int:", demo_list)
        print("Demo Raw Dictionary after List Int:", demo_dict)
        print("Demo List String after List Int:", demo_list_string)

        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, (4.4, 5.5, 6.6))
        demo_list = FileUtils.read_text_file(self.text_path, "list_float")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        demo_list_string = FileUtils.read_text_file(self.text_path, "list_string")
        print("Demo List after Tuple Float:", demo_list)
        print("Demo Raw Dictionary after Tuple Float:", demo_dict)
        print("Demo List String after Tuple Float:", demo_list_string)

        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, {"key1": "value1", "key2": "value2"})
        demo_list = FileUtils.read_text_file(self.text_path, "formatted_dictionary")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        demo_list_string = FileUtils.read_text_file(self.text_path, "list_string")
        print("Demo List after Dictionary:", demo_list)
        print("Demo Raw Dictionary after Dictionary:", demo_dict)
        print("Demo List String after Dictionary:", demo_list_string)

        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, "Single String Line as input")
        demo_list = FileUtils.read_text_file(self.text_path, "list_string")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        print("Demo List after Single String Line:", demo_list)
        print("Demo Raw Dictionary after Single String Line:", demo_dict)
            
        # runnning new demo
        self.new_demo()
        FileUtils.write_text_file(self.text_path, 123.45)
        demo_list_string = FileUtils.read_text_file(self.text_path, "list_string")
        demo_list_float = FileUtils.read_text_file(self.text_path, "list_float")
        demo_dict = FileUtils.read_text_file(self.text_path, "raw_dictionary")
        print("Demo List String after Float:", demo_list_string)
        print("Demo List Float after Float:", demo_list_float)
        print("Demo Raw Dictionary after Float:", demo_dict)

       # runnning new demo
        self.new_demo()
        FileUtils.write_csv_file(self.cvs_path, ["Column1", "Column2", "Column3"])
        demo_list = FileUtils.read_csv_file(self.cvs_path, "list_string")
        demo_dict = FileUtils.read_csv_file(self.cvs_path, "raw_dictionary")
        print("Demo List after CSV List String:", demo_list)
        print("Demo Raw Dictionary after CSV List String:", demo_dict)

        # runnning new demo
        self.new_demo()
        FileUtils.write_csv_file(self.cvs_path, {"Column1": "Value1", "Column2": "Value2"})
        demo_list = FileUtils.read_csv_file(self.cvs_path, "list_string")
        demo_dict = FileUtils.read_csv_file(self.cvs_path, "dictionary")
        print("Demo List after CSV Dictionary:", demo_list)
        print("Demo Dictionary after CSV Dictionary:", demo_dict)

        # runnning new demo
        self.new_demo()
        FileUtils.write_json_file(self.json_path, {"key1": "value1", "key2": "value2"})
        demo_json = FileUtils.read_json_file(self.json_path)
        print("Demo JSON after writing JSON file:", demo_json)


# main
if __name__ == "__main__":

    demo1 = DemoUtils("experiments1")
    demo1.demo()

    demo2 = DemoUtils("experiments2")
    demo2.demo("CreatedByDemo2")

    demo1.change_filename("ChangedByDemo1")
    demo2.demo()



