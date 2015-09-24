%Function xq = uniqnt(x, W, R)
%
%The function UNIQNT quantizes signal x with W bits linearly.
%Rounding is either towards nearest (R = 0, default) or towards.
%- infinity (R=-1).
%Input signal is assumed in the range [-1, 1]. The quantized
%output signal also is in the range [-1, 1].
%
%ARGUMENTS: x     - nx1 vector of n signal samples
%           W     - number of bits for quantization
%           R     - quantization characteristics
%
%RETURNS  : xq    - nx1 vector of n quantized signal samples 
%

%%%%%%%% Matlab code follows %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [xq] = uniqnt(x, W, R)

%%%%%%%% Setup Constants %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if nargin > 3 | nargin < 2
   errstr = char('!!! Incorrect # of input arguments');
   error(errstr);
end

%%%%%%%% Initialize Variables %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%% Main Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if nargin == 3 & R == -1
    % rounding towards - infinity
    xq = floor(x*(2^(W-1))) / (2^(W-1));
else
    % rounding towards nearest
    xq = round(x*(2^(W-1))) / (2^(W-1));
end
%%%%%%%% End Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

























