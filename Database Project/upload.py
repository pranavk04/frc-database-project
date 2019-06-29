import urllib.request
import json

# uploads the newest version of the file (after all changes are made) to the firebase storage. 
def upload_file():
    # opens the file and reads it into bytes so that it can be uploaded to firebase. 
    file = open("data/frcTestData.csv", "rb")
    data = file.read()
    url ="https://firebasestorage.googleapis.com/v0/b/frc-inventory-tracker.appspot.com/o/frcData%2FfrcTestData.csv"
    headers = {"Content-Type": "text/plain"}

    # actual request
    request = urllib.request.Request(url, data=data, headers=headers, method="POST")

    try:
        loader = urllib.request.urlopen(request)
        print("request sent")
   
    except urllib.error.URLError as e:
        message = json.loads(e.read())
        print(message["error"]["message"])
   
    else:
        print(loader.read())

upload_file()