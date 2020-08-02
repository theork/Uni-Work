function [assigned_labels, iter, log] = my_kmeans(data, c)
data_size = size(data, 1);
%allocate memory to variables
means = zeros(c, 2);
mean_ind = zeros(c,1);

%finds random starting means with error checking
for i = 1:c
    inf_stop = 0;
    while inf_stop < 50   %prevents infinite loop
        inf_stop = inf_stop + 1;
        rand_ind = randi(data_size);
        if ~ismember(rand_ind, mean_ind)    %checks if value is unique          
            break
        end
    end
    if inf_stop >= 50
        disp('couldnt find two unique indexes of data, try bigger dataset')
        return
    end
    mean_ind(i) = rand_ind;
    means(i, :) = data(rand_ind, :);
end

%allocate memory to/initialise more variables
iter = 0;
prev_means = means;
assigned_labels = zeros(size(data, 1), 1);
dist = zeros(c, 1);
log = cell(500, 4);

while iter < 500   %prevents infinite loop
    iter = iter + 1;
    je = 0;
    for i = 1:data_size
        for j = 1:c
            dist(j) = (data(i, 1) - means(j, 1)).^2 +...
                ((data(i, 2) - means(j, 2) ).^2);
            je = je + sum(dist);
        end        
        [~, assigned_labels(i)] = min(dist); %label = index of lowest value
    end

    for i = 1:c %finds new means of each cluster
        means(i, :) = mean(data(assigned_labels == i, :), 1);
    end
    
    %create a log of whats happening each iteration
    log{iter, 1} = je;
    log{iter, 2} = prev_means;
    log{iter, 3} = means;
    log{iter, 4} = assigned_labels;
    
    if means == prev_means  %breaks loop if calculations are finished
        break
    end
    prev_means = means;
end
if iter >= 1000
    disp('error - couldnt complete within 1000 iterations')
end