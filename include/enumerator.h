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
#include <cstring>

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
       Set word
       @param pointer on word
       @param word size. it should be less or equal than enumerator word size
     */
    inline void set_word(const unsigned int * const p_word,
			 unsigned int p_word_size
			 );

    /**
       get word
       @param pointer on word
       @param word size. it should be less or equal than enumerator word size
     */
    inline void get_word(unsigned int * const p_word,
			 unsigned int p_word_size
			 ) const;

    /**
       Method to indicate that first part of the word is invalid so that
       enumerator avoid to generate more word with this root
       @param number of items composing root
     */
    inline void invalidate_root(unsigned int p_nb_items);

    /**
       Destructor
     */
    inline ~enumerator(void);

    /**
       Method to compare external word with current word assuming they have the
       same size
       @param pointer on external word
    */
    inline int compare_word(unsigned int * p_word);

    /**
       Method to know the word size in case it was not specified
       @return word size
    **/
    inline unsigned int get_word_size(void) const;
  private:
    /**
       Remove value from index of word, increment corresponding number and
       return the value that was stored at index
       @param index in the word
       @return value that was stored at index
     */
    inline unsigned int release(unsigned int p_index);

    /**
       Set value at index of word, decrement corresponding number
       @param index in the word
       @param value to store at index
     */
    inline void take(unsigned int p_index,
		     unsigned int p_value
		     );

    /**
       Method to go back and prepare next iteration
       @return return true if go_back could not prepare a new iteration
     */
    inline bool go_back(void);

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
  unsigned int enumerator::get_word_size(void) const
  {
    return m_word_size;
  }

  //----------------------------------------------------------------------------
  int enumerator::compare_word(unsigned int * p_word)
  {
    assert(p_word);
    return memcmp(m_word, p_word, m_word_size*sizeof(unsigned int));
  }


  //----------------------------------------------------------------------------
  unsigned int enumerator::release(unsigned int p_index)
  {
    assert(p_index < m_word_size);
    assert(m_word[p_index]);
    unsigned int l_old = m_word[p_index];
    m_symbol_table[l_old - 1].incr();
    m_word[p_index] = 0;
    return l_old;
  }

  //----------------------------------------------------------------------------
  void enumerator::take(unsigned int p_index,
			unsigned int p_value
			)
  {
    m_word[p_index] = p_value;
    m_symbol_table[p_value - 1].decr();
  }

  //----------------------------------------------------------------------------
  bool enumerator::go_back(void)
  {
    bool l_generation_end = false;
    bool l_reverse_end = false;
    while(!l_reverse_end)
      {
	// In case item already reached end of symbol list reinit it and go to previous index
	if(m_symbol_table.size() == m_word[m_index])
	  {
	    release(m_index);
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
	    unsigned int l_old = release(m_index);
	    for(unsigned int l_candidate = l_old + 1;
		l_candidate <= m_symbol_table.size() && ! l_reverse_end;
		++ l_candidate
		)
	      {
		// if a symbol is available then choose it
		if(m_symbol_table[l_candidate - 1].get_number())
		  {
		    take(m_index, l_candidate);
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
    return l_generation_end;
  }

  //----------------------------------------------------------------------------
  void enumerator::set_word(const unsigned int * const p_word,
			    unsigned int p_word_size
			    )
  {
    assert(p_word_size <= m_word_size);

    // Set continu to true to be able to call generate
    m_continu = true;

    // Copy word
    for(m_index = 0;
	m_index < p_word_size;
	++m_index
	)
      {
	take(m_index,p_word[m_index]);
      }
    // Initialise remaining part of word
    for(unsigned int l_index = m_index;
	l_index < m_word_size;
	++l_index
	)
      {
	if(m_word[m_index])
	  {
	    release(m_index);
	  }
      }
  }

  //----------------------------------------------------------------------------
  void enumerator::get_word(unsigned int * const p_word,
			    unsigned int p_word_size
			    ) const
  {
    assert(p_word_size <= m_word_size);
    memcpy(p_word, m_word, p_word_size * sizeof(unsigned int));
  }

  //----------------------------------------------------------------------------
  void enumerator::invalidate_root(unsigned int p_nb_items)
  {
    assert(p_nb_items);
    assert(p_nb_items <= m_word_size);
    for(unsigned int l_index = p_nb_items;
	l_index < m_word_size;
	++l_index)
      {
	release(l_index);
      }
    m_index = p_nb_items - 1;
    go_back();
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
		// Go back along word to prepare next iteration
		m_index = m_word_size - 1;
		l_generation_end = go_back();
	      }
	    // Iterate along empty part of word and fill it with available symbols
	    if(m_index < m_word_size && 0 == m_word[m_index])
	      {
		unsigned int l_symbol_index = 0;
		while(0 == m_symbol_table[l_symbol_index].get_number())
		  {
		    ++l_symbol_index;
		  }
		take(m_index,m_symbol_table[l_symbol_index].get_index());
		++m_index;
	      }
	    m_count += m_index == m_word_size;
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
