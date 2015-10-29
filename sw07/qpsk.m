clc;
clear;
close all;

N = 4096;

g = 1;
x = ifft([0 g+0*j zeros(1,N-2)], 'symmetric');
y = ifft([0 0+g*j zeros(1,N-2)], 'symmetric');
z = ifft([0 g+g*j zeros(1,N-2)], 'symmetric');
figure(1);
plot([0:N-1], x, 'r-'); hold on;
plot([0:N-1], y, 'g-'); hold on;
plot([0:N-1], z, 'b-'); hold on;
grid on;
xlabel('n')
ylabel('x[n], y[n], z[n]');
legend('x[n]', 'y[n]', 'z[n]');
axis([0 N -1e-3 1e-3]);

sig00 = ifft([0 -g-g*j zeros(1,N-2)], 'symmetric');
sig01 = ifft([0 +g-g*j zeros(1,N-2)], 'symmetric');
sig10 = ifft([0 -g+g*j zeros(1,N-2)], 'symmetric');
sig11 = ifft([0 +g+g*j zeros(1,N-2)], 'symmetric');

signal = [sig00 sig11 sig00 sig11];
figure(2);
plot([0:length(signal)-1], signal, 'b-'); hold on;
grid on;
xlabel('n')
ylabel('signal');
axis([0 length(signal) -1e-3 1e-3]);

