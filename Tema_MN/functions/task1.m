## Copyright (C) 2021 Andrei
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn {} {@var{retval} =} task1 (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Andrei <Andrei@DESKTOP-PK505U9>
## Created: 2021-09-14

function new_X = task1(photo, k)
[m, n] = size(photo);

% Initializare matrice finala.
new_X = zeros(m, n);

% Convertirea matricei photo la tipul de date double.
photo = double(photo);

% Aplicarea algoritmului SVD asupra matricei photo.
[U, S, V] = svd(photo);

% Redimensionarea matricelor U, S si V la dimensiunile corespunzatoare.
U = U(:, 1:k);
S = S(1:k, 1:k);
V = V(:, 1:k);

% Calcularea aproximarii matricii initiale photo.
new_X = U * S * V';

% Transformarea matricei in uint8 pentru a fi o imagine valida.
new_X = uint8(new_X);
endfunction
