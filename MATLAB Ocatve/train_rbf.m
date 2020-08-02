function RBF = train_rbf(Data,Labels,M)
% Labels 1 or 2
centres = Data(1:M,:);
for i = 1:size(Data,1)
    z = Data(i,:);
    h(i,:) = exp(-(sum((centres - repmat(z,M,1)).^2,2)));
end
RBF.weights = [ones(size(Data,1),1) h]\Labels;
RBF.centres = centres;
