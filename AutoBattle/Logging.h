#pragma once

#include <iostream>

#define LOG_DESTRUCTOR(Message) std::cout << "||| Destroying " << Message << " |||" << std::endl;  
