clc, clear, close all

im = importdata('test_image.txt');
imx4 = importdata('test_image_x4.txt');
imnx4 = importdata('test_image_notx4.txt');

disp('sae')
x4 = sum(sum(abs(im - imx4)))
nx4 = sum(sum(abs(im - imnx4)))

disp('mae')
x4 = x4 / numel(im)
nx4 = nx4 / numel(im)

disp('sse')
x4 = sum(sum((im - imx4).^2))
nx4 = sum(sum((im - imnx4).^2))

disp('mse')
x4 = x4 / numel(im)
nx4 = nx4 / numel(im)

disp('rmse')
x4 = sqrt(x4)
nx4 = sqrt(nx4)



%% thresholding
threshold1 = importdata('Results/threshold1.txt');
threshold2 = importdata('Results/threshold2.txt');

figure
imshow(logical(threshold1))
figure
imshow(logical(threshold2))

disp('threshold answer check')
sum(sum(im >= 230))
sum(sum(im >= 100 & im <= 200))

%% convolution
% k = repmat(1 / 9, 3, 3);
% C = conv2(im, k, 'same');
% figure
% imshow(C);

figure('name', 'MeanFilter')
imshow(uint8(importdata('Results/MeanFilter.txt')));
figure('name', 'MeanFilter9')
imshow(uint8(importdata('Results/MeanFilter9.txt')));
figure('name', 'GaussianFilter')
imshow(uint8(importdata('Results/GaussianFilter.txt')));
figure('name', 'LaplacianFilter')
imshow(uint8(importdata('Results/LaplacianFilter.txt')));
figure('name', 'LaplacianFilter9')
imshow(uint8(importdata('Results/LaplacianFilter9.txt')));
figure('name', 'SobelXOperator')
imshow(uint8(importdata('Results/SobelXOperator.txt')));
figure('name', 'SobelYOperator')
imshow(uint8(importdata('Results/SobelYOperator.txt')));
figure('name', 'GradientMagnitude')
imshow(uint8(importdata('Results/GradientMagnitude.txt')));
figure('name', 'sharpenFilter')
imshow(uint8(importdata('Results/sharpenFilter.txt')));

