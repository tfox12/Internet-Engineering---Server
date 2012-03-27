from threadpool import *
import socket

class HttpGet:
    def __init__(self, connectionInfo):
        self.connectionInfo = connectionInfo
        self.requestText = ''

    def sendRequest(self):
        self.connectionInfo = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connectionInfo.connect((self.connectionInfo['host'], 80))
        print 'yup'
        self.requestText = 'GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP Client\r\n\r\n' % (self.connectionInfo['target'])
        
        bytesSent = self.connectionInfo.send(self.requestText)
        newFile = open(self.connectionInfo['fileName'], 'w')
        htmlString = ""
        while True:
            data = self.connectionInfo.recv(512)
            if not data:
                break
            
            htmlString = data
           
        
        
        newFile.write(htmlString)
        newFile.close() 
        return htmlString
    
