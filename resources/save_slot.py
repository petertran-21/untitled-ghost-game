import json
import os



filepath = os.getcwd() + "/Saves/Slot1"
print(filepath)
json_files = [pos_json for pos_json in os.listdir(filepath) if pos_json.endswith('.json')]
for filename in json_files:
    with open(filepath + '/' + filename, 'r') as json_file:
        print(filepath + '/' + filename)
        data = json.load(json_file)
        for gameObject in data["sprites"]:
            if ("scene_path" in gameObject):
                split = gameObject["scene_path"].split("/")
                gameObject["scene_path"] = "resources/Saves/Slot1/" + split[-1]


    with open (filepath + '/' + filename, 'w') as json_file:
        json.dump(data, json_file, indent=4)