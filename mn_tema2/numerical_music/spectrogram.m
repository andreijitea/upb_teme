function [S f t] = spectrogram(signal, fs, window_size)
% Calculeaza lungimea semnalului
[sig_len, ~] = size(signal);
% Calculeaza numarul de ferestre
num_win = floor(sig_len / window_size);

% Initializeaza variabilele de iesire
S = zeros(window_size, num_win);
f = zeros(window_size, 1);
t = zeros(num_win, 1);

% Pentru fiecare fereastra
for i = 1 : num_win
		% Extrage fereastra din semnal
		window = signal((i - 1) * window_size + 1 : i * window_size);

		% Aplica functia Hanning pe fereastra actuala
		hann_window = hanning(window_size);
		for j = 1 : window_size
			window(j) = window(j) * hann_window(j);
		end

		% Calculeaza FFT pentru fereastra actuala, cu o rezolutie de 2 ori mai mare
		fourier_window = fft(window, 2 * window_size);

		% Salveaza doar partea non-conjugata a transformatei
		S(:, i) = abs(fourier_window(1 : window_size));
end

% Calculeaza vectorul de frecvente
for i = 1 : window_size
		f(i) = (i - 1) * fs / (2 * window_size);
end

% Calculeaza vectorul de timp
for i = 1 : num_win
	t(i) = (i - 1) * window_size / fs;
end
endfunction

