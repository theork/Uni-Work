function out = rescaler(images, standard)

numIm = size(images, 2);
maxValue = zeros(numIm, 1);

%calculates the standard length of the longest side
if ~exist('standard', 'var') || standard == 0
    for i = 1:numIm
        h = size(images{i}, 1);
        w = size(images{i}, 2);
        maxValue(i) = max([w h]);
    end
    standard = mean(maxValue);
end

out = cell(1, numIm);

%resizes the longest side to equal standard and keeps aspect ratio
for i = 1:numIm
    h = size(images{i}, 1);
    w = size(images{i}, 2);
    if h > w %portrait
        ratio = h / standard;
        out{i} = imresize(images{i},[round(standard) round(w / ratio)]); 
    else %landscape 
        ratio = w / standard;
        out{i} = imresize(images{i},[round(h / ratio) round(standard)]);  
    end    
end
