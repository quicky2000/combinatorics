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

#ifndef _ENUMERATOR_H_
#define _ENUMERATOR_H_

#include "quicky_exception.h"
#include "symbol.h"
#include <iostream>
#include <cassert>
#include <vector>

namespace combinatorics
{

  /**
     Class designed to enumerate all possible combinations of a list of symbols
   */
  class enumerator
  {
  public:
  /**
     Enumerator constructor
     @param p_symbols List of symbols
     @param p_word_size size of word to be generated. It must not be greater
     than total number of symbols
  */
    inline enumerator(const std::vector<symbol> & p_symbols,
		      unsigned int p_word_size = 0
		      );
    /**
       Method generating a new combination of symbols
       @return true if there are some other combinations
     */
    inline bool generate(void);

    /**
       Method returning the index of current combination: 0 for the first
       @return index of current combination
    */
    inline unsigned int get_count(void)const;

    /**
       Display word content
     */
    inline void display_word(void)const;

    /**
       Destructor
     */
    inline ~enumerator(void);
  private:
    std::vector<symbol> m_symbol_table;
    unsigned int * m_word;
    unsigned int m_total_nb_symbol;
    unsigned int m_word_size;
    unsigned int m_index;
    unsigned int m_count;
    bool m_continu;
  };

  //----------------------------------------------------------------------------
  enumerator::enumerator(const std::vector<symbol> & p_symbols,
			 unsigned int p_word_size
			 ):
    m_symbol_table(p_symbols),
    m_word(nullptr),
    m_total_nb_symbol(0),
    m_word_size(p_word_size),
    m_index(0),
    m_count(0),
    m_continu(true)
    {
      // Computing total number of symbols      
      for(unsigned int l_index = 0; l_index < m_symbol_table.size(); ++l_index)
	{
	  m_total_nb_symbol += m_symbol_table[l_index].get_number();
	}
      // Computing word size
      m_word_size = p_word_size ? p_word_size : m_total_nb_symbol;
      if(m_word_size > m_total_nb_symbol)
	{
	  throw quicky_exception::quicky_runtime_exception("Word size is greater than total number of symbols",__LINE__,__FILE__);
	}

      // Initialise word
      m_word = new unsigned int[m_word_size];
      for(unsigned int l_index = 0 ; l_index < m_word_size ; ++l_index)
	{
	  m_word[l_index] = 0;
	}
    }

  //----------------------------------------------------------------------------
  bool enumerator::generate(void)
  {
    if(m_continu)
      {
	bool l_generation_end = false;
	while(!l_generation_end)
	  {
	    // Check if end of word is reached
	    if(m_word_size == m_index)
	      {
		++m_count;
		// Go back along word to prepare next iteration
		m_index = m_word_size - 1;
		bool l_reverse_end = false;
		while(!l_reverse_end)
		  {
		    // In case item already reached end of symbol list reinit it and go to previous index
		    if(m_symbol_table.size() == m_word[m_index])
		      {
			m_symbol_table[m_word[m_index] - 1].incr();
			m_word[m_index] = 0;
			if(m_index)
			  {
			    --m_index;
			  }
			else
			  {
			    m_continu = false;
			    l_generation_end = true;
			    l_reverse_end = true;
			  }
		      }
		    else
		      {
			// Go to next value for current item
			unsigned int l_old = m_word[m_index];
			m_symbol_table[l_old - 1].incr();
			m_word[m_index] = 0;
			for(unsigned int l_candidate = l_old + 1;
			    l_candidate <= m_symbol_table.size() && ! l_reverse_end;
			    ++ l_candidate
			    )
			  {
			    // if a symbol is available then choose it
			    if(m_symbol_table[l_candidate - 1].get_number())
			      {
				m_word[m_index] = l_candidate;
				m_symbol_table[l_candidate - 1].decr();
				++m_index;
				l_reverse_end = true;
			      }
			  }
			// If no new value availabe then continue to go back
			if(!l_reverse_end)
			  {
			    --m_index;
			  }
		      }
		  }
	      }
	    // Iterate along empty part of word and fill it with available symbols
	    if(m_index < m_word_size && 0 == m_word[m_index])
	      {
		unsigned int l_symbol_index = 0;
		while(0 == m_symbol_table[l_symbol_index].get_number())
		  {
		    ++l_symbol_index;
		  }
		m_word[m_index] = m_symbol_table[l_symbol_index].get_index();
		m_symbol_table[l_symbol_index].decr();
		++m_index;
	      }
	    l_generation_end |= m_index == m_word_size;
	  }
      }
    return m_continu;
  }

  //----------------------------------------------------------------------------
  unsigned int enumerator::get_count(void)const
  {
    return m_count;
  }

  //----------------------------------------------------------------------------
  void enumerator::display_word(void)const
  {
    // DIsplay word
    std::cout << m_count << "\t" ;
    for(unsigned int l_display_index = 0 ;
	l_display_index < m_word_size;
	++l_display_index
	)
      {
	std::cout << (char)('A' - 1 + m_word[l_display_index]);
      }
    std::cout << std::endl ;
  }

  //----------------------------------------------------------------------------
  enumerator::~enumerator(void)
  {
    delete[] m_word;
  }
}
#endif // _ENUMERATOR_H_
//EOF
