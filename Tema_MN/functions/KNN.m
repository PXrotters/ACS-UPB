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
## @deftypefn {} {@var{retval} =} KNN (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Andrei <Andrei@DESKTOP-PK505U9>
## Created: 2021-08-09

function prediction = KNN (labels, Y, test, k)
  % initializeaza prediction
  prediction = -1;
  
  % initializeaza distantele
  [m, n] = size (Y);
  distance = zeros (m, 1);
  
  % Pentru fiecare rand calculam distanta Euclidiana dintre acesta si
  % vectorul de test primit ca argument.
  for i = 1:m
  distance(i) = norm(Y(i, :) - test);
  end
  
  % Ordonam crescator distantele si tinem minte intr-un vector primele
  % k valori care reprezinta valorile adevarate ale acestor imagini care s-au
  % dovedit a fi cele mai apropiate.
  [~, indices] = sort(distance);
  k_nearest_labels = labels(indices(1:k));
  
  % Calculam predictia ca mediana celor k valori cele mai apropiate.
  prediction = median(k_nearest_labels);
endfunction
