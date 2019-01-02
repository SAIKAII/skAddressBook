#ifndef ADDRESSBOOK_UTIL_BASE64_TOOL_H_
#define ADDRESSBOOK_UTIL_BASE64_TOOL_H_

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

bool base64_encode(const std::string &input, std::string *output){
  typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::\
  transform_width<std::string::const_iterator, 6, 8>> base64_encode_iterator;
  std::stringstream result;
  std::copy(base64_encode_iterator(input.begin()), base64_encode_iterator(input.end()),
            std::ostream_iterator<char>(result));
  size_t equal_count = (3 - input.length() % 3) % 3;
  for(size_t i = 0; i < equal_count; ++i)
    result.put('=');
  *output = result.str();
  return output->empty() == false;
}

bool base64_decode(const std::string &input, std::string *output){
  typedef boost::archive::iterators::transform_width<boost::archive::iterators::\
  binary_from_base64<std::string::const_iterator>, 8, 6> base64_decode_iterator;
  std::stringstream result;
  try{
    std::copy(base64_decode_iterator(input.begin()), base64_decode_iterator(input.end()),
              std::ostream_iterator<char>(result));
  }catch(...){
    return false;
  }
  *output = result.str();
  return output->empty() == false;
}

#endif
