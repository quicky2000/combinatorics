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

#include "symbol.h"
#include <iostream>
#include <cassert>

namespace combinatorics
{
    //------------------------------------------------------------------------------
    void enumerate(void)
    {
      symbol l_symbol_table[3] = {symbol(1,1),symbol(2,2),symbol(3,3)};
      unsigned int l_nb_symbol = 3;
      unsigned int l_word_size = 6;
      unsigned int * l_word = new unsigned int[l_word_size];
      for(unsigned int l_index = 0 ; l_index < l_word_size ; ++l_index)
	{
	  l_word[l_index] = 0;
	}
      unsigned int l_index = 0;
      unsigned int l_count = 0;
      bool l_end = false;
      while(!l_end)
	{
	  if(0 == l_word[l_index])
	    {
	      unsigned int l_symbol_index = 0;
	      while(0 == l_symbol_table[l_symbol_index].get_number())
		{
		  ++l_symbol_index;
		}
	      l_word[l_index] = l_symbol_table[l_symbol_index].get_index();
	      l_symbol_table[l_symbol_index].decr();
	      ++l_index;
	    }

	  if(l_word_size == l_index)
	    {
	      std::cout << l_count << "\t" ;
	      for(unsigned int l_display_index = 0 ; l_display_index < l_word_size; ++l_display_index)
		{
		  std::cout << (char)('A' - 1 + l_word[l_display_index]);
		}
	      std::cout << std::endl ;
	      ++l_count;
	      l_index = l_word_size - 1;
	      //	  l_symbol_table[l_word[l_index] - 1].incr();
	      //	  l_word[l_index] = 0;
	      //	  l_index = 4;
	      bool l_reverse_end = false;
	      while(!l_reverse_end)
		{
		  if(l_nb_symbol == l_word[l_index])
		    {
		      l_symbol_table[l_word[l_index] - 1].incr();
		      l_word[l_index] = 0;
		      if(l_index)
			{
			  --l_index;
			}
		      else
			{
			  l_end = true;
			  l_reverse_end = true;
			}
		    }
		  else
		    {
		      unsigned int l_old = l_word[l_index];
		      l_symbol_table[l_old - 1].incr();
		      l_word[l_index] = 0;
		      for(unsigned int l_candidate = l_old + 1; l_candidate <= l_nb_symbol && ! l_reverse_end; ++ l_candidate)
			{
			  if(l_symbol_table[l_candidate - 1].get_number())
			    {
			      l_word[l_index] = l_candidate;
			      l_symbol_table[l_candidate - 1].decr();
			      ++l_index;
			      l_reverse_end = true;
			    }
			}
		      if(!l_reverse_end)
			{
			  --l_index;
			}
		    }
		}
	    }
	}
      delete[] l_word;
    }
}
#endif // _ENUMERATION_H_
//EOF
