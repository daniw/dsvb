function x = myfft(x)

N = 2^ceil(log2(length(x)));

W = exp(-1j*2*pi*[0:N/2-1]/N);

x = bitrevorder(x);

for S = 1 : log2(N) 
    B = N / 2 ^ S;
    D = 2 ^ (S - 1);
    for b = 1 : B
        for d = 1 : D
            i1 = (b - 1) * 2 ^ S + d;
            i2 = i1 + D;
            iw = mod((d - 1) * B, N/2) + 1;
            [x(i1) x(i2)] = butfly(x(i1), x(i2), W(iw));
        end
    end
end

