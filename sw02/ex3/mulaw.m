%Function Y = mulaw(X,u)
%
%The function MULAW perform logarithmic mu-law compression with
%parameter u, as defined in the standard for speech compression. 
%
%
%ARGUMENTS: X        - vector of input sample values
%           u        - parameter for mu-law compression

%
%RETURNS  : Y        - vector of compressed output samples.
%

%%%%%%%% Matlab code follows %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [Y] = mulaw(X,u)

%%%%%%%% Setup Constants %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if nargin ~= 2
   errstr = char('!!! Incorrect # of input arguments');
   error(errstr);
end

[rd,cd] = size(X);
if (rd > 1) & (cd > 1)
   errstr = char('!!! First input argument must be a vector');
   error(errstr);
end

[rd,cd] = size(u);
if (rd ~= 1) | (cd ~= 1)
   errstr = char('!!! Second input argument must be a scalar');
   error(errstr);
end

n = length(X);

%%%%%%%% Initialize Variables %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
                                       
%%%%%%%% Main Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Y = sign(X).* log(1.+(u*abs(X))) / log(1+u);

%%%%%%%% End Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

























