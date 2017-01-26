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
namespace combinatorics
{
  template <unsigned int N>
  class fact
  {
  public:
      static unsigned int compute(void);
  };

  template <unsigned int N>
    unsigned int fact<N>::compute(void)
    {
      return N * fact<N - 1>::compute();
    }
  
  template <>
    unsigned int fact<1>::compute(void)
    {
      return 1;
    }
  
}
#endif // _FORMULA_H_
//EOF
