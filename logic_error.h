#ifndef H_logic_error
#define H_logic_error

#include <stdexcept>
#include <iostream>

class logic_error : public runtime_error{

public:
      logic_error(const string& msg) : runtime_error(msg){}
      
      
};


#endif
