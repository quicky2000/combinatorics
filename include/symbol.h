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

#ifndef COMBINATORICS_SYMBOL_H
#define COMBINATORICS_SYMBOL_H

#include <iostream>
#include <cassert>

namespace combinatorics
{
    class symbol
    {
        friend std::ostream & operator<<(std::ostream & p_stream, const symbol & p_symbol);
    public:
        inline
        symbol(unsigned int p_index, unsigned int p_number);

        inline
        unsigned int
        get_index() const;

        inline
        unsigned int
        get_number() const;

        inline
        void
        decr();

        inline
        void
        incr();

    private:
        unsigned int m_index;
        unsigned int m_number;
        unsigned int m_max_number;
    };

    inline
    std::ostream & operator<<(std::ostream & p_stream, const symbol & p_symbol)
    {
        p_stream << (char)('A' - 1 + p_symbol.m_index) ;
        return p_stream;
    }

    //------------------------------------------------------------------------------
    symbol::symbol(unsigned int p_index, unsigned int p_number)
    :m_index(p_index)
    ,m_number(p_number)
    ,m_max_number(p_number)
    {
    }

    //------------------------------------------------------------------------------
    unsigned int
    symbol::get_index() const
    {
        return m_index;
    }

    //------------------------------------------------------------------------------
    unsigned int
    symbol::get_number() const
    {
        return m_number;
    }

    //------------------------------------------------------------------------------
    void
    symbol::decr()
    {
        assert(m_number);
        --m_number;
    }

    //------------------------------------------------------------------------------
    void
    symbol::incr()
    {
        assert(m_number < m_max_number);
        ++m_number;
    }

}
#endif // COMBINATORICS_SYMBOL_H
//EOF
