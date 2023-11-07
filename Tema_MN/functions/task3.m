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
## @deftypefn {} {@var{retval} =} pca_cov (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Andrei <Andrei@DESKTOP-PK505U9>
## Created: 2021-09-06

function new_X = task3(photo, pcs)
  [m, n] = size(photo);
  
  % Cast photo la double.
  photo = double(photo);
  
  % Calculează media fiecărui rând al matricei.
  medie = mean(photo, 2);
  
  % Normalizează matricea initială scazând din ea media fiecărui rând.
  normalized = photo - medie;
  
  % Calculează matricea de covarianta.
  Z = normalized * normalized' / (n - 1);
  
  % Calculează vectorii și valorile proprii ale matricei de covarianta.
  [V, ~] = eig(Z);
  
  % Ordonează descrescător valorile proprii și creează matricea V
  % formată din vectorii proprii așezați pe coloane.
  V = fliplr(V);
  
  % Pastrează doar primele pcs coloane din V.
  W = V(:, 1:pcs);
  
  % Creează matricea Y schimbând baza matricii inițiale.
  Y = W' * normalized;
  
  % Calculează matricea new_X care este o aproximare a matricii inițiale.
  new_X = W * Y + medie;
  
  % Transformă matricea în uint8 pentru a fi o imagine validă.
  new_X = uint8(new_X);
endfunction
