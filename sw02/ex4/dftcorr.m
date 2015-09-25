%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DFT as Correlation
% Autor: Waj, HSLU
% Date: 25-Jan-2011, 27-Sep-2012
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all;

%% User input parameters
% number of samples N
while 1
    N = input('Number of Samples (8 <= N <= 128): '); 
    if (N > 7) & (N < 129) break; end
end
% frequency index to be calculated
while 1
    k = input('Frequency index (0 <= k <= N-1): '); 
    if (k >= 0) & (k < N) break; end
end
% number of time-domain samples that are not zero
while 1
    L = input('Signal length (1 <= L <= N): '); 
    if (L > 0) & (L <= N) break; end
end
% type of signal to be analyzed (and frequency if sine)
while 1
    T = input('Signal type (0 = step, 1 = ramp, 2 = sine): '); 
    if (T == 0) | (T == 1) break; 
    elseif (T == 2) 
        while 1
            F = input('Signal frequency (1 <= F < N/2): '); 
            if (F > 0) & (F < N/2) break; end
        end
        break;
    end
end

%% Construct the time domain signal to be analyzed
n = [0:N-1];   % time index full range
l = [0:L-1];   % time index for range not equal zero
x = zeros(1,N);
if T == 0 % step
    x(1:L) = 1;
elseif T == 1 % ramp
    if L>1 % prevent NaN for L=1 !!!
       x(1:L) = l/(L-1); 
    end
else % sine
    x(1:L) = sin(2*pi*F*l/N);
end

%% Calculate the Harmonics (continous- and discrete time) :::ToDo:::
t = [0:0.001:N-1];  % "continous" time
cos_con = cos(2*pi*k*t/N);
cos_dis = cos(2*pi*k*n/N);
sin_con = sin(2*pi*k*t/N);
sin_dis = sin(2*pi*k*n/N);

%% Calculate the Correlation with given frequency index :::ToDo:::
cos_cor = cos_dis.*x;
cos_sum = zeros(1,N); cos_sum(k+1) = sum(cos_cor);
sin_cor = sin_dis.*x;
sin_sum = zeros(1,N); sin_sum(k+1) = sum(sin_cor);

%% Calculate k-th frequency coefficient from correlation :::ToDo:::
abs_sk = abs(cos_sum + j*sin_sum);
arg_sk = angle(cos_sum + j*sin_sum);

%% Calculate the complete spectrum (for reference)
s = fft(x);
re_s = real(s); im_s = imag(s);
abs_s = abs(s); arg_s = angle(s);

%% Plot
set(figure,'Name',strcat('DFT as Correlation:  Number of Samples N = ',...
                  num2str(N),', Frequency index k = ',num2str(k)));
              
subplot(4,3,1);
p(1) = stem(n,x); ah(1)=gca;
title('x[n]');

subplot(4,3,2);
p(2) = stem(n,x); ah(2)= gca;
title('x[n]');

subplot(4,3,3);hold on;
p(3) = bar(n,re_s);
stem(k,cos_sum(k+1),'r.')
ah(3) = gca;
title('Re(X_k)');

subplot(4,3,4); hold on;
p(4) = plot(t,cos_con,'r:');
plot(n,cos_dis,'r*');
ah(4) = gca;
title('cos_k');

subplot(4,3,5); hold on;
p(5) = plot(t,sin_con,'g:');
plot(n,sin_dis,'g*')
ah(5) = gca;
title('-sin_k');

subplot(4,3,6);hold on;
p(6) = bar(n,im_s);
stem(k,sin_sum(k+1),'g.') 
ah(6) = gca;
title('Im(X_k)');

subplot(4,3,7);
p(7) = plot(n,cos_cor,'r-');
ah(7) = gca;
title('cos_k * x[n]'); grid;

subplot(4,3,8);
p(8) = plot(n,sin_cor,'g-');
ah(8) = gca;
title('-sin_k * x[n]');

subplot(4,3,9);hold on;
p(9) = bar(n,abs_s);
stem(k,abs_sk(k+1),'m.')
ah(9) = gca;
title('abs(X_k)');

subplot(4,3,10);
p(10) = stem(n,cos_sum,'r-');
ah(10) = gca;
title('sum(cos_k * x[n]) = Re(X_k)');

subplot(4,3,11);
p(11) = stem(n,sin_sum,'g-');
ah(11) = gca;
title('sum(-sin_k * x[n]) = Im(X_k)');

subplot(4,3,12);hold on;
p(12) = bar(n,arg_s);
stem(k,arg_sk(k+1),'m.')
ah(12) = gca;
title('arg(X_k)');

% format axis
set(ah,'XLim',[0 N-1]);
set(ah,'Xgrid','on');
set(ah,'Ygrid','on');
for i=[1:12]
    max_v = max(get(p(i),'YData'));
    min_v = min(get(p(i),'YData'));
    set(ah(i),'YLim',[min_v-0.1*abs(min_v)  max_v+0.1*abs(max_v)+0.001]);
end
