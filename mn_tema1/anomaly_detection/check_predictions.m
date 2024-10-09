% Determina urmatoarele valori
% FP - numarul de date normale, care au fost considerate anomalii
% FN - numarul de anomalii, care nu au fost identificare
% TP - numarul de anomalii identificate corect
function [false_pozitives, false_negatives, true_pozitives] = check_predictions(predictions, truths)
	[n, ~] = size(predictions);

	% Initializeaza variabilele necesare
	false_pozitives = 0;
	false_negatives = 0;
	true_pozitives = 0;

	% Calculeaza numarul termenilor din cele 3 categorii
	for i = 1 : n
		if predictions(i) == 1 && truths(i) == 0
			false_pozitives = false_pozitives + 1;
		elseif predictions(i) == 0 && truths(i) == 1
			false_negatives = false_negatives + 1;
		elseif predictions(i) == 1 && truths(i) == 1
			true_pozitives = true_pozitives + 1;
		endif
	endfor

endfunction
