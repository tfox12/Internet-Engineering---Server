#GROUP: We probably don't have a name
#MEMBERS: Adam Davis, Tim Fox
#CS 4/55231 INTERNETENGINEERING 2012 SPRING
#INSTRUCTOR: Javed Khan
from UrlTools import parse_url
import re
import socket
from threads.threadpool import *
from HttpLib.HttpRequest import HttpGet, HttpPost
from HttpLib.HttpResponse import *

	
	


target = ''
host = ''
hostIp = ''
target = ''
fileName = ''
defaultPort = 80
port = 0

def fetchPage(url):
    threadPool = ThreadPool(20)
    connectionInfo = parse_url(url)
    
    
    port = defaultPort
    splitHost = connectionInfo['host'].split('@')
    splitHost = connectionInfo['host'].split(':')
    
    if len(splitHost) > 1:
    	connectionInfo['host'] = splitHost[0]
    	port = int(splitHost[1])
    
    

    
    hostIp = socket.gethostbyname(connectionInfo['host'])
    print ":::Connection Information:::\n\
    	Host: %s (IP: %s) \n\
    	Target: %s\n\
    	Port:	%s\n\
    	Protocol: %s\n" % ( connectionInfo['host'],hostIp, connectionInfo['target'], port, connectionInfo['protocol'])
        
    httpGet = HttpGet(connectionInfo)
    print ":::Message Sent:::\n %s" % (httpGet.requestText)
    
    #connecting to targetHost and recieving file
    try:
        httpResponse = HttpResponse(httpGet.sendRequest())
    except Exception, e:
        print e.message
    
    #Searching out target file for img tags...
    imgUrls = re.findall('img.*?src="(.*?)"', httpResponse.serverResponse)
    if len(imgUrls) == 0:
        imgUrls = re.findall('IMG.*?SRC="(.*?)"', httpResponse.serverResponse)

    
    for url in imgUrls:
    	connectionInfo = parse_url(url)
    	if connectionInfo['host'] is "":
    		connectionInfo['host'] = host
    
    	threadPool.add_task(HttpGet(connectionInfo).sendRequest(), )
    	
    threadPool.wait_for_finish()

    return httpResponse.serverResponse

