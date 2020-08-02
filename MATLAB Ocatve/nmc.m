function assignedlabel = nmc(data, labels)

nlabels = max(labels);
nm = zeros(nlabels, 2);
%finds nearest mean for each label
for i = 1:nlabels
  nm(i,:) = mean(data(labels == i,:));
end

%trains nmc
assignedlabel = zeros(size(labels));
dist = zeros(4,1);
for i = 1:numel(data(:,1))
  for j = 1:nlabels
    dist(j) = sqrt((data(i,1) - nm(j,1))^2 + (data(i,2) - nm(j,2))^2);
  end
  [~,assignedlabel(i)] = min(dist);  
end
error_rate = mean(assignedlabel ~= labels);
disp(['Error rate = ' num2str(error_rate * 100) '%'])

%creates set of points to apply
high = ceil(max(abs(data(:)))) + 5;
[xx, yy] = meshgrid(-high:high/100:high, -high:high/100:high);
points = [xx(:) yy(:)];
pointlabels = zeros(numel(points(:,1)),1);
for i = 1:numel(points(:,1))
  for j = 1:nlabels
    dist(j) = sqrt((points(i,1) - nm(j,1))^2 + (points(i,2) - nm(j,2))^2);
  end
  [~,pointlabels(i)] = min(dist);  
end

%plots nmc boundaries
figure, hold on, axis equal
colours = ['k'; 'r'; 'g'; 'b'; 'y'; 'c'; 'm'];
if numel(colours) < nlabels
    colours = rand(nlabels, 3);
end

for i = 1:nlabels
  plot(xx(pointlabels == i), yy(pointlabels == i), '.', 'color',...
      colours(i, :), 'markersize', 7)
  plot(data(labels == i, 1), data(labels == i, 2), 'x', 'color',...
      colours(i, :), 'markersize', 20)
  plot(nm(i, 1), nm(i, 2), '+', 'color', colours(i, :), 'markersize', 20)
end



