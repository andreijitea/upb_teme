function [L] = cholesky (A)
    [n,n] = size(A);
    L = zeros(n);

    % Pentru fiecare termen al diagonalei principale
    for p = 1 : n
        L(p,p) = sqrt(A(p,p));

        % Pentru fiecare termen de sub cel al diagonalei
        for i = p+1 : n
            L(i,p) = A(i,p)/L(p,p);
        end
        % Pentru fiecare termen al minorului din dreapta jos al termenului
        % actual de pe diagonala principala
        for i = p+1 : n
            for j = p+1 : n
                A(i,j) = A(i,j) - L(i,p) * L(j,p);
            end
        end
    end
endfunction
