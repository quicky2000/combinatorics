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
#ifndef _FACT_H_
#define _FACT_H_

#include <cinttypes>

namespace combinatorics
{
  template <uint64_t N>
  class fact
  {
  public:
      static const uint64_t m_value;
  };

  //----------------------------------------------------------------------------
  template <uint64_t N>
    const uint64_t fact<N>::m_value =  N * fact<N - 1>::m_value;
  
  template <>
  class fact<1>
  {
  public:
      static const uint64_t m_value = 1;
  };

  template <>
  class fact<0>
  {
  public:
      static const uint64_t m_value = 0;
  };

}
#endif // _FACT_H_
// EOF
