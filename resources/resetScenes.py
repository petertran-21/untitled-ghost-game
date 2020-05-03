import json, os
import glob

basePath = "~/Users/bradleybk/untitled-ghost-game/resources"
NewPaths = glob.glob(basePath+"/Saves/Slot1/*.json")
OGPaths =  glob.glob(basePath+"/scenes/*.json")

#remove paths from Saves/Slot1
for path in NewPaths:
    os.remove(path)

for path in OGPaths:
    with open(path, 'r') as json_file:
        data = json.load(json_file)
        for gameObject in data["sprites"]:
            if gameObject["id"] == "SceneTrigger":
                scene_path = gameObject["scene_path"]
                scenePathList = scene_path.split('/')
                fileName = scenePathList[len(scenePathList)-1]
                gameObject["scene_path"] = "./resources/Saves/Slot1/"+fileName

    # write to saves/slot1
    pathList = path.split('/')
    newpath = os.getcwd()+"/Saves/Slot1/"+pathList[len(pathList)-1]
    with open(newpath, 'w') as json_file:
        json.dump(data, json_file, indent=4)






#     data = json.load(json_file)
#     for gameObject in data["sprites"]:
#         gameObject["subtype"] = 2
#
#
# with open (filepath, 'w') as json_file:
#     json.dump(data, json_file, indent=4)