import json

filepath = 'Saves/Slot1/mountainCaveEntrance.json'
with open(filepath, 'r') as json_file:
    data = json.load(json_file)
    for gameObject in data["sprites"]:
        # print(gameObject)
        x = gameObject["posX"]
        y = gameObject["posY"]
        # print(x,y)
        # print(x//10, y//10)
        if ((x % 100) > 50):
            # round up
            x = (100 * (x // 100)) + 100
        else:
            # round down
            x = (100 * (x // 100))
        if ((y % 100) > 50):
            # round up
            y = (100 * (y // 100)) + 100
        else:
            # round down
            y = (100 * (y // 100))
        gameObject["posX"] = x
        gameObject["posY"] = y
        # print(x, y)
with open(filepath, 'w') as json_file:
    json.dump(data, json_file, indent=4)

#     data = json.load(json_file)
#     for gameObject in data["sprites"]:
#         gameObject["subtype"] = 2
#
#
# with open (filepath, 'w') as json_file:
#     json.dump(data, json_file, indent=4)