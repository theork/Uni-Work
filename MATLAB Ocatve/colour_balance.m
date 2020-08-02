function out = colour_balance(orig_im, s1, s2)
  im = double(orig_im);
  N = numel(im(:,:,1));
  sat_start = round(N * s1 / 100);
  sat_end = round(N * (1 - s2 / 100));  
  for i = 1:3
    layer = im(:,:,i);
    sorted = sort(layer(:));
    vmin = sorted(sat_start + 1);
    vmax = sorted(sat_end);
    layer(layer < vmin) = vmin;
    layer(layer > vmax) = vmax;
    out(:,:,i) = uint8(255 * (layer - vmin) / (vmax - vmin));    
  end
end
