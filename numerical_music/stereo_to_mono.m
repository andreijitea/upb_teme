function mono = stereo_to_mono(stereo)
  [m, n] = size(stereo)

  % Initializeaza semnalul mono
  mono = zeros(m, 1);

  % Calculeaza media aritmetica pentru fiecare linie
  mono = mean(stereo, 2);
  
  % Normalizeaza semnalul
  mono = mono / max(abs(mono));
endfunction

