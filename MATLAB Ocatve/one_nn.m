function Testing_Labels = one_nn(Data, Labels, Testing_Data)
Testing_Labels = zeros(numel(Testing_Data(:,1),1));
dist = zeros(1,numel(Data(:,1)));
for i = 1:numel(Testing_Data(:,1))
    for j = 1:numel(Data(:,1))
        dist(j) = sqrt((Testing_Data(i,1) -...
            Data(j,1))^2 + (Testing_Data(i,2) - Data(j,2))^2);
    end
    [~,DataInd] = min(dist);
    Testing_Labels(i) = Labels(DataInd);
end







