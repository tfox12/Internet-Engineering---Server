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