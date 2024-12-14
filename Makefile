# /*The cpps makefile is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the 
# Free Software Foundation, either version 3 of the License, or (at your option) any later version.

# The cpps makefile is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along with the cpps makefile.
# If not, see <https://www.gnu.org/licenses/>.*/


install: Lexer.cpp token/token.h
	clang++ -std=c++20 Lexer.cpp -o cpps 

clean:
	rm -f cpps
