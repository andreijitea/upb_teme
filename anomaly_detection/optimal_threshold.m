% Finds the best threshold to use for selecting outliers.
function [best_epsilon best_F1 associated_precision associated_recall] = optimal_threshold(truths, probabilities)
    % Inițializeaza variabilele necesare
    best_epsilon = 0;
    best_F1 = 0;
    associated_precision = 0;
    associated_recall = 0;
    eps = linspace(min(probabilities), max(probabilities), 1001);
    false_pozitives = 0;
    false_negatives = 0;
    true_pozitives = 0;

    %Cautarea celui mai bun prag (epsilon)
    for i = 1 : 1001
      % Predictions reprezinta un vector cu valori binare
      % Daca o probabilitate este mai mica decat pragul actual -> 1
      % Daca o probabilitate este mai mare decat pragul actual -> 0
      predictions = probabilities < eps(i);

      [false_pozitives, false_negatives, true_pozitives] = check_predictions(predictions, truths);
      [precision, recall, F1] = metrics(true_pozitives, false_pozitives, false_negatives);

      % Daca pragul actual este cel mai bun
      if F1 > best_F1
        best_F1 = F1;
        best_epsilon = eps(i);
        associated_precision = precision;
        associated_recall = recall;
      endif
    endfor
endfunction
