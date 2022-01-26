from flask import Flask, render_template
from pymongo import MongoClient

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/deletelocationhistory.html")
def deletehistory():
    mongo_client = MongoClient('localhost', 27017)

    db = mongo_client.GPSDB
    
    if 'location_history' in db.list_collection_names():
        db.drop_collection('location_history')
        return "Location history has been deleted."
    else:
        return "Location history is empty."
    

@app.route("/locationhistory.html")
def locationhistory():
    mongo_client = MongoClient('localhost', 27017)

    db = mongo_client.GPSDB
    
    latarr = []
    lngarr = []
        
    for record in db.get_collection('location_history').find({}, {'_id' : 0 , 'LAT' : 1, 'LNG' : 1}):
        lat,lng = list(record.values())
        latarr.append(float(lat))
        lngarr.append(float(lng))
        
    if 'location_history' in db.list_collection_names():
        return render_template("locationhistory.html", latarr=latarr, lngarr=lngarr)
    else:
        return "Location history is empty"

@app.route("/lastlocation.html")
def lastlocation():
    mongo_client = MongoClient('localhost', 27017)

    db = mongo_client.GPSDB
    
    lastcoords = []
        
    for record in db.get_collection('location_history').find({}, {'_id' : 0 , 'LAT' : 1, 'LNG' : 1}):
        lastlat,lastlng = list(record.values())
        lastcoords = [float(lastlat), float(lastlng)]
        
        
    if 'location_history' in db.list_collection_names():
        return render_template("lastlocation.html", lastcoords=lastcoords)
    else:
        return "Last location is unavailable"
                
