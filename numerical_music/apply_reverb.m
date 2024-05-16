function signal = apply_reverb(signal, impulse_response)
    % Ensure the impulse response is in mono
    impulse_response = stereo_to_mono(impulse_response);
    
    % Compute the convolution between the signal and the impulse response
    signal = fftconv(signal, impulse_response);
    
    % Normalize the resulting signal
    signal = signal / max(abs(signal));
endfunction

