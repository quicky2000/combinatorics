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

#ifndef _META_MAX_H_
#define _META_MAX_H_

#include <cinttypes>

namespace combinatorics
{
  template <uint64_t N, uint64_t P>
  class max
  {
  public:
    static const uint64_t m_value;
  private:
    template <uint64_t N2, uint64_t P2, bool B>
    class max_implem
      {
      public:
	static const uint64_t m_value;
      };

    template <uint64_t N2, uint64_t P2>
    class max_implem<N2,P2,true>
      {
      public:
	static const uint64_t m_value = N2;
      private:
      };

    template <uint64_t N2, uint64_t P2>
      class max_implem<N2,P2,false>
      {
      public:
	static const uint64_t m_value = P2;
      private:
      };

  };

  //----------------------------------------------------------------------------
  template <uint64_t N, uint64_t P>
  const uint64_t max<N,P>::m_value = max_implem<N,P, (N > P)>::m_value;

}
#endif // _META_MAX_H_
//EOF
