import json

filepath = 'scenes/beachRoom8.json'
with open(filepath, 'r') as json_file:
    data = json.load(json_file)
    for gameObject in data["sprites"]:
        gameObject["subtype"] = 2


with open (filepath, 'w') as json_file:
    json.dump(data, json_file, indent=4)