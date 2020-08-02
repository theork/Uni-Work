clear, clc, close all

Data = xlsread('../BirdEyeWeights.xlsx','Sheet1','j2:x73');
[~,FileNames] = xlsread('../BirdEyeWeights.xlsx','Sheet1','b2:b73');
[~,FeatureNames] = xlsread('../BirdEyeWeights.xlsx','Sheet1','j1:x1');
Ages = xlsread('../BirdEyeWeights.xlsx','Sheet1','aa2:aa73');
Weights = xlsread('../BirdEyeWeights.xlsx','Sheet1','h2:h73');

weighted = 0;
n = numel(FeatureNames);
N = size(Data,1);
count = 0;


for i = 1:n
    if weighted
        lm = fitlm(Data(:, i), Ages, 'weights', Weights);
    else
        lm = fitlm(Data(:, i), Ages);
    end
    if lm.coefTest <= 0.05
        count = count + 1;
        logger{count, 1} = i;
        logger{count, 2} = FeatureNames{i};
        logger{count, 3} = lm.Rsquared.Ordinary;
        logger{count, 4} = lm.Rsquared.Adjusted;
        logger{count, 5} = lm.coefTest;
        logger{count, 6} = lm;
        
%         figure, hold on
%         Y = lm.Fitted;
%         plot(Data(:, i), Ages, 'b.', 'markersize', 15)
%         plot(Data(:, i), Y, 'r*-')
%         plot([Data(:, i)'; Data(:, i)'], [Ages'; Y'],...
%             'k--', 'color', [1 1 1] * 0.7)
%         xlabel(FeatureNames{i})
%         ylabel('Age (months)')
        
    end
    
    singleVar(i, 1) = lm.coefTest;
    singleVar(i, 2) = lm.Rsquared.Adjusted;
end


count2 = 0;
for i = 1:n - 1
    for j = i + 1:n
        if weighted
            lm = fitlm([Data(:, i) Data(:, j)], Ages, 'weights', Weights);
        else
            lm = fitlm([Data(:, i) Data(:, j)], Ages);
        end
        if lm.coefTest <= 0.05
            count = count + 1;
            logger{count, 1} = [i j];
            logger{count, 2} = [FeatureNames{i} ' & ' FeatureNames{j}];
            logger{count, 3} = lm.Rsquared.Ordinary;
            logger{count, 4} = lm.Rsquared.Adjusted;
            logger{count, 5} = lm.coefTest;
            logger{count, 6} = lm;
            
%             figure, hold on
%             
%             x1 = Data(:, i);
%             x2 = Data(:, j);            
%             plot3(x1, x2, Ages, 'b.', 'markersize', 15)
%             B = lm.Coefficients.Estimate;
%             temp = B(1);
%             B = B(2:end);
%             B(3) = temp;
%             Y = lm.Fitted;
%             plot3(x1, x2, Y, 'r.')
%             
%             x1fit = linspace(min(x1), max(x1), 40);
%             x2fit = linspace(min(x2), max(x2), 40);
%             [X1FIT, X2FIT] = meshgrid(x1fit, x2fit);
%             YFIT = [X1FIT(:) X2FIT(:) ones(numel(X1FIT), 1)] * B;
%             mesh(X1FIT, X2FIT, reshape(YFIT, size(X1FIT)))
%             colormap(pink)
%             grid on
%             plot3([Data(:, i)'; Data(:, i)'], [Data(:, j)';...
%                 Data(:, j)'], [Ages'; Y'], 'k--', 'color', [1 1 1] * 0.7)
%             xlabel(FeatureNames{i})
%             ylabel(FeatureNames{j})
%             zlabel('Age')            
%             rotate3d
%             view(50, 10)
        end
        count2 = count2 + 1;
        pairsVar(count2, 1) = lm.coefTest;
        pairsVar(count2, 2) = lm.Rsquared.Adjusted;
    end
end

count2 = 0;
for i = 1:3:n
    if weighted
        lm = fitlm(Data(:, i:i+2), Ages, 'weights', Weights);
    else
        lm = fitlm(Data(:, i:i+2), Ages);
    end
    if lm.coefTest <= 0.05
        count = count + 1;
        logger{count, 1} = [i i+1 i+2];
        logger{count, 2} = [FeatureNames{i} ' & ' ...
            FeatureNames{i + 1} ' & ' FeatureNames{i + 2}];
        logger{count, 3} = lm.Rsquared.Ordinary;
        logger{count, 4} = lm.Rsquared.Adjusted;
        logger{count, 5} = lm.coefTest;
        logger{count, 6} = lm;
    end
    count2 = count2 + 1;
    spaceVar(count2, 1) = lm.coefTest;
    spaceVar(count2, 2) = lm.Rsquared.Adjusted;
end

if weighted
    lm = fitlm(Data, Ages, 'weights', Weights);
else
    lm = fitlm(Data, Ages);
end
if lm.coefTest <= 0.05
    count = count + 1;
    logger{count, 2} = 'ALL FEATURES';
    logger{count, 3} = lm.Rsquared.Ordinary;
    logger{count, 4} = lm.Rsquared.Adjusted;
    logger{count, 5} = lm.coefTest;
    logger{count, 6} = lm;    
end
allVar(1, 1) = lm.coefTest;
allVar(1, 2) = lm.Rsquared.Adjusted;

%plot k highest adjusted r square values
[~, maxrsq] = maxk(cell2mat(logger(:, 4)), 10);

for i = 1:numel(maxrsq)
    if numel(logger{maxrsq(i), 1}) == 1
        ii = logger{maxrsq(i), 1};
        figure, hold on
        Y = logger{maxrsq(i),6}.Fitted;
        plot(Data(:, ii), Ages, 'b.', 'markersize', 15)
        plot(Data(:, ii), Y, 'r*-')
        plot([Data(:, ii)'; Data(:, ii)'], [Ages'; Y'],...
            'k--', 'color', [1 1 1] * 0.7)
        xlabel(FeatureNames{ii})
        ylabel('Age (months)')
        
    elseif numel(logger{maxrsq(i), 1}) == 2
        %gets data indicies from log
        ii = logger{maxrsq(i), 1}(1);
        jj = logger{maxrsq(i), 1}(2);

        figure, hold on

        x1 = Data(:, ii);
        x2 = Data(:, jj);            
        plot3(x1, x2, Ages, 'b.', 'markersize', 15)
        B = logger{maxrsq(i),6}.Coefficients.Estimate;
        temp = B(1);
        B = B(2:end);
        B(3) = temp;
        Y = logger{maxrsq(i),6}.Fitted;
        plot3(x1, x2, Y, 'r.')

        x1fit = linspace(min(x1), max(x1), 40);
        x2fit = linspace(min(x2), max(x2), 40);
        [X1FIT, X2FIT] = meshgrid(x1fit, x2fit);
        YFIT = [X1FIT(:) X2FIT(:) ones(numel(X1FIT), 1)] * B;
        mesh(X1FIT, X2FIT, reshape(YFIT, size(X1FIT)))
        colormap(pink)
        grid on
        plot3([Data(:, ii)'; Data(:, ii)'], [Data(:, jj)';...
            Data(:, jj)'], [Ages'; Y'], 'k--', 'color', [1 1 1] * 0.7)
        xlabel(FeatureNames{ii})
        ylabel(FeatureNames{jj})
        zlabel('Age')            
        rotate3d
        view(50, 10)
        zlim([-200 600])
    else
        disp(['couldnt plot element ' num2str(i) ' - too many dimensions'])
    end
    
end


figure, hold on, grid on
plot(singleVar(:,1), singleVar(:,2), 'kx', 'markersize', 15, 'linewidth', 2)
plot(pairsVar(:,1), pairsVar(:,2), 'rx', 'markersize', 15, 'linewidth', 2)
plot(spaceVar(:,1), spaceVar(:,2), 'cx', 'markersize', 15, 'linewidth', 2)
plot(allVar(1,1), allVar(1,2), 'gx', 'markersize', 15, 'linewidth', 2)
axis([0 1 -0.065 0.1])
axis square
y = ylim;
plot([0.05 0.05], [y(1) y(2)], 'linewidth', 2)
title(['\fontsize{16}Plot to compare the resultant {\it p}-value'...
    ' and {\it r ^2}-adjusted between feature acquisition methods'])
xlabel('\fontsize{16}{\it p}-value')
ylabel('\fontsize{16}{\it r^2}-adjusted')
legend('\fontsize{14}Single Feature', '\fontsize{14}Feature Pairs',...
    '\fontsize{14}Colour Spaces', '\fontsize{14}All Features',...
    '\fontsize{14}Level of Significance')


