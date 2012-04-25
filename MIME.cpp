#include "MIME.h"

namespace Server 
{
  MIME::MIME(std::string uri)
  {
    std::string extension = uri.substr(uri.find_last_of('.')+1);
    
    if(extension == "gif")
      mType = "image/gif";
    else if(extension == "html" || extension == "py")
      mType = "text/html";
    else if(extension == "jpg" || extension == "jpeg")
      mType = "image/jpeg";
    else if (extension == "png")
      mType = "image/png";
  }
}