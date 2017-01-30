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


#ifndef _META_C_H_
#define _META_C_H_

#include "meta_max.h"
#include "meta_min.h"

#include <cinttypes>

namespace combinatorics
{
  template <uint64_t N, uint64_t P>
  class C
  {
  public:
  static const uint64_t m_value;
  private:
  template <uint64_t N2, uint64_t P2, uint64_t D = N2 - P2>
    class C_implem
    {
    public:
    static const uint64_t m_value;
    };
  
  template <uint64_t N2, uint64_t P2>
    class C_implem<N2,P2,0>
    {
    public:
    static const uint64_t m_value = 1;
    };
  
  };

  //----------------------------------------------------------------------------
  template <uint64_t N, uint64_t P>
    const uint64_t C<N,P>::m_value = C_implem<N, P>::m_value;

  //----------------------------------------------------------------------------
  template <uint64_t N, uint64_t P>
  template <uint64_t N2, uint64_t P2, uint64_t D>
    const uint64_t C<N,P>::C_implem<N2,P2,D>::m_value = partial_fact<N, max<N - P,P>::m_value + 1>::m_value / fact<min<N - P,P>::m_value>::m_value;

}
#endif // _META_C_H_
//EOF
