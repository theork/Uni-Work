
% Read the image from the ASCII file
figure;
colormap gray;
colorbar;
my_image = load('test_image.txt');

min_val = min(my_image(:))
max_val = max(my_image(:))
sum_val = sum(my_image(:))
mean_val = mean(my_image(:))
variance_val = var(my_image(:), 1)
std_dev_val = std(my_image(:), 1)
