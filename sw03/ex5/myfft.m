function x = myfft(x)

N = 2^ceil(log2(length(x)))

W = exp(-1j*2*pi*[0:N/2-1]/N);

x = bitrevorder(x);

for i = [1 3 5 7]
    [x(i) x(i + 1)] = butfly(x(i), x(i + 1), W(1));
end

for i = [1 2 5 6]
    [x(i) x(i + 2)] = butfly(x(i), x(i + 2), W(2*(1-mod(i,2))+1));
end

for i = [1 2 3 4]
    [x(i) x(i + 4)] = butfly(x(i), x(i + 4), W(i));
end

