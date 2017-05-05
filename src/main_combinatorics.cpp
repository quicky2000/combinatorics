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

#ifdef COMBINATORICS_SELF_TEST
#include "quicky_exception.h"
#include "enumeration.h"
#include "formula.h"
#include "meta_fact.h"
#include "meta_partial_fact.h"
#include "meta_A.h"
#include "meta_C.h"
#include "meta_max.h"
#include "meta_min.h"
#include <iostream>

int main(int argc,char ** argv)
{
  try
    {
      std::vector<combinatorics::symbol> l_symbols = {combinatorics::symbol(1,1),combinatorics::symbol(2,2),combinatorics::symbol(3,3)};
      combinatorics::enumerate(l_symbols);
      std::cout << "-------------------------------" << std::endl ;
      std::cout << combinatorics::min<1,2>::m_value << std::endl ;
      std::cout << combinatorics::min<2,1>::m_value << std::endl ;
      std::cout << combinatorics::max<1,2>::m_value << std::endl ;
      std::cout << combinatorics::max<2,1>::m_value << std::endl ;
      std::cout << combinatorics::fact<combinatorics::max<1,3>::m_value>::m_value << std::endl ;
      std::cout << combinatorics::max<combinatorics::fact<2>::m_value,combinatorics::fact<3>::m_value>::m_value << std::endl ;
      std::cout << "-------------------------------" << std::endl ;
      std::cout << combinatorics::fact<1>::m_value << std::endl;
      std::cout << combinatorics::fact<2>::m_value << std::endl;
      std::cout << combinatorics::fact<3>::m_value << std::endl;
      std::cout << combinatorics::fact<4>::m_value << std::endl;
      std::cout << combinatorics::formula::fact(1) << std::endl;
      std::cout << combinatorics::formula::fact(2) << std::endl;
      std::cout << combinatorics::formula::fact(3) << std::endl;
      std::cout << combinatorics::formula::fact(4) << std::endl;
      std::cout << combinatorics::partial_fact<5,3>::m_value << std::endl;
      std::cout << "-------------------------------" << std::endl ;
      std::cout << combinatorics::formula::partial_fact(3,3) << std::endl;
      std::cout << combinatorics::formula::partial_fact(3,2) << std::endl;
      std::cout << combinatorics::formula::partial_fact(4,2) << std::endl;
      std::cout << combinatorics::formula::partial_fact(4,3) << std::endl;
      std::cout << combinatorics::formula::partial_fact(5,4) << std::endl;
      std::cout << combinatorics::formula::partial_fact(5,3) << std::endl;
      std::cout << combinatorics::fact<combinatorics::partial_fact<3,2>::m_value>::m_value << std::endl;
      std::cout << "-------------------------------" << std::endl ;
      std::cout << combinatorics::max<combinatorics::formula::C(6,1),combinatorics::C<6,1>::m_value>::m_value << std::endl;
      std::cout << combinatorics::formula::C(6,1) << "\t" << combinatorics::C<6,1>::m_value << std::endl;
      std::cout << combinatorics::formula::C(6,2) << "\t" << combinatorics::C<6,2>::m_value <<  std::endl;
      std::cout << combinatorics::formula::C(6,3) << "\t" << combinatorics::C<6,3>::m_value <<  std::endl;
      std::cout << combinatorics::formula::C(6,4) << "\t" << combinatorics::C<6,4>::m_value <<  std::endl;
      std::cout << combinatorics::formula::C(6,5) << "\t" << combinatorics::C<6,5>::m_value <<  std::endl;
      std::cout << combinatorics::formula::C(6,6) << "\t" << combinatorics::C<6,6>::m_value <<  std::endl;
      std::cout << "-------------------------------" << std::endl ;
      std::cout << combinatorics::max<combinatorics::formula::A(6,1),combinatorics::A<6,1>::m_value>::m_value << std::endl;
      std::cout << combinatorics::formula::A(6,1) << "\t" << combinatorics::A<6,1>::m_value << std::endl;
      std::cout << combinatorics::formula::A(6,2) << "\t" << combinatorics::A<6,2>::m_value <<  std::endl;
      std::cout << combinatorics::formula::A(6,3) << "\t" << combinatorics::A<6,3>::m_value <<  std::endl;
      std::cout << combinatorics::formula::A(6,4) << "\t" << combinatorics::A<6,4>::m_value <<  std::endl;
      std::cout << combinatorics::formula::A(6,5) << "\t" << combinatorics::A<6,5>::m_value <<  std::endl;
      std::cout << combinatorics::formula::A(6,6) << "\t" << combinatorics::A<6,6>::m_value <<  std::endl;


      // Detect rotations by considering a size 8 word as a square with border of size 2
      std::vector<combinatorics::symbol> l_symbols2 =
	{
	  combinatorics::symbol(1,1),
	  combinatorics::symbol(2,1),
	  combinatorics::symbol(3,1),
	  combinatorics::symbol(4,1),
	  combinatorics::symbol(5,1),
	  combinatorics::symbol(6,1),
	  combinatorics::symbol(7,1),
	  combinatorics::symbol(8,1),
	};
      combinatorics::enumerator l_enumerator(l_symbols2);
      unsigned int l_reference_word[8];
      unsigned int l_reference_word2[8];
      unsigned int l_reference_word3[8];
      unsigned int l_tmp_word[8];
      bool l_ok = l_enumerator.generate();
      if(!l_ok)
	{
	  throw quicky_exception::quicky_logic_exception("Unable to generate first word", __LINE__, __FILE__);
	}
      l_enumerator.display_word();
      l_enumerator.get_word(l_tmp_word,8);
      for(unsigned int l_index = 0;
	  l_index < 8;
	  ++l_index
	  )
	{
	  l_reference_word[l_index] = l_tmp_word[(l_index + 2) % 8];
	  l_reference_word2[l_index] = l_tmp_word[(l_index + 4) % 8];
	  l_reference_word3[l_index] = l_tmp_word[(l_index + 6) % 8];
	}

      while(l_enumerator.generate())
      {
	l_enumerator.display_word();
	if(!l_enumerator.compare_word(l_reference_word))
	  {
	    std::cout << "1 <===========>" << std::endl ;
	    //  exit(0);
	  }
	if(!l_enumerator.compare_word(l_reference_word2))
	  {
	    std::cout << "2 <===========>" << std::endl ;
	    //exit(0);
	  }
	if(!l_enumerator.compare_word(l_reference_word3))
	  {
	    std::cout << "3 <===========>" << std::endl ;
	    break;
	  }
      }
      {
	std::vector<combinatorics::symbol> l_symbols =
	  {
	    combinatorics::symbol(1,1),
	    combinatorics::symbol(2,2),
	    combinatorics::symbol(3,3)
	  };
	{
	  combinatorics::enumerator l_enumerator(l_symbols);
	  while(l_enumerator.generate())
	    {
	      l_enumerator.display_word();
	    }
	}
	std::cout << "======================" << std::endl ;
	{
	  unsigned int l_init_word[6] = {3,3,1,2,2,3};
	  combinatorics::enumerator l_enumerator(l_symbols);
	  l_enumerator.set_word(l_init_word,6);
	  l_enumerator.set_count(49);
	  while(l_enumerator.generate())
	    {
	      l_enumerator.display_word();
	    }
	}
      }

    }
  catch(quicky_exception::quicky_runtime_exception & e)
    {
      std::cout << "ERROR : " << e.what() << std::endl ;
      return(-1);
    }
  catch(quicky_exception::quicky_logic_exception & e)
    {
      std::cout << "ERROR : " << e.what() << std::endl ;
      return(-1);
    }
  catch(std::exception & e)
    {
      std::cout << "ERROR from std::exception : " << e.what() << std::endl ;
      return(-1);
    }
  return EXIT_SUCCESS;
}
#endif // COMBINATORICS_SELF_TEST
// EOF
