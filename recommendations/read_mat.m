function mat = read_mat(path)
  % Parse the .csv file and return the matrix of values (without row and column headers).
  mat = csvread(path, 1, 1);
end
