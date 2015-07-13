function z= get_image() 
 global obj; %= videoinput('winvideo', 1);
 hblob = vision.BlobAnalysis('AreaOutputPort', false, ... % Set blob analysis handling
                                'CentroidOutputPort', true, ... 
                                'BoundingBoxOutputPort', true', ...
                                'MinimumBlobArea', 1500, ...
                                'MaximumBlobArea', 10000, ...
                                'MaximumCount', 10);
 y = getsnapshot(obj);
 redThresh= 0.10 ;
 rgbFrame= y ;
 
%obj = videoinput('winvideo', 1);
 %start(obj);
%data = getdata(obj);
 %im = getsnapshot(vid); 
 diffFrame = imsubtract(rgbFrame(:,:,1), rgb2gray(rgbFrame)); % Get red component of the image
    diffFrame = medfilt2(diffFrame, [3 3]); % Filter out the noise by using median filter
    binFrame = im2bw(diffFrame, redThresh); % Convert the image into binary image with the red objects as white
    [centroid, bbox] = step(hblob, binFrame); % Get the centroids and bounding boxes of the blobs
figure(3),imshow(binFrame) ;
if length(bbox(:,1))>0
 z=centroid(1,1);
  centroid
else
    z=0 ;
    %s(a);   
end