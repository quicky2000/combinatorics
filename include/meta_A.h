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

#ifndef COMBINATORICS_META_A_H
#define COMBINATORICS_META_A_H

#include <cinttypes>

namespace combinatorics
{
    template <uint64_t N, uint64_t P>
    class A
    {
    public:
        static const uint64_t m_value;
    private:
    };

    //----------------------------------------------------------------------------
    template <uint64_t N, uint64_t P>
    const uint64_t A<N,P>::m_value = partial_fact<N,N-P+1>::m_value;
}
#endif // COMBINATORICS_META_A_H
//EOF
