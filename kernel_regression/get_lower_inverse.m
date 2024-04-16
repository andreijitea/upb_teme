function [P] = get_lower_inverse (L)
  [n, n] = size(L);
  P = eye(n);

  for j = 1 : n-1
    for i = j+1 : n
        m = L(i,j) / L(j,j);
        P(i, :) = P(i,:) - m * P(j,:);
    endfor
  endfor

  for i = 1 : n
      P(i,:) = P(i,:) / L(i,i);

  endfor
endfunction
