from threads import *
import HttpResponse
import socket

class HttpGet(object):
    def __init__(self, connectionInfo):
        self.connectionInfo = connectionInfo
        self.requestText = ''

    def sendRequest(self):
        self.connectionSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connectionSocket.connect((self.connectionInfo['host'], 80))

        self.requestText = 'GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP Client\r\n\r\n' % (self.connectionInfo['target'])
        
        bytesSent = self.connectionSocket.send(self.requestText)
        newFile = open(self.connectionInfo['fileName'], 'w')
        htmlString = ""
        while True:
            data = self.connectionSocket.recv(512)
            if not data:
                break
            htmlString += data
           
        
        
        newFile.write(htmlString)
        newFile.close() 
        return htmlString
    
class HttpPost:
    
    def __init__(self, connectionInfo):
        self.connectionInfo = connectionInfo