import urllib.request
import json

def download_file():
    # firebase download url for data.csv
    url = "https://firebasestorage.googleapis.com/v0/b/frc-inventory-tracker.appspot.com/o/frcData%2FfrcTestData.csv?alt=media&token=13402e13-64fe-4c04-8e21-8d6e5b5476d3"

    try:
        loader = urllib.request.urlretrieve(url, "data/frcTestData.csv")

    except urllib.error.URLError as e:
        message = json.loads(e.read())
        print(message["error"]["message"])
    
    else:
        print(loader)

download_file()