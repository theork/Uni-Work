function [out_im, contour] = eye_detector_improved(im)
sen = 0.85;
radi = [15 19];

Tmax = 20;
it = 0;
nd = 0;
while nd ~= 1 && it < Tmax
    it = it + 1;
    if nd == 0
        sen = sen * 1.02;
        radi = radi + [-1 1];
    else
        sen = sen * 0.98;
        radi = radi + [1 -1];
    end

    if radi(1) < 6
        radi(1) = min([8, radi(2)-2]);
    end
    if radi(2) - radi(1) < 2
        radi(1) = max([1, radi(1)-1]);
    end
    if radi(2) - radi(1) > 9
        radi(2) = max([radi(1)+2 radi(2)-8]); 
    end

    [centre1,rad1] = imfindcircles(im,radi,'ObjectPolarity','dark',...
        'Sensitivity',sen,'Method','twostage');
    [centre2,rad2] = imfindcircles(im,radi,'ObjectPolarity',...
        'bright','Sensitivity',sen,'Method','twostage');

    nd = size(centre1, 1) + size(centre2, 1);
        
end
out_im = []; contour = [];


if size(centre1, 1) == 1
    %checks if the start point is out of range
    x = centre1(1) - rad1;
    y = centre1(2) - rad1;
    if x < 0
        x = 0;
    elseif x > size(im, 1)
        x = size(im, 1);
    end
    if y < 0 
        y = 0;
    elseif y > size(im, 2)
        y = size(im, 2);
    end
        
    out_im = uint8(imcrop(im, [x y ...
        (rad1 * 2) (rad1 * 2)]));
elseif size(centre2, 1) == 1
    %checks if the start point is out of range
    x = centre2(1) - rad2;
    y = centre2(2) - rad2;
    if x < 0
        x = 0;
    elseif x > size(im, 1)
        x = size(im, 1);
    end
    if y < 0 
        y = 0;
    elseif y > size(im, 2)
        y = size(im, 2);
    end
    
    out_im = uint8(imcrop(im, [x y...
        (rad2 * 2) (rad2 * 2)]));
else
    return
end

bw_im = rgb2gray(out_im);
mask = zeros(size(bw_im));
mask(5:end-5,5:end-5) = 1;
contour = activecontour(bw_im, mask);


end