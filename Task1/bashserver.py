from http.server import BaseHTTPRequestHandler, HTTPServer
import cgitb;
import cgi
import os

class handler(BaseHTTPRequestHandler):
    def do_POST(self): #overload function of HTTPserver to execute bash commands on receiving a proper request
       try: # try - catch block in case someone sends an invalid POST request
        self.send_response(200)
        self.send_header('Content-type','text/html')
        self.end_headers() # form response to the client

        form = cgi.FieldStorage(
        fp=self.rfile,
        headers=self.headers,
        environ={'REQUEST_METHOD': 'POST'}
        ) # extract all fields from the post request

        command = form.getvalue("command") # get data of field "command"
        print('Command received : ' + command);
        os.system(str(command)) # execute the bash command on the system
       except:
        print('Incorrect format for post request')

server = HTTPServer(('', 8000), handler)
print('bash http server started')
server.serve_forever()


