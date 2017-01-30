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

#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <cinttypes>

namespace combinatorics
{
  class formula
  {
  public:
    static inline constexpr uint64_t fact(uint64_t p);
    static inline constexpr uint64_t partial_fact(uint64_t n,
						  uint64_t p);
    static inline constexpr uint64_t C(uint64_t n,
				       uint64_t p
				       );
    static inline constexpr uint64_t A(uint64_t n,
				       uint64_t p
				       );
  private:
  };

  //----------------------------------------------------------------------------
  constexpr uint64_t formula::fact(uint64_t p)
  {
    return p > 1 ? p * fact(p - 1) : 1;
  }

  //----------------------------------------------------------------------------
  constexpr uint64_t formula::partial_fact(uint64_t n,
					   uint64_t p
					   )
  {
    return (n > p) ? n * partial_fact(n - 1, p) : n;
  }

  //----------------------------------------------------------------------------
  constexpr uint64_t formula::C(uint64_t n,
				uint64_t p
				)
  {
    return n != p ? partial_fact(n, ((n - p > p) ? n - p : p) + 1) / fact((n - p > p) ? p : n - p) : 1;
  }

  //----------------------------------------------------------------------------
  constexpr uint64_t formula::A(uint64_t n,
				uint64_t p
				)
  {
    return partial_fact(n, n - p + 1);
  }

}
#endif // _FORMULA_H_
//EOF
