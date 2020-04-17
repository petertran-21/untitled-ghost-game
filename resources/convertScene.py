import json

filepath = 'beachRoom6.json'
with open(filepath) as json_file:
    data = json.load(json_file)
    for gameObject in data["sprites"]:
        gameObject["subtype"] = 2

    json.dump(data, json_file)