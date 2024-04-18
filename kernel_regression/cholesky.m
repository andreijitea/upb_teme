function [L] = cholesky (A)
    [n,n] = size(A);
    L = zeros(n);

    for j = 1:n
        % Calcularea termenilor de pe diagonala principala
        L(j,j) = sqrt(A(j,j));
        % Calcularea termenilor de pe coloana j, de sub diagonala
        L(j+1:n, j) = A(j+1:n, j) / L(j,j);
        
        % Actualizarea minorului matricei A
        A(j+1:n, j+1:n) = A(j+1:n, j+1:n) - L(j+1:n, j) * L(j+1:n, j)';
    end
endfunction
