import StringIO

class HttpResponse(object):
    
    
    
    def __init__(self, contents):
        self.serverResponse = contents
        self.header = {}
        self.getHeader()
        
        
    def getHeader(self):

            if self.serverResponse[0:4] == "HTTP":
                buf = StringIO.StringIO(self.serverResponse)
                
                while buf.readline():
                    headerLine = buf.readline().split(':')
                    try:
                         self.header[headerLine[0]] = headerLine[1]
                    except:
                        break
                        
                