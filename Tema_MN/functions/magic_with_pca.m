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
## @deftypefn {} {@var{retval} =} magic_with_pca (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Andrei <Andrei@DESKTOP-PK505U9>
## Created: 2021-09-08

function [train, miu, Y, Vk] = magic_with_pca(train_mat, pcs)
  [m, n] = size(train_mat);
  
  % Initializare train
  train = zeros(m, n);
  
  % Initializare miu
  miu = zeros(1, n);
  
  % Initializare Y
  Y = zeros(m, pcs);
  
  % Initializare Vk
  Vk = zeros(n, pcs);
  
  % Cast train_mat la double.
  train_mat = double(train_mat);
  
  % Calculam media fiecarei coloane a matricii.
  miu = mean(train_mat);
  
  % Scadem media din matricea initiala.
  train_mat = train_mat - miu;
  
  % Calculam matricea de covarianta.
  cov_mat = cov(train_mat);
  
  % Calculam vectorii si valorile proprii ale matricei de covarianta.
  [V, D] = eig(cov_mat);
  
  % Ordonam descrescator valorile proprii si cream o matrice V formata din
  % vectorii proprii asezati pe coloane, astfel incat prima coloana sa fie
  % vectorul propriu corespunzator celei mai mari valori proprii si asa mai
  % departe.
  [~, aux] = sort(diag(D), 'descend');
  V = V(:, aux);
  
  % Pastram doar primele pcs coloane din matricea V.
  Vk = V(:, 1:pcs);
  
  % Cream matricea Y schimband baza matricii initiale.
  Y = train_mat * Vk;
  
  % Calculam matricea train care este o aproximatie a matricii initiale
  train = Y * Vk';
endfunction
