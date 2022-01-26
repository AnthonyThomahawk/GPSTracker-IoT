from http.server import BaseHTTPRequestHandler, HTTPServer
import cgitb;
import cgi
import os
from pymongo import MongoClient

def insert_coords(LAT, LNG):
    
    col = db.location_history
    
    LDICT = {
    "LAT" : str(LAT),
    "LNG" : str(LNG)
    }
    
    x = col.insert_one(LDICT)

    print("Inserted with ID " + str(x.inserted_id))

class handler(BaseHTTPRequestHandler):
    def do_GET(self):
       try:
        self.send_response(200)
        self.send_header('Content-type','text/plain')
        self.end_headers()
        
        print('Received :')
        
        x = self.path.split("/LAT=")
        z = x[1]
        coords = z.split("LNG=")
        print(coords)
        
        print("LAT = " + coords[0] + " LNG = " + coords[1])
        
        insert_coords(coords[0],coords[1])
        
       except Exception as e:
           print(e)
        


mongo_client = MongoClient('localhost', 27017)

db = mongo_client.GPSDB

server = HTTPServer(('', 8000), handler)
print('bash http server started')
server.serve_forever()
