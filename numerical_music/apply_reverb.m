function signal = apply_reverb(signal, impulse_response)
	% Modifica semnalul in mono
	impulse_response = stereo_to_mono(impulse_response);
	
	% Calculeaza convolutia semnalului
	signal = fftconv(signal, impulse_response);
	
	% Normalizeaza semnalul
	signal = signal / max(abs(signal));
endfunction

