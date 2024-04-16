% Determina urmatoarele valori
% FP - numarul de date normale, care au fost considerate anomalii
% FN - numarul de anomalii, care nu au fost identificare
% TP - numarul de anomalii identificate corect
function [false_pozitives, false_negatives, true_pozitives] = check_predictions(predictions, truths)
    false_pozitives = sum(predictions & ~truths);
    false_negatives = sum(~predictions & truths);
    true_pozitives = sum(predictions & truths);
endfunction
