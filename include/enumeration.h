/*    This file is part of combinatorics
      Copyright (C) 2017  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef _ENUMERATION_H_
#define _ENUMERATION_H_

#include "enumerator.h"
#include <iostream>
#include <cassert>
#include <vector>

namespace combinatorics
{

  /**
     Method designed to enumerate all possible combinations of a list of symbols
     @param p_symbols List of symbols
     @param p_word_size size of word to be generated. It must not be greater
     than total number of symbols
  */
  void enumerate(const std::vector<symbol> & p_symbols, unsigned int p_word_size = 0)
  {
    enumerator l_enumerator(p_symbols,p_word_size);
    while(l_enumerator.generate())
      {
	l_enumerator.display_word();
      }
  }
}
#endif // _ENUMERATION_H_
//EOF
