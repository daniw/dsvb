%Function r = snr(sig, nois)
%
%The function SNR computes the signal to noise ratio w.r.t. the
%average power of the signals, which is defined as:
%  r = 10 * log ( sum((sig(i))^2) / sum((nois(i))^2) ),
%where m_sig and m_nois are the mean values of sig and nois.
%
%
%ARGUMENTS: sig      - nx1 vector of n signal samples
%           nois     - nx1 vector of n noise samples
%
%RETURNS  : r        - signal-to-noise ratio in dB 
%

%%%%%%%% Matlab code follows %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [r] = snr(sig, nois)

%%%%%%%% Setup Constants %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

if nargin ~= 2
   errstr = char('!!! Incorrect # of input arguments');
   error(errstr);
end

[rs,cs] = size(sig);
[rn,cn] = size(nois);
if rs ~= rn
   errstr = char('!!! Input arguments must be of the same size');
   error(errstr);
end

%%%%%%%% Initialize Variables %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

r = 0;

%%%%%%%% Main Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

r = 10*log10(sum((sig).^2)/sum((nois).^2));

%%%%%%%% End Program %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

























