#GROUP: We probably don't have a name
#MEMBERS: Adam Davis, Tim Fox
#CS 4/55231 INTERNETENGINEERING 2012 SPRING
#INSTRUCTOR: Javed Khan

import re
import socket
from threadpool import *



def HttpGet(connectionInfo):
    connectionSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connectionSocket.connect((connectionInfo['host'], 80))
    print 'yup'
    httpGetRequest = 'GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP Client\r\n\r\n' % (connectionInfo['target'])

    bytesSent = connectionSocket.send(httpGetRequest)
    newFile = open(connectionInfo['fileName'], 'w')

    while True:
        data = connectionSocket.recv(512)
        if not data:
            break
        newFile.write(data)
    newFile.close() 
	
	
def parse_url(url):
	filename =''
	target = ''
	protocol = 'http'
	if len(url.split('://')) > 1:
		url =  url.split('://')
		protocol =  url[0]
		url = url[1]


	if url.split('/'):
		url = url.split('/')
		if len(url) > 1:
			host = url[0]
			index = 1
			while index < len(url):
				target += '/'+ url[index]
		
				if index == (len(url) -1):
					fileName = url[index]

				index = index + 1
		else:
			host = url[0]
			target = '/'
			fileName = 'index.html'
	connectionInfo = {'host' : host, 'target' : target, 'fileName' : fileName, 'protocol' : protocol}
	return connectionInfo

target = ''
host = ''
hostIp = ''
target = ''
fileName = ''
defaultPort = 80
port = 0

threadPool = ThreadPool(20)
connectionSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

url = raw_input("enter a url \n")
connectionInfo = parse_url(url)


port = defaultPort

splitHost = connectionInfo['host'].split('@')
if len(splitHost) > 1:
	print splitHost

splitHost = connectionInfo['host'].split(':')

if len(splitHost) > 1:
	connectionInfo['host'] = splitHost[0]
	port = int(splitHost[1])


host = connectionInfo['host']

hostIp = socket.gethostbyname(connectionInfo['host'])
print ":::Connection Information:::\n\
	Host: %s (IP: %s) \n\
	Target: %s\n\
	Port:	%s\n\
	Protocol: %s\n" % ( connectionInfo['host'],hostIp, connectionInfo['target'], port, connectionInfo['protocol'])
	  
#build HTTP GET request
httpGetRequest = 'GET %s HTTP/1.0\r\nHost: www.lol.biz\r\nUser-Agent: My HTTP Client\r\n\r\n' % (connectionInfo['target'])
print ":::Message Sent:::\n %s" % (httpGetRequest)

#connecting to targetHost and recieving file
connectionSocket.connect((connectionInfo['host'], port))
bytesSent = connectionSocket.send(httpGetRequest)

data = ''
data = connectionSocket.recv(1024)
html = ''
while data != '':
	html += data
	data = connectionSocket.recv(1024)
#saving copy of file....
newFile = open(connectionInfo['fileName'], 'w')
newFile.write(html)
newFile.close()

#Searching out target file for img tags...
imgUrls = re.findall('img.*?src="(.*?)"', html)

connectionSocket.close()

for url in imgUrls:
	connectionInfo = parse_url(url)
	if connectionInfo['host'] is "":
		connectionInfo['host'] = host

	#new socket for retrieving img srcs


	HttpGet(connectionInfo)
	
threadPool.wait_for_finish()

