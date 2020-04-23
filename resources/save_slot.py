import json

filepath = 'Saves/Slot1/beachRoom1.json'
with open(filepath, 'r') as json_file:
    data = json.load(json_file)
    for gameObject in data["sprites"]:
        if ("scene_path" in gameObject):
            split = gameObject["scene_path"].split("/")
            gameObject["scene_path"] = "resources/Saves/Slot1/" + split[-1]


with open (filepath, 'w') as json_file:
    json.dump(data, json_file, indent=4)