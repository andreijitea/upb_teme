function signal = low_pass(signal, fs, cutoff_freq)
    % Calculeaza transformata semnalului
    sig = fft(signal);
    
    % Compute all possible frequencies of the signal
    freqs = zeros(1, length(sig));
    for i = 1 : length(sig)
      freqs(i) = (i - 1) * fs / length(sig);
    end
    
    % Calculeaza vectorul masca (valori de 1 si 0)
    mask = freqs <= cutoff_freq;
    
    % Aplica produsul Hadamard
    sig_filt = zeros(size(sig));
    for i = 1 : length(sig)
      sig_filt(i) = sig(i) * mask(i);
    end
    
    % Calculeaza transformata inversa
    signal = ifft(sig_filt);
    
    % Normalizeaza semnalul filtrat
    signal = signal / max(abs(signal));
endfunction

