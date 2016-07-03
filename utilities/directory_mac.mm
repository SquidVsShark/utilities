#ifdef __APPLE__

#include "directory.hpp"
#import <dirent.h>
#import <Foundation/Foundation.h>


namespace util {


namespace dir {


const char *
resource_path()
{
  static char buffer_path[2048] = "\0";
  
  if(strcmp(buffer_path, "") == 0)
  {
    NSBundle *bundle = [NSBundle mainBundle];
    
    if(bundle == nil)
    {
      return "";
    }
    else
    {
      NSString *r_path = [bundle resourcePath];
      
      strcat(buffer_path, [r_path UTF8String]);
      strcat(buffer_path, "/");
    }
  }
  
  return buffer_path;
}


} // ns
} // ns


#endif