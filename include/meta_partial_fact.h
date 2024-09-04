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

#ifndef COMBINATORICS_META_PARTIAL_FACT_H
#define COMBINATORICS_META_PARTIAL_FACT_H

#include <cinttypes>

namespace combinatorics
{
    template <uint64_t A, uint64_t B>
    class partial_fact
    {
    public:
        static const uint64_t m_value;
    private:
        template <uint64_t A2, uint64_t B2, uint64_t C = A2 - B2>
        class partial_fact_implem
        {
        public:
            static const uint64_t m_value;
        };

        template <uint64_t A2, uint64_t B2>
        class partial_fact_implem<A2,B2,1>
        {
        public:
            static const uint64_t m_value;
        };
  
        template <uint64_t A2, uint64_t B2>
        class partial_fact_implem<A2,B2,0>
        {
        public:
            static const uint64_t m_value;
        };
    };

    //----------------------------------------------------------------------------
    template <uint64_t A, uint64_t B>
    const uint64_t partial_fact<A, B>::m_value = partial_fact_implem<A,B>::m_value;

    //----------------------------------------------------------------------------
    template <uint64_t A, uint64_t B>
    template <uint64_t A2, uint64_t B2, uint64_t C>
    const uint64_t partial_fact<A,B>::partial_fact_implem<A2,B2,C>::m_value =  A * partial_fact<A - 1,B>::m_value;

    //----------------------------------------------------------------------------
    template <uint64_t A, uint64_t B>
    template <uint64_t A2, uint64_t B2>
    const uint64_t partial_fact<A,B>::partial_fact_implem<A2,B2,1>::m_value = A * B;

    //----------------------------------------------------------------------------
    template <uint64_t A, uint64_t B>
    template <uint64_t A2, uint64_t B2>
    const uint64_t partial_fact<A,B>::partial_fact_implem<A2,B2,0>::m_value = A;

}
#endif // COMBINATORICS_META_PARTIAL_FACT_H
//EOF
