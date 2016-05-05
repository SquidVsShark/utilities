#ifndef STRING_HELPERS_INCLUDED_CC0C05E9_7D4D_4A69_B002_6E59BDC031B9
#define STRING_HELPERS_INCLUDED_CC0C05E9_7D4D_4A69_B002_6E59BDC031B9


#include <string>
#include <regex>
#include <iterator>
#include "file_helpers.hpp"


namespace util {


// Strip out the filename in a path.
inline std::string
get_dir_from_filepath(const std::string &filepath)
{
  auto loc = filepath.find_last_of("/");
  
  if(loc != std::string::npos)
  {
    return filepath.substr(0, loc + 1);
  }
  
  return ""; // Found no seperator
}


/*
  This will search a string for and #include "file" declerations
  and then search for those files from the given directories to search.
  If found it will insert the contents into the string. If it cannout be found
  it will be replaced with an empty string.
  It will not deal with subincludes.
*/
inline std::string
hash_include_string(const std::string &string_to_search, const std::vector<std::string> &dirs_to_search)
{
  std::string result = string_to_search;

  // Search for #include
  const std::regex re("[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*?");
  const auto begin_it = std::sregex_iterator(string_to_search.begin(), string_to_search.end(), re);
  const auto end_it   = std::sregex_iterator();

  for(auto it = begin_it; it != end_it; ++it)
  {
    const std::string include  = (*it)[0].str();
    const std::string filename = (*it)[1].str();

    // Search for file in given directories.
    for(const auto &dir : dirs_to_search)
    {
      const std::string contents  = file::get_contents_from_file(dir + filename);
      const std::size_t find      = result.find(include);

      if(find != std::string::npos)
      {
        result.erase(find, include.length());
        result.insert(find, contents);
      }
    }
  }

  return result;
}


} // ns


#endif // include guard
