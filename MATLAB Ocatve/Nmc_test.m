clc, clear, close all

data = [
    -0.5517	5.5203
    -5.6134	-12.9933
    -7.1059	-6.2478
    3.6524	1.0332
    17.6076	2.5379
    4.4574	-5.8006
    -2.4729	1.3009
    12.5651	0.8582
    -4.2208	0.2344
    -1.9649	5.4084
    7.6052	-17.4098
    12.5604	6.7209
    6.1117	5.7811
    2.3581	12.8833
    12.7784	12.2772
    -0.5573	17.5293
    -8.6875	3.8364
    -5.6466	8.4122
    -8.0014	7.2338
    2.6925	8.3898
    -6.657	8.6046
    -10.5213	16.7029
    13.1314	0.5412
    22.3896	0.2983
    9.9344	-8.5383];

labels = [ones(10, 1); ones(5, 1) * 2; ones(7, 1) * 3; ones(3, 1) * 4];

nmc(data, labels);

%create random larger dataset 
rand_data_size = randi(800) + 200;
rand_clusters = randi(7) + 3;
section = floor(rand_data_size / rand_clusters);
rand_data = [];
rand_labels = [];
for i = 1:rand_clusters
    x1 = randn(section, 1) * (rand() * 5) + ((rand()-1/2) * 30);
    x2 = randn(section, 1) * (rand() * 5) + ((rand()-1/2) * 30);
    rand_data = [rand_data; x1 x2];
    rand_labels = [rand_labels; ones(section, 1) * i];
end
labels = rand_labels;
data = rand_data;

nmc(rand_data, rand_labels);