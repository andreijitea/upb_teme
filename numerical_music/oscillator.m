function x = oscillator(freq, fs, dur, A, D, S, R)
  % Seteaza vectorul de timp
  t = linspace(0, dur, dur * fs);

  % Seteaza unda sinusoidala
  x = sin(2 * pi * freq * t);
  x = x';

  % Calculeaza numarul de sample-uri
  [tot_sam, ~] = size(x);
  a_sam = floor(A * fs);
  d_sam = floor(D * fs);
  r_sam = floor(R * fs);
  s_sam = tot_sam - a_sam - d_sam - r_sam;

  % Calculeaza envelope-ul ADSR
  a_env = linspace(0, 1, a_sam);
  d_env = linspace(1, S, d_sam);
  s_env = S * ones(1, s_sam);
  r_env = linspace(S, 0, r_sam);

  % Concateneaza ADSR intr-un singur envelope
  env = [a_env'; d_env'; s_env'; r_env'];
  % Aplica envelope-ul pe unda sinusoidala

  x = x .* env;

endfunction

