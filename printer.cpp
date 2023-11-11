//
// Created by Yurii Bondarenko on 11/11/23.
//

#include <iostream>

namespace cpp::print {

	namespace {
		int line_number = 1;
	}

	template<typename P>

	void print_v(P arg) {
		std::cout << line_number++ << " > " << arg << std::endl;
	}
}
