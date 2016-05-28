#ifndef STRING_HELPERS_INCLUDED_CC0C05E9_7D4D_4A69_B002_6E59BDC031B9
#define STRING_HELPERS_INCLUDED_CC0C05E9_7D4D_4A69_B002_6E59BDC031B9


#include <string>
#include <regex>
#include <iterator>
#include <string.h>
#include <stddef.h>
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


// Stip out the filepath and return the filename
inline std::string
get_filename_from_path(const std::string &filepath)
{
  auto loc = filepath.find_last_of("/");
  
  if(loc != std::string::npos)
  {
    return filepath.substr(loc + 1, filepath.size() - loc);
  }
  
  return ""; // Found no seperator}
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


#ifdef _WIN32

/*	$OpenBSD: strlcpy.c,v 1.11 2006/05/05 15:27:38 millert Exp $	*/

/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
inline size_t
strlcpy(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0) {
		while (--n != 0) {
			if ((*d++ = *s++) == '\0')
				break;
		}
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}
#endif


#endif // include guard
