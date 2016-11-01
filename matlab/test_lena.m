function test_grayscale()

% Copy the latest build to the current folder
copyfile('../build/vc2015/SiCEnc/Debug/SiCEnc.exe','.');
copyfile('../build/vc2015/SiCEnc/Debug/SiCDec.exe','.');

% Load the Lena image and convert to grayscale
X = double(imread('../images/Misc/lena_std.bmp'));
X = uint8(0.299 * X(:,:,1) + 0.587 * X(:,:,2) + 0.114 * X(:,:,3));
imwrite(X,'lena_gray.bmp');

% Write the corresponding raw format for HEVC
fh = fopen('lena_gray.raw','wb');
fwrite(fh,X');
fclose(fh);

% Create the RD curve vectors
rateSic = zeros(1,100);
distSic = zeros(1,100);

% Process at different quantization levels for SiC
a = 1;
for qp = 20:52
    % Encode the image using the given quantizer
    system(sprintf('SiCEnc lena_gray.bmp lena.sic CHROMA_400 %d',qp));
    system('SiCDec lena.sic lena_sic.bmp');

    % Calculate the bitrate
    dirObj = dir('lena.sic');
    rateSic(a) = 8 * dirObj.bytes / numel(X);
    clear functions;
    
    % Calculate the distortion
    Y = imread('lena_sic.bmp');
    distSic(a) = psnr(Y(:,:,1),X);
    
    close all;
    imshow(Y);
    
    % Update the counter
    a = a + 1;
end

% Truncate the curves
rateSic = rateSic(1:a-1);
distSic = distSic(1:a-1);

% % Create the RD curve vectors
% rateHevc = zeros(1,52);
% distHevc = zeros(1,52);
% 
% % Process at different quantization levels for HEVC
% a = 1;
% for qp = 0:51
%     % Encode the image using the given quantization parameter
%     system(sprintf('TAppEncoder -i lena_gray.raw -c encoder_intra_main_rext_gray.cfg -wdt 512 -hgt 512 -fr 1 -f 1 -q %d',qp));
%     
%     % Calculate the bitrate
%     dirObj = dir('str.bin');
%     rateHevc(a) = dirObj.bytes / numel(X);
%     clear functions;
%     
%     % Calculate the distortion
%     fh = fopen('rec.yuv','rb');
%     Y = uint8(fread(fh,[size(X,2) size(X,1)],'uint16'))';
%     fclose(fh);
%     distHevc(a) = psnr(Y(:,:,1),X);
%     
%     a = a + 1;
% end

% Create the RD curve vectors
rateJpeg = zeros(1,100);
distJpeg = zeros(1,100);

% Process at different quantization levels for HEVC
a = 1;
for q = 1:100
    % Encode the image using the given quality
    imwrite(X,'lena.jpg','Quality',q);
    
    % Calculate the bitrate
    dirObj = dir('lena.jpg');
    rateJpeg(a) = 8 * dirObj.bytes / numel(X);
    clear functions;
    
    % Calculate the distortion
    Y = imread('lena.jpg');
    distJpeg(a) = psnr(Y(:,:,1),X);
    
    a = a + 1;
end

close all;
plot(rateSic,distSic,'k-',rateJpeg,distJpeg,'k--');
xlim([0.25 1.75]);
