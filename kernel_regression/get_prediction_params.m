function [a] = get_prediction_params (K, y, lambda)
  [m, ~] = size(K);
  aux = inv(lambda * eye(m) + K);
  a = lambda * aux * y;
endfunction
