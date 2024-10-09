% Determina parametrii conform carora se stabileste pragul epsilon
function [precision recall F1] = metrics(true_pozitives, false_pozitives, false_negatives)
	% Calculeaza conform formulelor din PDF
	precision = true_pozitives / (true_pozitives + false_pozitives);
	recall = true_pozitives / (true_pozitives + false_negatives);
	F1 = (2*precision*recall) / (precision + recall);
endfunction
